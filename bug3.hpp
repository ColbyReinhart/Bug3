#ifndef BUG_HPP
#define BUG_HPP

const int MAX_MALE_AGE = 30;
const int MAX_FEMALE_AGE = 37;
const int BREED_COOLDOWN = 3;

const int M_TO_F_RATIO = 1;

class Population {
public:
    Population();
    Population(unsigned long long int start_pop, double sterile_percent, int sterile_interval, int sterile_period, int sterile_age);
    Population(unsigned long long int start_pop, unsigned long long int sterile_amount, int sterile_interval, int sterile_period, int sterile_age);
    void die();
    void age();
    unsigned long long int breed();
    void introduce_sterile_males();
    void update();
private:
    unsigned long long int males_[MAX_MALE_AGE];
    unsigned long long int females_[MAX_FEMALE_AGE];
    unsigned long long int sterile_males_[MAX_MALE_AGE];
    unsigned long long int breeds[BREED_COOLDOWN];
    double death_rate_;
    double mate_rate_;
    unsigned long long int stable_pop_;
    double sterile_percent;
    unsigned long long int sterile_amount;
    int sterile_interval;
    int sterile_period;
};

#endif