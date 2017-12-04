import os
import common

def main():
    buildDir = os.path.join(common.getRoot(), "_Temp", "Docs", "Engine")
    common.mkdir(buildDir)
    common.callBlockingWithOutput(["cmake", "-DGenerateDocs=ON", "-B" + buildDir, "-H" + common.getRoot()])
    common.callBlockingWithOutput(["cmake", "--build", buildDir, "--target", "standardese_docs_engine"])
    
if __name__ == "__main__":
    main()