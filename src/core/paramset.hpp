#ifndef PARAMSET_HPP
#define PARAMSET_HPP

#include <memory>
#include <typeinfo>
#include <unordered_map>
#include <iostream>

#include "common.hpp"

using std::bad_cast;
using std::shared_ptr;
using std::make_shared;
using std::unordered_map;

// Generic class to be inherited by the other class below
// Like the Animal class that both Dog and Cat are born from
class Object {
	Object() = default;
	virtual ~Object() = default;
};

template<typename T>
class Value : public Object {
public:
	T m_value;

	Value(const T& v) {
		m_value = v;
	}

	~Value() = default;
};

class ParamSet {
private:
	unordered_map<string, shared_ptr<Object>> m_render_opts;

public:
	ParamSet() = default;
	~ParamSet() = default;
	
	//Converts from the generic type to a more specific one
	//Like from Animal to Dog
	template<typename T>
	T retrieve(const string& key, const T& def) {
		const auto search = m_render_opts.find(key);

		if(search == m_render_opts.end()) {
			return def;
		}

	  	try {
			auto test = dynamic_cast<Value<T>>(search->second);
		} catch (const bad_cast& e) {
			std::cout << "Cast failed: [" << e.what() << "]" << std::endl;
		}

		return dynamic_cast<Value<T>>(search->second).m_value;
	}

	template<typename T>
	void assign(const string key, const T& value) {
		m_render_opts[key] = make_shared<Value<T>>(value);
	}
};


#endif //PARAMSET_HPP
