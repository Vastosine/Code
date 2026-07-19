#include <iostream>
#include <istream>
#include <map>
#include <ostream>
#include <stack>
#include <string>
#include <vector>
#include <sstream>

using std::cerr;
using std::endl;
using std::istream;
using std::ostream;
using std::string;
using std::vector;
using std::stack;

class Json {
public:
    typedef unsigned long long size_type;
	enum Type {
		_Int,
		_Float,
		_String,
		_Bool,
		_Array,
		_Map
	};
	virtual void print() const = 0;
	virtual bool setValue(const string &) = 0;
	bool setValue(const char *str) {
        return setValue(string(str));
    };

	Type getType() const {
		return type;
	}

	Json() {
		setTab(2);
	}

	void setTab(int count) {
		Tab = string(count, ' ');
		tabSize = count;
	}

    static vector<size_type> getMap(const string &s) {
        size_type n = s.size();
        vector<size_type> result(n, -1);
        stack<size_type> st;
        for (size_type i = 0; i < n; i++) {
            if (s[i] == '{' || s[i] == '[') {
                st.push(i);
            }
            if (s[i] == '}' || s[i] == ']') {
                if (st.empty()) {
                    cerr << "Invalid map format" << endl;
                    return result;
                }
                size_type start = st.top();
                st.pop();
                if (s[i] == '}') {
                    result[start] = i;
                } else {
                    result[start] = i - 1;
                }
            }
        }
        return result;
    }

    friend Type getType(const string &str, size_type pos = 0) {
        size_type start = str.find_first_not_of(" \'\"\t\n\r", pos);
        if (str[start] == string::npos) {
            throw std::invalid_argument("Invalid integer format");
        }
        if (str[start] == '{') return _Map;
        if (str[start] == '[') return _Array;
        if (str[start] == '\"' || str[start] == '\'') return _String;
        size_type end = str.find_first_not_of("+-0123456789", start);
        if (str[end] == '.') return _Float;
        if (start == end) throw std::invalid_argument("Invalid integer format");
        return _Int;
    }

protected:
	Type type;
	string Tab;
	int tabSize;
};

class Int : public Json {
public:
    Int() : value("0") {
        type = Type::_Int;
    }

    Int(const string &value) {
        setValue(value);
    }

    Int(const char *value) {
        setValue(value);
    }

    template<typename T>
	Int(T value) : value(std::to_string(value)) {
		type = Type::_Int;
	}

    virtual bool setValue(const string &str) {
        size_type begin = str.find_first_of("+-0123456789");
        if (begin == string::npos) {
            cerr << "Invalid integer format" << endl;
            throw std::invalid_argument("Invalid integer format");
            return false;
        }
        size_type end = str.find_first_not_of("+-0123456789", begin);
        if (end == string::npos) {
            end = str.size();
        }
        this->value = str.substr(begin, end - begin);
        std::istringstream(this->value) >> intValue;
        return true;
    }

	virtual void print() const {
		cerr << value << endl;
	}

private:
	string value;
    size_type intValue;
};

class Float : public Json {
public:
    template<typename T>
	Float(T value = 0.0) : value(value) {
		type = Type::_Float;
	}

    Float(const char *value) {
        setValue(value);
    }

    Float(const string &str) {
        setValue(str);
    }

    virtual bool setValue(const string &str) {
        size_type begin = str.find_first_of("+-0123456789.");
        if (begin == string::npos) {
            cerr << "Invalid double format" << endl;
            throw std::invalid_argument("Invalid double format");
            return false;
        }
        size_type end = str.find_first_not_of("+-0123456789", begin);
        if (end == string::npos) {
            end = str.size();
        }
        this->value = std::stod(str.substr(begin, end - begin));
        return true;
    }

	virtual void print() const {
		cerr << value << endl;
	}

private:
	double value;
};

class String : public Json {
public:
	String(const string &value = "") : value(value) {
		type = Type::_String;
	}

	String(const char *value) : value(value) {
		type = Type::_String;
	}

    virtual bool setValue(const string &str) {
        value = str;
        return true;
    }

	virtual void print() const {
		cerr << value << endl;
	}

private:
	string value;
};

class Bool : public Json {
public:
	Bool(bool value = false) : value(value) {
		type = Type::_Bool;
	}

    Bool(const char *value) {
        setValue(value);
    }

    Bool(const string &value) {
        setValue(value);
    }

    virtual bool setValue(const string &str) {
        if (str.substr(0, 4) != "true" && str.substr(0, 5) != "false") {
            cerr << "Invalid boolean format" << endl;
            throw std::invalid_argument("Invalid boolean format");
            return false;
        }
        value = str.substr(0, 4) == "true";
        return true;
    }

	virtual void print() const {
		cerr << (value ? "true" : "false") << endl;
	}

private:
	bool value;
};

class Array : public Json {
public:
	Array(const vector<Json *> &elements = {}) : elements(elements) {
		type = Type::_Array;
	}

    Array(const string &value) {

    }

    virtual bool setValue(const string &str) {
        vector<size_type> map = getMap(str);
        return setValue(str, map);
    }

    bool setValue(const string &str, const vector<size_type> &map) {
        size_type pos = 1, start = 0;
        elements.clear();

        while (true) {

            size_type start = str.find_first_of(",{[\"\'");
        }
        return true;
    }

	virtual void print() const {
		cerr << "[" << endl;
		for (const auto &element : elements) {
			element->print();
		}
		cerr << "]" << endl;
	}

private:
	vector<Json *> elements;
};

class Map : public Json {
	using _map = std::map<string, Json *>;

public:
	Map(const _map &values = {}) : values(values) {
		type = Type::_Map;
	}

	virtual void print() const {
		cerr << "{";
		for (const auto &pair : values) {
			cerr << Tab << pair.first << ": ";
			pair.second->print();
		}
		cerr << "}";
	}

    Json *&operator[](const string &key) {
        return values[key];
    }

private:
	_map values;
};

// Json *Json::read(const string &str, int &pos = *new int(0)) {
//     if (str.empty()) {
//         return nullptr;
//     }

//     if (str[0] == '{') {
//         Map *map = new Map();
//         string::size_type pos = 1;
//         while (pos < str.size()) {
//             string::size_type end = str.find(':', pos);
//             if (end == string::npos) {
//                 cerr << "Invalid map format" << endl;
//                 return nullptr;
//             }
//             string key = str.substr(pos, end - pos);
//             pos = end + 1;
//             while (pos < str.size() && (str[pos] == '|' || str[pos] == ' ')) {
//                 pos++;
//             }
//             if (pos == str.size()) {
//                 cerr << "Invalid map format" << endl;
//                 return nullptr;
//             }
//             Json *value = read(str.substr(pos));
//             if (value == nullptr) {
//                 // cerr << "Invalid map format" << endl;
//                 return nullptr;
//             }
//             (*map)[key] = value;
//             pos = str.find(',', pos);
//             if (pos == string::npos) {
//                 break;
//             }
//             pos++;
//         }
//         return map;
//     }
//     return this;
// }

int main() {
    Float a("qwd15.50");
    a.print();
}