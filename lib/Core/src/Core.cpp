#include "Core.h"

Core::Core(Graphics * one, Terminal * two) {
    GLU = one;
    GUI = two;
}

String Core::controller(uint8_t to, uint8_t data) {
    String responce;
    if(to == 1) {
        responce = GUI->listen(data);
    }
    return exec(responce);
}

String Core::exec(String input) {

	if(input.equals(""))
		return "";

	String output = "";
	String command = "";

	String tmp_command_val[2] = {"", ""};
	String command_val = "";

	bool ready_command = false;
	bool status = false;

	uint8_t num_of_opening_brackets = 0;
	uint8_t num_of_closing_brackets = 0;

	for(uint8_t i = 0; input[i] != '\0'; i++) {

		if(!ready_command && input[i] != ' ') {
			uint8_t j = i;
			while(input[j] != ' ') {
				command += input[j];
				j++;
			}
			i = j+1;
			ready_command = true;
		}

		if(ready_command) {
			tmp_command_val[status] += input[i];
			if(input[i] == '(') {
				num_of_opening_brackets++;
			}
			else if(input[i] == ')') {
				num_of_closing_brackets++;
			}
		}
	}
	if(num_of_opening_brackets != num_of_closing_brackets) {
		return "Syntax error [brackets].";
	}
	for(uint8_t to_repeat = 0; to_repeat < num_of_opening_brackets; to_repeat++) {
		for(uint8_t i = 0; tmp_command_val[status][i] != '\0'; i++) {

			if(tmp_command_val[status][i] == '(') {
				String tmp_operation = "";
				uint8_t j = i+1;
				while(tmp_command_val[status][j] != ')') {
					if(tmp_command_val[status][j] == '(') {
						tmp_operation = "";
						j++;
						continue;
					}
					tmp_operation += tmp_command_val[status][j];
					j++;
				}
				i = j+1;
				tmp_command_val[!status] += exec(tmp_operation);
				continue;
			}

			tmp_command_val[!status] += tmp_command_val[status][i];
		}
		tmp_command_val[status] = "";
		status = !status;
	}

	for(uint8_t i = 0; tmp_command_val[status][i] != '\0'; i++) {
		if(tmp_command_val[status][i] != ' ')
			command_val += tmp_command_val[status][i];
	}

	if(command.equals("scolor")) {
		uint16_t *val_array = explode(command_val);
		GLU->setColor(val_array[0], val_array[1], val_array[2]);
		delete[] val_array;
	}
	else if(command.equals("drect")) {
		uint16_t *val_array = explode(command_val);
		GLU->drawQuad(val_array[0], val_array[1], val_array[2], val_array[3]);
		delete[] val_array;
	}
	else if(command.equals("delay")) {
		uint16_t *val_array = explode(command_val);
		delay(val_array[0]);
		delete[] val_array;
	}
	else if(command.equals("say")) {
		output = command_val;
	}
	else if(command.equals("chfm")) {
		output = String(freeMemory());
	}
	else if(command.equals("erase")) {
		GUI->erase();
	}
	else if(command.equals("dline")) {
		uint16_t *val_array = explode(command_val);
		GLU->drawLine(val_array[0], val_array[1], val_array[2], val_array[3]);
		delete[] val_array;
	}
	else if(command.equals("dpix")) {
		uint16_t *val_array = explode(command_val);
		GLU->drawPix(val_array[0], val_array[1]);
		delete[] val_array;
	}
	else if(command.equals("sback")) {
		uint16_t *val_array = explode(command_val);
		GLU->setBackground(val_array[0], val_array[1], val_array[2]);
		delete[] val_array;
	}
	else if(command.equals("sfont")) {
		uint16_t *val_array = explode(command_val);
		GLU->setFont(val_array[0]);
		delete[] val_array;
	}
	return output;
}
