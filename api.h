typedef double (*processingFunc)(double);

struct s_processingMethod
{
	const char * const name;
	const char * const description;
	processingFunc function;
    const char * const options;
};

typedef struct s_processingMethod processingMethod;

typedef processingMethod(*initMethod)(void);
