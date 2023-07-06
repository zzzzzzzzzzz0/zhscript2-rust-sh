use std::mem;

pub type Ptr_ = *const fn();

pub fn call__(p:Ptr_, args2: &Vec<usize>, fargs2: &Vec<f64>,
		ret_low: &mut usize, ret_high: &mut usize, ret_float: &mut f64) {
	//z1__(p, args2, fargs2, ret_low, ret_high, ret_float);
	match args2.len() {
		//4|
		//5|
		//6 => {}
		_ => z2a__(p, args2, fargs2, ret_low, ret_high, ret_float),
	}
	//z3__(p, args2, fargs2, ret_low, ret_high, ret_float);
	/*match args2.len() {
		_ => z4__(p, args2, fargs2, ret_low, ret_high, ret_float),
		_ => {}
	}*/
}

fn z4__(p:Ptr_, args2: &Vec<usize>, fargs2: &Vec<f64>, ret_low: &mut usize, ret_high: &mut usize, ret_float: &mut f64) {
	println!("call__z4__ {} {}", args2.len(), fargs2.len());

	let args = args2.as_ptr().wrapping_offset(args2.len() as isize - 1);
	let len = args2.len();
	let fargs = fargs2.as_ptr().wrapping_offset(fargs2.len() as isize - 1);
	let flen = fargs2.len();
	let lo:u64;
	let hi:u64;
	unsafe {
		llvm_asm!("
			lea    rdi, [rip + lfs]
			movsxd rsi, dword ptr [rdi + $7 * 4]
			add    rsi, rdi
			jmp    rsi
			lfs:
			.long lf0 - lfs
			.long lf1 - lfs
			.long lf2 - lfs
			.long lf3 - lfs
			.long lf4 - lfs
			.long lf5 - lfs
			.long lf6 - lfs
			.long lf7 - lfs
			.long lf8 - lfs
			lf8:
			movsd xmm7, qword ptr [$6]
			sub   $6, 8
			lf7:
			movsd xmm6, qword ptr [$6]
			sub   $6, 8
			lf6:
			movsd xmm5, qword ptr [$6]
			sub   $6, 8
			lf5:
			movsd xmm4, qword ptr [$6]
			sub   $6, 8
			lf4:
			movsd xmm3, qword ptr [$6]
			sub   $6, 8
			lf3:
			movsd xmm2, qword ptr [$6]
			sub   $6, 8
			lf2:
			movsd xmm1, qword ptr [$6]
			sub   $6, 8
			lf1:
			movsd xmm0, qword ptr [$6]
			lf0:
			lea    r12, [$5 - 6]
			cmp    $5, 6
			mov    rdi, 0
			cmovbe r12, rdi
			jbe    lp6
			test   r12, 1
			je     lp
			sub    rsp, 8
			lp:
			push   qword ptr [$4]
			sub    $4, 8
			sub    $5, 1
			cmp    $5, 6
			jne    lp
			lp6:
			lea    rdi, [rip + ls]
			movsxd rsi, dword ptr [rdi + $5 * 4]
			add    rsi, rdi
			jmp    rsi
			ls:
			.long l0 - ls
			.long l1 - ls
			.long l2 - ls
			.long l3 - ls
			.long l4 - ls
			.long l5 - ls
			.long l6 - ls
			l6:
			mov r9, qword ptr [$4]
			sub $4, 8
			l5:
			mov r8, qword ptr [$4]
			sub $4, 8
			l4:
			mov rcx, qword ptr [$4]
			sub $4, 8
			l3:
			mov rdx, qword ptr [$4]
			sub $4, 8
			l2:
			mov rsi, qword ptr [$4]
			sub $4, 8
			l1:
			mov rdi, qword ptr [$4]
			l0:
			mov  rax, $7
			call $3
			lea  rsp, [rsp + r12 * 8]
			test r12, 1
			je   lna
			add  rsp, 8
			lna:
		"
		: "={ax}"(lo), "={dx}"(hi), "={xmm0}"(*ret_float)
		: "{r13}"(p), "{r14}"(args), "{r15}"(len), "{r10}"(fargs), "{r11}"(flen)
		: "memory", "rsp"
		: "volatile", "alignstack", "intel"
		);
	}
	*ret_low  = lo as usize;
	*ret_high = hi as usize;
}

