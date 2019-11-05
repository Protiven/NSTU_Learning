using System;
using System.Collections.Generic;
using System.Linq;

namespace Laba3
{
    using static Functions;

    public abstract class Expr
    {
        public abstract double Compute(IReadOnlyDictionary<string, double> variableValues);
        public abstract IEnumerable<string> Variables { get; }
        public abstract bool IsConstant { get; }
        public abstract bool IsPolynom { get; }
        public static Add operator +(Expr a, Expr b) => new Add(a, b);
        public static UnaryMin operator -(Expr c) => new UnaryMin(c);
        public static Sub operator -(Expr a, Expr b) => new Sub(a, b);
        public static Mult operator *(Expr a, Expr b) => new Mult(a, b);
        public static Div operator /(Expr a, Expr b) => new Div(a, b);
        public static implicit operator Expr(double x) => new Constant(x);
    }

    static class Functions
    {
        public static Sinh Sinh(Expr a) => new Sinh(a);
        public static Cosh Cosh(Expr a) => new Cosh(a);
        public static Tanh Tanh(Expr a) => new Tanh(a);
        public static CTanh CTanh(Expr a) => new CTanh(a);
    }

    public class Constant : Expr
    {
        public double Value { get; }
        public override IEnumerable<string> Variables => null;
        public override bool IsConstant => true;
        public override bool IsPolynom => true;
        public Constant(double value) => this.Value = value;
        public override double Compute(IReadOnlyDictionary<string, double> variableValues) => Value;
        public override string ToString()
        {
            return $"{Value}";
        }
    }

    public class Variable : Expr
    {
        public string Name { get; }
        public Variable(string name) => this.Name = name;
        public override IEnumerable<string> Variables => new List<string> { Name };
        public override bool IsConstant => false;
        public override bool IsPolynom => true;
        public override double Compute(IReadOnlyDictionary<string, double> variableValues)
        {
            if (variableValues.ContainsKey(Name))
                return variableValues[Name];
            throw new ArgumentException("Not found variable");
        }

        public override string ToString()
        {
            return $"{Name}";
        }
    }

    abstract public class BinaryOperation : Expr
    {
        protected Expr Arg1 { get; set; }
        protected Expr Arg2 { get; set; }
        public BinaryOperation(Expr arg1, Expr arg2)
        {
            this.Arg1 = arg1;
            this.Arg2 = arg2;
        }
        public override IEnumerable<string> Variables => Arg1.Variables.Union<string>(Arg2.Variables);
    }

    public class Add : BinaryOperation
    {
        public Add(Expr arg1, Expr arg2) : base(arg1, arg2) { }
        public override double Compute(IReadOnlyDictionary<string, double> variableValues) => Arg1.Compute(variableValues) + Arg2.Compute(variableValues);
        public override bool IsConstant => Arg1.IsConstant && Arg2.IsConstant;
        public override bool IsPolynom => Arg1.IsPolynom && Arg2.IsPolynom;
        public override string ToString()
        { 
            return $"({Arg1} + {Arg2})";
        }

    }

    public class Sub : BinaryOperation
    {
        public Sub(Expr arg1, Expr arg2) : base(arg1, arg2) { }
        public override double Compute(IReadOnlyDictionary<string, double> variableValues) => Arg1.Compute(variableValues) - Arg2.Compute(variableValues);
        public override bool IsConstant => Arg1.IsConstant && Arg2.IsConstant;
        public override bool IsPolynom => Arg1.IsPolynom && Arg2.IsPolynom;
        public override string ToString()
        {
            return $"({Arg1} - {Arg2})";
        }
    }

    public class Mult : BinaryOperation
    {
        public Mult(Expr arg1, Expr arg2) : base(arg1, arg2) { }
        public override double Compute(IReadOnlyDictionary<string, double> variableValues) => Arg1.Compute(variableValues) * Arg2.Compute(variableValues);
        public override bool IsConstant => Arg1.IsConstant && Arg2.IsConstant;
        public override bool IsPolynom => Arg1.IsPolynom && Arg2.IsPolynom;
        public override string ToString()
        {
            return ($"({Arg1} * {Arg2})");
        }
    }

