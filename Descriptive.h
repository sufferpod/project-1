#include "question.h"

using namespace std;

class Descriptive : public Question
{
public:
    Descriptive(string qu, DateTime cr, User us) : Question(qu, "Descriptive", cr, us) {}
    void AddAnswer() { this->answer = answer; }
    void print() {}
    void printAll() {}
    static Descriptive *create(string question, DateTime createdAt, User user)
    {
        Descriptive x(question, createdAt, user);
        return &x;
    }
    Descriptive *edit(string question, DateTime createdAt, User user)
    {
        this->question = question;
        this->createdAt = createdAt;
        this->user = user;
        return new Descriptive(question, createdAt, user);
    }

private:
    string answer;
};
