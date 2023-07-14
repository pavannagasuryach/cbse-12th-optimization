#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#define LCD_RS_PIN   PB0   // LCD Register Select (RS) pin
#define LCD_EN_PIN   PB1   // LCD Enable (EN) pin
#define LCD_DATA_PIN PB4   // LCD data pins (DB4-DB7) connected to PB4-PB7

#define MEM_ADDR_1   0x2001  // Memory location 2001H
#define MEM_ADDR_2   0x2002  // Memory location 2002H
#define MEM_ADDR_3   0x2003  // Memory location 2003H

// Function prototypes
void lcd_init(void);
void lcd_command(uint8_t cmd);
void lcd_data(uint8_t data);
void lcd_string(const char *str);

int main(void) {
    uint8_t result;

    // LCD initialization
    lcd_init();

    // Load the value of memory location 2001H into register pair H-L
    asm volatile("ldi r26, lo8(MEM_ADDR_1)");
    asm volatile("ldi r27, hi8(MEM_ADDR_1)");
    asm volatile("ld r24, Z");

    // Load the immediate value 0x21 into register A
    asm volatile("ldi r22, 0x21");

    // Increment register pair H-L to point to memory location 2002H
    asm volatile("adiw r26, 0x0001");

    // Add the value at memory location 2002H to register A
    asm volatile("ld r23, Z");
    asm volatile("add r22, r23");

    // Increment register pair H-L to point to memory location 2003H
    asm volatile("adiw r26, 0x0001");

    // Store the result in register A into memory location 2003H
    asm volatile("st Z, r22");

    // Load the result from memory location 2003H into the result variable
    asm volatile("ldi r26, lo8(MEM_ADDR_3)");
    asm volatile("ldi r27, hi8(MEM_ADDR_3)");
    asm volatile("ld r24, Z");
    asm volatile("mov %0, r24" : "=r" (result));

    // Display the result on the LCD
    lcd_command(0x80);  // Set cursor to the beginning of the first line
    lcd_string("Result: ");
    lcd_data(result + '0');  // Convert the result to character and display it

    // Infinite loop
    while (1) {
        // Add any additional code here if required
    }
}

void lcd_init(void) {
    // Initialize LCD interface
    DDRB |= (1 << LCD_RS_PIN) | (1 << LCD_EN_PIN) | 0xF0;
    _delay_ms(20);

    // Send initialization commands
    lcd_command(0x02);  // Return home
    lcd_command(0x28);  // 4-bit mode, 2-line display
    lcd_command(0x06);  // Entry mode: increment cursor, no shift
    lcd_command(0x0C);  // Display on, cursor off, blink off
    lcd_command(0x01);  // Clear display
    _delay_ms(2);
}

void lcd_command(uint8_t cmd) {
    PORTB &= ~(1 << LCD_RS_PIN);   // Set RS pin low for command mode
    PORTB &= ~(1 << LCD_EN_PIN);   // Set EN pin low
    _delay_us(1);
    PORTB = (cmd & 0xF0) | (PORTB & 0x0F);  // Send upper nibble
    PORTB |= (1 << LCD_EN_PIN);    // Set EN pin high
    _delay_us(1);
    PORTB &= ~(1 << LCD_EN_PIN);   // Set EN pin low

    _delay_us(100);

    PORTB &= ~(1 << LCD_RS_PIN);   // Set RS pin low for command mode
    PORTB &= ~(1 << LCD_EN_PIN);   // Set EN pin low
    _delay_us(1);
    PORTB = ((cmd & 0x0F) << 4) | (PORTB & 0x0F);  // Send lower nibble
    PORTB |= (1 << LCD_EN_PIN);    // Set EN pin high
    _delay_us(1);
    PORTB &= ~(1 << LCD_EN_PIN);   // Set EN pin low

    _delay_us(200);
}

void lcd_data(uint8_t data) {
    PORTB |= (1 << LCD_RS_PIN);    // Set RS pin high for data mode
    PORTB &= ~(1 << LCD_EN_PIN);   // Set EN pin low
    _delay_us(1);
    PORTB = (data & 0xF0) | (PORTB & 0x0F);  // Send upper nibble
    PORTB |= (1 << LCD_EN_PIN);    // Set EN pin high
    _delay_us(1);
    PORTB &= ~(1 << LCD_EN_PIN);   // Set EN pin low

    _delay_us(100);

    PORTB |= (1 << LCD_RS_PIN);    // Set RS pin high for data mode
    PORTB &= ~(1 << LCD_EN_PIN);   // Set EN pin low
    _delay_us(1);
    PORTB = ((data & 0x0F) << 4) | (PORTB & 0x0F);  // Send lower nibble
    PORTB |= (1 << LCD_EN_PIN);    // Set EN pin high
    _delay_us(1);
    PORTB &= ~(1 << LCD_EN_PIN);   // Set EN pin low

    _delay_us(200);
}

void lcd_string(const char *str) {
    while (*str) {
        lcd_data(*str++);
    }
}
