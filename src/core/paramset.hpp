#ifndef PARAMSET_HPP
#define PARAMSET_HPP

#include <memory>
#include <typeinfo>
#include <unordered_map>

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
	T retrieve(const string& key, const T& def);

	//Assing a value to a key without casting the type
	template<typename T>
	void assign(const string key, const T& value);

	template<typename T>
	bool contains(const string key);
};


#endif //PARAMSET_HPP
