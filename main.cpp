#include <stdio.h>
#include <stdlib.h>
#include <vector>

#ifdef WIN32
    #include <io.h>             // _find{first,next}
    #include <Windows.h> 		// HMODULE
#else
    #include <dlfcn.h>
    #include <dirent.h>         // {open,read}dir
    #include <string.h>         // strlen()
#endif

#include "api.h"

std::vector<processingMethod> availableMethods;

int loadLibrary(const char * const libraryName)
{
#ifdef WIN32
	HMODULE pipeline_library = LoadLibrary(libraryName);
#else
    void * pipeline_library = dlopen(libraryName, RTLD_LAZY);
#endif

	if (pipeline_library == NULL) {
		// report error ...
		return -1;
	} else {
		// Now call the defined entry point to get the spec
#ifdef WIN32
		FARPROC _init = GetProcAddress(pipeline_library, "pipeline_init");
#else
        void *_init = dlsym(pipeline_library, "pipeline_init");
#endif

		if (_init)
		{
			initMethod init = (initMethod)_init;

			availableMethods.push_back(init());
		}
		else
		{
			fprintf(stderr, "Couldn't get something (%p)\n", _init);
		}

		return 0;
	}
}

#ifdef WIN32

void loadProcessingFunctions()
{
	intptr_t file;
	_finddata_t filedata;

	file = _findfirst("libs\\*.dll", &filedata);
	if (file != -1)
	{
		do
		{
			printf("Found '%s'\n", filedata.name);

			char filepath[256];
			sprintf_s(filepath, 255, "libs\\%s", filedata.name);

			if (-1 == loadLibrary(filepath))
			{
				fprintf(stdout, "Couldn't load '%s'\n", filedata.name);
			}
			else
			{
				// Success
			}

		} while (_findnext(file, &filedata) == 0);
	}
}

#else

void loadProcessingFunctions()
{
    DIR *dir;
    struct dirent *ent;

    if ((dir = opendir("libs")) != NULL)
    {
        while((ent = readdir(dir)) != NULL)
        {
            if (ent->d_type == DT_REG)
            {
                size_t extlen = strlen(LIBRARY_EXTENSION);

                if (strlen(ent->d_name) > extlen)
                {
                    char *extStart = ent->d_name + strlen(ent->d_name) - extlen;

                    if (0 == strncmp(extStart, LIBRARY_EXTENSION, extlen))
                    {
                        char filepath[256];
                        snprintf(filepath, 255, "libs/%s", ent->d_name);

                        if (-1 == loadLibrary(filepath))
                        {
                            fprintf(stdout, "Couldn't load '%s'\n", ent->d_name);
                        }
                        else
                        {
                            // Success
                        }
                    }
                    else
                    {
                        printf("Ignoring '%s'\n", ent->d_name);
                    }
                }
            }
        }

        closedir(dir);
    }
}

#endif

void describeProcessingFunction(void)
{
	for (auto thing :  availableMethods)
	{
		printf("%s : %s", thing.name, thing.description);
        if (thing.options)
        {
            printf(" (%s)", thing.options);
        }
        printf("\n");
	}
}

int main(int argc, char *argv[])
{
	std::vector<processingFunc> pipeline;

	loadProcessingFunctions();

	describeProcessingFunction();

	if (argc == 2)
	{
		char *ch = argv[1];

		while (*ch)
		{
			for (auto thing :  availableMethods)
			{
				if (*ch == thing.name[0])
				{
					pipeline.push_back(thing.function);
				}
			}

			ch++;
		}
	}
	else
	{
		// Just do everything in the order we discovered it
		for (auto thing :  availableMethods)
		{
			pipeline.push_back(thing.function);
		}
	}

	double value = 100;
	for (auto thing : pipeline)
	{
		printf("%lf", value);
		value = thing(value);
		printf("-> %lf\n", value);
	}

	printf("Pipeline flushed, result : %lf\n", value);

	return 0;
}
