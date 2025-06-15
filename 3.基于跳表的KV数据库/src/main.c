#include "../include/include.h"

#include <stdio.h>
/*全局变量*/
skiplist *sklist;
INSERT_ON_ODD_SHOW insert_on_or_show = INSERT_OFF;
SEARCH_ON_ODD_SHOW search_on_or_show = SEARCH_ON;

int main(int argc, char *argv[])
{

    sklist = skiplist_create();
    read_data_from_disk(get_appdata_path(DATE_FILE), sklist);
    insert_on_or_show = INSERT_ON;
    parser(argc, argv);
    save_data_to_disk(get_appdata_path(DATE_FILE), sklist);
    return 0;
}