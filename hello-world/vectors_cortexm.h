/*
 *   * Copyright (C) 2015 Freie Universität Berlin
 *     *
 *       * This file is subject to the terms and conditions of the GNU Lesser
 *         * General Public License v2.1. See the file LICENSE in the top level
 *           * directory for more details.
 *             */
 
 #ifndef VECTORS_CORTEXM_H
 #define VECTORS_CORTEXM_H
 
 #ifdef __cplusplus
 extern "C" {
      #endif
      
      #include "cpu_conf.h"
      
      #define WEAK_DEFAULT    __attribute__((weak,alias("dummy_handler")))
      
      #define ISR_VECTOR(x)   __attribute__((used,section(".vectors." # x )))
      
      #define CPU_NONISR_EXCEPTIONS   (15)
      
      typedef void (*isr_t)(void);
       
       typedef struct {
                void* _estack;                          
                     isr_t vectors[CPU_NONISR_EXCEPTIONS];   
                      } cortexm_base_t;
        
        void reset_handler_default(void);
         
         void nmi_default(void);
          
          void hard_fault_default(void);
           
           /* The following four exceptions are only present for Cortex-M3 and -M4 CPUs */
           #if defined(CPU_ARCH_CORTEX_M3) || defined(CPU_ARCH_CORTEX_M4) || \
               defined(CPU_ARCH_CORTEX_M4F) || defined(CPU_ARCH_CORTEX_M7)
           
           void mem_manage_default(void);
            
            void bus_fault_default(void);
             
             void usage_fault_default(void);
              
              void debug_mon_default(void);
               #endif
               
               void dummy_handler_default(void);
                
                #ifdef __cplusplus
                }
 #endif
 
 #endif /* VECTORS_CORTEXM_H */