fn z3__(p:Ptr_, args2: &Vec<usize>, fargs2: &Vec<f64>, ret_low: &mut usize, ret_high: &mut usize, ret_float: &mut f64) {
	println!("call__z3__ {} {}", args2.len(), fargs2.len());
	let args = args2.as_ptr().wrapping_offset(args2.len() as isize - 1);
	let len = args2.len();
	let fargs = fargs2.as_ptr().wrapping_offset(fargs2.len() as isize - 1);
	let flen = fargs2.len();
	unsafe {
		llvm_asm!("
			lea    r12, [$3 - 6]
			cmp    $3, 6
			mov    rdi, 0
			cmovbe r12, rdi
			jbe    lp6
			test   r12, 1
			je     lp
			sub    rsp, 8
			lp:
			push   qword ptr [$2]
			sub    $2, 8
			sub    $3, 1
			cmp    $3, 6
			jne    lp
			lp6:
			lea    rdi, [rip + ls]
			movsxd rsi, dword ptr [rdi + $3 * 4]
			add    rsi, rdi
			jmp    rsi
			ls:
			.long l0 - ls
			.long l1 - ls
			.long l2 - ls
			.long l3 - ls
			.long l4 - ls
			.long l5 - ls
			.long l6 - ls
			l6:
			mov r9, qword ptr [$2]
			sub $2, 8
			l5:
			mov r8, qword ptr [$2]
			sub $2, 8
			l4:
			mov rcx, qword ptr [$2]
			sub $2, 8
			l3:
			mov rdx, qword ptr [$2]
			sub $2, 8
			l2:
			mov rsi, qword ptr [$2]
			sub $2, 8
			l1:
			mov rdi, qword ptr [$2]
			l0:
			mov  rax, $5
			call $1
			lea  rsp, [rsp + r12 * 8]
			test r12, 1
			je   lna
			add  rsp, 8
			lna:
		"
		: "={ax}"(*ret_low)
		: "{r13}"(p), "{r14}"(args), "{r15}"(len), "{r10}"(fargs), "{r11}"(flen)
		: "memory", "rsp"
		: "volatile", "alignstack", "intel"
		);
	}
}

