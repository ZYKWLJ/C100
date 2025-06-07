 printf("Created skip list\n");

    printf("Searching for 100 in empty list: %s\n",
           skiplist_search(obj, 100) ? "PASS" : "FAIL");

    skiplist_insert(obj, 50);
    skiplist_insert(obj, 30);
    skiplist_insert(obj, 70);
    skiplist_insert(obj, 20);
    skiplist_insert(obj, 40);
    skiplist_insert(obj, 60);
    skiplist_insert(obj, 80);
    printf("Added elements: 20, 30, 40, 50, 60, 70, 80\n");

    printf("Searching for 30: %s\n",
           skiplist_search(obj, 30) ? "PASS" : "FAIL");
    printf("Searching for 50: %s\n",
           skiplist_search(obj, 50) ? "PASS" : "FAIL");
    printf("Searching for 80: %s\n",
           skiplist_search(obj, 80) ? "PASS" : "FAIL");

    printf("Searching for 10: %s\n",
           skiplist_search(obj, 10) ? "FAIL" : "PASS");
    printf("Searching for 90: %s\n",
           skiplist_search(obj, 90) ? "FAIL" : "PASS");

    printf("Erasing 30: %s\n",
           skiplist_erase(obj, 30) ? "PASS" : "FAIL");
    printf("Searching for 30 after erase: %s\n",
           skiplist_search(obj, 30) ? "FAIL" : "PASS");

    printf("Erasing 80: %s\n",
           skiplist_erase(obj, 80) ? "PASS" : "FAIL");
    printf("Searching for 80 after erase: %s\n",
           skiplist_search(obj, 80) ? "FAIL" : "PASS");

    printf("Erasing 100: %s\n",
           skiplist_erase(obj, 100) ? "FAIL" : "PASS");

    skiplist_insert(obj, 50);
    printf("Added duplicate 50. Searching: %s\n",
           skiplist_search(obj, 50) ? "PASS" : "FAIL");

    printf("Erasing 20: %s\n",
           skiplist_erase(obj, 20) ? "PASS" : "FAIL");
    printf("Erasing 40: %s\n",
           skiplist_erase(obj, 40) ? "PASS" : "FAIL");
    printf("Erasing 50: %s\n",
           skiplist_erase(obj, 50) ? "PASS" : "FAIL");
    printf("Erasing 60: %s\n",
           skiplist_erase(obj, 60) ? "PASS" : "FAIL");
    printf("Erasing 70: %s\n",
           skiplist_erase(obj, 70) ? "PASS" : "FAIL");

    printf("Searching for 50 in empty list: %s\n",
           skiplist_search(obj, 50) ? "FAIL" : "PASS");

    skiplist_free(obj);