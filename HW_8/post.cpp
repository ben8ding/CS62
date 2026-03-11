#include "post.h"

Post::Post()
{
    messageId_ = -1;
    profileId_ = 0;
    authorId_ = 0;
    message_ = "";
    likes_ = std::vector<int>();
}

Post::Post(int profileId, int authorId, std::string message, std::vector<int> likes)
{
    messageId_ = -1;
    profileId_ = profileId;
    authorId_ = authorId;
    message_ = message;
    likes_ = likes;
}

int Post::getMessageId()
{
    return messageId_;
}
void Post::setMessageId(int id)
{
    messageId_ = id;
}
int Post::getProfileId()
{
    return profileId_;
}
int Post::getAuthorId()
{
    return authorId_;
}
std::string Post::getMessage()
{
    return message_;
}
std::vector<int> Post::getLikes()
{
    return likes_;
}

std::string Post::getURL()
{
    return "";
}

std::string Post::toString() {
    return message_ + " (" + std::to_string(likes_.size()) + " likes)";
}

void Post::addLike(int userId) {
    if (std::find(likes_.begin(), likes_.end(), userId) == likes_.end()) {
        likes_.push_back(userId);
    }
}

LinkPost::LinkPost(): Post() {
        url_ = "";
    }

LinkPost::LinkPost(int profileId, int authorId, std::string message, std::vector<int> likes, std::string url)
    : Post(profileId, authorId, message, likes) {
    url_ = url;
}

std::string LinkPost::getURL()
{
    return url_;
}

std::string LinkPost::toString()
{
    return getMessage() + " (url: " + url_ + ") (" + std::to_string(getLikes().size()) + " likes)";
}
