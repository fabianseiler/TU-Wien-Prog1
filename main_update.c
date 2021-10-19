#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <duma.h>


typedef enum error_e
{
    SUCCESS=0,
    NULL_POINTER_ERROR,     //1
    ALLOC_FAILURE_ERROR,    //2
    OUT_OF_RANGE_ERROR,     //3
    DIMENSION_MISMATCH_ERROR//4
} error_t;

typedef struct vector_s
{
    long *values;
    long dim;
} vector_t;

typedef struct vec_array_s
{
    vector_t **vectors;
    long lenght;
} vec_array_t;

typedef double (*measure_f) (vector_t *);


error_t vector_allocate(vector_t *vec, long dim);
error_t vector_clear(vector_t *vec);
error_t vector_fill(vector_t *vec, long index, long value);
error_t vector_print(vector_t *vec);
error_t vector_change_dim(vector_t *vec, long new_dim);
error_t vector_add(vector_t *vec_a, vector_t *vec_b, vector_t *vec_sum);
error_t vector_slice(vector_t *vec, long index_a, long index_b);
vector_t *vector_allocate_dynamic(long dim);
error_t vector_free(vector_t *vec);
vec_array_t *vec_array_allocate(long lenght);
error_t vec_array_free(vec_array_t *array);
error_t vec_array_store(vec_array_t *array, vector_t *vec);
error_t vec_array_delete_at(vec_array_t *array, long index);
error_t vec_array_save(vec_array_t *array, char *file_name);
double vector_norm(vector_t *vec);
error_t vec_array_sort(vec_array_t *array, measure_f sort_key);



int main(){


    // Part A
    vector_t vec_a = {NULL, 0};
    vector_t vec_b = {NULL, 0};
    vector_t vec_c = {NULL, 0};
    vector_allocate(&vec_a, 10);
    vector_allocate(&vec_b, 10);
    vector_allocate(&vec_c, 10);
    vector_fill(&vec_a, 0, 5);
    vector_fill(&vec_b, 4, 8);
    vector_print(&vec_a);
    vector_print(&vec_b);

    // Part B
    vector_add(&vec_a, &vec_b, &vec_c);
    vector_print(&vec_c);
    vector_slice(&vec_c, 3, 7);
    vector_print(&vec_c);
    vector_clear(&vec_c);
    vector_clear(&vec_b);
    vector_clear(&vec_a);

    // Part C
    vector_t *vec_d = vector_allocate_dynamic(10);
    vector_print(vec_d);
    vector_fill(vec_d, 2, 7);
    vector_print(vec_d);
    vector_free(vec_d);

    // Part D
    vec_array_t *vec_arr = vec_array_allocate(10);
    vector_t *vec_e = vector_allocate_dynamic(10);
    vector_t *vec_f = vector_allocate_dynamic(8);

    vector_fill(vec_e, 2, 3);
    vector_fill(vec_f, 3, 8);

    vec_array_store(vec_arr, vec_e);
    vec_array_store(vec_arr, vec_f);

    vec_array_sort(vec_arr, vector_norm);

    for(int i=0; i<vec_arr->lenght; i++){
        vector_print(vec_arr->vectors[i]);
    }

    //Part E
    vec_array_save(vec_arr, "test.txt");
    //vec_arr = vec_array_load("test.txt");
    vec_array_delete_at(vec_arr, 1);

     for(int i=0; i<vec_arr->lenght; i++){
        vector_print(vec_arr->vectors[i]);
    }
    vec_array_delete_at(vec_arr, 1);

    for(int i=0; i<vec_arr->lenght; i++){
            vector_print(vec_arr->vectors[i]);
        }


    //Part F
    vector_t *vec_n = vector_allocate_dynamic(5);
    vector_fill(vec_n, 0, 1);
    vector_fill(vec_n, 1, 2);
    double norm = vector_norm(vec_n);
    printf("Norm: %lf\n", norm);
    vec_array_free(vec_arr);

    //vec_array_allocate(vec_arr, 10);


    return 0;
}

error_t vector_allocate(vector_t *vec, long dim){
    // Allocates memory for a vector_t with the size of dim if the vector isn't allocated yet
    if(vec->values == NULL){
        vec->values = calloc(dim, sizeof(long));
        vec->dim = dim;
        return SUCCESS;
    }
    else{
        return ALLOC_FAILURE_ERROR;
    }
}

