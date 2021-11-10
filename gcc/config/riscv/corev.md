;; Machine description for CORE-V operations.
;; Copyright (C) 2011-2020 Free Software Foundation, Inc.
;; Contributed by Nazareno Bruschi (nazareno.bruschi@embecosm.com)
;; and Enrico Tabanelli (enrico.tabanelli@embecosm.com).
;; Based on MIPS target for GNU compiler.

;; This file is part of GCC.

;; GCC is free software; you can redistribute it and/or modify
;; it under the terms of the GNU General Public License as published by
;; the Free Software Foundation; either version 3, or (at your option)
;; any later version.

;; GCC is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.

;; You should have received a copy of the GNU General Public License
;; along with GCC; see the file COPYING3.  If not see
;; <http://www.gnu.org/licenses/>.

;;
;;  ....................
;;
;;      CORE-V MEM INSN
;;
;;  ....................

(define_mode_attr length_size [(SI "4") (HI "2") (QI "1")])

(define_insn "cv_load<mode>_postinc"
  [(set (match_operand:ANYI 0 "register_operand" "=r")
        (mem:ANYI (post_inc:SI (match_operand:SI 1 "register_operand" "+r")))
   )
  ]
  "TARGET_COREV_MEM"
  "cv.<load> %0, <length_size>(%1!)"
  [(set_attr "type" "load")
   (set_attr "mode" "<MODE>")]
)

(define_insn "cv_load<mode>_<u>ext_postinc"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (any_extend:SI
             (mem:ANYI (post_inc:SI (match_operand:SI 1 "register_operand" "+r")))
        )
   )
  ]
  "TARGET_COREV_MEM"
  "cv.<load><u> %0, <length_size>(%1!)"
  [(set_attr "type" "load")
   (set_attr "mode" "<MODE>")]
)

(define_insn "cv_load<mode>_postdec"
  [(set (match_operand:ANYI 0 "register_operand" "=r")
        (mem:ANYI (post_dec:SI (match_operand:SI 1 "register_operand" "+r")))
   )
  ]
  "TARGET_COREV_MEM"
  "cv.<load> %0, -<length_size>(%1!)"
  [(set_attr "type" "load")
   (set_attr "mode" "<MODE>")]
)

(define_insn "cv_load<mode>_<u>ext_postdec"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (any_extend:SI
             (mem:ANYI (post_dec:SI (match_operand:SI 1 "register_operand" "+r")))
        )
   )
  ]
  "TARGET_COREV_MEM"
  "cv.<load><u> %0, -<length_size>(%1!)"
  [(set_attr "type" "load")
   (set_attr "mode" "<MODE>")]
)

(define_insn "cv_load<mode>_postmod_disp"
  [(set (match_operand:ANYI 0 "register_operand" "=r,r")
        (mem:ANYI (post_modify:SI (match_operand:SI 1 "register_operand" "+r,r")
                                     (plus:SI (match_dup 1) (match_operand:SI 2 "nonmemory_operand" "r,I"))))
   )
  ]
  "TARGET_COREV_MEM"
  "cv.<load> %0, %2(%1!)"
  [(set_attr "type" "load,load")
   (set_attr "mode" "<MODE>")]
)

(define_insn "cv_load<mode>_<u>ext_postmod_disp"
  [(set (match_operand:SI 0 "register_operand" "=r,r")
        (any_extend:SI
                    (mem:ANYI (post_modify:SI (match_operand:SI 1 "register_operand" "+r,r")
                                                 (plus:SI (match_dup 1) (match_operand:SI 2 "nonmemory_operand" "r,I"))))
        )
   )
  ]
  "TARGET_COREV_MEM"
  "cv.<load><u> %0, %2(%1!)"
  [(set_attr "type" "load,load")
   (set_attr "mode" "<MODE>")]
)

(define_insn "cv_load<mode>_postmod_reg"
  [(set (match_operand:ANYI 0 "register_operand" "=r")
        (mem:ANYI (plus:SI (match_operand:SI 1 "register_operand" "r")
                              (match_operand:SI 2 "register_operand" "r")))
   )
  ]
  "TARGET_COREV_MEM"
  "cv.<load> %0, %2(%1)"
  [(set_attr "type" "load")
   (set_attr "mode" "<MODE>")]
)

(define_insn "cv_load<mode>_<u>ext_postmod_reg"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (any_extend: SI (mem:ANYI (plus:SI (match_operand:SI 1 "register_operand" "r")
                                     (match_operand:SI 2 "register_operand" "r"))))
   )
  ]
  "TARGET_COREV_MEM"
  "cv.<load><u> %0, %2(%1)"
  [(set_attr "type" "load")
   (set_attr "mode" "<MODE>")]
)

(define_insn "cv_store<mode>_postinc"
  [(set (mem:ANYI (post_inc:SI (match_operand:SI 0 "register_operand" "+r,r")))
	(match_operand:ANYI 1 "nonmemory_operand" "r,J")
   )
  ]
  "TARGET_COREV_MEM"
  "@
   cv.<store> %1, <length_size>(%0!)
   cv.<store> x0, <length_size>(%0!)"
  [(set_attr "type" "store,store")
   (set_attr "mode" "<MODE>")]
)

(define_insn "cv_store<mode>_postdec"
  [(set (mem:ANYI (post_dec:SI (match_operand:SI 0 "register_operand" "+r,r")))
        (match_operand:ANYI 1 "nonmemory_operand" "r,J")
   )
  ]
  "TARGET_COREV_MEM"
  "@
   cv.<store> %1, -<length_size>(%0!)
   cv.<store> x0, -<length_size>(%0!)"
  [(set_attr "type" "store,store")
   (set_attr "mode" "<MODE>")]
)

(define_insn "cv_store<mode>_postmod_disp"
  [(set (mem:ANYI (post_modify:SI (match_operand:SI 0 "register_operand" "+r,r,r,r")
                                     (plus:SI (match_dup 0) (match_operand:SI 2 "nonmemory_operand" "r,r,I,I"))))
        (match_operand:ANYI 1 "nonmemory_operand" "r,J,r,J")
   )
  ]
  "TARGET_COREV_MEM"
  "@
   cv.<store> %1, %2(%0!)
   cv.<store> x0, %2(%0!)
   cv.<store> %1, %2(%0!)
   cv.<store> x0, %2(%0!)"
  [(set_attr "type" "store,store,store,store")
   (set_attr "mode" "<MODE>")]
)

(define_insn "cv_store<mode>_postmod_reg"
  [(set (mem:ANYI (plus:SI (match_operand:SI 0 "register_operand" "r,r")
                              (match_operand:SI 1 "register_operand" "r,r")))
        (match_operand:ANYI 2 "nonmemory_operand" "r,J")
   )
  ]
  "TARGET_COREV_MEM"
  "@
   cv.<store> %2, %1(%0)
   cv.<store> x0, %1(%0)"
  [(set_attr "type" "store,store")
   (set_attr "mode" "<MODE>")]
)
