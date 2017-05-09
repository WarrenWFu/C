/*******************************************************************************
 *
 * author:Warren Fu
 * date:
 * description:使用javac HelloWorld.java之后用java HelloWorld运行即可
 * 就算不使用super(),同样会调用父类的默认构造函数
 *
*******************************************************************************/
public class HelloWorld{
    class Foo {
        Foo() {
            System.out.println("from father!");
        }
    }

    class Bar extends Foo {
        Bar() {
            super();//有没有这句都会调用父类的默认构造函数
            System.out.println("from child!");
        }
    }

    class Bar2 extends Bar {
        Bar2() {
            System.out.println("from grandson!");
        }
    }
    public static void main(String[] args){
        System.out.println("Hello world!");

        HelloWorld hw = new HelloWorld();
        Bar2 bar = hw.new Bar2();

    }
}
