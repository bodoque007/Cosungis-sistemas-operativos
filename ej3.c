mutex access;

int driver_init(void) {
  mutex_init( & access);
  return 0;
}

int driver_read(int __user * data) {
  int btn_status;

  mutex_lock( & access);
  //equiv a (IN(BTN_STATUS) & 1) != 1
  while (!(IN(BTN_STATUS) & 0x1)) {

  }

  OUT(BTN_STATUS, IN(BTN_STATUS) & ~0x2);

  mutex_unlock( & access);

  btn_status = BTN_PRESSED;
  if (copy_to_user(data, & btn_status, sizeof(int))) {
    return -EFAULT;
  }

  return 0;
}

