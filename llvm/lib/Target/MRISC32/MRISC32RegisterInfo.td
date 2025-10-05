//===----------------------------------------------------------===//
//  Declaration that defines the MRISC32 Register file
//===----------------------------------------------------------===//

class MRISC32Reg<bits<5> Enc, string n> : Register<n> {
    let HWEncoding{4-0} = Enc;
    let Namespace  = "mrisc32";
}

foreach I = 0-31 in {
    let isConstant = !eq(0, I) in
        def R#I : MRISC32Reg<I, "R"#I>;
}

class MRISC32RegisterClass<list<ValueType> types, int size, int alignment,
                            dag regList, int copycost = 1>
                           : RegisterClass<"mrisc32", types, alignment, regList> {

        let Size = size;
        let CopyCost = copycost;
}

def GPR : MRISC32RegisterClass<[i32, f32], 32, 32, (add (sequence "R%u", 0, 31))>;

