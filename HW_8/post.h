#ifndef POST_H
#define POST_H

#include <string>
#include <set>

class Post{
    public:

        // constructors
        Post();
        Post(int profileId, int authorId, std::string message, std::set<int> likes);

        // getters and setters
        int getMessageId();
        void setMessageId(int id);
        int getProfileId();
        int getAuthorId();
        std::string getMessage();
        std::set<int> getLikes();
        void addLike(int userId);
        
        // virtual methods
        virtual std::string getURL();
        virtual std::string toString();

    private:

        //fields
        int messageId_;
        int profileId_;
        int authorId_;
        std::string message_;
        std::set<int> likes_;

};

class LinkPost : public Post{
    public:
        LinkPost();
        LinkPost(int profileId, int authorId, std::string message, std::set<int> likes, std::string url);

        std::string getURL();
        std::string toString();

    private:
        std::string url_;

};
#endif
