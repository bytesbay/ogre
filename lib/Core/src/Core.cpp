#include "Core.h"

String Core::root;
uint8_t Core::variables_num;
uint16_t * Core::variables;

void Core::begin() {
    root = "/";
}

void Core::buzzer(uint8_t note, uint16_t sec) {
    pinMode(5, OUTPUT);
    tone(5, note * 60);
    delay(sec);
    analogWrite(5, 0);
    pinMode(5, INPUT);
}

bool Core::script(String path) {
    File file = SD.open(path);
    if(file) {
        String command;
        while (file.available()) {
            uint8_t symbol = file.read();
            if(symbol == '\r') continue;
            if(symbol == '\n') {
                exec(command);
                command = "";
                continue;
            }
            command += symbol;
        }
        return true;
    } else {
        return false;
    }
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
			while(input[j] != ' ' && input[j] != '\0') {
				command += input[j];
				j++;
			}
			i = j;
			ready_command = true;
            continue;
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
        return "[ <r>ERROR</> ] Missing bracket.\n";
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
		Graphics::setColor(val_array[0], val_array[1], val_array[2]);
		delete[] val_array;
	}
	else if(command.equals("drect")) {
		uint16_t *val_array = explode(command_val);
		Graphics::drawQuad(val_array[0], val_array[1], val_array[2], val_array[3]);
		delete[] val_array;
	}
	else if(command.equals("delay")) {
		uint16_t *val_array = explode(command_val);
		delay(val_array[0]);
		delete[] val_array;
	}
	else if(command.equals("echo")) {
		output = command_val+"\n";
	}
	else if(command.equals("chfm")) {
		uint16_t freemem = freeMemory();
        if(freemem > 5000) output = "<g>"+String(freemem)+"</> bytes.\n";
        else if(freemem < 2000) output = "<r>"+String(freemem)+"</> bytes.\n";
        else output = "<y>"+String(freemem)+"</> bytes.\n";
	}
	else if(command.equals("dline")) {
		uint16_t *val_array = explode(command_val);
		Graphics::drawLine(val_array[0], val_array[1], val_array[2], val_array[3]);
		delete[] val_array;
	}
	else if(command.equals("dpix")) {
		uint16_t *val_array = explode(command_val);
		Graphics::drawPix(val_array[0], val_array[1]);
		delete[] val_array;
	}
	else if(command.equals("sback")) {
		uint16_t *val_array = explode(command_val);
		Graphics::setBackground(val_array[0], val_array[1], val_array[2]);
		delete[] val_array;
	}
	else if(command.equals("sfont")) {
		uint16_t *val_array = explode(command_val);
		Graphics::setFont(val_array[0]);
		delete[] val_array;
	}
    else if(command.equals("malloc")) {
        if(variables_num < 255) addElem(variables, variables_num, 0);
        else output = "[ <r>ERROR</> ] Too many variables.\n";
	}
    else if(command.equals("var")) {
		uint16_t *val_array = explode(command_val);
        if(val_array[0] <= variables_num) variables[val_array[0]] = val_array[1];
        else output = "[ <r>ERROR</> ] Invalid var index.\n";
		delete[] val_array;
	}
    else if(command.equals("rvar")) {
		uint16_t *val_array = explode(command_val);
        if(val_array[0] <= variables_num) output = variables[val_array[0]]+"\n";
        else output = "[ <r>ERROR</> ] Invalid var index.\n";
		delete[] val_array;
	}
    else if(command.equals("+")) {
		uint16_t *val_array = explode(command_val);
		output = String(val_array[0] + val_array[1])+"\n";
		delete[] val_array;
	}
    else if(command.equals("-")) {
		uint16_t *val_array = explode(command_val);
		output = String(val_array[0] - val_array[1])+"\n";
		delete[] val_array;
	}
    else if(command.equals("*")) {
		uint16_t *val_array = explode(command_val);
		output = String(val_array[0] * val_array[1])+"\n";
		delete[] val_array;
	}
    else if(command.equals("/")) {
		uint16_t *val_array = explode(command_val);
		output = String(val_array[0] / val_array[1])+"\n";
		delete[] val_array;
	}
    else if(command.equals("buzz")) {
		uint16_t *val_array = explode(command_val);
		buzzer(val_array[0], val_array[1]);
		delete[] val_array;
	}
    else if(command.equals("ls")) {
        File dir = SD.open(root);
        while (true) {
            File entry = dir.openNextFile();
            if (!entry) break;
            if (entry.isDirectory()) {
                output += "<y>"+String(entry.name())+"</>";
            } else {
                output += "<o>"+String(entry.name())+"</>";
            }
            output += "\n";
            entry.close();
        }
	}
    else if(command.equals("cd")) {
        if(command_val[0] != '/') {
            root += '/' + command_val;
        }
        else if(command_val[0] != '.') {
            command_val.remove(0);
            root += command_val;
        }
        else {
            root = command_val;
        }
	}
    else if(command.equals("ipo")) {
        bool status = false;
        if(command_val[0] == '/') {
            status = script(command_val);
        }
        else if(command_val[0] == '.') {
            command_val.remove(1);
            command_val.remove(0);
            status = script(root + command_val);
        }
        else {
            status = script(root + command_val);
        }
        if(!status) output = "[ <r>ERROR</> ] Couldn't find file";
	}
	return output;
}
