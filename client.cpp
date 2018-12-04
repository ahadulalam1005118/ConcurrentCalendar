//
// Created by ahad on 11/14/18.
//

#include <sstream>
#include <zconf.h>
#include <netdb.h>
#include <strings.h>
#include <fstream>
#include <cstring>
#include <arpa/inet.h>
#include <algorithm>
#include "client.h"
#define MAXCONN 10
const unsigned MAXBUFLEN = 512;
client *client::_client = NULL;
bool client::login_status = false;
int sockfd;
int client_as_server_sockfd;
pthread_mutex_t accept_lock = PTHREAD_MUTEX_INITIALIZER;
//char buf[MAXBUFLEN];
// int sockfd;
string client::current_username = "";
vector<friends_info> client::friends_list = {};
vector<connected_friends> client::friends_sockfd = {};
vector<event_info> client::current_events = {};
void * client::process_connection(void *arg) {
    //_client = this;
    int n;
    char buf[MAXBUFLEN];
    //response response;
    pthread_detach(pthread_self());
    while (1) {
        cout << login_status <<endl;//communication occurs
        n = read(sockfd, buf,MAXBUFLEN);
        //n = recvfrom(sockfd,response, sizeof(struct response),0,)
        if (n <= 0) {
            if (n == 0) {
                cout << "server closed" << endl;
                _client->begin(_client->configuration_file_path);
                _client->run();
                //pthread_exit(0);
            } else {
                cout << "something wrong" << endl;
            }
            close(sockfd);
            // we directly exit the whole process.
            return(NULL);
        }
        buf[n] = '\0';
        cout << buf << endl;
        vector<string> locs_friends_commands;
        //vector<string>locs_commands;
        vector<string> commands;
        commands = _client->split(buf,'$');
        if(commands[0] == "loggedin") {
            if(commands[2] == "data") {
                vector<event_info> events;
                vector<string> event_strings;
                event_strings = _client->split(commands[3],'%');
                cout << event_strings.size() << endl;
                //cout << event_strings[0] << endl;
                for(int i=0; i<event_strings.size(); i++) {
                    vector<string> each_event = _client->split(event_strings[i],'|');
                    if(each_event.size() == 5) {
                        event_info cur_evnt;
                        for(int j=0;j<each_event.size(); j++) {
                            //event_info cur_evnt;
                            cur_evnt.hostname = each_event[0];
                            cur_evnt.date = each_event[1];
                            cur_evnt.start_time = each_event[2];
                            cur_evnt.end_time = each_event[3];
                            cur_evnt.event_desc = each_event[4];

                            //events.push_back(cur_evnt);

                        }
                        events.push_back(cur_evnt);

                    }

                }
                //cout << events.size() << endl;
                _client->current_events.clear();
                _client->current_events = events;
                //cout << "size"<< _client->current_events.size() << endl;




                //this->current_events.clear();
               // this->current_events = events;

            }
            current_username = commands[1];
            login_status = true;
           // _client->handle_loggedin_command_from_server();
            if(commands.size() > 2) {
                locs_friends_commands = _client->split(commands[2],'|');
                for(int cnt =0; cnt < locs_friends_commands.size(); cnt++) {
                    vector<string>locs_commands;
                    locs_commands = _client->split(locs_friends_commands[cnt],':');
                    if(locs_commands[0] == "locs") {
                        friends_info new_friend;
                        new_friend.ip_addr = locs_commands[1];
                        new_friend.username = locs_commands[2];
                        cout << locs_commands[1] << endl;
                        cout << locs_commands[2] << endl;
                        //cout << _client->friends_list.size() << endl;
                        if(!_client->exists(locs_commands[2])) {
                            client::friends_list.push_back(new_friend);
                        }

                        //_client->friends_list.push_back(new_friend);
                    }

                }

            }


        }
        else if(commands[0] == "loggedout") {
            _client->evict_user_from_friends(commands[1]);

        }
        else if(commands[0] == "data") {
            cout << commands[1] << endl;
            vector<event_info> events;
            vector<string> event_strings;
            event_strings = _client->split(commands[1],'%');
            cout << event_strings.size() << endl;
            //cout << event_strings[0] << endl;
            for(int i=0; i<event_strings.size(); i++) {
                vector<string> each_event = _client->split(event_strings[i],'|');
                if(each_event.size() == 5) {
                    event_info cur_evnt;
                    for(int j=0;j<each_event.size(); j++) {
                        //event_info cur_evnt;
                        cur_evnt.hostname = each_event[0];
                        cur_evnt.date = each_event[1];
                        cur_evnt.start_time = each_event[2];
                        cur_evnt.end_time = each_event[3];
                        cur_evnt.event_desc = each_event[4];

                        //events.push_back(cur_evnt);

                    }
                    events.push_back(cur_evnt);

                }

            }
            //cout << events.size() << endl;
            _client->current_events.clear();
            _client->current_events = events;
            //cout << "size"<< _client->current_events.size() << endl;




            //this->current_events.clear();
           // this->current_events = events;



        }
        else {
            vector<string>locs_split;
            vector<string> locs;
            locs_split = _client->split(buf, '|');
            locs = _client->split(locs_split[0],':');
            if (locs[0] == "locs") {
                friends_info new_friend;
                new_friend.ip_addr = locs[1];
                new_friend.username = locs[2];
                //cout << locs_commands[1] << endl;
                //cout << locs_commands[2] << endl;
                //cout << _client->friends_list.size() << endl;
                if (!_client->exists(locs[2])) {
                    client::friends_list.push_back(new_friend);
                }

            }
        }

        //cout << commands[0] << endl;
        //cout << commands[1] << endl;

        //locs_commands = _client->split(commands[1],':');


        for(int i=0; i<_client->friends_list.size(); i++) {
            cout << _client->friends_list[i].username << " "
                 <<  _client->friends_list[i].ip_addr << endl;

        }
        sleep(1);
        //handle_command_from_server(string buf);
    }
}
vector<event_info> client::get_events() {
    sleep(1);

    return _client->current_events;

}

