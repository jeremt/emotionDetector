/**
 * Json
 *
 * Simple Json class to work with json almost
 * like in javascript.
 *
 * Jeremie Taboada <taboada.jeremie@gmail.com>
 */

#ifndef JSON_HPP_
# define JSON_HPP_

/**
 * Include some dependencies from STL.
 */
# include <iostream>
# include <stdexcept>
# include <typeinfo>
# include <vector>
# include <map>
# include <string>
# include <sstream>
# include <fstream>

/**
 * @class Json
 * This class represente a json object to parse/stringify
 * json like in javascript.
 */
class Json
{
private:

  /**
   * @enum TokenType
   * Used to know the type of the current token.
   */
  enum TokenType {
    kTokenUndefined,
    kTokenString,
    kTokenNumber,
    kTokenLeftBrace,
    kTokenRightBrace,
    kTokenLeftBracket,
    kTokenRightBracket,
    kTokenComma,
    kTokenColon,
    kTokenBoolean,
    kTokenNull
  };

  /**
   * @struct Token
   * Used to tokenize json string.
   */
  struct Token {
    std::string value;
    TokenType type;
    Token(std::string value="", TokenType type = kTokenUndefined)
    : value(value)
    , type(type)
    {}
  };

public:

  typedef std::vector<Json> Array;
  typedef std::vector<std::pair<std::string, Json> > Object;

  /**
   * @enum Type
   * Represente the type of the current Json node.
   */
  enum Type {
    STRING,
    OBJECT,
    ARRAY,
    BOOLEAN,
    NUMBER,
    EMPTY,
    UNDEFINED
  };

public:

  /**
   * Default constructor.
   */
  Json()
    : _value("")
    , _type(UNDEFINED)
  {}

  /**
   * Construct a new Json object according a type.
   */
  Json(Type t, std::string const &v)
    : _value(v)
    , _type(t)
  {}

  /**
   * Copy constructor.
   */
  Json(Json const &other)
    : _value(other._value)
    , _type(other._type)
    , _props(other._props)
    , _index(other._index)
    , _arr(other._arr)
  {}

  /**
   * Create json object from string value.
   */
  Json(std::string const &value)
    : _value(value)
    , _type(STRING)
  {}

  /**
   * Create json object from char * value.
   */
  Json(char const *value)
    : _value(value)
    , _type(STRING)
  {}

  /**
   * Create json object from double value.
   */
  Json(double value)
    : _value(_convert<double, std::string>(value))
    , _type(NUMBER)
  {}

  /**
   * Create json object from boolean value.
   */
  Json(bool value)
    : _value(value ? "true" : "false")
    , _type(BOOLEAN)
  {}

  /**
   * Assignement operator.
   */
  Json &operator=(Json const &other)
  {
    if (this != &other)
    {
      _value = other._value;
      _type = other._type;
      _props = other._props;
      _index = other._index;
      _arr = other._arr;
    }
    return *this;
  }

  /**
   * Assign the given number to this Json value.
   */
  Json &operator=(unsigned int value)
  {
    _value = _convert<unsigned int, std::string>(value);
    _type = NUMBER;
    return *this;
  }

  /**
   * Assign the given number to this Json value.
   */
  Json &operator=(double value)
  {
    _value = _convert<double, std::string>(value);
    _type = NUMBER;
    return *this;
  }

  /**
   * Assign the given number to this Json value.
   */
  Json &operator=(int value)
  {
    _value = _convert<int, std::string>(value);
    _type = NUMBER;
    return *this;
  }

  /**
   * Assign the given boolean to this Json value.
   */
  Json &operator=(bool value)
  {
    _value = value ? "true" : "false";
    _type = BOOLEAN;
    return *this;
  }

  /**
   * Assign the given string to this Json value.
   */
  Json &operator=(std::string const &value)
  {
    _value = value;
    _type = STRING;
    return *this;
  }

  /**
   * Assign the given char * to this Json value.
   */
  Json &operator=(char const *value)
  {
    _value = value;
    _type = STRING;
    return *this;
  }

  /**
   * Clear all json object content like if was just created.
   */
  void clear()
  {
    _type = UNDEFINED;
    _value.clear();
    _props.clear();
    _index.clear();
    _arr.clear();
    _tokens.clear();
  }