error_t vector_clear(vector_t *vec){
    // Clears the Values and dim of a vector_t
    if (vec->values != NULL){
        free(vec->values);
        vec->values = NULL;
        vec->dim = 0;
        return SUCCESS;
    }
    else{
        return NULL_POINTER_ERROR;
    }
}

error_t vector_fill(vector_t *vec, long index, long value){
    // Fills in a value at an certain index into a vector_t->values if index and vector_t are valid
    if (index >= 0 && index < vec->dim){
        if (vec == NULL){
            return NULL_POINTER_ERROR;
        }
        else{
            vec->values[index] = value;
            return SUCCESS;
        }
    }
    else{
        return OUT_OF_RANGE_ERROR;
    }
}

error_t vector_print(vector_t *vec){
    // if the vector_t is allocated print out all values
    if (vec != NULL && vec->values != NULL){
        printf("[");
        for (int i=0; i<vec->dim; i++){
            printf("%ld", vec->values[i]);
            if (i != vec->dim-1){
                printf(", ");
            }
        }
        printf("]\n");
        return SUCCESS;
    }
    else return NULL_POINTER_ERROR;
}

error_t vector_change_dim(vector_t *vec, long new_dim){
    // Changes the dim of a vector_t and allocates the new values
    if (vec->values != NULL){
        if (new_dim >= 0){
            vec->values = realloc(vec->values, new_dim*sizeof(long));
            if (new_dim > vec->dim){
                for (long i=0; i< (new_dim-vec->dim);i++){
                    free(vec->values[vec->dim + i]);
                }
            }
            vec->dim = new_dim;
            return SUCCESS;
        }
        else return OUT_OF_RANGE_ERROR;
    }
    else return NULL_POINTER_ERROR;
}

error_t vector_add(vector_t *vec_a, vector_t *vec_b, vector_t *vec_sum){
    // adds two vector_t value fields together in a third vector_t, if vec_a and vec_b are valid
    if (vec_a->values != NULL && vec_b->values != NULL){
        if (vec_a->dim == vec_b->dim){
            for(int i=0; i<vec_a->dim; i++){
                vec_sum->values[i] = vec_a->values[i] + vec_b->values[i];
            }
            return SUCCESS;
        }
        else return DIMENSION_MISMATCH_ERROR;
    }
    else return NULL_POINTER_ERROR;
}

error_t vector_slice(vector_t *vec, long index_a, long index_b){
    // Removes Values between the index a and b and changes the dim of vector_t
    if (vec->values == NULL){
        return NULL_POINTER_ERROR;
    }
    else{
        if(index_a<0 || index_b<0 || index_a > index_b || index_b>vec->dim){
            return OUT_OF_RANGE_ERROR;
        }
        else{
            long ind_diff = index_b-index_a;
            for(long i=0; i<ind_diff; i++){
                vec->values[i] = vec->values[index_a + i];
            }
            vector_change_dim(vec, ind_diff);
            return SUCCESS;
        }
    }
}

vector_t *vector_allocate_dynamic(long dim){
    // Returns a pointer to an allocated memory for a vector_t
    vector_t *vec_p = malloc(sizeof(vector_t));
    vec_p->values = calloc(dim, sizeof(long));
    vec_p->dim = dim;
    return vec_p;
}

error_t vector_free(vector_t *vec){
    // Frees the allocated memory of a *vector_t
    if (vec != NULL && vec->values != NULL){
        free(vec->values);
        free(vec);
        vec = NULL;
        return SUCCESS;
    }
    else return NULL_POINTER_ERROR;
}

vec_array_t *vec_array_allocate(long lenght){
    // Allocates Memory for an array of "lenght" * vector_t and allocates each vector_t with dim 0
    vec_array_t *vec_p = malloc(sizeof(vec_array_t));
    vec_p->vectors = calloc(lenght, sizeof(vector_t));
    vec_p->lenght = lenght;
    for(long i=0; i<lenght; i++){
        vec_p->vectors[i] = vector_allocate_dynamic(0);
    }
    return vec_p;
}

