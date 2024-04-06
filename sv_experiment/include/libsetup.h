extern "C" {
extern char* snps_setup_get_value(const char*, int);
extern void snps_setup_parse();
extern void mem_initialize();
extern int snps_setup_init(int argc, char **argv, int count, ...);
extern void snps_setup_directory(const char*);
extern char** snps_get_setup_directory();
extern void snps_setup_filename(const char*);
extern void snps_setup_scan_args(const char*, int, const char*, int);
extern void snps_setup_iterate_all_libs(int op, void (*cbFunc)(const char*, const char*));
extern char* snps_get_filename_for_var(char const *varName, int op);
}