  /**
   * Return a stringified Json object.
   */
  std::string str() const
  {
    return _str(1);
  }

  /**
   * Return the type of the json object.
   */
  Type type()
  {
    return _type;
  }

  /**
   * Add a property to a Json object.
   *
   * @param key the property key.
   * @param v the property value.
   */
  void push(std::string key, Json const &v)
  {
    if (_type == UNDEFINED)
      _type = OBJECT;
    else if (_type != OBJECT)
      throw std::runtime_error("the json node should be an array");
    _index[key] = _props.size();
    _props.push_back(make_pair(key, v));
  }

  /**
   * Add a value to a Json _array.
   *
   * @param v the value.
   */
  void push(Json const &v)
  {
    if (_type == UNDEFINED)
      _type = ARRAY;
    else if (_type != ARRAY)
      throw std::runtime_error("the json node should be an array");
    _arr.push_back(v);
  }

  /**
   * Return double value.
   */
  operator double() const
  {
    return _convert<std::string, double>(_value);
  }

  /**
   * Return an array value.
   */
  operator Array() const
  {
    return _arr;
  }

  /**
   * Return an object value.
   */
  operator Object() const
  {
    return _props;
  }

  /**
   * Return bool value.
   */
  bool is() const
  {
    return _value == "true";
  }

  /**
   * Return string value.
   */
  operator std::string() const
  {
    return _value;
  }

  /**
   * Return the number of elems into
   * the current json object.
   */
  size_t size() const
  {
    switch (_type)
      {
      case ARRAY:
        return _arr.size();
      case OBJECT:
        return _props.size();
      case STRING:
        return _value.size();
      case NUMBER:
        return 1;
      default:
        return 0;
      }
    return 0;
  }

  /**
   * Derefence Json array or object from the
   * given index.
   */
  Json &operator[](size_t i)
  {
    if (_type == UNDEFINED)
      _type = ARRAY;
    if (_type != ARRAY)
      throw std::range_error("cannot dereference this type of value");
    if (i >= _arr.size())
    {
      size_t n = _arr.size();
      while (n++ <= i) push(Json());
    }
    return _arr.at(i);
  }

  /**
   * Dereference Json object from the given key.
   */
  Json &operator[](std::string const &s)
  {
    if (_type == UNDEFINED)
      _type = OBJECT;
    if (_type != OBJECT)
      throw std::range_error("cannot dereference this type of value");
    if (_index.find(s) == _index.end())
      push(s, Json());
    return _props[_index[s]].second;
  }

  /**
   * Test the type of the Json value.
   */
  bool operator==(Type type)
  {
    return _type == type;
  }

  /**
   * Parse the given string to create a Json object.
   */
  void parse(const std::string& str)
  {
    if (str.size())
    {
      int k;
      _tokenize(str);
      *this = _parse(_tokens, 0, k);
    }
    else
      *this = Json();
  }

  /**
   * Load data from the given stream into the Json object.
   */
  void load(std::istream &is)
  {
    std::string str;
    std::string tmp;

    while (!is.eof())
      {
        std::getline(is, tmp);
        str += tmp;
      }
    parse(str);
  }

  /**
   * Simple stream operator to load json from stream.
   */
  void operator<<(std::istream &is) {
    load(is);
  }

  /**
   * Simple stream operator to serialize json into a string.
   */
  void operator>>(std::string &input) {
    input = str();
  }

  /**
   * Load data from the given file.
   */
  void load(std::string const &path)
  {
    std::ifstream f(path.c_str());

    if (!f.is_open())
      throw std::runtime_error("cannot open file `" + path + "`");
    load(f);
  }

private:

  // All after all is private stuffs, nothing interesting about
  // lib usage ;)

  /**
   * Simple helper to convert any variable to another.
   *
   * @param From Convert from the given value.
   * @param To Convert to the result value.
   */
  template<typename From, typename To>
  static To _convert(From const &val)
  {
    std::stringstream ss;
    To res;

    ss << val;
    ss >> res;
    return res;
  }

