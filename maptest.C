#include "lib/json_run_map.h"

//Esto es una macro de ejemplo donde se usa el mapa para filtrar canales con threshold mayor de 50
void maptest(){
    
    // Initialize the map, don't forget the const! mumbo jumno otherwhise
    const Run_map map_of_runs=Run_map("laura_la_lia.json");

    for (auto i:map_of_runs.json_map) {
        if (i["threshold"]>50 && i["threshold"]!="" && ){cout<<i["run"]<<"  "<< i["threshold"]<<endl;}
    }

}