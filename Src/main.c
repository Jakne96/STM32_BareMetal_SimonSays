#include "stm32f4xx.h"
#include <stdio.h>
#include <stdlib.h>

#define DELAY_COUNT    ( 830000 )   /* delay count */

void gpio_init(){
	  //Clock enable
	  SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOCEN);

	  //GPIO setup
	  GPIOC->MODER &= ~((0x3 << 0*2 )|
	  (0x3 << 1*2) |
	  (0x3 << 2*2) |
	  (0x3 << 3*2) |
	  (0x3 << 4*2) |
	  (0x3 << 5*2) |
	  (0x3 << 6*2) |
	  (0x3 << 7*2));
	  GPIOC->MODER |= (0x0 << 0*2 )|
	  (0x0 << 1*2) |
	  (0x0 << 2*2) |
	  (0x0 << 3*2) |
	  (0x1 << 4*2) |
	  (0x1 << 5*2) |
	  (0x1 << 6*2) |
	  (0x1 << 7*2);
	  //Pull-up configuration
	  GPIOC->PUPDR &= ~((0x3 << 0*2)|
	  (0x3 << 1*2) |
	  (0x3 << 2*2) |
	  (0x3 << 3*2));
	  GPIOC->PUPDR |= (0x1 << 0*2)|
	  (0x1 << 1*2) |
	  (0x1 << 2*2) |
	  (0x1 << 3*2);
}

static void delay( void ) //primitive delay for demonstration purposes only, TODO: prepare a timer based solution
{
    volatile uint32_t i = 0;
     for( i=0; i<=DELAY_COUNT; i++ );
}

//matrices to store sequence for repetition
uint8_t steps[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint8_t check_matrix[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

uint8_t number_of_steps = 3;
uint8_t play_count = 0;

void game_reset(){
	number_of_steps = 3;
}

//increases number of steps to repeat each level
void advance_level(){
	number_of_steps++;
}


void led_light(uint8_t led_number){
	GPIOC->ODR |= (0x1 << (led_number + 3));
}

void led_reset(){
	GPIOC->ODR &= ~((0x1 << 4) |
	(0x1 << 5) |
	(0x1 << 6) |
	(0x1 << 7));
}

void welcome_led_display(){
	for(uint8_t light_repetition = 0; light_repetition< 3; light_repetition++){
  	led_light(1);
  	led_light(2);
  	led_light(3);
  	led_light(4);
  	delay();
  	led_reset();
  	delay();
  	  }
}

void lose_led_display(){
	led_reset();
	led_light(1);
	delay();
	led_light(2);
	delay();
	led_light(3);
	delay();
	led_light(4);
	delay();
	led_reset();
	delay();
}

void correct_led_display(){
	if(play_count == number_of_steps){
		  for(int k = 0; k< 3; k++){
			  led_light(1);
			  led_light(3);
			  delay();
			  led_reset();
			  led_light(2);
			  led_light(4);
			  delay();
		      led_reset(); //turn off LEDs on PC4-7;
		}
	 		  delay();
	}
}

void win_led_display(){
	for(int r = 0; r < 4; r++){
	  led_reset();
	  led_light(1);
	  led_light(2);
	  delay();
	  led_reset();
	  led_light(3);
	  led_light(4);
	  delay();
	}
	  led_light(1);
	  led_light(2);
	  led_light(3);
	  led_light(4);
	  delay();
	  led_reset();
	  delay();
}


void sequence_randomization(){
	for(int step = 0; step < number_of_steps; step++){
		    steps[step] = (rand() % 4) + 1;
	}
}

void sequence_display(){
	for (int show = 0; show < number_of_steps; show++)
	  {
		  led_light(steps[show]);
		  delay();
		  led_reset();
		  delay();
	  }
}

void checking_win_condition(){
	if(number_of_steps > 5){
		  win_led_display();
		  number_of_steps = 4;
		  welcome_led_display();
	  }
}

uint8_t read_button(){
	uint32_t input = (GPIOC->IDR & 0x0000000F);

	if(input == 0x0000000E) return 1;
	if(input == 0x0000000D) return 2;
	if(input == 0x0000000B) return 3;
	if(input == 0x00000007) return 4;

return 0;

}

void waiting_for_input(){
	uint8_t button = 0;

	while(button == 0){
		button = read_button();
		check_matrix[play_count] = button;
	}
}

int main(void)
{
	gpio_init();
    welcome_led_display();

  /* Game loop */
  while(1)
  {
	  advance_level();
	  checking_win_condition();
	  sequence_randomization();
	  sequence_display();
	  play_count = 0; //number of repeated steps

	  while(play_count != number_of_steps){

		  waiting_for_input();
		  if(check_matrix[play_count] == steps[play_count]){
	  				  led_light(steps[play_count]);
	  				  delay();
	  				  led_reset();
	  				  delay();
	  				  play_count++;
	  			  } else {
	  				  lose_led_display();
	  				  game_reset();
	  				  break;
		  			  }
		  			  if(play_count == number_of_steps){
		  			  correct_led_display();
		    }
	  }

  }
  }

