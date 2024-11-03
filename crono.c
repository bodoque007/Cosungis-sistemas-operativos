#define CHRONO_CURRENT_TIME
#define CHRONO_CTRL
#define CHRONO_RESET

int driver_init() {
  return 0;
}

int driver_read(int * data) {
	int current_time;
	current_time = IN(CHRONO_CURRENT_TIME);
  copy_to_user(user_data, &current_time, sizeof(current_time));
  return 0;
}


int driver_write(int * data) {
  OUT(CHRONO_CTRL, CHRONO_RESET);
  return 0;
}
