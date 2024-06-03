#pragma once
#include "Permission.h"
#include "Tag.h"
#include "Users.h"
#include "Question.h"

Permission *Gpermissions[100] = {new Permission("add-descriptive-question"), new Permission("add-four-choice-question"),
                                 new Permission("edit-descriptive-question"), new Permission("edit-four-choice-question"),
                                 new Permission("add-user"), NULL};

Tag *Gtags[100] = {NULL};

User *users[100] = {NULL};

Question *questions[100] = {NULL};