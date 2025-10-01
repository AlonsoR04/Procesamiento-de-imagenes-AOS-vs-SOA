
#ifndef PROGARS_H
#define PROGARS_H

#include <string>
#include <vector>

static constexpr int MIN_NUM_ARGUMENTS = 3;
static constexpr int MAX_NUM_ARGUMENTS = 5;

int convertir_entero(std::string const & string);
int numero_argumentos_erroneo(int const n_param);
int validar_argumentos(int const argc, std::vector<std::string> const & args);
int check_op(int const n_param, std::vector<std::string> const & args);
int check_info(int const n_param, std::vector<std::string> const & args);
int check_maxlevel(int const n_param, std::vector<std::string> const & args);
int check_cutfreq(int const n_param, std::vector<std::string> const & args);
int check_resize(int const n_param, std::vector<std::string> const & args);
int check_compress(int const n_param, std::vector<std::string> const & args);

#endif
