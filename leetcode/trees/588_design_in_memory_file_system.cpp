/*
 * 588. Design In-Memory File System (Hard)
 *
 * https://leetcode.com/problems/design-in-memory-file-system/
 *
 * Design a data structure that simulates an in-memory file system.
 *
 * Implement the FileSystem class:
 * - FileSystem() Initializes the object of the system.
 * - vector<string> ls(string path)
 *   - If path is a file path, returns a list that only contains this file's
 *     name.
 *   - If path is a directory path, returns the list of file and directory
 *     names in this directory.
 *   The answer should be in lexicographic order.
 * - void mkdir(string path) Makes a new directory according to the given
 *   path. The given directory path does not exist. If the middle directories
 *   in the path do not exist, you should create them as well.
 * - void addContentToFile(string filePath, string content)
 *   - If filePath does not exist, creates that file containing given content.
 *   - If filePath already exists, appends the given content to original
 *     content.
 * - string readContentFromFile(string filePath) Returns the content in the
 *   file at filePath.
 *
 * Example:
 * Input
 *   ["FileSystem", "ls", "mkdir", "addContentToFile", "ls", "readContentFromFile"]
 *   [[], ["/"], ["/a/b/c"], ["/a/b/c/d", "hello"], ["/"], ["/a/b/c/d"]]
 * Output
 *   [null, [], null, null, ["a"], "hello"]
 *
 * Explanation
 *   FileSystem fileSystem = new FileSystem();
 *   fileSystem.ls("/");                         // return []
 *   fileSystem.mkdir("/a/b/c");
 *   fileSystem.addContentToFile("/a/b/c/d", "hello");
 *   fileSystem.ls("/");                         // return ["a"]
 *   fileSystem.readContentFromFile("/a/b/c/d"); // return "hello"
 *
 * Constraints:
 * - 1 <= path.length, filePath.length <= 100
 * - path and filePath are absolute paths which begin with '/' and do not end
 *   with '/' except that the path is just "/".
 * - You can assume that all directory names and file names only contain
 *   lowercase letters, and the same names will not exist in the same
 *   directory.
 * - You can assume that all operations will be passed valid parameters, and
 *   users will not attempt to retrieve file content or list a directory or
 *   file that does not exist.
 * - You can assume that the parent directory for the file in addContentToFile
 *   will exist.
 * - 1 <= content.length <= 50
 * - At most 300 calls will be made to ls, mkdir, addContentToFile, and
 *   readContentFromFile.
 */

#include <cassert>
#include <string>
#include <vector>

using namespace std;

class FileSystem {
public:
    FileSystem() {
        // TODO: implement
    }

    vector<string> ls(string path) {
        // TODO: implement
        throw "not implemented";
    }

    void mkdir(string path) {
        // TODO: implement
        throw "not implemented";
    }

    void addContentToFile(string filePath, string content) {
        // TODO: implement
        throw "not implemented";
    }

    string readContentFromFile(string filePath) {
        // TODO: implement
        throw "not implemented";
    }
};

