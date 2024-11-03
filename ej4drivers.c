mutex access;
semaphore sem;
#define PRESSED_ITR = 7;

void handler() {
  sem.signal();
}


int driver_init(void) {
  sem_init(&sem, 0);
  request_irq(PRESSED_ITR, handler);

  OUT(BTN_STATUS, BTN_INT);
  return 0;
}

int driver_remove() {
  free_irq(PRESSED_ITR);
}

int driver_read(int __user * data) {
  int btn_status;

  mutex_lock( & access);
  sem.wait();
  mutex_unlock( & access);
  
  OUT(BTN_STATUS, BTN_INT);
  btn_status = BTN_PRESSED;
  if (copy_to_user(data, & btn_status, sizeof(int))) {
    return -EFAULT;
  }

  return 0;
}
