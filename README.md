Plugin pipeline experiments
---------------------------

Just a playground for dynamic loading of libraries following a plugin pattern
and experiments in CMake.

Todo:

 * Output binaries into preferred locations (all libs in ./libs off the root)
 * Proper finding of system libraries
 * Cleaner/less repetitive #ifdef WIN32 stuff

On Windows, build as:

	:: If you need the env vars setting up
    "c:\Program Files (x86)\Microsoft Visual Studio 12.0\Common7\Tools\vsvars32.bat"

    mkdir build
    cd build
    cmake ..

	::
	devenv Pipeline.sln /build Debug /project ALL_BUILD
	
Run as:

	Pipeline <steps>
	
Where steps is a list of initials of the steps to run (currently D, Q, S)
