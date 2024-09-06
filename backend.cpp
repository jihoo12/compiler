class Backend {
private:
std::vector<string> out;
char leave = 0xC9;
char syscall = 0x0F05;
char init = 0x554889E5;
public:
inline void movregreg(char num) {

}
inline void movreg() {
}
inline void movmem() {
}
};
