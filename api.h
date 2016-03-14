typedef void *(*processingFunc)(void *);

enum DataTypes {
    DOUBLE_PRIMITIVE,
    UNSIGNED_PRIMITIVE,
    DOUBLE_ARRAY,
    UNSIGNED_ARRAY
};

static const char * EnumStrings[] = {
    "double",
    "unsigned",
    "double []",
    "unsigned []"
};

const char *enumAsText(DataTypes val) {
    return EnumStrings[val];
}

class Plugin {
    
public:
    Plugin(const char * const name, const char * const description, DataTypes accepts, DataTypes returns)
    : m_accepts(accepts),
      m_returns(returns),
      m_name(name),
      m_description(description)
     {};
     
    DataTypes accepts(void) { return m_accepts; };
    DataTypes returns(void) { return m_returns; };
    virtual void *method(void *) = 0;
    const char * const name(void) { return m_name; };
    const char * const description(void) { return m_description; };
    
private:
    DataTypes m_accepts, m_returns;
    const char * const m_name;
    const char * const m_description;
};

typedef Plugin*(*initMethod)(void);
