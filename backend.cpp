class Backend {
private:
std::vector<char> out;
char leave = 0xC9;
char syscall = 0x0F05;
char init = 0x554889E5;
public:
inline void movregreg(char num) {
  out.push_back(0x48);
  out.push_back(0x89);
  out.push_back(num);
}
inline void movreg() {
}
inline void movmem() {
}
};