int main() {
    // Example from the problem statement.
    {
        FileSystem fs;
        assert(fs.ls("/").empty());
        fs.mkdir("/a/b/c");
        fs.addContentToFile("/a/b/c/d", "hello");
        assert(fs.ls("/") == vector<string>({"a"}));
        assert(fs.readContentFromFile("/a/b/c/d") == "hello");
    }

    // Listing a file path returns only that file's name.
    {
        FileSystem fs;
        fs.mkdir("/a/b/c");
        fs.addContentToFile("/a/b/c/d", "hello");
        assert(fs.ls("/a/b/c/d") == vector<string>({"d"}));
        assert(fs.ls("/a/b/c") == vector<string>({"d"}));
    }

    // mkdir creates every missing intermediate directory.
    {
        FileSystem fs;
        fs.mkdir("/x/y/z");
        assert(fs.ls("/") == vector<string>({"x"}));
        assert(fs.ls("/x") == vector<string>({"y"}));
        assert(fs.ls("/x/y") == vector<string>({"z"}));
        assert(fs.ls("/x/y/z").empty());
    }

    // mkdir reuses directories that already exist along the path.
    {
        FileSystem fs;
        fs.mkdir("/a/b");
        fs.mkdir("/a/c/d");
        assert(fs.ls("/a") == vector<string>({"b", "c"}));
        assert(fs.ls("/a/b").empty());
        assert(fs.ls("/a/c") == vector<string>({"d"}));
    }

    // Files can live directly in the root directory.
    {
        FileSystem fs;
        fs.addContentToFile("/notes", "abc");
        assert(fs.ls("/") == vector<string>({"notes"}));
        assert(fs.ls("/notes") == vector<string>({"notes"}));
        assert(fs.readContentFromFile("/notes") == "abc");
    }

    // Adding to an existing file appends instead of overwriting.
    {
        FileSystem fs;
        fs.addContentToFile("/f", "ab");
        fs.addContentToFile("/f", "cd");
        assert(fs.readContentFromFile("/f") == "abcd");
        fs.addContentToFile("/f", "e");
        assert(fs.readContentFromFile("/f") == "abcde");
        assert(fs.ls("/") == vector<string>({"f"}));
    }

    // Files and directories are listed together in lexicographic order.
    {
        FileSystem fs;
        fs.mkdir("/zoo");
        fs.addContentToFile("/apple", "x");
        fs.mkdir("/m");
        fs.addContentToFile("/banana", "y");
        assert(fs.ls("/") == vector<string>({"apple", "banana", "m", "zoo"}));
    }

    // Lexicographic order places a prefix before its extensions.
    {
        FileSystem fs;
        fs.mkdir("/ba");
        fs.addContentToFile("/b", "1");
        fs.mkdir("/ab");
        fs.addContentToFile("/a", "2");
        fs.mkdir("/abc");
        assert(fs.ls("/") == vector<string>({"a", "ab", "abc", "b", "ba"}));
    }

    // The same name may appear in different directories.
    {
        FileSystem fs;
        fs.mkdir("/a");
        fs.addContentToFile("/a/a", "inner");
        fs.mkdir("/b/a");
        fs.addContentToFile("/b/a/a", "deep");
        assert(fs.ls("/a") == vector<string>({"a"}));
        assert(fs.ls("/a/a") == vector<string>({"a"}));
        assert(fs.ls("/b/a") == vector<string>({"a"}));
        assert(fs.readContentFromFile("/a/a") == "inner");
        assert(fs.readContentFromFile("/b/a/a") == "deep");
    }

    // Separate files keep separate contents.
    {
        FileSystem fs;
        fs.mkdir("/docs");
        fs.addContentToFile("/docs/one", "first");
        fs.addContentToFile("/docs/two", "second");
        fs.addContentToFile("/docs/one", "more");
        assert(fs.readContentFromFile("/docs/one") == "firstmore");
        assert(fs.readContentFromFile("/docs/two") == "second");
        assert(fs.ls("/docs") == vector<string>({"one", "two"}));
    }

    // Deepest file path allowed by the 100-character limit.
    {
        FileSystem fs;
        string directory;
        for (int i = 0; i < 49; i++) {
            directory += "/a";
        }

        string filePath = directory + "/b";
        assert(filePath.size() == 100);

        fs.mkdir(directory);
        fs.addContentToFile(filePath, "bottom");
        assert(fs.ls(directory) == vector<string>({"b"}));
        assert(fs.ls(filePath) == vector<string>({"b"}));
        assert(fs.readContentFromFile(filePath) == "bottom");
    }

    // 299 maximum-length appends followed by one read uses all 300 calls.
    {
        FileSystem fs;
        string expected;
        for (int i = 0; i < 299; i++) {
            string content(50, static_cast<char>('a' + i % 26));
            fs.addContentToFile("/log", content);
            expected += content;
        }

        assert(fs.readContentFromFile("/log") == expected);
    }

    return 0;
}