error_t vec_array_free(vec_array_t *array){
    // Frees the Memory for all vector_t in the array and the array iteslf
    if (array != NULL){
        if (array->vectors != NULL){
            for (long i=0; i < array->lenght; i++){
                vector_free(array->vectors[i]);
            }
            free(array->vectors);
            free(array);
            return SUCCESS;
        }
        else return NULL_POINTER_ERROR;
    }
    else return NULL_POINTER_ERROR;
}

error_t vec_array_store(vec_array_t *array, vector_t *vec){
    // Stores an vector_t in the next free spot in the array and allocates more memory if all slots are full
    if(array != NULL && array->vectors != NULL && vec != NULL && vec->values != NULL){
        for(long i=0; i < array->lenght; i++){
            if(array->vectors[i]->dim == 0){
                vector_free(array->vectors[i]);
                array->vectors[i] = vec;
                return SUCCESS;
            }
        }
        array->vectors = realloc(array->vectors, (array->lenght+1)*sizeof(vector_t));
        array->lenght = array->lenght + 1;
        array->vectors[array->lenght] = vec;
        return SUCCESS;
    }
    else return NULL_POINTER_ERROR;
}

error_t vec_array_delete_at(vec_array_t *array, long index){
    //Deletes 1 vector_t in the array at an index
    //Immer noch iwo ein leak, wtf C
    if(array != NULL && array->vectors != NULL){
        if(index >= 0 && index < array->lenght){
            for(long i=index; i<array->lenght-1;i++){
                array->vectors[i] = array->vectors[i+1];
            }
        }
        else return OUT_OF_RANGE_ERROR;

        array->vectors = realloc(array->vectors, (array->lenght-1)*sizeof(vector_t));
        array->lenght = array->lenght-1;
        return SUCCESS;
    }
    else return NULL_POINTER_ERROR;
}

error_t vec_array_save(vec_array_t *array, char *file_name){
    // Saves the Array in a file and writes an x when the vector is empty
    // Leaks in der funk
    FILE *fp = fopen(file_name, "w");
    if(fp != NULL){
        for (long i=0; i<array->lenght; i++){
            if(array->vectors[i]->dim == 0){
                fprintf(fp, "x\n");
            }
            else{
                for(long j=0; j<array->vectors[i]->dim; j++){
                    fprintf(fp, "%ld", array->vectors[i]->values[j]);
                    if(j != array->vectors[i]->dim-1){
                        fprintf(fp, ",");
                    }
                    else{
                        fprintf(fp, "\n");
                    }
                }
            }
        }
        fclose(fp);
        return SUCCESS;
    }
    else return NULL_POINTER_ERROR;
}

vec_array_t *vec_array_load(char *file_name){
    // Returns a pointer to a vec_array_t that is filled with the vectors saved in the file
    //halbwegs fertig
    vec_array_t *vec_array = vec_array_allocate(0);
    FILE *fp = fopen(file_name, "r");
    if (fp != NULL){
        while(fp != NULL){
            while(1){
                long temp = 0;
                fscanf(fp, "%ld", temp);
                if(fgetc(fp) == '\n'){
                    break;
                }
            }
        }
        fclose(fp);
        return vec_array;
    }
    else printf("Error bei dem file!\n");
}

double vector_norm(vector_t *vec){
    // Returns a double thats the norm of the values of vector_t
    if (vec != NULL && vec->values != NULL){
    double norm=0;
    for(long i=0; i<vec->dim; i++){
        norm += pow(vec->values[i], 2);
    }
    norm = sqrt(norm);
    return norm;
    }
    else{
        printf("Vector nicht alloziert!\n");
        return 0;
    }
}

error_t vec_array_sort(vec_array_t *array, measure_f sort_key){
    // Sorts an array from lowest to highest for the sort_key function
    vector_t *vec_temp = NULL;
    if (array != NULL && array->vectors != NULL){
        for(long i=0; i<array->lenght; i++){
            for(long j=1; j<array->lenght; j++){
                if(sort_key(array->vectors[i]) < sort_key(array->vectors[i+j])){
                    vec_temp = array->vectors[i];
                    array->vectors[i] = array->vectors[i+j];
                    array->vectors[i+j] = vec_temp;
                    //free vec_temp ??
                }
            }
        }
        return SUCCESS;
    }
    else return NULL_POINTER_ERROR;
}
