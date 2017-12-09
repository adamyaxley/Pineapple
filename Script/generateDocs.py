#!/usr/bin/env python
import sys

if sys.version_info[0] != 3:
    print("This script requires Python version 3.x")
    sys.exit(1)

import os
import shutil
import argparse
import time
import common

def main():
    startTime = time.time()
    
    # Parse arguments
    parser = argparse.ArgumentParser()
    parser.add_argument("--standardese-path", dest="standardesePath", action="store", help="The path to the standardese binary", required=True)
    parser.add_argument("--quiet", dest="quiet", action="store_true", help="Don't show CMake or standardese output")
    args = parser.parse_args()
    
    # Generate docs using CMake and Standardese
    buildDir = os.path.join(common.getRoot(), "_Temp", "Docs", "Engine")
    common.mkdir(buildDir)
    common.callBlocking(not (args.quiet), ["cmake", 
                                       "-DGENERATE_DOCS=ON", 
                                       "-DGENERATE_TESTS=OFF", 
                                       "-DGENERATE_DEMOS=OFF", 
                                       "-DGENERATE_PLUGINS=OFF", 
                                       "-B" + buildDir, 
                                       "-H" + common.getRoot(), 
                                       "-DSTANDARDESE_TOOL=" + args.standardesePath])
    common.callBlocking(not (args.quiet), ["cmake", 
                                       "--build", buildDir, 
                                       "--target", "standardese_docs_engine"])
    
    # Copy generated docs to Docs
    generatedDir = os.path.join(buildDir, "standardese_docs_engine")
    copyDir = os.path.join(common.getRoot(), "Docs", "Engine")
    common.mkdir(copyDir)
    docFiles = common.getFiles(generatedDir, ".md")
    for file in docFiles:
        # Below functionality is for updating only a single file, but it doesn't quite work well yet because standardese can't link to other files in this mode
        #if os.stat(file).st_mtime > os.stat(os.path.join(copyDir, os.path.basename(file))).st_mtime:
        #    print("\t" + file)
        shutil.copy2(file, copyDir)
    
    print("Done! {} seconds".format(time.time() - startTime))
    
if __name__ == "__main__":
    main()