 /*
  *   * Copyright (C) 2017 Eistec AB
  *     *
  *       * This file is subject to the terms and conditions of the GNU Lesser General
  *         * Public License v2.1. See the file LICENSE in the top level directory for more
  *           * details.
  *             */
 
 #ifndef VECTORS_KINETIS_H
 #define VECTORS_KINETIS_H
 
 #include <stdint.h>
 #include "vectors_cortexm.h"
 
 #ifdef __cplusplus
 extern "C" {
      #endif
      
      void dummy_handler(void);
       
       /* Kinetis specific interrupt vectors */
       void isr_adc0(void);         
        void isr_adc1(void);         
         void isr_adc2(void);         
          void isr_can0_bus_off(void); 
           void isr_can0_error(void);   
            void isr_can0_ored_message_buffer(void); 
             void isr_can0_rx_warning(void); 
              void isr_can0_tx_warning(void); 
               void isr_can0_wake_up(void); 
                void isr_can1_bus_off(void); 
                 void isr_can1_error(void);   
                  void isr_can1_ored_message_buffer(void); 
                   void isr_can1_rx_warning(void); 
                    void isr_can1_tx_warning(void); 
                     void isr_can1_wake_up(void); 
                      void isr_cmp0(void);         
                       void isr_cmp1(void);         
                        void isr_cmp2(void);         
                         void isr_cmp3(void);         
                          void isr_cmt(void);          
                           void isr_dac0(void);         
                            void isr_dac1(void);         
                             void isr_dma0(void);         
                              void isr_dma1(void);         
                               void isr_dma2(void);         
                                void isr_dma3(void);         
                                 void isr_dma4(void);         
                                  void isr_dma5(void);         
                                   void isr_dma6(void);         
                                    void isr_dma7(void);         
                                     void isr_dma8(void);         
                                      void isr_dma9(void);         
                                       void isr_dma10(void);        
                                        void isr_dma11(void);        
                                         void isr_dma12(void);        
                                          void isr_dma13(void);        
                                           void isr_dma14(void);        
                                            void isr_dma15(void);        
                                             void isr_dma0_dma16(void);   
                                              void isr_dma1_dma17(void);   
                                               void isr_dma2_dma18(void);   
                                                void isr_dma3_dma19(void);   
                                                 void isr_dma4_dma20(void);   
                                                  void isr_dma5_dma21(void);   
                                                   void isr_dma6_dma22(void);   
                                                    void isr_dma7_dma23(void);   
                                                     void isr_dma8_dma24(void);   
                                                      void isr_dma9_dma25(void);   
                                                       void isr_dma10_dma26(void);  
                                                        void isr_dma11_dma27(void);  
                                                         void isr_dma12_dma28(void);  
                                                          void isr_dma13_dma29(void);  
                                                           void isr_dma14_dma30(void);  
                                                            void isr_dma15_dma31(void);  
                                                             void isr_dma_error(void);    
                                                              void isr_enet_1588_timer(void); 
                                                               void isr_enet_error(void);   
                                                                void isr_enet_receive(void); 
                                                                 void isr_enet_transmit(void); 
                                                                  void isr_ftfa(void);         
                                                                   void isr_ftfa_collision(void); 
                                                                    void isr_ftfe(void);         
                                                                     void isr_ftfe_collision(void); 
                                                                      void isr_ftfl(void);         
                                                                       void isr_ftfl_collision(void); 
                                                                        void isr_ftm0(void);         
                                                                         void isr_ftm1(void);         
                                                                          void isr_ftm2(void);         
                                                                           void isr_ftm3(void);         
                                                                            void isr_i2c0(void);         
                                                                             void isr_i2c1(void);         
                                                                              void isr_i2c2(void);         
                                                                               void isr_i2c3(void);         
                                                                                void isr_i2s0_rx(void);      
                                                                                 void isr_i2s0_tx(void);      
                                                                                  void isr_llwu(void);         
                                                                                   void isr_lptmr0(void);       
                                                                                    void isr_lpuart0(void);      
                                                                                     void isr_lpuart1(void);      
                                                                                      void isr_lpuart2(void);      
                                                                                       void isr_lpuart3(void);      
                                                                                        void isr_lpuart4(void);      
                                                                                         void isr_lpuart5(void);      
                                                                                          void isr_lvd_lvw(void);      
                                                                                           void isr_mcg(void);          
                                                                                            void isr_mcm(void);          
                                                                                             void isr_pdb0(void);         
                                                                                              void isr_pit0(void);         
                                                                                               void isr_pit1(void);         
                                                                                                void isr_pit2(void);         
                                                                                                 void isr_pit3(void);         
                                                                                                  void isr_porta(void);        
                                                                                                   void isr_portb(void);        
                                                                                                    void isr_portc(void);        
                                                                                                     void isr_portd(void);        
                                                                                                      void isr_porte(void);        
                                                                                                       void isr_rng(void);          
                                                                                                        void isr_rtc(void);          
                                                                                                         void isr_rtc_seconds(void);  
                                                                                                          void isr_sdhc(void);         
                                                                                                           void isr_spi0(void);         
                                                                                                            void isr_spi1(void);         
                                                                                                             void isr_spi2(void);         
                                                                                                              void isr_swi(void);          
                                                                                                               void isr_tpm0(void);         
                                                                                                                void isr_tpm1(void);         
                                                                                                                 void isr_tpm2(void);         
                                                                                                                  void isr_tsi0(void);         
                                                                                                                   void isr_uart0_err(void);    
                                                                                                                    void isr_uart0_lon(void);    
                                                                                                                     void isr_uart0_rx_tx(void);  
                                                                                                                      void isr_uart1_err(void);    
                                                                                                                       void isr_uart1_rx_tx(void);  
                                                                                                                        void isr_uart2_err(void);    
                                                                                                                         void isr_uart2_rx_tx(void);  
                                                                                                                          void isr_uart3_err(void);    
                                                                                                                           void isr_uart3_rx_tx(void);  
                                                                                                                            void isr_uart4_err(void);    
                                                                                                                             void isr_uart4_rx_tx(void);  
                                                                                                                              void isr_uart5_err(void);    
                                                                                                                               void isr_uart5_rx_tx(void);  
                                                                                                                                void isr_usb0(void);         
                                                                                                                                 void isr_usbdcd(void);       
                                                                                                                                  void isr_wdog_ewm(void);     
                                                                                                                                   #ifdef __cplusplus
                                                                                                                                   } /* extern "C" */
 #endif
 
 #endif /* VECTORS_KINETIS_H */
