#!/usr/bin/env python
import sys

if sys.version_info[0] != 3:
    print("This script requires Python version 3.x")
    sys.exit(1)

import os
import shutil
import argparse
import common

def main():
    # Parse arguments
    parser = argparse.ArgumentParser()
    parser.add_argument("--standardese-path", dest="standardesePath", action="store", help="The path to the standardese binary", required=True)
    args = parser.parse_args()
    
    # Generate docs using CMake and Standardese
    buildDir = os.path.join(common.getRoot(), "_Temp", "Docs", "Engine")
    common.mkdir(buildDir)
    common.callBlockingWithOutput(["cmake", "-DGenerateDocs=ON", "-B" + buildDir, "-H" + common.getRoot(), "-DSTANDARDESE_TOOL=" + args.standardesePath])
    common.callBlockingWithOutput(["cmake", "--build", buildDir, "--target", "standardese_docs_engine"])
    
    # Copy generated docs to Docs
    generatedDir = os.path.join(buildDir, "standardese_docs_engine")
    copyDir = os.path.join(common.getRoot(), "Docs", "Engine")
    common.mkdir(copyDir)
    docFiles = common.getFiles(generatedDir, ".md")
    print("Generated Files")
    for file in docFiles:
        print("\t" + file)
        shutil.copy2(file, copyDir)
    
    print("Done!")
    
if __name__ == "__main__":
    main()