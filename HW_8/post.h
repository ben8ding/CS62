#ifndef POST_H
#define POST_H

#include <string>
#include <vector>

class Post{
    public:

        // constructors
        Post();
        Post(int profileId, int authorId, std::string message, std::vector<int> likes);

        // getters and setters
        int getMessageId();
        void setMessageId(int id);
        int getProfileId();
        int getAuthorId();
        std::string getMessage();
        std::vector<int> getLikes();
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
        std::vector<int> likes_;

};

class LinkPost : public Post{
    public:
        LinkPost();
        LinkPost(int profileId, int authorId, std::string message, std::vector<int> likes, std::string url);

        std::string getURL();
        std::string toString();

    private:
        std::string url_;

};
#endif