fn z2a__(p:Ptr_, args2: &Vec<usize>, fargs2: &Vec<f64>, ret_low: &mut usize, ret_high: &mut usize, ret_float: &mut f64) {
	println!("call__z2a__ {} {}", args2.len(), fargs2.len());

	let args = args2.as_ptr().wrapping_offset(args2.len() as isize - 1);
	let len = args2.len();
	let fargs = fargs2.as_ptr().wrapping_offset(fargs2.len() as isize - 1);
	let flen = fargs2.len();
	let lo:u64;
	let hi:u64;
	let f:f64;
	unsafe {
		asm!(
			r"
			lea    rdi, [rip + lfs]
			movsxd rsi, dword ptr [rdi + r11 * 4]
			add    rsi, rdi
			jmp    rsi
			lfs:
			.long lf0 - lfs
			.long lf1 - lfs
			.long lf2 - lfs
			.long lf3 - lfs
			.long lf4 - lfs
			.long lf5 - lfs
			.long lf6 - lfs
			.long lf7 - lfs
			.long lf8 - lfs
			lf8:
			movsd xmm7, qword ptr [r10]
			sub   r10, 8
			lf7:
			movsd xmm6, qword ptr [r10]
			sub   r10, 8
			lf6:
			movsd xmm5, qword ptr [r10]
			sub   r10, 8
			lf5:
			movsd xmm4, qword ptr [r10]
			sub   r10, 8
			lf4:
			movsd xmm3, qword ptr [r10]
			sub   r10, 8
			lf3:
			movsd xmm2, qword ptr [r10]
			sub   r10, 8
			lf2:
			movsd xmm1, qword ptr [r10]
			sub   r10, 8
			lf1:
			movsd xmm0, qword ptr [r10]
			lf0:
			lea    r12, [r15 - 6]
			cmp    r15, 6
			mov    rdi, 0
			cmovbe r12, rdi
			jbe    lp6
			test   r12, 1
			je     lp
			sub    rsp, 8
			lp:
			push   qword ptr [r14]
			sub    r14, 8
			sub    r15, 1
			cmp    r15, 6
			jne    lp
			lp6:
			lea    rdi, [rip + ls]
			movsxd rsi, dword ptr [rdi + r15 * 4]
			add    rsi, rdi
			jmp    rsi
			ls:
			.long l0 - ls
			.long l1 - ls
			.long l2 - ls
			.long l3 - ls
			.long l4 - ls
			.long l5 - ls
			.long l6 - ls
			l6:
			mov  r9, qword ptr [r14]
			sub  r14, 8
			l5:
			mov  r8, qword ptr [r14]
			sub  r14, 8
			l4:
			mov  rcx, qword ptr [r14]
			sub  r14, 8
			l3:
			mov  rdx, qword ptr [r14]
			sub  r14, 8
			l2:
			mov  rsi, qword ptr [r14]
			sub  r14, 8
			l1:
			mov  rdi, qword ptr [r14]
			l0:
			mov  rax, r11
			call r13
			lea  rsp, [rsp + r12 * 8]
			test r12, 1
			je   lna
			add  rsp, 8
			lna:
			",
			in("r13") p,
			in("r14") args,
			in("r15") len,
			in("r10") fargs,
			in("r11") flen,
			lateout("rax") lo, lateout("rdx") hi, lateout("xmm0") f,
		);
	}
	*ret_low  = lo as usize;
	*ret_high = hi as usize;
	*ret_float = f;
}
fn z2__(p:Ptr_, args2: &Vec<usize>, fargs2: &Vec<f64>, ret_low: &mut usize, ret_high: &mut usize, ret_float: &mut f64) {
	let args = args2.as_ptr().wrapping_offset(args2.len() as isize - 1);
	let len = args2.len();
	let fargs = fargs2.as_ptr().wrapping_offset(fargs2.len() as isize - 1);
	let flen = fargs2.len();
	println!("call__z2__ {} {}", len, flen);

	let lo:u64;
	let hi:u64;
	let f:f64;
	unsafe {
		asm!(
			/*
			lea    rdi, [rip + lfs]
			movsxd rsi, dword ptr [rdi + {flen} * 4]
			add    rsi, rdi
			jmp    rsi
			lfs:
			.long lf0 - lfs
			.long lf1 - lfs
			.long lf2 - lfs
			.long lf3 - lfs
			.long lf4 - lfs
			.long lf5 - lfs
			.long lf6 - lfs
			.long lf7 - lfs
			.long lf8 - lfs
			lf8:
			movsd xmm7, qword ptr [{fargs}]
			sub   {fargs}, 8
			lf7:
			movsd xmm6, qword ptr [{fargs}]
			sub   {fargs}, 8
			lf6:
			movsd xmm5, qword ptr [{fargs}]
			sub   {fargs}, 8
			lf5:
			movsd xmm4, qword ptr [{fargs}]
			sub   {fargs}, 8
			lf4:
			movsd xmm3, qword ptr [{fargs}]
			sub   {fargs}, 8
			lf3:
			movsd xmm2, qword ptr [{fargs}]
			sub   {fargs}, 8
			lf2:
			movsd xmm1, qword ptr [{fargs}]
			sub   {fargs}, 8
			lf1:
			movsd xmm0, qword ptr [{fargs}]
			lf0:
			*/
			r"
			lea    r12, [{len} - 6]
			cmp    {len}, 6
			mov    rdi, 0
			cmovbe r12, rdi
			jbe    lp6
			test   r12, 1
			je     lp
			sub    rsp, 8
			lp:
			push   qword ptr [{args}]
			sub    {args}, 8
			sub    {len}, 1
			cmp    {len}, 6
			jne    lp
			lp6:
			lea    rdi, [rip + ls]
			movsxd rsi, dword ptr [rdi + {len} * 4]
			add    rsi, rdi
			jmp    rsi
			ls:
			.long l0 - ls
			.long l1 - ls
			.long l2 - ls
			.long l3 - ls
			.long l4 - ls
			.long l5 - ls
			.long l6 - ls
			l6:
			mov  r9, qword ptr [{args}]
			sub  {args}, 8
			l5:
			mov  r8, qword ptr [{args}]
			sub  {args}, 8
			l4:
			mov  rcx, qword ptr [{args}]
			sub  {args}, 8
			l3:
			mov  rdx, qword ptr [{args}]
			sub  {args}, 8
			l2:
			mov  rsi, qword ptr [{args}]
			sub  {args}, 8
			l1:
			mov  rdi, qword ptr [{args}]
			l0:
			call {}
			",
			/*

			mov  rax, {flen}

			lea  rsp, [rsp + r12 * 8]
			test r12, 1
			je   lna2
			add  rsp, 8
			lna2:
			*/
			in(reg) p,
			args = in(reg) args,
			len = in(reg) len,
			//fargs = in(reg) fargs,
			//flen = in(reg) flen,
			lateout("rax") lo, lateout("rdx") hi, lateout("xmm0") f,
			//out("rcx") _,
			//out("r10") _, out("r11") _, out("r12") _,
			//options(nomem)
		);
	}
	*ret_low  = lo as usize;
	*ret_high = hi as usize;
	*ret_float = f;
}