    public class Div : BinaryOperation
    {
        public Div(Expr arg1, Expr arg2) : base(arg1, arg2) { }
        public override double Compute(IReadOnlyDictionary<string, double> variableValues)
        {
            if (Arg2.Compute(variableValues) == 0)
                throw new ArgumentException("number is zero");
            else
                return Arg1.Compute(variableValues) / Arg2.Compute(variableValues);
        }

        public override bool IsConstant => Arg1.IsConstant && Arg2.IsConstant;
        public override bool IsPolynom => Arg1.IsPolynom && Arg2.IsConstant;
        public override string ToString()
        {
            return $"({Arg1} / {Arg2})";
        }
    }

    public abstract class UnaryOperations : Expr
    {
        protected Expr Arg1 { get; set; }
        public UnaryOperations(Expr arg1)
        {
            this.Arg1 = arg1;
        }
        public override IEnumerable<string> Variables => Arg1.Variables;
        public override bool IsConstant => Arg1.IsConstant;
        public override bool IsPolynom => Arg1.IsPolynom;
    }

    public class UnaryMin : UnaryOperations
    {
        public UnaryMin(Expr arg1) : base(arg1) { }
        public override double Compute(IReadOnlyDictionary<string, double> variableValues) => -Arg1.Compute(variableValues);
        public override string ToString()
        {
            return $"(- {Arg1})";
        }
    }

    public abstract class Function : Expr
    {
        protected Expr Arg1 { get; set; }
        public Function(Expr arg1)
        {
            this.Arg1 = arg1;
        }
        public override IEnumerable<string> Variables => Arg1.Variables;
        public override bool IsConstant => Arg1.IsConstant;
        public override bool IsPolynom => Arg1.IsConstant;
    }

    public class Sinh : Function
    { 
        public Sinh(Expr arg1) : base(arg1) { }

        public override double Compute(IReadOnlyDictionary<string, double> variableValues)
        {
            return Math.Sinh(Arg1.Compute(variableValues));
        }

        public override string ToString()
        {
            return $"Sinh({Arg1})";
        }
    }

    public class Cosh : Function
    {
        public Cosh(Expr arg1) : base(arg1) { }

        public override double Compute(IReadOnlyDictionary<string, double> variableValues)
        {
            return Math.Cosh(Arg1.Compute(variableValues));
        }

        public override string ToString()
        {
            return $"Cosh({Arg1})";
        }
    }

    public class Tanh : Function
    {
        public Tanh(Expr arg1) : base(arg1) { }

        public override double Compute(IReadOnlyDictionary<string, double> variableValues)
        { 
            return Math.Tanh(Arg1.Compute(variableValues));
        }

        public override string ToString()
        {
            return $"Tanh({Arg1})";
        }
    }

    public class CTanh : Function
    {
        public CTanh(Expr arg1) : base(arg1) { }

        public override double Compute(IReadOnlyDictionary<string, double> variableValues)
        {
            if (Arg1.Compute(variableValues) != 0)
                return 1 / Math.Tanh(Arg1.Compute(variableValues));
            else throw new ArgumentException("number is zero");
        }

        public override string ToString()
        {
            return $"CTanh({Arg1})";
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            var a = new Variable("a");
            var b = new Variable("b");
            var c = new Variable("c");
            var x = new Constant(4);


            Tanh expr = new Tanh(2 * x);


            Console.WriteLine($"const = {expr.IsConstant}");
            Console.WriteLine($"polynom = {expr.IsPolynom}");
            Console.Write(expr);
            Console.WriteLine($" = { expr.Compute(new Dictionary<string, double> { ["a"] = 8, ["b"] = 4, ["c"] = 3 })}");
            Console.ReadKey();
        }
    }
}
