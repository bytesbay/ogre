#include "Functions.h"

void addElem(uint16_t *& array, uint8_t len, uint16_t val) {
	uint16_t * tmp = new uint16_t[len];
	for(uint8_t i = 0; i < len; i++) {
		tmp[i] = array[i];
	}
	tmp[len-1] = val;

	array = tmp;
}
uint16_t * explode(String str) {

	String val = "";

	uint8_t val_index = 1;
	uint16_t * result_ptr = new uint16_t[1];

	for(uint8_t i = 0; i < str.length(); i++) {

		if(str[i] != ',' && str[i] != '\0') {
			val += str[i];
			if(str[i+1] == ',' || str[i+1] == '\0') {
				addElem(result_ptr, val_index, atoi(val.c_str()));
				val_index++;
				val = "";
				continue;
			}
		}
	}

	return result_ptr;
}
