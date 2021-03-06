#ifndef extensions_v1beta1_supplemental_groups_strategy_options_TEST
#define extensions_v1beta1_supplemental_groups_strategy_options_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define extensions_v1beta1_supplemental_groups_strategy_options_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/extensions_v1beta1_supplemental_groups_strategy_options.h"
extensions_v1beta1_supplemental_groups_strategy_options_t* instantiate_extensions_v1beta1_supplemental_groups_strategy_options(int include_optional);



extensions_v1beta1_supplemental_groups_strategy_options_t* instantiate_extensions_v1beta1_supplemental_groups_strategy_options(int include_optional) {
  extensions_v1beta1_supplemental_groups_strategy_options_t* extensions_v1beta1_supplemental_groups_strategy_options = NULL;
  if (include_optional) {
    extensions_v1beta1_supplemental_groups_strategy_options = extensions_v1beta1_supplemental_groups_strategy_options_create(
      list_create(),
      "0"
    );
  } else {
    extensions_v1beta1_supplemental_groups_strategy_options = extensions_v1beta1_supplemental_groups_strategy_options_create(
      list_create(),
      "0"
    );
  }

  return extensions_v1beta1_supplemental_groups_strategy_options;
}


#ifdef extensions_v1beta1_supplemental_groups_strategy_options_MAIN

void test_extensions_v1beta1_supplemental_groups_strategy_options(int include_optional) {
    extensions_v1beta1_supplemental_groups_strategy_options_t* extensions_v1beta1_supplemental_groups_strategy_options_1 = instantiate_extensions_v1beta1_supplemental_groups_strategy_options(include_optional);

	cJSON* jsonextensions_v1beta1_supplemental_groups_strategy_options_1 = extensions_v1beta1_supplemental_groups_strategy_options_convertToJSON(extensions_v1beta1_supplemental_groups_strategy_options_1);
	printf("extensions_v1beta1_supplemental_groups_strategy_options :\n%s\n", cJSON_Print(jsonextensions_v1beta1_supplemental_groups_strategy_options_1));
	extensions_v1beta1_supplemental_groups_strategy_options_t* extensions_v1beta1_supplemental_groups_strategy_options_2 = extensions_v1beta1_supplemental_groups_strategy_options_parseFromJSON(jsonextensions_v1beta1_supplemental_groups_strategy_options_1);
	cJSON* jsonextensions_v1beta1_supplemental_groups_strategy_options_2 = extensions_v1beta1_supplemental_groups_strategy_options_convertToJSON(extensions_v1beta1_supplemental_groups_strategy_options_2);
	printf("repeating extensions_v1beta1_supplemental_groups_strategy_options:\n%s\n", cJSON_Print(jsonextensions_v1beta1_supplemental_groups_strategy_options_2));
}

int main() {
  test_extensions_v1beta1_supplemental_groups_strategy_options(1);
  test_extensions_v1beta1_supplemental_groups_strategy_options(0);

  printf("Hello world \n");
  return 0;
}

#endif // extensions_v1beta1_supplemental_groups_strategy_options_MAIN
#endif // extensions_v1beta1_supplemental_groups_strategy_options_TEST