  /**
   * Add some spaces to the current line.
   */
  std::string _addSpaces(int d) const
  {
    std::string s = "";
    while (d--)
      s += "  ";
    return s;
  }

  /**
   * Stringify the json, indented by `d`.
   */
  std::string _str(int d) const
  {
    std::string s;

    switch (_type)
    {
      case STRING:
        return "\"" + _value + "\"";

      case NUMBER:
      case BOOLEAN:
        return _value;

      case EMPTY:
        return "null";

      case OBJECT:
        s = "{\n";
        for (size_t i = 0; i < _props.size(); ++i)
        {
          s += _addSpaces(d) + "\"" + _props[i].first + "\": ";
          s += _props[i].second._str(d + 1);
          s += i == _props.size() - 1 ? "" : ",";
          s += "\n";
        }
        s += _addSpaces(d-1) + "}";
        return s;

      case ARRAY:
        s = "[";
        for (size_t i = 0; i < _arr.size(); ++i)
        {
        if (i) s += ", ";
        s += _arr[i]._str(d + 1);
        }
        s += "]";
        return s;

      default: break;
    }
    return "undefined";
  }

  /**
   * Return if the given char is a whitespace or not.
   */
  bool _isSpace(char c) const
  {
    return std::string(" \n\r ").find(c) != std::string::npos;
  }

  /**
   * Return the index of the next space.
   */
  int _nextSpace(std::string const &data, int i) const
  {
    int size = data.size();

    while (i <  size)
      {
        if (data[i] == '"')
    {
      ++i;
      while (i < size && (data[i] != '"' || data[i-1] == '\\'))
        ++i;
    }
        if (data[i] == '\'')
    {
      ++i;
      while (i < size && (data[i] != '\'' || data[i-1] == '\\'))
        ++i;
    }
        if (_isSpace(data[i]))
    return i;
        ++i;
      }
    return size;
  }

  /**
   * Skip spaces to the next token.
   */
  int _skipSpaces(std::string const &data, int i) const
  {
    int size = data.size();

    while (i < size)
      {
        if (!_isSpace(data[i]))
    return i;
        ++i;
      }
    return -1;
  }

  void _check_string(size_t &k, std::string const &token)
  {
    size_t i = k + 1;
    while (i < token.size() && (token[i] != '"' || token[i - 1] == '\\'))
      ++i;
    _tokens.push_back(Token(token.substr(k+1, i-k-1), kTokenString));
    k = i + 1;
  }

  void _check_comma(size_t &k, std::string const &)
  {
    _tokens.push_back(Token(",", kTokenComma));
    ++k;
  }

  void _check_true(size_t &k, std::string const &token)
  {
    std::string tok;

    tok = k+3 < token.size() ? token.substr(k, 4) : "";
    if (tok != "true")
      throw std::runtime_error("unknown token \"" + tok + "\"");
    _tokens.push_back(Token("true", kTokenBoolean));
    k += 4;
  }

  void _check_false(size_t &k, std::string const &token)
  {
    std::string tok;

    tok = k+4 < token.size() ? token.substr(k, 5) : "";
    if (tok != "false")
      throw std::runtime_error("unknown token \"" + tok + "\"");
    _tokens.push_back(Token("false", kTokenBoolean));
    k += 5;
  }

  void _check_null(size_t &k, std::string const &token)
  {
    std::string tok;

    tok = k+3 < token.size() ? token.substr(k, 4) : "";
    if (tok != "null")
      throw std::runtime_error("unknown token \"" + tok + "\"");
    _tokens.push_back(Token("null", kTokenNull));
    k += 4;
  }

  void _check_undefined(size_t &k, std::string const &token)
  {
    std::string tok;

    tok = k+8 < token.size() ? token.substr(k, 9) : "";
    if (tok != "undefined")
      throw std::runtime_error("unknown token \"" + tok + "\"");
    _tokens.push_back(Token("undefined", kTokenUndefined));
    k += 9;
  }

  void _check_right_brace(size_t &k, std::string const &)
  {
    _tokens.push_back(Token("}", kTokenRightBrace));
    k++;
  }

  void _check_left_brace(size_t &k, std::string const &)
  {
    _tokens.push_back(Token("{", kTokenLeftBrace));
    k++;
  }

