#include <stdlib.h>
#include <stdio.h>

#define n_sector 3
int glob=0;

float*** create_sector_times(unsigned int* n_drivers, unsigned int* n_laps){
    unsigned int drivers,laps;
    int i,j,k;
    float temp;
    float ***main_arr;
    scanf("%u %u", &drivers, &laps);
    *n_drivers=drivers;
    *n_laps=laps;
    if((main_arr= malloc(drivers * sizeof(*main_arr))) == NULL){
        free(main_arr);
        return NULL;
    }
    for(i=0; i<drivers; i++){
        if((main_arr[i]= malloc(laps * sizeof(**main_arr))) == NULL){
            free(main_arr);
            return NULL;
        }    
    }
    for(i=0; i<drivers; i++){
        for(j=0; j<laps; j++){
            if((main_arr[i][j]= malloc(n_sector * sizeof(***main_arr))) == NULL){
                free(main_arr);
                return NULL;
            }
        }
    }
    for(i=0; i<drivers; i++){
        for(j=0; j<laps; j++){
            for(k=0; k<n_sector; k++){
                scanf("%f",&temp);
                main_arr[i][j][k] = temp;
            }
        }
    }
    return main_arr;
}


unsigned int** create_positions(unsigned int* p_drivers, unsigned int* n_races){
    unsigned int drivers,races;
    int i,j;
    unsigned int temp;
    unsigned int **pos;
    scanf("%u %u", &drivers, &races);
    *p_drivers = drivers;
    *n_races = races;
    if((pos= malloc(drivers * sizeof(*pos))) == NULL){
        free(pos);
        return NULL;
    }
    for(i=0; i<drivers; i++){
        if((pos[i]= malloc(races * sizeof(**pos))) == NULL){
            free(pos);
            return NULL;
        }
    }
    for(i=0; i<drivers; i++){
        for(j=0; j<races; j++){
            scanf("%u",&temp);
            pos[i][j] = temp;
        }
    }
    
    return pos;
}


float** calculate_lap_times(float*** sector_times, unsigned int n_drivers, unsigned int n_laps){
    float **times;
    int i,j,k;
    float sum;
    if((times= malloc(n_drivers * sizeof(*times))) == NULL){
        free(times);
        return NULL;
    }
    for(i=0; i<n_drivers; i++){
        if((times[i]= malloc(n_laps * sizeof(**times))) == NULL){
            free(times);
            return NULL;
        }
    }
    for(i=0; i<n_drivers; i++){
        for(j=0; j<n_laps; j++){
            sum=0;
            for(k=0; k<n_sector; k++){
                sum+= sector_times[i][j][k];    
            }
            times[i][j]=sum;
        }
    }

    return times;
}


unsigned int find_fastest_lap(float** lap_times, unsigned int n_drivers, unsigned int n_laps){
    int i,j,fast_driver;
    float time,fastest = 1000.0;
    for(i=0; i<n_drivers; i++){
        for(j=0; j<n_laps; j++){
            time=lap_times[i][j];
            if(time<fastest){
                fastest = time;
                fast_driver = i;
            }
            else continue;
        }
    }
    return fast_driver;
}


unsigned int find_driver_fastest_lap(float** lap_times_of_driver, unsigned int n_laps){
    int i,j,fast_lap;
    float sum, fastest=1000.0;
    for(i=0; i<n_laps; i++){
        sum=0;
        for(j=0; j<3; j++){
            sum+= lap_times_of_driver[i][j];     
        }
        if(sum < fastest){
            fastest=sum;
            fast_lap=i;
        }
        else continue;
    }
    return (unsigned int)i;
}


float* selection_sort(float* arr, unsigned int len, char ord){
    int i, not_sorted=1, index=0, min_index;
    float *copy_arr, *temp_arr;
    float min=1000.0, cur,temp;
    copy_arr= malloc(len * sizeof(*arr));
    for(i=0; i<len; i++) copy_arr[i] = arr[i];
    while(not_sorted){
        if(glob == len){
            not_sorted=0;
            break;
        }
        else{
            for(i=glob; i<len; i++){
                cur = copy_arr[i];
                if(cur < min){
                    min = cur;
                    min_index=i;
                } 
            }
            glob+=1;
            temp = copy_arr[min_index];
            copy_arr[min_index] = copy_arr[index];
            copy_arr[index] = temp;
            index+=1;
        }
    }
    switch(ord){
        case 'A': 
        break;

        case 'D':
        temp_arr= malloc(len * sizeof(*arr));
        for(i=(len-1),index=0; i>=0; i--,index++){
            temp_arr[index] = copy_arr[i];    
        }
        for(i=0; i<len; i++){
            copy_arr[i] = temp_arr[i];
        }
    }
    return copy_arr;
}


unsigned int* find_finishing_positions(float** lap_times, unsigned int n_drivers, unsigned int n_laps){
    int i,j, not_sorted=1, min_index, index=0;
    float total, cur, min= 1000.0, temp_min;
    float *totals;
    unsigned int *drivers; unsigned int temp_driver;
    drivers= malloc(n_drivers * sizeof(unsigned int));
    totals= malloc(n_drivers * sizeof(float));
    for(i=0; i<n_drivers; i++){
        total=0.0;
        drivers[i]=(unsigned int)i;
        for(j=0; j<n_laps; j++){
            total+= lap_times[i][j];    
        }
        totals[i]= total;
    }
    glob=0;
    while(not_sorted){
        if(glob == n_drivers){
            not_sorted=0;
            break;
        }
        else{
            for(i=glob; i<n_drivers; i++){
                cur = totals[i];
                if(cur < min){
                    min = cur;
                    min_index=i;
                }    
            }
            glob+=1;
            temp_min = totals[min_index];
            totals[min_index] = totals[index];
            totals[index] = temp_min;
            temp_driver = drivers[min_index];
            drivers[min_index] = drivers[index];
            index+=1;
        }
    }
    return drivers;
}


float* find_time_diff(float** lap_times, unsigned int n_drivers, unsigned int n_laps, unsigned int driver1,unsigned int driver2){
    int i,j;    
    float diff, last_diff=0;
    float *time_diff;
    time_diff= malloc(n_laps * sizeof(float));
    for(i=0; i<n_laps; i++){
        diff = lap_times[driver1][i] - lap_times[driver2][i] + last_diff;
        last_diff = lap_times[driver1][i] - lap_times[driver2][i];
        time_diff[i] = diff;   
    }
    return time_diff;
}


unsigned int* calculate_total_points(unsigned int** positions, unsigned int p_drivers, unsigned int n_races){
    int i,j;
    unsigned int *points, *total_points; unsigned int temp, position, sum; 
    points = malloc(p_drivers * sizeof(unsigned int));
    total_points = malloc(p_drivers * sizeof(unsigned int));
    for(i=0; i<p_drivers; i++){
        scanf("%u",&temp);
        points[i] = temp;
    }
    for(i=0; i<p_drivers; i++){
        sum=0;
        for(j=0; j<n_races; j++){
            position = positions[i][j];
            sum+= points[position-1];
        }
        total_points[i] = sum;
    }
    return total_points;
}


unsigned int find_season_ranking(unsigned int* total_points, unsigned int p_drivers, unsigned int id){
    int i;
    unsigned int drivers_point = total_points[id]; unsigned int rank=1;
    for(i=0; i<p_drivers; i++){
        if(i == id) continue;
        else if(total_points[i] >= drivers_point){
            if((total_points[i]) == (drivers_point)){
                if(i < id) rank++;
            }
            else rank++;
        }
    }
    return rank;
}
