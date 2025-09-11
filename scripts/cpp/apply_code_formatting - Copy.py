# Created with python 3.11.4

# This script applies basic formatting and cleanups to the various CPP files.
# Just run it.

import glob
import os


class IndexPair:
    beginIndex = 0
    endIndex = 0
    def is_contained(self, index: int) -> bool:
        return index >= self.beginIndex and index < self.endIndex


def build_quote_pairs(line: str) -> list[IndexPair]:
    l = list[IndexPair]()
    index = -1
    while True:
        index = line.find('"', index+1)
        if index < 0:
            break
        if index > 0 and line[-1] == '\\':
            continue
        if len(l) == 0 or l[-1].endIndex != 0:
            pair = IndexPair()
            pair.beginIndex = index
            l.append(pair)
        else:
            l[-1].endIndex = index + 1
    return l


def is_contained(l: list[IndexPair], index: int) -> bool:
    for e in l:
        if e.is_contained(index):
            return True
    return False


def apply_formatting(line: str, inBlockComment: bool) -> str:
    commentBeginIndex = line.find("//")
    quotePairs = build_quote_pairs(line)

    # Strip useless comments behind scope end
    scopeEndIndex = line.find('}')
    if scopeEndIndex >= 0:
        if scopeEndIndex == 0 or line[:scopeEndIndex].isspace():
            afterScopeIndex = scopeEndIndex + 1
            while line[afterScopeIndex] == ';':
                afterScopeIndex += 1
            namespaceCommentBeginIndex = line.find("// namespace")
            if commentBeginIndex >= 0 and namespaceCommentBeginIndex < 0:
                if afterScopeIndex == commentBeginIndex or line[afterScopeIndex:commentBeginIndex].isspace():
                    line = line[:commentBeginIndex]

    if not inBlockComment:
        # Add spaces around assignments operators
        searchChars = ['=', '|=', '&=', '+=', '-=', '*=', '/=', '%=', '^=', '<<=', '>>=']
        for searchChar in searchChars:
            searchCharLen = len(searchChar)
            searchIndex = -1
            while True:
                searchIndex = line.find(searchChar, searchIndex+1)
                if searchIndex < 0:
                    break # Nothing else found
                if commentBeginIndex >= 0 and searchIndex > commentBeginIndex:
                    break # Found in inline comment
                if is_contained(quotePairs, searchIndex):
                    continue # Found in quote string
                operatorKeywordIndex = line.find("operator")
                if operatorKeywordIndex >= 0 and operatorKeywordIndex < searchIndex:
                    continue # Naive skip operator function
                if searchChar == '=' and searchIndex < len(line)-searchCharLen and (
                    line[searchIndex+1] == '='):
                    continue # Skip '=='
                if searchChar == '=' and searchIndex > 0 and (
                    line[searchIndex-1] == '=' or
                    line[searchIndex-1] == '|' or
                    line[searchIndex-1] == '&' or
                    line[searchIndex-1] == '+' or
                    line[searchIndex-1] == '-' or
                    line[searchIndex-1] == '/' or
                    line[searchIndex-1] == '*' or
                    line[searchIndex-1] == '%' or
                    line[searchIndex-1] == '!' or
                    line[searchIndex-1] == '<' or
                    line[searchIndex-1] == '>'):
                    continue # Skip the '==', '|=', '&=', ...
                if searchIndex > 0 and not line[searchIndex-1].isspace():
                    line = line[:searchIndex] + ' ' + line[searchIndex:] # Add leading space
                    searchIndex += 1
                if searchIndex < len(line)-searchCharLen and not line[searchIndex+searchCharLen].isspace():
                    line = line[:searchIndex+searchCharLen] + ' ' + line[searchIndex+searchCharLen:] # Add trailing space

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
    fileNames = []
    fileNames.extend(glob.glob(os.path.join(core_dir, '**', '*.h'), recursive=True))
    fileNames.extend(glob.glob(os.path.join(core_dir, '**', '*.cpp'), recursive=True))
    fileNames.extend(glob.glob(os.path.join(core_dir, '**', '*.inl'), recursive=True))
    fileNames.extend(glob.glob(os.path.join(generals_dir, '**', '*.h'), recursive=True))
    fileNames.extend(glob.glob(os.path.join(generals_dir, '**', '*.cpp'), recursive=True))
    fileNames.extend(glob.glob(os.path.join(generals_dir, '**', '*.inl'), recursive=True))
    fileNames.extend(glob.glob(os.path.join(generalsmd_dir, '**', '*.h'), recursive=True))
    fileNames.extend(glob.glob(os.path.join(generalsmd_dir, '**', '*.cpp'), recursive=True))
    fileNames.extend(glob.glob(os.path.join(generalsmd_dir, '**', '*.inl'), recursive=True))

    for fileName in fileNames:
        with open(fileName, 'r', encoding="cp1252") as file:
            try:
                lines = file.readlines()
            except UnicodeDecodeError:
                continue # Not good.

        #inBlockComment = False
        #for line in lines:
        #    # naive block comment recognition
        #    blockCommentBeginIndex = line.find('/*')
        #    blockCommentEndIndex = line.find('*/', blockCommentBeginIndex)
        #    inBlockCommentTmp = inBlockComment
        #    if blockCommentBeginIndex >= 0:
        #        inBlockCommentTmp = True
        #        inBlockComment = True
        #    if blockCommentEndIndex >= 0:
        #        inBlockComment = False
        #    # do the formatting
        #    line = apply_formatting(line, inBlockCommentTmp)
#
        #continue

        with open(fileName, 'w', encoding="cp1252") as file:
            inBlockComment = False
            for line in lines:
                # naive block comment recognition
                blockCommentBeginIndex = line.find('/*')
                blockCommentEndIndex = line.find('*/', blockCommentBeginIndex)
                inBlockCommentTmp = inBlockComment
                if blockCommentBeginIndex >= 0:
                    inBlockCommentTmp = True
                    inBlockComment = True
                if blockCommentEndIndex >= 0:
                    inBlockComment = False
                # do the formatting
                line = apply_formatting(line, inBlockCommentTmp)
                file.write(line)
            if lines:
                lastLine = lines[-1]
                if lastLine and lastLine[-1] != '\n':
                    file.write("\n") # write new line to end of file

    return


if __name__ == "__main__":
    main()
