# Created with python 3.11.4

# This script applies basic formatting and cleanups to the various CPP files.
# Requires installation of Uncrustify version 0.81.0_f on PATH
# Just run it.

import glob
import subprocess
import os


def apply_formatting(line: str, blockCommentBeginIndex: int) -> str:
    # Strip useless comments behind scope end
    scopeEndIndex = line.find('}')
    if scopeEndIndex >= 0:
        if scopeEndIndex == 0 or line[:scopeEndIndex].isspace():
            afterScopeIndex = scopeEndIndex + 1
            while afterScopeIndex < len(line) and line[afterScopeIndex] == ';':
                afterScopeIndex += 1
            commentBeginIndex = line.find("//")
            namespaceCommentBeginIndex = line.find("// namespace")
            if commentBeginIndex >= 0 and namespaceCommentBeginIndex < 0:
                if afterScopeIndex == commentBeginIndex or line[afterScopeIndex:commentBeginIndex].isspace():
                    line = line[:commentBeginIndex]

    #if blockCommentBeginIndex >= 0:
    #    lineLen = min(blockCommentBeginIndex, len(line))
    #else:
    #    lineLen = len(line)
    #lineNoLeadingSpace = line.lstrip()
    #if len(lineNoLeadingSpace) >= 2 and (lineNoLeadingSpace[:2] == "/*" or lineNoLeadingSpace[:2] == "//"):
    #    pass
    #else:
    #    line = line[:lineLen].lstrip() + line[lineLen:]

    # Remove trailing whitespace
    line = line.rstrip()
    line += "\n"

    return line


def main():
    current_dir = os.path.dirname(os.path.abspath(__file__))
    root_dir = os.path.join(current_dir, "..", "..")
    root_dir = os.path.normpath(root_dir)
    core_dir = os.path.join(root_dir, "Core")
    generals_dir = os.path.join(root_dir, "Generals")
    generalsmd_dir = os.path.join(root_dir, "GeneralsMD")
    utility_dir = os.path.join(root_dir, "Dependencies", "Utility")
    uncrustify_file = os.path.join(current_dir, "uncrustify.cfg")
    fileNames = []

    for ext in ["*.cpp", "*.h", "*.inl"]:
    #for ext in ["*.h", "*.inl"]:
        fileNames.extend(glob.glob(os.path.join(core_dir, '**', ext), recursive=True))
        fileNames.extend(glob.glob(os.path.join(generals_dir, '**', ext), recursive=True))
        fileNames.extend(glob.glob(os.path.join(generalsmd_dir, '**', ext), recursive=True))
        fileNames.extend(glob.glob(os.path.join(utility_dir, '**', ext), recursive=True))

    for fileName in fileNames:
        print(f"Process file {fileName}")
        # Read
        with open(fileName, 'r', encoding="cp1252") as file:
            try:
                lines = file.readlines()
            except UnicodeDecodeError:
                continue # Not good.

        # Process
        inBlockComment = False
        for index, line in enumerate(lines):
            # naive block comment recognition
            if inBlockComment:
                blockCommentBeginIndex = 0  # comment started earlier, applies to whole line
            else:
                blockCommentBeginIndex = line.find('/*')

            if inBlockComment:
                endIndex = line.find('*/')
                if endIndex >= 0:
                    inBlockComment = False
            elif blockCommentBeginIndex >= 0:
                endIndex = line.find('*/', blockCommentBeginIndex)
                if endIndex < 0:
                    inBlockComment = True

            lines[index] = apply_formatting(line, blockCommentBeginIndex)

        # Write
        with open(fileName, 'w', encoding="cp1252") as file:
            file.writelines(lines)

    i = 0

    for fileName in fileNames:
        args = ["uncrustify", "-c", uncrustify_file, "--replace", "--no-backup", fileName]
        subprocess.run(args=args, check=True)
        i+=1
        #if i==16:
        #    break

    return




if __name__ == "__main__":
    main()
