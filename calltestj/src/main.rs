#![feature(proc_macro_hygiene, llvm_asm, asm)]
#![allow(dead_code, unused_variables, unused_unsafe, unused_imports)]

use zhscript2::{u_::*, as_ref__, as_mut_ref__};

mod g_;
mod funcs_;

fn z__(env:&code_::Env_) -> Result2_ {
	let v = vec!["libstdc++.so.6"];
	let v:Vec<String> = v.iter().map(|s| s.to_string()).collect();

	let mut funcs = match funcs_::List_::new(&v) {
		Ok(funcs) => funcs,
		Err(e) => return result2_::err__(e)
	};

	let argv2 = vec![];
	let p = |ret2:&result_::List_| {
		let mut s = String::new();
		ret2.s2__(b'j', &mut s);
		println!("{}", s);
	};
	let mut f1 = |v2:Vec<&str>, ret2| {
		let v2:Vec<String> = v2.iter().map(|s| s.to_string()).collect();
		let fi = match funcs.add__(&v2) {
			Ok(i) => i,
			Err(s) => return result2_::err__(s)
		};
		p(&ret2);
		fi.call__(&argv2, &ret2, 0, &env)
	};

	f1(vec!["getuid", "i"], result_::List_::new())?;
	{
		let mut ret2 = result_::List_::new();
		ret2.add__("USER");
		f1(vec!["getenv", "c*-c*"], ret2)?;
	}
	{
		let v2 = vec!["sprintf", "-B-c*"];
		let v2:Vec<String> = v2.iter().map(|s| s.to_string()).collect();
		let fi = match funcs.add__(&v2) {
			Ok(i) => i,
			Err(s) => return result2_::err__(s)
		};
		let w = as_ref__!(env.w);
		use funcs_::typ_::Typ_;

		let mut ret2 = result_::List_::new();
		ret2.add__("");
		p(&ret2);
		fi.call__(&vec![], &ret2, 0, &env)?;

		let mut ret2 = result_::List_::new();
		ret2.add__("%s");
		w.dunhao__(&mut ret2); ret2.add__("啊");
		p(&ret2);
		fi.call__(&vec![Typ_::CharPtr], &ret2, 0, &env)?;

		let mut ret2 = result_::List_::new();
		ret2.add__("%5s%5s");
		for _ in 1..=2 {
			w.dunhao__(&mut ret2); ret2.add__("哦");
		}
		p(&ret2);
		fi.call__(&vec![Typ_::CharPtr, Typ_::CharPtr], &ret2, 0, &env)?;

		let mut ret2 = result_::List_::new();
		ret2.add__("-%d-%d-%d-");
		for _ in 1..=3 {
			w.dunhao__(&mut ret2); ret2.add__("3");
		}
		p(&ret2);
		fi.call__(&vec![Typ_::Int, Typ_::Int, Typ_::Int, ], &ret2, 0, &env)?;

		for i in 4..=7 {
			let mut ret2 = result_::List_::new();
			{
				let mut s = String::new();
				for _ in 0..i {
					s.push_str("%c");
				}
				ret2.add__(&s);
			}
			for i2 in 0..i {
				w.dunhao__(&mut ret2);
				ret2.add__(i2 + 22);
			}
			p(&ret2);
			let mut v = vec![];
			for _ in 0..i {
				v.push(Typ_::Char);
			}
			fi.call__(&v, &ret2, 0, &env)?;
		}

		let mut ret2 = result_::List_::new();
		ret2.add__("%f%f");
		w.dunhao__(&mut ret2); ret2.add__("1.1");
		w.dunhao__(&mut ret2); ret2.add__("2.22");
		p(&ret2);
		fi.call__(&vec![Typ_::Float, Typ_::Float], &ret2, 0, &env)?;
	}

	for i in &as_ref__!(env.ret).a_ {
		println!("{:?}", i);
	}
	ok__()
}

fn main() {
	let w = t__(World_::new());
	let q = Qv_::new2(Some(as_ref__!(w).top_q_.clone()));
	let ret = t__(result_::List_::new());
	let env = code_::Env_::new(t__(q), w.clone(), ret.clone());

	println!("{:?}", z__(&env));
	
	/*let mut fv = vec![];
	println!("{:?}", z1__("/zzzzzzzzzzz/github/bin/zhscript2/lib/gjke4.so", vec!["sp_len__", "i-c*-Z"], &mut fv));
	println!("{:?}", z1__("/zzzzzzzzzzz/github/bin/zhscript2/lib/gjk4.so", vec!["cnum__", "c*-c*"], &mut fv));
	println!("{:?}", z1__("/zzzzzzzzzzz/github/bin/zhscript2/lib/gjk4.so", vec!["capsy__", "-E-S-c*"], &mut fv));
	
	let mut ret2 = result_::List_::new();
	ret2.clear();
	ret2.add__("1234");
	println!("{:?}", z2__(fv[0].clone(), &ret2, &env));
	ret2.clear();
	ret2.add__("12345678901234567890.1234567890");
	println!("{:?}", z2__(fv[1].clone(), &ret2, &env));
	ret2.clear();
	ret2.add__("12345678901234567890.12345");
	println!("{:?}", z2__(fv[2].clone(), &ret2, &env));
	
	println!("{:?}", as_ref__!(ret).a_);*/
}

fn z1__(so:&str, v2:Vec<&str>, fv:&mut Vec<funcs_::RI_>) -> Result2_ {
	let v = vec![so];
	let v:Vec<String> = v.iter().map(|s| s.to_string()).collect();
	let v2:Vec<String> = v2.iter().map(|s| s.to_string()).collect();

	let mut funcs = match funcs_::List_::new(&v) {
		Ok(funcs) => funcs,
		Err(e) => return result2_::err__(e)
	};

	match funcs.add__(&v2) {
		Ok(i) => {
			fv.push(i);
			ok__()
		}
		Err(s) => result2_::err__(s)
	}
}
fn z2__(fi:funcs_::RI_, ret2:&result_::List_, env:&code_::Env_) -> Result2_ {
	let argv2 = vec![];
	fi.call__(&argv2, &ret2, 0, &env)
}
