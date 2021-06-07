# 引数の扱い

## スタック

```
	pushq	%rbp
	movq	%rsp, %rbp
	movl	$0, %eax
	popq	%rbp
	ret
```

1.pushhqでrbp(ベースポインタ)を8バイト上げる
2.movqでrbpにsp(スタックポインタ)を代入
3.popqでrbpを8バイト下げてretでリターン

## 引数
### 1つの場合
```
	pushq	%rbp
	movq	%rsp, %rbp
	movl	%edi, -4(%rbp)
	movl	-4(%rbp), %eax
	addl	%eax, %eax
	popq	%rbp
	ret
```
movl レジスタの中身を４バイトでコピー

1.ediをrbpが示すポインターの4バイト後ろから4バイト先までにコピー
2.1のメモリ領域をeaxにコピー
3.eaxにeaxを加算

ediに第一引数が入ってきている？

eaxが戻り値を格納するレジスタ

### 2つの場合
```
	pushq	%rbp
	movq	%rsp, %rbp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	-4(%rbp), %edx
	movl	-8(%rbp), %eax
	addl	%edx, %eax
	popq	%rbp
	ret
```

1.ediをrbpが示すポインターの4バイト後ろから4バイト先までにコピー
2.esiをrbpが示すポインターの8バイト後ろから4バイト先までにコピー
3.1のメモリ領域をedxにコピー
4.2のメモリ領域をeaxにコピー
5.eaxにedxを加算

ediが第一引数
esiに第二引数が入ってきている？

#### 実際に見てみる
```
int main() {
    printf("%d\n", sum2(1,2));
    return 0;
}
```

関数が終わる直前で
movl	%edi, %eax
を追加
出力結果：1
movl	%esi, %eax
だと
出力結果：2

### 多い場合
```
	pushq	%rbp
	movq	%rsp, %rbp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	%edx, -12(%rbp)
	movl	%ecx, -16(%rbp)
	movl	%r8d, -20(%rbp)
	movl	%r9d, -24(%rbp)
	movl	-4(%rbp), %edx
	movl	-8(%rbp), %eax
	addl	%eax, %edx
	movl	-12(%rbp), %eax
	addl	%eax, %edx
	movl	-16(%rbp), %eax
	addl	%eax, %edx
	movl	-20(%rbp), %eax
	addl	%eax, %edx
	movl	-24(%rbp), %eax
	addl	%eax, %edx
	movl	16(%rbp), %eax
	addl	%eax, %edx
	movl	24(%rbp), %eax
	addl	%eax, %edx
	movl	32(%rbp), %eax
	addl	%eax, %edx
	movl	40(%rbp), %eax
	addl	%eax, %edx
	movl	48(%rbp), %eax
	addl	%eax, %edx
	movl	56(%rbp), %eax
	addl	%eax, %edx
	movl	64(%rbp), %eax
	addl	%eax, %edx
	movl	72(%rbp), %eax
	addl	%eax, %edx
	movl	80(%rbp), %eax
	addl	%eax, %edx
	movl	88(%rbp), %eax
	addl	%edx, %eax
	popq	%rbp
	ret
```

6個まではレジスタに入れられているが、
7個目からベースポインタを元にスタックで積まれている

関数呼び出し元の状態
```
	pushq	$16
	pushq	$15
	pushq	$14
	pushq	$13
	pushq	$12
	pushq	$11
	pushq	$10
	pushq	$9
	pushq	$8
	pushq	$7
	movl	$6, %r9d
	movl	$5, %r8d
	movl	$4, %ecx
	movl	$3, %edx
	movl	$2, %esi
	movl	$1, %edi
	call	many_sum
```

rspの上に引数を積んで行って
関数の中に入った時のスタックは、積んだものも一緒にpushでずれる
16からアクセスしているのは、アドレスを入れるために16バイト使用しているためと予想

７個目以降の積まれた値はさらに関数呼ばれるとどうなる？
詳しく関数のスタックについて見る時確認する
```
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$40, %rsp
	movl	%edi, -20(%rbp)
	movl	%esi, -24(%rbp)
	movl	%edx, -28(%rbp)
	movl	%ecx, -32(%rbp)
	movl	%r8d, -36(%rbp)
	movl	%r9d, -40(%rbp)
	movl	-24(%rbp), %edx
	movl	-20(%rbp), %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	sum2
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %edx
	movl	-28(%rbp), %eax
	addl	%eax, %edx
	movl	-32(%rbp), %eax
	addl	%eax, %edx
	movl	-36(%rbp), %eax
	addl	%eax, %edx
	movl	-40(%rbp), %eax
	addl	%eax, %edx
	movl	16(%rbp), %eax
	addl	%eax, %edx
	movl	24(%rbp), %eax
	addl	%eax, %edx
	movl	32(%rbp), %eax
	addl	%eax, %edx
	movl	40(%rbp), %eax
	addl	%eax, %edx
	movl	48(%rbp), %eax
	addl	%eax, %edx
	movl	56(%rbp), %eax
	addl	%eax, %edx
	movl	64(%rbp), %eax
	addl	%eax, %edx
	movl	72(%rbp), %eax
	addl	%eax, %edx
	movl	80(%rbp), %eax
	addl	%eax, %edx
	movl	88(%rbp), %eax
	addl	%edx, %eax
	leave
	ret
```


