#ifndef _LINIOWIR_H_
#define _LINIOWIR_H_

void liniowir_set_enabled(bool enabled);

bool liniowir_get_enabled(void);


void liniowir_set_forward_speed(float speed);

float liniowir_get_forward_speed(void);


void liniowir_set_centering_speed(float speed);

float liniowir_get_centering_speed(void);


void liniowir_set_rotation_kp(float kp);

float liniowir_get_rotation_kp(void);

#endif // _LINIOWIR_H_
