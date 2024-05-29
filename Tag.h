#include <string>
using namespace std;
class Tag
{
private:
    string title;

public:
    Tag(string ti) : title(ti) {}
    static Tag *create(string ti)
    {
        return new Tag(ti);
    }
};