  void _check_right_bracket(size_t &k, std::string const &)
  {
    _tokens.push_back(Token("]", kTokenRightBracket));
    k++;
  }

  void _check_left_bracket(size_t &k, std::string const &)
  {
    _tokens.push_back(Token("[", kTokenLeftBracket));
    k++;
  }

  void _check_colon(size_t &k, std::string const &)
  {
    _tokens.push_back(Token(":", kTokenColon));
    k++;
  }

  bool _check_digit(size_t &k, std::string const &token)
  {
    if (token[k] == '-' || (token[k] <= '9' && token[k] >= '0'))
    {
      size_t i = k;
      if (token[i] == '-')
        ++i;
      while (i < token.size() &&
              ((token[i] <= '9' && token[i] >= '0') ||
                token[i] == '.' ||
                token[i] == 'e' ||
                token[i] == '+' ||
                token[i] == '-'))
      ++i;
      _tokens.push_back(Token(token.substr(k, i-k), kTokenNumber));
      k = i;
      return true;
    }
    return false;
  }

  /**
   * Tokenize the given string.
   */
  void _tokenize(std::string const &data)
  {
    std::string token;
    int next = 0;
    size_t size, k;
    int index;

    _tokens.clear();
    while ((index = _skipSpaces(data, next)) >= 0)
      {
        next = _nextSpace(data, index);
        token = data.substr(index, next-index);
        size = token.size();
        k = 0;
        while (k < size)
    {
      switch (token[k])
        {
        case '"': _check_string(k, token);        break;
        case ',': _check_comma(k, token);         break;
        case 't': _check_true(k, token);          break;
        case 'f': _check_false(k, token);         break;
        case 'n': _check_null(k, token);          break;
        case 'u': _check_undefined(k, token);     break;
        case '}': _check_right_brace(k, token);   break;
        case '{': _check_left_brace(k, token);    break;
        case ']': _check_right_bracket(k, token); break;
        case '[': _check_left_bracket(k, token);  break;
        case ':': _check_colon(k, token);         break;
        default:
          if (_check_digit(k, token) == false)
            throw std::runtime_error("unknown token \"" + token.substr(k) + "\"");
        }
    }
      }
  }

  /**
   * Parse the given token and get Json object.
   *
   * @todo Refactoring this ugly parsing and modify
   * the current instance.
   */
  Json _parse(std::vector<Token> v, int i, int& r) const
  {
    Json current;
    int j;
    int k;

    switch (v[i].type)
    {
      case kTokenLeftBrace:
        current._type = OBJECT;
        k = i + 1;
        while (v[k].type != kTokenRightBrace)
        {
          std::string key = v[k].value;
          k += 2;
          j = k;
          Json vv = _parse(v, k, j);
          current.push(key, vv);
          k = j;
          if (v[k].type == kTokenComma) k++;
        }
        r = k + 1;
        return current;

      case kTokenLeftBracket:
        current._type = ARRAY;
        k = i + 1;
        while (v[k].type != kTokenRightBracket)
        {
          j = k;
          Json vv = _parse(v, k, j);
          current.push(vv);
          k = j;
          if (v[k].type == kTokenComma) k++;
        }
        r = k + 1;
        return current;

      case kTokenNumber:
        current._type = NUMBER;
        current._value = v[i].value;
        r = i + 1;
        return current;

      case kTokenString:
        current._type = STRING;
        current._value = v[i].value;
        r = i + 1;
        return current;

      case kTokenBoolean:
        current._type = BOOLEAN;
        current._value = v[i].value;
        r = i + 1;
        return current;

      case kTokenNull:
        current._type = EMPTY;
        current._value = "null";
        r = i + 1;
        return current;

      case kTokenUndefined:
        current._type = UNDEFINED;
        current._value = "undefined";
        r = i + 1;
        return current;

      default:
        throw std::runtime_error("invalid json data");
    }
    return current;
  }

private:
  std::string _value;
  Type _type;
  Object _props;
  std::map<std::string, int> _index;
  Array _arr;
  std::vector<Token> _tokens;

};

#endif /* !JSON_HPP_ */