void client::evict_user_from_friends(string username){
    this->friends_list.erase(
            std::remove_if(this->friends_list.begin(), this->friends_list.end(), [&](friends_info const & usr) {
                return usr.username == username;
            }),
            this->friends_list.end());
}
void client::write_to_sockfd(string str) {
    write(sockfd,str.c_str(),str.length());
}

template<typename Out>
void client :: split(const std::string &s, char delim, Out result) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

int client::exists(string username) {
    int flag = 0;
    for(int cnt=0; cnt<_client->friends_list.size(); cnt++) {
        if(_client->friends_list[cnt].username == username) {
            flag = 1;
        }
    }
    if(flag == 1) return 1;
    else return 0;
}
string client::get_friend_address(string username) {
    for(int i=0; i<friends_list.size(); i++) {
        if(friends_list[i].username == username) return friends_list[i].ip_addr;
    }
}

std::vector<std::string> client :: split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

int client::begin(std::string config_file_path) {
    _client = this;
    this->configuration_file_path = config_file_path;
    return EXIT_SUCCESS;
}
config client :: split_string_config(string s, string delimiter){
    config conf;
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        conf.name = token;
        s.erase(0, pos + delimiter.length());
    }
    conf.argv = s;
    return conf;
}
vector<config> client :: get_configurations(string filename){
    vector<config> configuration;
    //config conf;
    ifstream inFile;
    const char * file = filename.c_str();
    inFile.open(file,ios::binary|ios::in);
    if (inFile.fail()) {
        cout << "Could Not Open File\n";
    } else {
        std::string line;
        while(getline(inFile, line)) {
            config conf = split_string_config(line,":");
            configuration.push_back(conf);
        }
    }
    inFile.close();
    return configuration;
}
int client ::is_connected(string username) {
    int flag = 0;
    for(int i=0; i< this->friends_sockfd.size(); i++) {
        if(friends_sockfd[i].username.compare(username) == 0) {
            flag = friends_sockfd[i].sockfd;
        }
    }
    if(flag > 0) return flag;
    else return -1;
}
int client::run() {
    int rv, flag;
    ssize_t n;
    struct addrinfo hints, *res, *ressave;
    pthread_t tid;


    //cout << get_configurations(this->configuration_file_path)[0].argv << " "
         //<< get_configurations(this->configuration_file_path)[1].argv << endl;

    bzero(&hints, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((rv = getaddrinfo(get_configurations(this->configuration_file_path)[0].argv.c_str() ,
                          get_configurations(this->configuration_file_path)[1].argv.c_str() , &hints, &res)) != 0) {
        cout << "getaddrinfo wrong: " << gai_strerror(rv) << endl;
        EXIT_SUCCESS;
    }

    ressave = res;
    flag = 0;
    do {
        sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if (sockfd < 0)
            continue;
        if (connect(sockfd, res->ai_addr, res->ai_addrlen) == 0) {
            flag = 1;
            break;
        }
        close(sockfd);
    } while ((res = res->ai_next) != NULL);
    freeaddrinfo(ressave);

    if (flag == 0) {
        fprintf(stderr, "cannot connect\n");
        EXIT_SUCCESS;
    }
    pthread_create(&tid, NULL, &process_connection, NULL);


}
