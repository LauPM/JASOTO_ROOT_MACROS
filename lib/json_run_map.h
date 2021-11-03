#include"json.hpp"

class Run_map{

    public:
        Run_map(){}
        Run_map(string map_file){
            std::ifstream i(map_file);
            i >> json_map;
        }

        nlohmann::json json_map;
        // nlohmann::json getCollectionWithProperty(std::string property){
        //     nlohmann::json subSetPDmap;
        //     std::copy_if (json_map.begin(), json_map.end(), std::back_inserter(subSetPDmap),
        //         [property](const nlohmann::json e)->bool
        //         {return e[property];} );
        //     return subSetPDmap;
        // }
        nlohmann::json getCollectionWithProperty(std::string property){
            nlohmann::json subSetPDmap;
            std::copy_if (json_map.begin(), json_map.end(), std::back_inserter(subSetPDmap),
                [property](const nlohmann::json e)->int
                {return e[property];} );
            return subSetPDmap;
        }

    private:

};