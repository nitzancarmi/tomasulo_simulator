#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

#define ARRAY_LENGTH(array) (sizeof((array))/sizeof((array)[0]))

enum inst_opcode {
	LD = 0,
	ST = 1,
	ADD = 2,
	SUB = 4,
	MULT = 5,
	DIV = 6,
	HALT = 7
};

enum inst_type {
	ADD_TYPE,
	MULT_TYPE,
	DIV_TYPE,
	MEM_TYPE
};

struct reserve_station {
	enum inst_type type;
	bool unit;
	bool busy;
	int time;
	int delay;
	enum inst_opcode opcode;
	unsigned int Vj;
	unsigned int Vk;
	unsigned int Qj;
	unsigned int Qk;
	int pc;
};

int MAX_UNITS[4];
struct reserve_station *resv_stations;

void init_config_params(char *filepath) {
	FILE *fin;
	char *line;
	int read, i;
	char* token, *param;
	int value;
	int add_nr_reservation, mul_nr_reservation, div_nr_reservation;
	int add_delay, mul_delay, div_delay;

	fin = fopen(filepath, "r");
	if (!fin) {
		printf("File doesn't open\n");
		return;
	}

	while ((read = getline(&line, NULL, fin)) != -1) {
		token = strtok(line, " =");
		param = strtok(NULL, " =");
		value = (int)strtol(strtok(NULL, " ="), NULL, 0);

		if (!strcmp(param, "add_nr_units")) {
			MAX_UNITS[ADD_TYPE] = value;
		}

		if (!strcmp(param, "mul_nr_units")) {
			MAX_UNITS[MULT_TYPE] = value;
		}

		if (!strcmp(param, "div_nr_units")) {
			MAX_UNITS[DIV_TYPE] = value;
		}

		if (!strcmp(param, "add_nr_reservation")) {
			add_nr_reservation = value;
		}

		if (!strcmp(param, "mul_nr_reservation")) {
			mul_nr_reservation = value;
		}

		if (!strcmp(param, "div_nr_reservation")) {
			div_nr_reservation = value;
		}

		if (!strcmp(param, "add_delay")) {
			add_delay = value;
		}

		if (!strcmp(param, "mul_delay")) {
			mul_delay = value;
		}

		if (!strcmp(param, "div_delay")) {
			div_delay = value;
		}

		if (!strcmp(param, "mem_delay")) {
			printf("mem_delay isn't implemented yet\n");
			//do something
		}

		if (!strcmp(param, "mem_nr_load_buffers")) {
			printf("mem_nr_load_buffers isn't implemented yet\n");
			//do something
		}

		if (!strcmp(param, "mem_nr_store_buffers")) {
			printf("mem_nr_store_buffers isn't implemented yet\n");
			//do something
		}
	}

	resv_stations = malloc(sizeof(struct reserve_station) *
							(add_nr_reservation +
							mul_nr_reservation +
							div_nr_reservation));
	for (i = 0; i < add_nr_reservation; i++) {
		resv_stations[i].type = ADD_TYPE;
		resv_stations[i].delay = add_delay;
	}
	for (i = add_nr_reservation; i < add_nr_reservation + mul_nr_reservation; i++) {
		resv_stations[i].type = MULT_TYPE;
		resv_stations[i].delay = mul_delay;

	}
	for (i = add_nr_reservation + mul_nr_reservation; i < add_nr_reservation + mul_nr_reservation + div_nr_reservation; i++) {
		resv_stations[i].type = DIV_TYPE;
		resv_stations[i].delay = div_delay;
	}

	fclose(fin);
}

void destroy_config_params() {
	free(resv_stations);
}
int main(int argc, char *argv[]) {

	printf("Hello Shani!\n");

	init_config_params(argv[1]);
	if (!resv_stations) {
		printf("Failed to init cfg file\n");
		return 1;
	}

	destroy_config_params();
	return 0;
}