fn z1__(p:Ptr_, args2: &Vec<usize>, fargs2: &Vec<f64>, ret_low: &mut usize, ret_high: &mut usize, ret_float: &mut f64) {
	println!("call__z1__ {}", args2.len());
	let lo:u64;
	let hi:u64;
	let f:f64;
	loop {
		unsafe {
			if args2.len() == 0 {
				asm!("call {}", in(reg) p,
					lateout("rax") lo, lateout("rdx") hi, lateout("xmm0") f);
				break
			}
			if args2.len() == 1 {
				asm!("call {}", in(reg) p, in("rdi") args2[0],
					lateout("rax") lo, lateout("rdx") hi, lateout("xmm0") f);
				break
			}
			if args2.len() == 2 {
				asm!("call {}", in(reg) p, in("rdi") args2[0], in("rsi") args2[1],
					lateout("rax") lo, lateout("rdx") hi, lateout("xmm0") f);
				break
			}
			if args2.len() == 3 {
				asm!("call {}", in(reg) p, in("rdi") args2[0], in("rsi") args2[1], in("rdx") args2[2],
					lateout("rax") lo, lateout("rdx") hi, lateout("xmm0") f);
				break
			}
			if args2.len() == 4 {
				asm!("call {}", in(reg) p, in("rdi") args2[0], in("rsi") args2[1], in("rdx") args2[2], in("rcx") args2[3],
					lateout("rax") lo, lateout("rdx") hi, lateout("xmm0") f);
				break
			}
			if args2.len() == 5 {
				asm!("call {}", in(reg) p, in("rdi") args2[0], in("rsi") args2[1], in("rdx") args2[2], in("rcx") args2[3], in("r8") args2[4],
					lateout("rax") lo, lateout("rdx") hi, lateout("xmm0") f);
				break
			}
			if args2.len() == 6 {
				asm!("call {}", in(reg) p, in("rdi") args2[0], in("rsi") args2[1], in("rdx") args2[2], in("rcx") args2[3], in("r8") args2[4], in("r9") args2[5],
					lateout("rax") lo, lateout("rdx") hi, lateout("xmm0") f);
				break
			}
			println!("未调用");
			return
		}
	}
	*ret_low  = lo as usize;
	*ret_high = hi as usize;
	*ret_float = f;
}

pub trait IntoArg {
    fn into_arg(self) -> Vec<usize>;
}

impl<T> IntoArg for *const T {
    fn into_arg(self) -> Vec<usize> {
        vec![self as usize]
    }
}

impl<T> IntoArg for *mut T {
    fn into_arg(self) -> Vec<usize> {
        vec![self as usize]
    }
}

impl IntoArg for f32 {
    fn into_arg(self) -> Vec<usize> {
        (self as f64).into_arg()
    }
}

macro_rules! impl_intoarg {
    ($($ty:ty), *) => {
        $(impl IntoArg for $ty {
            fn into_arg(self) -> Vec<usize> {
                let len = mem::size_of::<$ty>() / mem::size_of::<usize>();
                if len <= 1 {
                    vec![self as usize]
                } else {
                    unsafe {
                        std::slice::from_raw_parts(&self as *const _ as *const usize, len).to_vec()
                    }
                }
            }
        })*
    };
}

impl_intoarg!(i8, u8, i16, u16, i32, u32, i64, u64, i128, u128, isize, usize, f64);
