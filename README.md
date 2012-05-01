
p2iOS - @VERSION@
=========================
a Processing.org to iOS converter, with openFrameworks inside (dun DUN dun DUN!)
based on processing.js originally by John Resig.

About p2iOS
--------
* License:           MIT (see included LICENSE file for full license)
* Github Repo:       http://github.com/gimlids/processing-js

Usage
-----

Get the code:

    git clone git://github.com/gimlids/processing-js.git
    git checkout develop-processingcc

Install Mozilla SpiderMonkey JSShell for command-line JavaScript using brew OS X package manager:

    brew install spidermonkey

Convert a Processing .pde file to an Objective-C++ file suitable for use with the p2iOS runtime:

    ./p2iOS.sh my_sketch.pde > my_sketch.mm

Finally (not yet implemented), add my_sketch.mm, p2iOS.h, and openFrameworks to your Xcode iOS project.
