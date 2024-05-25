#include "transport/Transport.h"
#include <httplib.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include "CardInfo.h"

using json = nlohmann::json;

Transport& Transport::getInstance()
{
    static Transport instance;
    return instance;
}
//
//void Transport::init()
//{
//   
//}

std::vector<unsigned long long> Transport::findDueCards() {
    // Create JSON request body
    json request_body = {
        {"action", "findCards"},
        {"version", 6},
        {"params", {{"query", "is:due"}}}
    };

    httplib::Client cli("http://localhost:8765");
    auto res = cli.Post("/", request_body.dump(), "application/json");

    if (res && res->status == 200) {
        auto response_body = json::parse(res->body);
        if (response_body.contains("error") && !response_body["error"].is_null()) {
            throw std::runtime_error(response_body["error"].get<std::string>());
        }
        return response_body["result"].get<std::vector<unsigned long long>>();
    }
    else {
        throw std::runtime_error("Request failed with status: " + std::to_string(res->status));
    }
}

std::vector<std::string> Transport::getWords(const std::vector<unsigned long long>& inCardIds)
{
    json request_body = {
       {"action", "cardsInfo"},
       {"version", 6},
       {"params", {{"cards", inCardIds}}}
    };

    std::vector<std::string> output;
    output.reserve(inCardIds.size());

    httplib::Client cli("http://localhost:8765");
    auto res = cli.Post("/", request_body.dump(), "application/json");

    if (res && res->status == 200) {
        auto response_body = json::parse(res->body);
        if (response_body.contains("error") && !response_body["error"].is_null()) {
            throw std::runtime_error(response_body["error"].get<std::string>());
        }

        // Return the JSON result directly
        for (const auto& x : response_body["result"]) {
            output.push_back(x["fields"]["Word"]["value"].get<std::string>());
        }
    }
    else {
        throw std::runtime_error("Request failed with status: ");
    }

    return output;
}

std::vector<CardInfo> Transport::getCardInfo(const std::vector<std::string>& inCardIds)
{
    std::vector<CardInfo> result;
    httplib::Client cli("https://jisho.org");
    for (const auto& word : inCardIds) {
        std::string url = "/api/v1/search/words?keyword=" + word;

        auto res = cli.Get(url.c_str());

        if (res && res->status == 200) {
            auto jsonData = nlohmann::json::parse(res->body);

            // Extract and print the meanings
            const auto& entry = jsonData["data"][0];
            const auto& word = entry["japanese"][0]["word"].get<std::string>();
            std::cout << "Word: " << word << std::endl;
            std::cout << "Reading: " << entry["japanese"][0]["reading"].get<std::string>() << std::endl;
            const auto& sense = entry["senses"][0];
            const auto& meanings = sense["english_definitions"].get<std::vector<std::string>>();
            if (!meanings.empty()) {
                result.emplace_back(word, meanings[0]);
                std::cout << "Meanings: " << meanings[0] << std::endl;
            }
            std::cout << std::endl;
        }
        else {
            throw std::runtime_error("Failed to get response from Jisho API");
        }
    }

    return result;
}
