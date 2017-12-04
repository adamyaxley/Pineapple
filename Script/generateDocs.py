import os
import shutil
import argparse
import common

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--standardese-path", dest="standardesePath", action="store", help="The path to the standardese binary", required=True)
    args = parser.parse_args()
    
    buildDir = os.path.join(common.getRoot(), "_Temp", "Docs", "Engine")
    common.mkdir(buildDir)
    common.callBlockingWithOutput(["cmake", "-DGenerateDocs=ON", "-B" + buildDir, "-H" + common.getRoot(), "-DSTANDARDESE_TOOL=" + args.standardesePath])
    common.callBlockingWithOutput(["cmake", "--build", buildDir, "--target", "standardese_docs_engine"])
    
    # Copy generated docs to Docs
    generatedDir = os.path.join(buildDir, "standardese_docs_engine")
    copyDir = os.path.join(common.getRoot(), "Docs", "Engine")
    print("Copying generated docs from {} to {}".format(generatedDir, copyDir))
    common.mkdir(copyDir)
    docFiles = common.getFiles(generatedDir, ".md")
    print(docFiles)
    for file in docFiles:
        print("Copying {} to {}".format(file, copyDir))
        shutil.copy2(file, copyDir)
    
    print("Done!")
    
if __name__ == "__main__":
    main()