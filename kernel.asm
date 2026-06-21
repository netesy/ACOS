
kernel.elf:     file format elf64-x86-64


Disassembly of section .text:

0000000000100000 <memcpy>:
  100000:	55                   	push   %rbp
  100001:	48 89 e5             	mov    %rsp,%rbp
  100004:	48 83 ec 30          	sub    $0x30,%rsp
  100008:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10000c:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  100010:	48 89 55 e8          	mov    %rdx,-0x18(%rbp)
  100014:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  100018:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  10001c:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  100020:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
  100024:	48 c7 45 d0 00 00 00 	movq   $0x0,-0x30(%rbp)
  10002b:	00
  10002c:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  100030:	48 3b 45 e8          	cmp    -0x18(%rbp),%rax
  100034:	0f 83 27 00 00 00    	jae    100061 <memcpy+0x61>
  10003a:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  10003e:	48 8b 4d d0          	mov    -0x30(%rbp),%rcx
  100042:	8a 14 08             	mov    (%rax,%rcx,1),%dl
  100045:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  100049:	48 8b 4d d0          	mov    -0x30(%rbp),%rcx
  10004d:	88 14 08             	mov    %dl,(%rax,%rcx,1)
  100050:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  100054:	48 83 c0 01          	add    $0x1,%rax
  100058:	48 89 45 d0          	mov    %rax,-0x30(%rbp)
  10005c:	e9 cb ff ff ff       	jmp    10002c <memcpy+0x2c>
  100061:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  100065:	48 83 c4 30          	add    $0x30,%rsp
  100069:	5d                   	pop    %rbp
  10006a:	c3                   	ret
  10006b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000100070 <memset>:
  100070:	55                   	push   %rbp
  100071:	48 89 e5             	mov    %rsp,%rbp
  100074:	48 83 ec 28          	sub    $0x28,%rsp
  100078:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10007c:	89 75 f4             	mov    %esi,-0xc(%rbp)
  10007f:	48 89 55 e8          	mov    %rdx,-0x18(%rbp)
  100083:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  100087:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  10008b:	48 c7 45 d8 00 00 00 	movq   $0x0,-0x28(%rbp)
  100092:	00
  100093:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  100097:	48 3b 45 e8          	cmp    -0x18(%rbp),%rax
  10009b:	0f 83 21 00 00 00    	jae    1000c2 <memset+0x52>
  1000a1:	8b 45 f4             	mov    -0xc(%rbp),%eax
  1000a4:	88 c2                	mov    %al,%dl
  1000a6:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  1000aa:	48 8b 4d d8          	mov    -0x28(%rbp),%rcx
  1000ae:	88 14 08             	mov    %dl,(%rax,%rcx,1)
  1000b1:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  1000b5:	48 83 c0 01          	add    $0x1,%rax
  1000b9:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
  1000bd:	e9 d1 ff ff ff       	jmp    100093 <memset+0x23>
  1000c2:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  1000c6:	48 83 c4 28          	add    $0x28,%rsp
  1000ca:	5d                   	pop    %rbp
  1000cb:	c3                   	ret
  1000cc:	0f 1f 40 00          	nopl   0x0(%rax)

00000000001000d0 <memmove>:
  1000d0:	55                   	push   %rbp
  1000d1:	48 89 e5             	mov    %rsp,%rbp
  1000d4:	48 83 ec 38          	sub    $0x38,%rsp
  1000d8:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  1000dc:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  1000e0:	48 89 55 e8          	mov    %rdx,-0x18(%rbp)
  1000e4:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  1000e8:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  1000ec:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  1000f0:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
  1000f4:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  1000f8:	48 3b 45 d8          	cmp    -0x28(%rbp),%rax
  1000fc:	0f 83 42 00 00 00    	jae    100144 <memmove+0x74>
  100102:	48 c7 45 d0 00 00 00 	movq   $0x0,-0x30(%rbp)
  100109:	00
  10010a:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  10010e:	48 3b 45 e8          	cmp    -0x18(%rbp),%rax
  100112:	0f 83 27 00 00 00    	jae    10013f <memmove+0x6f>
  100118:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  10011c:	48 8b 4d d0          	mov    -0x30(%rbp),%rcx
  100120:	8a 14 08             	mov    (%rax,%rcx,1),%dl
  100123:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  100127:	48 8b 4d d0          	mov    -0x30(%rbp),%rcx
  10012b:	88 14 08             	mov    %dl,(%rax,%rcx,1)
  10012e:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  100132:	48 83 c0 01          	add    $0x1,%rax
  100136:	48 89 45 d0          	mov    %rax,-0x30(%rbp)
  10013a:	e9 cb ff ff ff       	jmp    10010a <memmove+0x3a>
  10013f:	e9 5a 00 00 00       	jmp    10019e <memmove+0xce>
  100144:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  100148:	48 3b 45 d8          	cmp    -0x28(%rbp),%rax
  10014c:	0f 86 47 00 00 00    	jbe    100199 <memmove+0xc9>
  100152:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  100156:	48 89 45 c8          	mov    %rax,-0x38(%rbp)
  10015a:	48 83 7d c8 00       	cmpq   $0x0,-0x38(%rbp)
  10015f:	0f 86 2f 00 00 00    	jbe    100194 <memmove+0xc4>
  100165:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  100169:	48 8b 4d c8          	mov    -0x38(%rbp),%rcx
  10016d:	48 83 e9 01          	sub    $0x1,%rcx
  100171:	8a 14 08             	mov    (%rax,%rcx,1),%dl
  100174:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  100178:	48 8b 4d c8          	mov    -0x38(%rbp),%rcx
  10017c:	48 83 e9 01          	sub    $0x1,%rcx
  100180:	88 14 08             	mov    %dl,(%rax,%rcx,1)
  100183:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  100187:	48 83 c0 ff          	add    $0xffffffffffffffff,%rax
  10018b:	48 89 45 c8          	mov    %rax,-0x38(%rbp)
  10018f:	e9 c6 ff ff ff       	jmp    10015a <memmove+0x8a>
  100194:	e9 00 00 00 00       	jmp    100199 <memmove+0xc9>
  100199:	e9 00 00 00 00       	jmp    10019e <memmove+0xce>
  10019e:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  1001a2:	48 83 c4 38          	add    $0x38,%rsp
  1001a6:	5d                   	pop    %rbp
  1001a7:	c3                   	ret
  1001a8:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  1001af:	00

00000000001001b0 <memcmp>:
  1001b0:	55                   	push   %rbp
  1001b1:	48 89 e5             	mov    %rsp,%rbp
  1001b4:	48 83 ec 38          	sub    $0x38,%rsp
  1001b8:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  1001bc:	48 89 75 e8          	mov    %rsi,-0x18(%rbp)
  1001c0:	48 89 55 e0          	mov    %rdx,-0x20(%rbp)
  1001c4:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  1001c8:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
  1001cc:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  1001d0:	48 89 45 d0          	mov    %rax,-0x30(%rbp)
  1001d4:	48 c7 45 c8 00 00 00 	movq   $0x0,-0x38(%rbp)
  1001db:	00
  1001dc:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  1001e0:	48 3b 45 e0          	cmp    -0x20(%rbp),%rax
  1001e4:	0f 83 58 00 00 00    	jae    100242 <memcmp+0x92>
  1001ea:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  1001ee:	48 8b 4d c8          	mov    -0x38(%rbp),%rcx
  1001f2:	0f b6 04 08          	movzbl (%rax,%rcx,1),%eax
  1001f6:	48 8b 4d d0          	mov    -0x30(%rbp),%rcx
  1001fa:	48 8b 55 c8          	mov    -0x38(%rbp),%rdx
  1001fe:	0f b6 0c 11          	movzbl (%rcx,%rdx,1),%ecx
  100202:	39 c8                	cmp    %ecx,%eax
  100204:	0f 84 22 00 00 00    	je     10022c <memcmp+0x7c>
  10020a:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  10020e:	48 8b 4d c8          	mov    -0x38(%rbp),%rcx
  100212:	0f b6 04 08          	movzbl (%rax,%rcx,1),%eax
  100216:	48 8b 4d d0          	mov    -0x30(%rbp),%rcx
  10021a:	48 8b 55 c8          	mov    -0x38(%rbp),%rdx
  10021e:	0f b6 0c 11          	movzbl (%rcx,%rdx,1),%ecx
  100222:	29 c8                	sub    %ecx,%eax
  100224:	89 45 fc             	mov    %eax,-0x4(%rbp)
  100227:	e9 1d 00 00 00       	jmp    100249 <memcmp+0x99>
  10022c:	e9 00 00 00 00       	jmp    100231 <memcmp+0x81>
  100231:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  100235:	48 83 c0 01          	add    $0x1,%rax
  100239:	48 89 45 c8          	mov    %rax,-0x38(%rbp)
  10023d:	e9 9a ff ff ff       	jmp    1001dc <memcmp+0x2c>
  100242:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%rbp)
  100249:	8b 45 fc             	mov    -0x4(%rbp),%eax
  10024c:	48 83 c4 38          	add    $0x38,%rsp
  100250:	5d                   	pop    %rbp
  100251:	c3                   	ret
  100252:	66 66 66 66 66 2e 0f 	data16 data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
  100259:	1f 84 00 00 00 00 00

0000000000100260 <strcmp>:
  100260:	55                   	push   %rbp
  100261:	48 89 e5             	mov    %rsp,%rbp
  100264:	48 83 ec 18          	sub    $0x18,%rsp
  100268:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10026c:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  100270:	48 8b 4d f8          	mov    -0x8(%rbp),%rcx
  100274:	31 c0                	xor    %eax,%eax
  100276:	80 39 00             	cmpb   $0x0,(%rcx)
  100279:	88 45 ef             	mov    %al,-0x11(%rbp)
  10027c:	0f 84 16 00 00 00    	je     100298 <strcmp+0x38>
  100282:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  100286:	0f be 00             	movsbl (%rax),%eax
  100289:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
  10028d:	0f be 09             	movsbl (%rcx),%ecx
  100290:	39 c8                	cmp    %ecx,%eax
  100292:	0f 94 c0             	sete   %al
  100295:	88 45 ef             	mov    %al,-0x11(%rbp)
  100298:	8a 45 ef             	mov    -0x11(%rbp),%al
  10029b:	a8 01                	test   $0x1,%al
  10029d:	0f 85 05 00 00 00    	jne    1002a8 <strcmp+0x48>
  1002a3:	e9 1d 00 00 00       	jmp    1002c5 <strcmp+0x65>
  1002a8:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  1002ac:	48 83 c0 01          	add    $0x1,%rax
  1002b0:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  1002b4:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  1002b8:	48 83 c0 01          	add    $0x1,%rax
  1002bc:	48 89 45 f0          	mov    %rax,-0x10(%rbp)
  1002c0:	e9 ab ff ff ff       	jmp    100270 <strcmp+0x10>
  1002c5:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  1002c9:	0f b6 00             	movzbl (%rax),%eax
  1002cc:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
  1002d0:	0f b6 09             	movzbl (%rcx),%ecx
  1002d3:	29 c8                	sub    %ecx,%eax
  1002d5:	48 83 c4 18          	add    $0x18,%rsp
  1002d9:	5d                   	pop    %rbp
  1002da:	c3                   	ret
  1002db:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000001002e0 <strncmp>:
  1002e0:	55                   	push   %rbp
  1002e1:	48 89 e5             	mov    %rsp,%rbp
  1002e4:	48 83 ec 28          	sub    $0x28,%rsp
  1002e8:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  1002ec:	48 89 75 e8          	mov    %rsi,-0x18(%rbp)
  1002f0:	48 89 55 e0          	mov    %rdx,-0x20(%rbp)
  1002f4:	48 c7 45 d8 00 00 00 	movq   $0x0,-0x28(%rbp)
  1002fb:	00
  1002fc:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  100300:	48 3b 45 e0          	cmp    -0x20(%rbp),%rax
  100304:	0f 83 6a 00 00 00    	jae    100374 <strncmp+0x94>
  10030a:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10030e:	48 8b 4d d8          	mov    -0x28(%rbp),%rcx
  100312:	80 3c 08 00          	cmpb   $0x0,(%rax,%rcx,1)
  100316:	0f 84 20 00 00 00    	je     10033c <strncmp+0x5c>
  10031c:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  100320:	48 8b 4d d8          	mov    -0x28(%rbp),%rcx
  100324:	0f be 04 08          	movsbl (%rax,%rcx,1),%eax
  100328:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  10032c:	48 8b 55 d8          	mov    -0x28(%rbp),%rdx
  100330:	0f be 0c 11          	movsbl (%rcx,%rdx,1),%ecx
  100334:	39 c8                	cmp    %ecx,%eax
  100336:	0f 84 22 00 00 00    	je     10035e <strncmp+0x7e>
  10033c:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  100340:	48 8b 4d d8          	mov    -0x28(%rbp),%rcx
  100344:	0f b6 04 08          	movzbl (%rax,%rcx,1),%eax
  100348:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  10034c:	48 8b 55 d8          	mov    -0x28(%rbp),%rdx
  100350:	0f b6 0c 11          	movzbl (%rcx,%rdx,1),%ecx
  100354:	29 c8                	sub    %ecx,%eax
  100356:	89 45 fc             	mov    %eax,-0x4(%rbp)
  100359:	e9 1d 00 00 00       	jmp    10037b <strncmp+0x9b>
  10035e:	e9 00 00 00 00       	jmp    100363 <strncmp+0x83>
  100363:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  100367:	48 83 c0 01          	add    $0x1,%rax
  10036b:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
  10036f:	e9 88 ff ff ff       	jmp    1002fc <strncmp+0x1c>
  100374:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%rbp)
  10037b:	8b 45 fc             	mov    -0x4(%rbp),%eax
  10037e:	48 83 c4 28          	add    $0x28,%rsp
  100382:	5d                   	pop    %rbp
  100383:	c3                   	ret
  100384:	66 66 66 2e 0f 1f 84 	data16 data16 cs nopw 0x0(%rax,%rax,1)
  10038b:	00 00 00 00 00

0000000000100390 <strlen>:
  100390:	55                   	push   %rbp
  100391:	48 89 e5             	mov    %rsp,%rbp
  100394:	48 83 ec 10          	sub    $0x10,%rsp
  100398:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10039c:	48 c7 45 f0 00 00 00 	movq   $0x0,-0x10(%rbp)
  1003a3:	00
  1003a4:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  1003a8:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
  1003ac:	80 3c 08 00          	cmpb   $0x0,(%rax,%rcx,1)
  1003b0:	0f 84 11 00 00 00    	je     1003c7 <strlen+0x37>
  1003b6:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  1003ba:	48 83 c0 01          	add    $0x1,%rax
  1003be:	48 89 45 f0          	mov    %rax,-0x10(%rbp)
  1003c2:	e9 dd ff ff ff       	jmp    1003a4 <strlen+0x14>
  1003c7:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  1003cb:	48 83 c4 10          	add    $0x10,%rsp
  1003cf:	5d                   	pop    %rbp
  1003d0:	c3                   	ret
  1003d1:	66 66 66 66 66 66 2e 	data16 data16 data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
  1003d8:	0f 1f 84 00 00 00 00
  1003df:	00

00000000001003e0 <__cxa_pure_virtual>:
  1003e0:	55                   	push   %rbp
  1003e1:	48 89 e5             	mov    %rsp,%rbp
  1003e4:	e9 00 00 00 00       	jmp    1003e9 <__cxa_pure_virtual+0x9>
  1003e9:	f4                   	hlt
  1003ea:	e9 fa ff ff ff       	jmp    1003e9 <__cxa_pure_virtual+0x9>
  1003ef:	90                   	nop

00000000001003f0 <_Znwm>:
  1003f0:	55                   	push   %rbp
  1003f1:	48 89 e5             	mov    %rsp,%rbp
  1003f4:	48 83 ec 10          	sub    $0x10,%rsp
  1003f8:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  1003fc:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  100400:	e8 4b 83 00 00       	call   108750 <_ZN4acos6memory7kmallocEm>
  100405:	48 89 45 f0          	mov    %rax,-0x10(%rbp)
  100409:	48 83 7d f0 00       	cmpq   $0x0,-0x10(%rbp)
  10040e:	0f 85 0b 00 00 00    	jne    10041f <_Znwm+0x2f>
  100414:	e9 00 00 00 00       	jmp    100419 <_Znwm+0x29>
  100419:	f4                   	hlt
  10041a:	e9 fa ff ff ff       	jmp    100419 <_Znwm+0x29>
  10041f:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  100423:	48 83 c4 10          	add    $0x10,%rsp
  100427:	5d                   	pop    %rbp
  100428:	c3                   	ret
  100429:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000100430 <_ZdlPv>:
  100430:	55                   	push   %rbp
  100431:	48 89 e5             	mov    %rsp,%rbp
  100434:	48 83 ec 10          	sub    $0x10,%rsp
  100438:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10043c:	48 83 7d f8 00       	cmpq   $0x0,-0x8(%rbp)
  100441:	0f 84 09 00 00 00    	je     100450 <_ZdlPv+0x20>
  100447:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  10044b:	e8 d0 83 00 00       	call   108820 <_ZN4acos6memory5kfreeEPv>
  100450:	48 83 c4 10          	add    $0x10,%rsp
  100454:	5d                   	pop    %rbp
  100455:	c3                   	ret
  100456:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
  10045d:	00 00 00

0000000000100460 <_Znam>:
  100460:	55                   	push   %rbp
  100461:	48 89 e5             	mov    %rsp,%rbp
  100464:	48 83 ec 10          	sub    $0x10,%rsp
  100468:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10046c:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  100470:	e8 7b ff ff ff       	call   1003f0 <_Znwm>
  100475:	48 83 c4 10          	add    $0x10,%rsp
  100479:	5d                   	pop    %rbp
  10047a:	c3                   	ret
  10047b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000100480 <_ZdaPv>:
  100480:	55                   	push   %rbp
  100481:	48 89 e5             	mov    %rsp,%rbp
  100484:	48 83 ec 10          	sub    $0x10,%rsp
  100488:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10048c:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  100490:	e8 9b ff ff ff       	call   100430 <_ZdlPv>
  100495:	48 83 c4 10          	add    $0x10,%rsp
  100499:	5d                   	pop    %rbp
  10049a:	c3                   	ret
  10049b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000001004a0 <_ZdlPvm>:
  1004a0:	55                   	push   %rbp
  1004a1:	48 89 e5             	mov    %rsp,%rbp
  1004a4:	48 83 ec 10          	sub    $0x10,%rsp
  1004a8:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  1004ac:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  1004b0:	48 83 7d f8 00       	cmpq   $0x0,-0x8(%rbp)
  1004b5:	0f 84 09 00 00 00    	je     1004c4 <_ZdlPvm+0x24>
  1004bb:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  1004bf:	e8 5c 83 00 00       	call   108820 <_ZN4acos6memory5kfreeEPv>
  1004c4:	48 83 c4 10          	add    $0x10,%rsp
  1004c8:	5d                   	pop    %rbp
  1004c9:	c3                   	ret
  1004ca:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

00000000001004d0 <_ZN4acos7storage14AHCIControllerC1Em>:
  1004d0:	55                   	push   %rbp
  1004d1:	48 89 e5             	mov    %rsp,%rbp
  1004d4:	48 83 ec 10          	sub    $0x10,%rsp
  1004d8:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  1004dc:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  1004e0:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  1004e4:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
  1004e8:	48 89 08             	mov    %rcx,(%rax)
  1004eb:	c7 80 08 01 00 00 00 	movl   $0x0,0x108(%rax)
  1004f2:	00 00 00
  1004f5:	48 83 c4 10          	add    $0x10,%rsp
  1004f9:	5d                   	pop    %rbp
  1004fa:	c3                   	ret
  1004fb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000100500 <_ZN4acos7storage14AHCIController10initializeEv>:
  100500:	55                   	push   %rbp
  100501:	48 89 e5             	mov    %rsp,%rbp
  100504:	48 83 ec 40          	sub    $0x40,%rsp
  100508:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  10050c:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  100510:	48 89 45 c8          	mov    %rax,-0x38(%rbp)
  100514:	48 83 38 00          	cmpq   $0x0,(%rax)
  100518:	0f 85 09 00 00 00    	jne    100527 <_ZN4acos7storage14AHCIController10initializeEv+0x27>
  10051e:	c6 45 ff 00          	movb   $0x0,-0x1(%rbp)
  100522:	e9 fc 00 00 00       	jmp    100623 <_ZN4acos7storage14AHCIController10initializeEv+0x123>
  100527:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  10052b:	48 8b 00             	mov    (%rax),%rax
  10052e:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
  100532:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  100536:	8b 48 04             	mov    0x4(%rax),%ecx
  100539:	81 c9 00 00 00 80    	or     $0x80000000,%ecx
  10053f:	89 48 04             	mov    %ecx,0x4(%rax)
  100542:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  100546:	8b 40 0c             	mov    0xc(%rax),%eax
  100549:	89 45 e4             	mov    %eax,-0x1c(%rbp)
  10054c:	c7 45 e0 00 00 00 00 	movl   $0x0,-0x20(%rbp)
  100553:	83 7d e0 20          	cmpl   $0x20,-0x20(%rbp)
  100557:	0f 83 b3 00 00 00    	jae    100610 <_ZN4acos7storage14AHCIController10initializeEv+0x110>
  10055d:	8b 45 e4             	mov    -0x1c(%rbp),%eax
  100560:	8b 4d e0             	mov    -0x20(%rbp),%ecx
  100563:	ba 01 00 00 00       	mov    $0x1,%edx
  100568:	d3 e2                	shl    %cl,%edx
  10056a:	89 d1                	mov    %edx,%ecx
  10056c:	21 c8                	and    %ecx,%eax
  10056e:	83 f8 00             	cmp    $0x0,%eax
  100571:	0f 84 86 00 00 00    	je     1005fd <_ZN4acos7storage14AHCIController10initializeEv+0xfd>
  100577:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  10057b:	48 05 00 01 00 00    	add    $0x100,%rax
  100581:	8b 4d e0             	mov    -0x20(%rbp),%ecx
  100584:	c1 e1 07             	shl    $0x7,%ecx
  100587:	c1 e9 02             	shr    $0x2,%ecx
  10058a:	89 c9                	mov    %ecx,%ecx
  10058c:	48 c1 e1 02          	shl    $0x2,%rcx
  100590:	48 01 c8             	add    %rcx,%rax
  100593:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
  100597:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  10059b:	8b 40 28             	mov    0x28(%rax),%eax
  10059e:	83 e0 0f             	and    $0xf,%eax
  1005a1:	83 f8 03             	cmp    $0x3,%eax
  1005a4:	0f 85 4e 00 00 00    	jne    1005f8 <_ZN4acos7storage14AHCIController10initializeEv+0xf8>
  1005aa:	bf 20 01 00 00       	mov    $0x120,%edi
  1005af:	e8 3c fe ff ff       	call   1003f0 <_Znwm>
  1005b4:	48 89 c7             	mov    %rax,%rdi
  1005b7:	48 89 7d c0          	mov    %rdi,-0x40(%rbp)
  1005bb:	8b 75 e0             	mov    -0x20(%rbp),%esi
  1005be:	48 8b 55 d8          	mov    -0x28(%rbp),%rdx
  1005c2:	e8 e9 01 00 00       	call   1007b0 <_ZN4acos7storage8AHCIPortC1EjPv>
  1005c7:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  1005cb:	48 89 45 d0          	mov    %rax,-0x30(%rbp)
  1005cf:	48 8b 7d d0          	mov    -0x30(%rbp),%rdi
  1005d3:	e8 68 00 00 00       	call   100640 <_ZN4acos7storage8AHCIPort9configureEv>
  1005d8:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  1005dc:	48 8b 55 d0          	mov    -0x30(%rbp),%rdx
  1005e0:	8b 88 08 01 00 00    	mov    0x108(%rax),%ecx
  1005e6:	89 ce                	mov    %ecx,%esi
  1005e8:	83 c6 01             	add    $0x1,%esi
  1005eb:	89 b0 08 01 00 00    	mov    %esi,0x108(%rax)
  1005f1:	89 c9                	mov    %ecx,%ecx
  1005f3:	48 89 54 c8 08       	mov    %rdx,0x8(%rax,%rcx,8)
  1005f8:	e9 00 00 00 00       	jmp    1005fd <_ZN4acos7storage14AHCIController10initializeEv+0xfd>
  1005fd:	e9 00 00 00 00       	jmp    100602 <_ZN4acos7storage14AHCIController10initializeEv+0x102>
  100602:	8b 45 e0             	mov    -0x20(%rbp),%eax
  100605:	83 c0 01             	add    $0x1,%eax
  100608:	89 45 e0             	mov    %eax,-0x20(%rbp)
  10060b:	e9 43 ff ff ff       	jmp    100553 <_ZN4acos7storage14AHCIController10initializeEv+0x53>
  100610:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  100614:	83 b8 08 01 00 00 00 	cmpl   $0x0,0x108(%rax)
  10061b:	0f 97 c0             	seta   %al
  10061e:	24 01                	and    $0x1,%al
  100620:	88 45 ff             	mov    %al,-0x1(%rbp)
  100623:	8a 45 ff             	mov    -0x1(%rbp),%al
  100626:	24 01                	and    $0x1,%al
  100628:	0f b6 c0             	movzbl %al,%eax
  10062b:	48 83 c4 40          	add    $0x40,%rsp
  10062f:	5d                   	pop    %rbp
  100630:	c3                   	ret
  100631:	66 66 66 66 66 66 2e 	data16 data16 data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
  100638:	0f 1f 84 00 00 00 00
  10063f:	00

0000000000100640 <_ZN4acos7storage8AHCIPort9configureEv>:
  100640:	55                   	push   %rbp
  100641:	48 89 e5             	mov    %rsp,%rbp
  100644:	48 83 ec 40          	sub    $0x40,%rsp
  100648:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10064c:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  100650:	48 89 45 c8          	mov    %rax,-0x38(%rbp)
  100654:	48 8b 40 10          	mov    0x10(%rax),%rax
  100658:	48 89 45 f0          	mov    %rax,-0x10(%rbp)
  10065c:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  100660:	8b 48 18             	mov    0x18(%rax),%ecx
  100663:	83 e1 fe             	and    $0xfffffffe,%ecx
  100666:	89 48 18             	mov    %ecx,0x18(%rax)
  100669:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10066d:	8b 48 18             	mov    0x18(%rax),%ecx
  100670:	83 e1 ef             	and    $0xffffffef,%ecx
  100673:	89 48 18             	mov    %ecx,0x18(%rax)
  100676:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10067a:	8b 48 18             	mov    0x18(%rax),%ecx
  10067d:	81 e1 00 80 00 00    	and    $0x8000,%ecx
  100683:	b0 01                	mov    $0x1,%al
  100685:	83 f9 00             	cmp    $0x0,%ecx
  100688:	88 45 c7             	mov    %al,-0x39(%rbp)
  10068b:	0f 85 15 00 00 00    	jne    1006a6 <_ZN4acos7storage8AHCIPort9configureEv+0x66>
  100691:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  100695:	8b 40 18             	mov    0x18(%rax),%eax
  100698:	25 00 40 00 00       	and    $0x4000,%eax
  10069d:	83 f8 00             	cmp    $0x0,%eax
  1006a0:	0f 95 c0             	setne  %al
  1006a3:	88 45 c7             	mov    %al,-0x39(%rbp)
  1006a6:	8a 45 c7             	mov    -0x39(%rbp),%al
  1006a9:	a8 01                	test   $0x1,%al
  1006ab:	0f 85 05 00 00 00    	jne    1006b6 <_ZN4acos7storage8AHCIPort9configureEv+0x76>
  1006b1:	e9 05 00 00 00       	jmp    1006bb <_ZN4acos7storage8AHCIPort9configureEv+0x7b>
  1006b6:	e9 bb ff ff ff       	jmp    100676 <_ZN4acos7storage8AHCIPort9configureEv+0x36>
  1006bb:	e8 e0 6e 00 00       	call   1075a0 <_ZN4acos6memory9pmm_allocEv>
  1006c0:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
  1006c4:	e8 d7 6e 00 00       	call   1075a0 <_ZN4acos6memory9pmm_allocEv>
  1006c9:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  1006cd:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  1006d1:	89 c1                	mov    %eax,%ecx
  1006d3:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  1006d7:	89 08                	mov    %ecx,(%rax)
  1006d9:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  1006dd:	48 c1 e8 20          	shr    $0x20,%rax
  1006e1:	89 c1                	mov    %eax,%ecx
  1006e3:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  1006e7:	89 48 04             	mov    %ecx,0x4(%rax)
  1006ea:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  1006ee:	89 c1                	mov    %eax,%ecx
  1006f0:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  1006f4:	89 48 08             	mov    %ecx,0x8(%rax)
  1006f7:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  1006fb:	48 c1 e8 20          	shr    $0x20,%rax
  1006ff:	89 c1                	mov    %eax,%ecx
  100701:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  100705:	89 48 0c             	mov    %ecx,0xc(%rax)
  100708:	c7 45 dc 00 00 00 00 	movl   $0x0,-0x24(%rbp)
  10070f:	83 7d dc 20          	cmpl   $0x20,-0x24(%rbp)
  100713:	0f 8d 70 00 00 00    	jge    100789 <_ZN4acos7storage8AHCIPort9configureEv+0x149>
  100719:	e8 82 6e 00 00       	call   1075a0 <_ZN4acos6memory9pmm_allocEv>
  10071e:	48 89 c2             	mov    %rax,%rdx
  100721:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  100725:	48 63 4d dc          	movslq -0x24(%rbp),%rcx
  100729:	48 89 54 c8 20       	mov    %rdx,0x20(%rax,%rcx,8)
  10072e:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  100732:	48 63 55 dc          	movslq -0x24(%rbp),%rdx
  100736:	48 c1 e2 05          	shl    $0x5,%rdx
  10073a:	48 01 d1             	add    %rdx,%rcx
  10073d:	48 89 4d d0          	mov    %rcx,-0x30(%rbp)
  100741:	48 63 4d dc          	movslq -0x24(%rbp),%rcx
  100745:	48 8b 4c c8 20       	mov    0x20(%rax,%rcx,8),%rcx
  10074a:	89 ca                	mov    %ecx,%edx
  10074c:	48 8b 4d d0          	mov    -0x30(%rbp),%rcx
  100750:	89 51 08             	mov    %edx,0x8(%rcx)
  100753:	48 63 4d dc          	movslq -0x24(%rbp),%rcx
  100757:	48 8b 44 c8 20       	mov    0x20(%rax,%rcx,8),%rax
  10075c:	48 c1 e8 20          	shr    $0x20,%rax
  100760:	89 c1                	mov    %eax,%ecx
  100762:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  100766:	89 48 0c             	mov    %ecx,0xc(%rax)
  100769:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  10076d:	66 8b 08             	mov    (%rax),%cx
  100770:	66 83 e1 e0          	and    $0xffe0,%cx
  100774:	66 83 c9 00          	or     $0x0,%cx
  100778:	66 89 08             	mov    %cx,(%rax)
  10077b:	8b 45 dc             	mov    -0x24(%rbp),%eax
  10077e:	83 c0 01             	add    $0x1,%eax
  100781:	89 45 dc             	mov    %eax,-0x24(%rbp)
  100784:	e9 86 ff ff ff       	jmp    10070f <_ZN4acos7storage8AHCIPort9configureEv+0xcf>
  100789:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10078d:	8b 48 18             	mov    0x18(%rax),%ecx
  100790:	83 c9 10             	or     $0x10,%ecx
  100793:	89 48 18             	mov    %ecx,0x18(%rax)
  100796:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10079a:	8b 48 18             	mov    0x18(%rax),%ecx
  10079d:	83 c9 01             	or     $0x1,%ecx
  1007a0:	89 48 18             	mov    %ecx,0x18(%rax)
  1007a3:	48 83 c4 40          	add    $0x40,%rsp
  1007a7:	5d                   	pop    %rbp
  1007a8:	c3                   	ret
  1007a9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

00000000001007b0 <_ZN4acos7storage8AHCIPortC1EjPv>:
  1007b0:	55                   	push   %rbp
  1007b1:	48 89 e5             	mov    %rsp,%rbp
  1007b4:	48 83 ec 20          	sub    $0x20,%rsp
  1007b8:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  1007bc:	89 75 f4             	mov    %esi,-0xc(%rbp)
  1007bf:	48 89 55 e8          	mov    %rdx,-0x18(%rbp)
  1007c3:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  1007c7:	48 89 7d e0          	mov    %rdi,-0x20(%rbp)
  1007cb:	e8 90 de 00 00       	call   10e660 <_ZN4acos7storage11BlockDeviceC2Ev>
  1007d0:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  1007d4:	48 b9 d0 f2 10 00 00 	movabs $0x10f2d0,%rcx
  1007db:	00 00 00
  1007de:	48 83 c1 10          	add    $0x10,%rcx
  1007e2:	48 89 08             	mov    %rcx,(%rax)
  1007e5:	8b 4d f4             	mov    -0xc(%rbp),%ecx
  1007e8:	89 48 08             	mov    %ecx,0x8(%rax)
  1007eb:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  1007ef:	48 89 48 10          	mov    %rcx,0x10(%rax)
  1007f3:	48 c7 40 18 00 00 00 	movq   $0x0,0x18(%rax)
  1007fa:	00
  1007fb:	48 83 c4 20          	add    $0x20,%rsp
  1007ff:	5d                   	pop    %rbp
  100800:	c3                   	ret
  100801:	66 66 66 66 66 66 2e 	data16 data16 data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
  100808:	0f 1f 84 00 00 00 00
  10080f:	00

0000000000100810 <_ZN4acos7storage8AHCIPort13find_cmd_slotEv>:
  100810:	55                   	push   %rbp
  100811:	48 89 e5             	mov    %rsp,%rbp
  100814:	48 83 ec 18          	sub    $0x18,%rsp
  100818:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  10081c:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
  100820:	48 8b 41 10          	mov    0x10(%rcx),%rax
  100824:	8b 40 34             	mov    0x34(%rax),%eax
  100827:	48 8b 49 10          	mov    0x10(%rcx),%rcx
  10082b:	8b 49 38             	mov    0x38(%rcx),%ecx
  10082e:	09 c8                	or     %ecx,%eax
  100830:	89 45 ec             	mov    %eax,-0x14(%rbp)
  100833:	c7 45 e8 00 00 00 00 	movl   $0x0,-0x18(%rbp)
  10083a:	83 7d e8 20          	cmpl   $0x20,-0x18(%rbp)
  10083e:	0f 8d 32 00 00 00    	jge    100876 <_ZN4acos7storage8AHCIPort13find_cmd_slotEv+0x66>
  100844:	8b 45 ec             	mov    -0x14(%rbp),%eax
  100847:	8b 4d e8             	mov    -0x18(%rbp),%ecx
  10084a:	d3 e8                	shr    %cl,%eax
  10084c:	83 e0 01             	and    $0x1,%eax
  10084f:	83 f8 00             	cmp    $0x0,%eax
  100852:	0f 85 0b 00 00 00    	jne    100863 <_ZN4acos7storage8AHCIPort13find_cmd_slotEv+0x53>
  100858:	8b 45 e8             	mov    -0x18(%rbp),%eax
  10085b:	89 45 fc             	mov    %eax,-0x4(%rbp)
  10085e:	e9 1a 00 00 00       	jmp    10087d <_ZN4acos7storage8AHCIPort13find_cmd_slotEv+0x6d>
  100863:	e9 00 00 00 00       	jmp    100868 <_ZN4acos7storage8AHCIPort13find_cmd_slotEv+0x58>
  100868:	8b 45 e8             	mov    -0x18(%rbp),%eax
  10086b:	83 c0 01             	add    $0x1,%eax
  10086e:	89 45 e8             	mov    %eax,-0x18(%rbp)
  100871:	e9 c4 ff ff ff       	jmp    10083a <_ZN4acos7storage8AHCIPort13find_cmd_slotEv+0x2a>
  100876:	c7 45 fc ff ff ff ff 	movl   $0xffffffff,-0x4(%rbp)
  10087d:	8b 45 fc             	mov    -0x4(%rbp),%eax
  100880:	48 83 c4 18          	add    $0x18,%rsp
  100884:	5d                   	pop    %rbp
  100885:	c3                   	ret
  100886:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
  10088d:	00 00 00

0000000000100890 <_ZN4acos7storage8AHCIPort10read_blockEmPv>:
  100890:	55                   	push   %rbp
  100891:	48 89 e5             	mov    %rsp,%rbp
  100894:	48 83 ec 60          	sub    $0x60,%rsp
  100898:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  10089c:	48 89 75 e8          	mov    %rsi,-0x18(%rbp)
  1008a0:	48 89 55 e0          	mov    %rdx,-0x20(%rbp)
  1008a4:	48 8b 7d f0          	mov    -0x10(%rbp),%rdi
  1008a8:	48 89 7d a8          	mov    %rdi,-0x58(%rbp)
  1008ac:	48 8b 47 10          	mov    0x10(%rdi),%rax
  1008b0:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
  1008b4:	e8 57 ff ff ff       	call   100810 <_ZN4acos7storage8AHCIPort13find_cmd_slotEv>
  1008b9:	89 45 d4             	mov    %eax,-0x2c(%rbp)
  1008bc:	83 7d d4 ff          	cmpl   $0xffffffff,-0x2c(%rbp)
  1008c0:	0f 85 0c 00 00 00    	jne    1008d2 <_ZN4acos7storage8AHCIPort10read_blockEmPv+0x42>
  1008c6:	c7 45 fc ff ff ff ff 	movl   $0xffffffff,-0x4(%rbp)
  1008cd:	e9 e4 01 00 00       	jmp    100ab6 <_ZN4acos7storage8AHCIPort10read_blockEmPv+0x226>
  1008d2:	48 8b 45 a8          	mov    -0x58(%rbp),%rax
  1008d6:	48 8b 4d d8          	mov    -0x28(%rbp),%rcx
  1008da:	8b 49 04             	mov    0x4(%rcx),%ecx
  1008dd:	89 c9                	mov    %ecx,%ecx
  1008df:	48 c1 e1 20          	shl    $0x20,%rcx
  1008e3:	48 8b 55 d8          	mov    -0x28(%rbp),%rdx
  1008e7:	8b 12                	mov    (%rdx),%edx
  1008e9:	89 d2                	mov    %edx,%edx
  1008eb:	48 09 d1             	or     %rdx,%rcx
  1008ee:	48 89 4d c8          	mov    %rcx,-0x38(%rbp)
  1008f2:	48 8b 4d c8          	mov    -0x38(%rbp),%rcx
  1008f6:	48 63 55 d4          	movslq -0x2c(%rbp),%rdx
  1008fa:	48 c1 e2 05          	shl    $0x5,%rdx
  1008fe:	48 01 d1             	add    %rdx,%rcx
  100901:	48 89 4d c0          	mov    %rcx,-0x40(%rbp)
  100905:	48 8b 4d c0          	mov    -0x40(%rbp),%rcx
  100909:	66 8b 11             	mov    (%rcx),%dx
  10090c:	66 83 e2 e0          	and    $0xffe0,%dx
  100910:	66 83 ca 05          	or     $0x5,%dx
  100914:	66 89 11             	mov    %dx,(%rcx)
  100917:	48 8b 4d c0          	mov    -0x40(%rbp),%rcx
  10091b:	66 8b 11             	mov    (%rcx),%dx
  10091e:	66 83 e2 bf          	and    $0xffbf,%dx
  100922:	66 83 ca 00          	or     $0x0,%dx
  100926:	66 89 11             	mov    %dx,(%rcx)
  100929:	48 8b 4d c0          	mov    -0x40(%rbp),%rcx
  10092d:	66 c7 41 02 01 00    	movw   $0x1,0x2(%rcx)
  100933:	48 63 4d d4          	movslq -0x2c(%rbp),%rcx
  100937:	48 8b 44 c8 20       	mov    0x20(%rax,%rcx,8),%rax
  10093c:	48 89 45 b8          	mov    %rax,-0x48(%rbp)
  100940:	48 8b 7d b8          	mov    -0x48(%rbp),%rdi
  100944:	31 f6                	xor    %esi,%esi
  100946:	ba 00 01 00 00       	mov    $0x100,%edx
  10094b:	e8 20 f7 ff ff       	call   100070 <memset>
  100950:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  100954:	89 c1                	mov    %eax,%ecx
  100956:	48 8b 45 b8          	mov    -0x48(%rbp),%rax
  10095a:	89 88 80 00 00 00    	mov    %ecx,0x80(%rax)
  100960:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  100964:	48 c1 e8 20          	shr    $0x20,%rax
  100968:	89 c1                	mov    %eax,%ecx
  10096a:	48 8b 45 b8          	mov    -0x48(%rbp),%rax
  10096e:	89 88 84 00 00 00    	mov    %ecx,0x84(%rax)
  100974:	48 8b 45 b8          	mov    -0x48(%rbp),%rax
  100978:	8b 88 8c 00 00 00    	mov    0x8c(%rax),%ecx
  10097e:	81 e1 00 00 c0 ff    	and    $0xffc00000,%ecx
  100984:	81 c9 ff 01 00 00    	or     $0x1ff,%ecx
  10098a:	89 88 8c 00 00 00    	mov    %ecx,0x8c(%rax)
  100990:	48 8b 45 b8          	mov    -0x48(%rbp),%rax
  100994:	8b 88 8c 00 00 00    	mov    0x8c(%rax),%ecx
  10099a:	81 e1 ff ff ff 7f    	and    $0x7fffffff,%ecx
  1009a0:	81 c9 00 00 00 80    	or     $0x80000000,%ecx
  1009a6:	89 88 8c 00 00 00    	mov    %ecx,0x8c(%rax)
  1009ac:	48 8b 45 b8          	mov    -0x48(%rbp),%rax
  1009b0:	48 89 45 b0          	mov    %rax,-0x50(%rbp)
  1009b4:	48 8b 45 b0          	mov    -0x50(%rbp),%rax
  1009b8:	c6 00 27             	movb   $0x27,(%rax)
  1009bb:	48 8b 45 b0          	mov    -0x50(%rbp),%rax
  1009bf:	8a 48 01             	mov    0x1(%rax),%cl
  1009c2:	80 e1 7f             	and    $0x7f,%cl
  1009c5:	80 c9 80             	or     $0x80,%cl
  1009c8:	88 48 01             	mov    %cl,0x1(%rax)
  1009cb:	48 8b 45 b0          	mov    -0x50(%rbp),%rax
  1009cf:	c6 40 02 25          	movb   $0x25,0x2(%rax)
  1009d3:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  1009d7:	88 c1                	mov    %al,%cl
  1009d9:	48 8b 45 b0          	mov    -0x50(%rbp),%rax
  1009dd:	88 48 04             	mov    %cl,0x4(%rax)
  1009e0:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  1009e4:	48 c1 e8 08          	shr    $0x8,%rax
  1009e8:	88 c1                	mov    %al,%cl
  1009ea:	48 8b 45 b0          	mov    -0x50(%rbp),%rax
  1009ee:	88 48 05             	mov    %cl,0x5(%rax)
  1009f1:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  1009f5:	48 c1 e8 10          	shr    $0x10,%rax
  1009f9:	88 c1                	mov    %al,%cl
  1009fb:	48 8b 45 b0          	mov    -0x50(%rbp),%rax
  1009ff:	88 48 06             	mov    %cl,0x6(%rax)
  100a02:	48 8b 45 b0          	mov    -0x50(%rbp),%rax
  100a06:	c6 40 07 40          	movb   $0x40,0x7(%rax)
  100a0a:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  100a0e:	48 c1 e8 18          	shr    $0x18,%rax
  100a12:	88 c1                	mov    %al,%cl
  100a14:	48 8b 45 b0          	mov    -0x50(%rbp),%rax
  100a18:	88 48 08             	mov    %cl,0x8(%rax)
  100a1b:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  100a1f:	48 c1 e8 20          	shr    $0x20,%rax
  100a23:	88 c1                	mov    %al,%cl
  100a25:	48 8b 45 b0          	mov    -0x50(%rbp),%rax
  100a29:	88 48 09             	mov    %cl,0x9(%rax)
  100a2c:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  100a30:	48 c1 e8 28          	shr    $0x28,%rax
  100a34:	88 c1                	mov    %al,%cl
  100a36:	48 8b 45 b0          	mov    -0x50(%rbp),%rax
  100a3a:	88 48 0a             	mov    %cl,0xa(%rax)
  100a3d:	48 8b 45 b0          	mov    -0x50(%rbp),%rax
  100a41:	c6 40 0c 01          	movb   $0x1,0xc(%rax)
  100a45:	48 8b 45 b0          	mov    -0x50(%rbp),%rax
  100a49:	c6 40 0d 00          	movb   $0x0,0xd(%rax)
  100a4d:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  100a51:	c7 40 10 ff ff ff ff 	movl   $0xffffffff,0x10(%rax)
  100a58:	8b 4d d4             	mov    -0x2c(%rbp),%ecx
  100a5b:	b8 01 00 00 00       	mov    $0x1,%eax
  100a60:	d3 e0                	shl    %cl,%eax
  100a62:	89 c1                	mov    %eax,%ecx
  100a64:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  100a68:	89 48 38             	mov    %ecx,0x38(%rax)
  100a6b:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  100a6f:	8b 40 38             	mov    0x38(%rax),%eax
  100a72:	8b 4d d4             	mov    -0x2c(%rbp),%ecx
  100a75:	ba 01 00 00 00       	mov    $0x1,%edx
  100a7a:	d3 e2                	shl    %cl,%edx
  100a7c:	89 d1                	mov    %edx,%ecx
  100a7e:	21 c8                	and    %ecx,%eax
  100a80:	83 f8 00             	cmp    $0x0,%eax
  100a83:	0f 84 26 00 00 00    	je     100aaf <_ZN4acos7storage8AHCIPort10read_blockEmPv+0x21f>
  100a89:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  100a8d:	8b 40 10             	mov    0x10(%rax),%eax
  100a90:	25 00 00 00 40       	and    $0x40000000,%eax
  100a95:	83 f8 00             	cmp    $0x0,%eax
  100a98:	0f 84 0c 00 00 00    	je     100aaa <_ZN4acos7storage8AHCIPort10read_blockEmPv+0x21a>
  100a9e:	c7 45 fc ff ff ff ff 	movl   $0xffffffff,-0x4(%rbp)
  100aa5:	e9 0c 00 00 00       	jmp    100ab6 <_ZN4acos7storage8AHCIPort10read_blockEmPv+0x226>
  100aaa:	e9 bc ff ff ff       	jmp    100a6b <_ZN4acos7storage8AHCIPort10read_blockEmPv+0x1db>
  100aaf:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%rbp)
  100ab6:	8b 45 fc             	mov    -0x4(%rbp),%eax
  100ab9:	48 83 c4 60          	add    $0x60,%rsp
  100abd:	5d                   	pop    %rbp
  100abe:	c3                   	ret
  100abf:	90                   	nop

0000000000100ac0 <_ZN4acos7storage8AHCIPort11write_blockEmPKv>:
  100ac0:	55                   	push   %rbp
  100ac1:	48 89 e5             	mov    %rsp,%rbp
  100ac4:	48 83 ec 18          	sub    $0x18,%rsp
  100ac8:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  100acc:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  100ad0:	48 89 55 e8          	mov    %rdx,-0x18(%rbp)
  100ad4:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  100ad9:	48 83 c4 18          	add    $0x18,%rsp
  100add:	5d                   	pop    %rbp
  100ade:	c3                   	ret
  100adf:	90                   	nop

0000000000100ae0 <_ZN4acos7storage8AHCIPort5flushEv>:
  100ae0:	55                   	push   %rbp
  100ae1:	48 89 e5             	mov    %rsp,%rbp
  100ae4:	50                   	push   %rax
  100ae5:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  100ae9:	48 83 c4 08          	add    $0x8,%rsp
  100aed:	5d                   	pop    %rbp
  100aee:	c3                   	ret
  100aef:	90                   	nop

0000000000100af0 <_ZN4acos7storage9PartitionC1EPNS0_11BlockDeviceEmm>:
  100af0:	55                   	push   %rbp
  100af1:	48 89 e5             	mov    %rsp,%rbp
  100af4:	48 83 ec 30          	sub    $0x30,%rsp
  100af8:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  100afc:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  100b00:	48 89 55 e8          	mov    %rdx,-0x18(%rbp)
  100b04:	48 89 4d e0          	mov    %rcx,-0x20(%rbp)
  100b08:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  100b0c:	48 89 7d d8          	mov    %rdi,-0x28(%rbp)
  100b10:	e8 4b db 00 00       	call   10e660 <_ZN4acos7storage11BlockDeviceC2Ev>
  100b15:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  100b19:	48 b9 18 f3 10 00 00 	movabs $0x10f318,%rcx
  100b20:	00 00 00
  100b23:	48 83 c1 10          	add    $0x10,%rcx
  100b27:	48 89 08             	mov    %rcx,(%rax)
  100b2a:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
  100b2e:	48 89 48 08          	mov    %rcx,0x8(%rax)
  100b32:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  100b36:	48 89 48 10          	mov    %rcx,0x10(%rax)
  100b3a:	48 8b 4d e0          	mov    -0x20(%rbp),%rcx
  100b3e:	48 89 48 18          	mov    %rcx,0x18(%rax)
  100b42:	48 83 c4 30          	add    $0x30,%rsp
  100b46:	5d                   	pop    %rbp
  100b47:	c3                   	ret
  100b48:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  100b4f:	00

0000000000100b50 <_ZN4acos7storage9Partition10read_blockEmPv>:
  100b50:	55                   	push   %rbp
  100b51:	48 89 e5             	mov    %rsp,%rbp
  100b54:	48 83 ec 30          	sub    $0x30,%rsp
  100b58:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  100b5c:	48 89 75 e8          	mov    %rsi,-0x18(%rbp)
  100b60:	48 89 55 e0          	mov    %rdx,-0x20(%rbp)
  100b64:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
  100b68:	48 89 4d d8          	mov    %rcx,-0x28(%rbp)
  100b6c:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  100b70:	48 3b 41 18          	cmp    0x18(%rcx),%rax
  100b74:	0f 82 0c 00 00 00    	jb     100b86 <_ZN4acos7storage9Partition10read_blockEmPv+0x36>
  100b7a:	c7 45 fc ff ff ff ff 	movl   $0xffffffff,-0x4(%rbp)
  100b81:	e9 1d 00 00 00       	jmp    100ba3 <_ZN4acos7storage9Partition10read_blockEmPv+0x53>
  100b86:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  100b8a:	48 8b 78 08          	mov    0x8(%rax),%rdi
  100b8e:	48 8b 70 10          	mov    0x10(%rax),%rsi
  100b92:	48 03 75 e8          	add    -0x18(%rbp),%rsi
  100b96:	48 8b 55 e0          	mov    -0x20(%rbp),%rdx
  100b9a:	48 8b 07             	mov    (%rdi),%rax
  100b9d:	ff 50 10             	call   *0x10(%rax)
  100ba0:	89 45 fc             	mov    %eax,-0x4(%rbp)
  100ba3:	8b 45 fc             	mov    -0x4(%rbp),%eax
  100ba6:	48 83 c4 30          	add    $0x30,%rsp
  100baa:	5d                   	pop    %rbp
  100bab:	c3                   	ret
  100bac:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000100bb0 <_ZN4acos7storage9Partition11write_blockEmPKv>:
  100bb0:	55                   	push   %rbp
  100bb1:	48 89 e5             	mov    %rsp,%rbp
  100bb4:	48 83 ec 30          	sub    $0x30,%rsp
  100bb8:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  100bbc:	48 89 75 e8          	mov    %rsi,-0x18(%rbp)
  100bc0:	48 89 55 e0          	mov    %rdx,-0x20(%rbp)
  100bc4:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
  100bc8:	48 89 4d d8          	mov    %rcx,-0x28(%rbp)
  100bcc:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  100bd0:	48 3b 41 18          	cmp    0x18(%rcx),%rax
  100bd4:	0f 82 0c 00 00 00    	jb     100be6 <_ZN4acos7storage9Partition11write_blockEmPKv+0x36>
  100bda:	c7 45 fc ff ff ff ff 	movl   $0xffffffff,-0x4(%rbp)
  100be1:	e9 1d 00 00 00       	jmp    100c03 <_ZN4acos7storage9Partition11write_blockEmPKv+0x53>
  100be6:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  100bea:	48 8b 78 08          	mov    0x8(%rax),%rdi
  100bee:	48 8b 70 10          	mov    0x10(%rax),%rsi
  100bf2:	48 03 75 e8          	add    -0x18(%rbp),%rsi
  100bf6:	48 8b 55 e0          	mov    -0x20(%rbp),%rdx
  100bfa:	48 8b 07             	mov    (%rdi),%rax
  100bfd:	ff 50 18             	call   *0x18(%rax)
  100c00:	89 45 fc             	mov    %eax,-0x4(%rbp)
  100c03:	8b 45 fc             	mov    -0x4(%rbp),%eax
  100c06:	48 83 c4 30          	add    $0x30,%rsp
  100c0a:	5d                   	pop    %rbp
  100c0b:	c3                   	ret
  100c0c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000100c10 <_ZN4acos7storage9Partition5flushEv>:
  100c10:	55                   	push   %rbp
  100c11:	48 89 e5             	mov    %rsp,%rbp
  100c14:	48 83 ec 10          	sub    $0x10,%rsp
  100c18:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  100c1c:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  100c20:	48 8b 78 08          	mov    0x8(%rax),%rdi
  100c24:	48 8b 07             	mov    (%rdi),%rax
  100c27:	ff 50 20             	call   *0x20(%rax)
  100c2a:	48 83 c4 10          	add    $0x10,%rsp
  100c2e:	5d                   	pop    %rbp
  100c2f:	c3                   	ret

0000000000100c30 <_ZN4acos7storage16PartitionManager9enumerateEPNS0_11BlockDeviceE>:
  100c30:	55                   	push   %rbp
  100c31:	48 89 e5             	mov    %rsp,%rbp
  100c34:	48 81 ec 40 02 00 00 	sub    $0x240,%rsp
  100c3b:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  100c3f:	48 83 7d f8 00       	cmpq   $0x0,-0x8(%rbp)
  100c44:	0f 85 05 00 00 00    	jne    100c4f <_ZN4acos7storage16PartitionManager9enumerateEPNS0_11BlockDeviceE+0x1f>
  100c4a:	e9 7a 01 00 00       	jmp    100dc9 <_ZN4acos7storage16PartitionManager9enumerateEPNS0_11BlockDeviceE+0x199>
  100c4f:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  100c53:	48 8d 95 f0 fd ff ff 	lea    -0x210(%rbp),%rdx
  100c5a:	48 8b 07             	mov    (%rdi),%rax
  100c5d:	31 c9                	xor    %ecx,%ecx
  100c5f:	89 ce                	mov    %ecx,%esi
  100c61:	ff 50 10             	call   *0x10(%rax)
  100c64:	83 f8 00             	cmp    $0x0,%eax
  100c67:	0f 84 05 00 00 00    	je     100c72 <_ZN4acos7storage16PartitionManager9enumerateEPNS0_11BlockDeviceE+0x42>
  100c6d:	e9 57 01 00 00       	jmp    100dc9 <_ZN4acos7storage16PartitionManager9enumerateEPNS0_11BlockDeviceE+0x199>
  100c72:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  100c76:	48 be b0 f8 10 00 00 	movabs $0x10f8b0,%rsi
  100c7d:	00 00 00
  100c80:	e8 4b 02 00 00       	call   100ed0 <_ZN4acos7storage17FileSystemManager15probe_and_mountEPNS0_11BlockDeviceEPKc>
  100c85:	0f b6 45 ee          	movzbl -0x12(%rbp),%eax
  100c89:	83 f8 55             	cmp    $0x55,%eax
  100c8c:	0f 85 37 01 00 00    	jne    100dc9 <_ZN4acos7storage16PartitionManager9enumerateEPNS0_11BlockDeviceE+0x199>
  100c92:	0f b6 45 ef          	movzbl -0x11(%rbp),%eax
  100c96:	3d aa 00 00 00       	cmp    $0xaa,%eax
  100c9b:	0f 85 28 01 00 00    	jne    100dc9 <_ZN4acos7storage16PartitionManager9enumerateEPNS0_11BlockDeviceE+0x199>
  100ca1:	c7 85 ec fd ff ff 00 	movl   $0x0,-0x214(%rbp)
  100ca8:	00 00 00
  100cab:	83 bd ec fd ff ff 04 	cmpl   $0x4,-0x214(%rbp)
  100cb2:	0f 8d 0c 01 00 00    	jge    100dc4 <_ZN4acos7storage16PartitionManager9enumerateEPNS0_11BlockDeviceE+0x194>
  100cb8:	48 8d 85 f0 fd ff ff 	lea    -0x210(%rbp),%rax
  100cbf:	48 05 be 01 00 00    	add    $0x1be,%rax
  100cc5:	8b 8d ec fd ff ff    	mov    -0x214(%rbp),%ecx
  100ccb:	c1 e1 04             	shl    $0x4,%ecx
  100cce:	48 63 c9             	movslq %ecx,%rcx
  100cd1:	48 01 c8             	add    %rcx,%rax
  100cd4:	48 89 85 e0 fd ff ff 	mov    %rax,-0x220(%rbp)
  100cdb:	48 8b 85 e0 fd ff ff 	mov    -0x220(%rbp),%rax
  100ce2:	8a 40 04             	mov    0x4(%rax),%al
  100ce5:	88 85 df fd ff ff    	mov    %al,-0x221(%rbp)
  100ceb:	0f b6 85 df fd ff ff 	movzbl -0x221(%rbp),%eax
  100cf2:	83 f8 00             	cmp    $0x0,%eax
  100cf5:	0f 85 05 00 00 00    	jne    100d00 <_ZN4acos7storage16PartitionManager9enumerateEPNS0_11BlockDeviceE+0xd0>
  100cfb:	e9 b0 00 00 00       	jmp    100db0 <_ZN4acos7storage16PartitionManager9enumerateEPNS0_11BlockDeviceE+0x180>
  100d00:	48 8b 85 e0 fd ff ff 	mov    -0x220(%rbp),%rax
  100d07:	8b 40 08             	mov    0x8(%rax),%eax
  100d0a:	89 85 d8 fd ff ff    	mov    %eax,-0x228(%rbp)
  100d10:	48 8b 85 e0 fd ff ff 	mov    -0x220(%rbp),%rax
  100d17:	8b 40 0c             	mov    0xc(%rax),%eax
  100d1a:	89 85 d4 fd ff ff    	mov    %eax,-0x22c(%rbp)
  100d20:	83 bd d4 fd ff ff 00 	cmpl   $0x0,-0x22c(%rbp)
  100d27:	0f 85 05 00 00 00    	jne    100d32 <_ZN4acos7storage16PartitionManager9enumerateEPNS0_11BlockDeviceE+0x102>
  100d2d:	e9 7e 00 00 00       	jmp    100db0 <_ZN4acos7storage16PartitionManager9enumerateEPNS0_11BlockDeviceE+0x180>
  100d32:	bf 20 00 00 00       	mov    $0x20,%edi
  100d37:	e8 b4 f6 ff ff       	call   1003f0 <_Znwm>
  100d3c:	48 89 c7             	mov    %rax,%rdi
  100d3f:	48 89 bd c0 fd ff ff 	mov    %rdi,-0x240(%rbp)
  100d46:	48 8b 75 f8          	mov    -0x8(%rbp),%rsi
  100d4a:	8b 85 d8 fd ff ff    	mov    -0x228(%rbp),%eax
  100d50:	89 c2                	mov    %eax,%edx
  100d52:	8b 85 d4 fd ff ff    	mov    -0x22c(%rbp),%eax
  100d58:	89 c1                	mov    %eax,%ecx
  100d5a:	e8 91 fd ff ff       	call   100af0 <_ZN4acos7storage9PartitionC1EPNS0_11BlockDeviceEmm>
  100d5f:	48 8b 85 c0 fd ff ff 	mov    -0x240(%rbp),%rax
  100d66:	48 89 85 c8 fd ff ff 	mov    %rax,-0x238(%rbp)
  100d6d:	48 83 bd c8 fd ff ff 	cmpq   $0x0,-0x238(%rbp)
  100d74:	00
  100d75:	0f 84 30 00 00 00    	je     100dab <_ZN4acos7storage16PartitionManager9enumerateEPNS0_11BlockDeviceE+0x17b>
  100d7b:	8b 85 ec fd ff ff    	mov    -0x214(%rbp),%eax
  100d81:	05 00 01 00 00       	add    $0x100,%eax
  100d86:	48 63 f8             	movslq %eax,%rdi
  100d89:	48 8b b5 c8 fd ff ff 	mov    -0x238(%rbp),%rsi
  100d90:	e8 2b 1e 00 00       	call   102bc0 <_ZN4acos7storage14StorageManager15register_deviceEmPNS0_11BlockDeviceE>
  100d95:	48 8b bd c8 fd ff ff 	mov    -0x238(%rbp),%rdi
  100d9c:	48 be b0 f8 10 00 00 	movabs $0x10f8b0,%rsi
  100da3:	00 00 00
  100da6:	e8 25 01 00 00       	call   100ed0 <_ZN4acos7storage17FileSystemManager15probe_and_mountEPNS0_11BlockDeviceEPKc>
  100dab:	e9 00 00 00 00       	jmp    100db0 <_ZN4acos7storage16PartitionManager9enumerateEPNS0_11BlockDeviceE+0x180>
  100db0:	8b 85 ec fd ff ff    	mov    -0x214(%rbp),%eax
  100db6:	83 c0 01             	add    $0x1,%eax
  100db9:	89 85 ec fd ff ff    	mov    %eax,-0x214(%rbp)
  100dbf:	e9 e7 fe ff ff       	jmp    100cab <_ZN4acos7storage16PartitionManager9enumerateEPNS0_11BlockDeviceE+0x7b>
  100dc4:	e9 00 00 00 00       	jmp    100dc9 <_ZN4acos7storage16PartitionManager9enumerateEPNS0_11BlockDeviceE+0x199>
  100dc9:	48 81 c4 40 02 00 00 	add    $0x240,%rsp
  100dd0:	5d                   	pop    %rbp
  100dd1:	c3                   	ret
  100dd2:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
  100dd9:	00 00 00
  100ddc:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000100de0 <_ZN4acos7storage17FileSystemManager19register_filesystemEPKcPNS_3vfs10FileSystemE>:
  100de0:	55                   	push   %rbp
  100de1:	48 89 e5             	mov    %rsp,%rbp
  100de4:	48 83 ec 20          	sub    $0x20,%rsp
  100de8:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  100dec:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  100df0:	48 83 3c 25 80 46 15 	cmpq   $0x8,0x154680
  100df7:	00 08
  100df9:	0f 83 c3 00 00 00    	jae    100ec2 <_ZN4acos7storage17FileSystemManager19register_filesystemEPKcPNS_3vfs10FileSystemE+0xe2>
  100dff:	48 c7 45 e8 00 00 00 	movq   $0x0,-0x18(%rbp)
  100e06:	00
  100e07:	48 8b 4d f8          	mov    -0x8(%rbp),%rcx
  100e0b:	48 8b 55 e8          	mov    -0x18(%rbp),%rdx
  100e0f:	31 c0                	xor    %eax,%eax
  100e11:	80 3c 11 00          	cmpb   $0x0,(%rcx,%rdx,1)
  100e15:	88 45 e7             	mov    %al,-0x19(%rbp)
  100e18:	0f 84 0b 00 00 00    	je     100e29 <_ZN4acos7storage17FileSystemManager19register_filesystemEPKcPNS_3vfs10FileSystemE+0x49>
  100e1e:	48 83 7d e8 1f       	cmpq   $0x1f,-0x18(%rbp)
  100e23:	0f 92 c0             	setb   %al
  100e26:	88 45 e7             	mov    %al,-0x19(%rbp)
  100e29:	8a 45 e7             	mov    -0x19(%rbp),%al
  100e2c:	a8 01                	test   $0x1,%al
  100e2e:	0f 85 05 00 00 00    	jne    100e39 <_ZN4acos7storage17FileSystemManager19register_filesystemEPKcPNS_3vfs10FileSystemE+0x59>
  100e34:	e9 39 00 00 00       	jmp    100e72 <_ZN4acos7storage17FileSystemManager19register_filesystemEPKcPNS_3vfs10FileSystemE+0x92>
  100e39:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  100e3d:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  100e41:	8a 14 08             	mov    (%rax,%rcx,1),%dl
  100e44:	48 b8 40 45 15 00 00 	movabs $0x154540,%rax
  100e4b:	00 00 00
  100e4e:	48 6b 0c 25 80 46 15 	imul   $0x28,0x154680,%rcx
  100e55:	00 28
  100e57:	48 01 c8             	add    %rcx,%rax
  100e5a:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  100e5e:	88 14 08             	mov    %dl,(%rax,%rcx,1)
  100e61:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  100e65:	48 83 c0 01          	add    $0x1,%rax
  100e69:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
  100e6d:	e9 95 ff ff ff       	jmp    100e07 <_ZN4acos7storage17FileSystemManager19register_filesystemEPKcPNS_3vfs10FileSystemE+0x27>
  100e72:	48 b8 40 45 15 00 00 	movabs $0x154540,%rax
  100e79:	00 00 00
  100e7c:	48 6b 0c 25 80 46 15 	imul   $0x28,0x154680,%rcx
  100e83:	00 28
  100e85:	48 01 c8             	add    %rcx,%rax
  100e88:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  100e8c:	c6 04 08 00          	movb   $0x0,(%rax,%rcx,1)
  100e90:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
  100e94:	48 b8 40 45 15 00 00 	movabs $0x154540,%rax
  100e9b:	00 00 00
  100e9e:	48 6b 14 25 80 46 15 	imul   $0x28,0x154680,%rdx
  100ea5:	00 28
  100ea7:	48 01 d0             	add    %rdx,%rax
  100eaa:	48 89 48 20          	mov    %rcx,0x20(%rax)
  100eae:	48 8b 04 25 80 46 15 	mov    0x154680,%rax
  100eb5:	00
  100eb6:	48 83 c0 01          	add    $0x1,%rax
  100eba:	48 89 04 25 80 46 15 	mov    %rax,0x154680
  100ec1:	00
  100ec2:	48 83 c4 20          	add    $0x20,%rsp
  100ec6:	5d                   	pop    %rbp
  100ec7:	c3                   	ret
  100ec8:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  100ecf:	00

0000000000100ed0 <_ZN4acos7storage17FileSystemManager15probe_and_mountEPNS0_11BlockDeviceEPKc>:
  100ed0:	55                   	push   %rbp
  100ed1:	48 89 e5             	mov    %rsp,%rbp
  100ed4:	48 83 ec 20          	sub    $0x20,%rsp
  100ed8:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  100edc:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  100ee0:	48 83 7d f8 00       	cmpq   $0x0,-0x8(%rbp)
  100ee5:	0f 84 0b 00 00 00    	je     100ef6 <_ZN4acos7storage17FileSystemManager15probe_and_mountEPNS0_11BlockDeviceEPKc+0x26>
  100eeb:	48 83 7d f0 00       	cmpq   $0x0,-0x10(%rbp)
  100ef0:	0f 85 05 00 00 00    	jne    100efb <_ZN4acos7storage17FileSystemManager15probe_and_mountEPNS0_11BlockDeviceEPKc+0x2b>
  100ef6:	e9 f2 00 00 00       	jmp    100fed <_ZN4acos7storage17FileSystemManager15probe_and_mountEPNS0_11BlockDeviceEPKc+0x11d>
  100efb:	48 c7 45 e8 00 00 00 	movq   $0x0,-0x18(%rbp)
  100f02:	00
  100f03:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  100f07:	48 3b 04 25 80 46 15 	cmp    0x154680,%rax
  100f0e:	00
  100f0f:	0f 83 b1 00 00 00    	jae    100fc6 <_ZN4acos7storage17FileSystemManager15probe_and_mountEPNS0_11BlockDeviceEPKc+0xf6>
  100f15:	48 b8 40 45 15 00 00 	movabs $0x154540,%rax
  100f1c:	00 00 00
  100f1f:	48 6b 4d e8 28       	imul   $0x28,-0x18(%rbp),%rcx
  100f24:	48 01 c8             	add    %rcx,%rax
  100f27:	48 8b 40 20          	mov    0x20(%rax),%rax
  100f2b:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  100f2f:	48 83 7d e0 00       	cmpq   $0x0,-0x20(%rbp)
  100f34:	0f 85 05 00 00 00    	jne    100f3f <_ZN4acos7storage17FileSystemManager15probe_and_mountEPNS0_11BlockDeviceEPKc+0x6f>
  100f3a:	e9 76 00 00 00       	jmp    100fb5 <_ZN4acos7storage17FileSystemManager15probe_and_mountEPNS0_11BlockDeviceEPKc+0xe5>
  100f3f:	48 8b 7d e0          	mov    -0x20(%rbp),%rdi
  100f43:	48 8b 75 f8          	mov    -0x8(%rbp),%rsi
  100f47:	48 8b 55 f0          	mov    -0x10(%rbp),%rdx
  100f4b:	48 8b 07             	mov    (%rdi),%rax
  100f4e:	ff 50 20             	call   *0x20(%rax)
  100f51:	a8 01                	test   $0x1,%al
  100f53:	0f 85 05 00 00 00    	jne    100f5e <_ZN4acos7storage17FileSystemManager15probe_and_mountEPNS0_11BlockDeviceEPKc+0x8e>
  100f59:	e9 52 00 00 00       	jmp    100fb0 <_ZN4acos7storage17FileSystemManager15probe_and_mountEPNS0_11BlockDeviceEPKc+0xe0>
  100f5e:	48 bf b2 f8 10 00 00 	movabs $0x10f8b2,%rdi
  100f65:	00 00 00
  100f68:	e8 23 95 00 00       	call   10a490 <_ZN4acos3hal12serial_printEPKc>
  100f6d:	48 bf 40 45 15 00 00 	movabs $0x154540,%rdi
  100f74:	00 00 00
  100f77:	48 6b 45 e8 28       	imul   $0x28,-0x18(%rbp),%rax
  100f7c:	48 01 c7             	add    %rax,%rdi
  100f7f:	e8 0c 95 00 00       	call   10a490 <_ZN4acos3hal12serial_printEPKc>
  100f84:	48 bf e9 f8 10 00 00 	movabs $0x10f8e9,%rdi
  100f8b:	00 00 00
  100f8e:	e8 fd 94 00 00       	call   10a490 <_ZN4acos3hal12serial_printEPKc>
  100f93:	48 8b 7d f0          	mov    -0x10(%rbp),%rdi
  100f97:	e8 f4 94 00 00       	call   10a490 <_ZN4acos3hal12serial_printEPKc>
  100f9c:	48 bf 04 f9 10 00 00 	movabs $0x10f904,%rdi
  100fa3:	00 00 00
  100fa6:	e8 e5 94 00 00       	call   10a490 <_ZN4acos3hal12serial_printEPKc>
  100fab:	e9 3d 00 00 00       	jmp    100fed <_ZN4acos7storage17FileSystemManager15probe_and_mountEPNS0_11BlockDeviceEPKc+0x11d>
  100fb0:	e9 00 00 00 00       	jmp    100fb5 <_ZN4acos7storage17FileSystemManager15probe_and_mountEPNS0_11BlockDeviceEPKc+0xe5>
  100fb5:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  100fb9:	48 83 c0 01          	add    $0x1,%rax
  100fbd:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
  100fc1:	e9 3d ff ff ff       	jmp    100f03 <_ZN4acos7storage17FileSystemManager15probe_and_mountEPNS0_11BlockDeviceEPKc+0x33>
  100fc6:	48 bf c7 f8 10 00 00 	movabs $0x10f8c7,%rdi
  100fcd:	00 00 00
  100fd0:	e8 bb 94 00 00       	call   10a490 <_ZN4acos3hal12serial_printEPKc>
  100fd5:	48 8b 7d f0          	mov    -0x10(%rbp),%rdi
  100fd9:	e8 b2 94 00 00       	call   10a490 <_ZN4acos3hal12serial_printEPKc>
  100fde:	48 bf 04 f9 10 00 00 	movabs $0x10f904,%rdi
  100fe5:	00 00 00
  100fe8:	e8 a3 94 00 00       	call   10a490 <_ZN4acos3hal12serial_printEPKc>
  100fed:	48 83 c4 20          	add    $0x20,%rsp
  100ff1:	5d                   	pop    %rbp
  100ff2:	c3                   	ret
  100ff3:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
  100ffa:	00 00 00
  100ffd:	0f 1f 00             	nopl   (%rax)

0000000000101000 <__cxx_global_var_init>:
  101000:	55                   	push   %rbp
  101001:	48 89 e5             	mov    %rsp,%rbp
  101004:	48 83 ec 10          	sub    $0x10,%rsp
  101008:	48 b8 90 46 15 00 00 	movabs $0x154690,%rax
  10100f:	00 00 00
  101012:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  101016:	e9 00 00 00 00       	jmp    10101b <__cxx_global_var_init+0x1b>
  10101b:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  10101f:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  101023:	e8 38 00 00 00       	call   101060 <_ZN4acos7storage12_GLOBAL__N_113FAT32FileNodeC2Ev>
  101028:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10102c:	48 83 c0 30          	add    $0x30,%rax
  101030:	48 b9 90 46 15 00 00 	movabs $0x154690,%rcx
  101037:	00 00 00
  10103a:	48 81 c1 00 0c 00 00 	add    $0xc00,%rcx
  101041:	48 39 c8             	cmp    %rcx,%rax
  101044:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  101048:	0f 85 cd ff ff ff    	jne    10101b <__cxx_global_var_init+0x1b>
  10104e:	48 83 c4 10          	add    $0x10,%rsp
  101052:	5d                   	pop    %rbp
  101053:	c3                   	ret
  101054:	66 66 66 2e 0f 1f 84 	data16 data16 cs nopw 0x0(%rax,%rax,1)
  10105b:	00 00 00 00 00

0000000000101060 <_ZN4acos7storage12_GLOBAL__N_113FAT32FileNodeC2Ev>:
  101060:	55                   	push   %rbp
  101061:	48 89 e5             	mov    %rsp,%rbp
  101064:	48 83 ec 10          	sub    $0x10,%rsp
  101068:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10106c:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  101070:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  101074:	e8 77 d8 00 00       	call   10e8f0 <_ZN4acos3vfs4NodeC2Ev>
  101079:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10107d:	48 b9 98 f3 10 00 00 	movabs $0x10f398,%rcx
  101084:	00 00 00
  101087:	48 83 c1 10          	add    $0x10,%rcx
  10108b:	48 89 08             	mov    %rcx,(%rax)
  10108e:	c6 40 08 00          	movb   $0x0,0x8(%rax)
  101092:	48 c7 40 10 00 00 00 	movq   $0x0,0x10(%rax)
  101099:	00
  10109a:	c7 40 18 00 00 00 00 	movl   $0x0,0x18(%rax)
  1010a1:	c7 40 1c 00 00 00 00 	movl   $0x0,0x1c(%rax)
  1010a8:	c7 40 20 00 00 00 00 	movl   $0x0,0x20(%rax)
  1010af:	c7 40 24 00 00 00 00 	movl   $0x0,0x24(%rax)
  1010b6:	c6 40 28 00          	movb   $0x0,0x28(%rax)
  1010ba:	48 83 c4 10          	add    $0x10,%rsp
  1010be:	5d                   	pop    %rbp
  1010bf:	c3                   	ret

00000000001010c0 <__cxx_global_var_init.1>:
  1010c0:	55                   	push   %rbp
  1010c1:	48 89 e5             	mov    %rsp,%rbp
  1010c4:	48 83 ec 10          	sub    $0x10,%rsp
  1010c8:	48 b8 90 52 15 00 00 	movabs $0x155290,%rax
  1010cf:	00 00 00
  1010d2:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  1010d6:	e9 00 00 00 00       	jmp    1010db <__cxx_global_var_init.1+0x1b>
  1010db:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  1010df:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  1010e3:	e8 38 00 00 00       	call   101120 <_ZN4acos7storage12_GLOBAL__N_112FAT32DirNodeC2Ev>
  1010e8:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  1010ec:	48 83 c0 28          	add    $0x28,%rax
  1010f0:	48 b9 90 52 15 00 00 	movabs $0x155290,%rcx
  1010f7:	00 00 00
  1010fa:	48 81 c1 80 02 00 00 	add    $0x280,%rcx
  101101:	48 39 c8             	cmp    %rcx,%rax
  101104:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  101108:	0f 85 cd ff ff ff    	jne    1010db <__cxx_global_var_init.1+0x1b>
  10110e:	48 83 c4 10          	add    $0x10,%rsp
  101112:	5d                   	pop    %rbp
  101113:	c3                   	ret
  101114:	66 66 66 2e 0f 1f 84 	data16 data16 cs nopw 0x0(%rax,%rax,1)
  10111b:	00 00 00 00 00

0000000000101120 <_ZN4acos7storage12_GLOBAL__N_112FAT32DirNodeC2Ev>:
  101120:	55                   	push   %rbp
  101121:	48 89 e5             	mov    %rsp,%rbp
  101124:	48 83 ec 10          	sub    $0x10,%rsp
  101128:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10112c:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  101130:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  101134:	e8 b7 d7 00 00       	call   10e8f0 <_ZN4acos3vfs4NodeC2Ev>
  101139:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10113d:	48 b9 e0 f3 10 00 00 	movabs $0x10f3e0,%rcx
  101144:	00 00 00
  101147:	48 83 c1 10          	add    $0x10,%rcx
  10114b:	48 89 08             	mov    %rcx,(%rax)
  10114e:	c6 40 08 00          	movb   $0x0,0x8(%rax)
  101152:	48 c7 40 10 00 00 00 	movq   $0x0,0x10(%rax)
  101159:	00
  10115a:	c7 40 18 00 00 00 00 	movl   $0x0,0x18(%rax)
  101161:	c7 40 1c 00 00 00 00 	movl   $0x0,0x1c(%rax)
  101168:	c7 40 20 00 00 00 00 	movl   $0x0,0x20(%rax)
  10116f:	c6 40 24 00          	movb   $0x0,0x24(%rax)
  101173:	48 83 c4 10          	add    $0x10,%rsp
  101177:	5d                   	pop    %rbp
  101178:	c3                   	ret
  101179:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000101180 <_ZN4acos7storage15FAT32FileSystemC1EPNS0_11BlockDeviceE>:
  101180:	55                   	push   %rbp
  101181:	48 89 e5             	mov    %rsp,%rbp
  101184:	48 83 ec 20          	sub    $0x20,%rsp
  101188:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10118c:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  101190:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  101194:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
  101198:	e8 43 d6 00 00       	call   10e7e0 <_ZN4acos3vfs10FileSystemC2Ev>
  10119d:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  1011a1:	48 b9 60 f3 10 00 00 	movabs $0x10f360,%rcx
  1011a8:	00 00 00
  1011ab:	48 83 c1 10          	add    $0x10,%rcx
  1011af:	48 89 08             	mov    %rcx,(%rax)
  1011b2:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
  1011b6:	48 89 48 08          	mov    %rcx,0x8(%rax)
  1011ba:	48 83 c4 20          	add    $0x20,%rsp
  1011be:	5d                   	pop    %rbp
  1011bf:	c3                   	ret

00000000001011c0 <_ZN4acos7storage15FAT32FileSystem4openEPKc>:
  1011c0:	55                   	push   %rbp
  1011c1:	48 89 e5             	mov    %rsp,%rbp
  1011c4:	48 83 ec 30          	sub    $0x30,%rsp
  1011c8:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  1011cc:	48 89 75 e8          	mov    %rsi,-0x18(%rbp)
  1011d0:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  1011d4:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
  1011d8:	48 83 7d e8 00       	cmpq   $0x0,-0x18(%rbp)
  1011dd:	0f 84 0f 00 00 00    	je     1011f2 <_ZN4acos7storage15FAT32FileSystem4openEPKc+0x32>
  1011e3:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  1011e7:	48 83 78 08 00       	cmpq   $0x0,0x8(%rax)
  1011ec:	0f 85 0d 00 00 00    	jne    1011ff <_ZN4acos7storage15FAT32FileSystem4openEPKc+0x3f>
  1011f2:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  1011f9:	00
  1011fa:	e9 8d 00 00 00       	jmp    10128c <_ZN4acos7storage15FAT32FileSystem4openEPKc+0xcc>
  1011ff:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  101203:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  101207:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  10120b:	0f be 00             	movsbl (%rax),%eax
  10120e:	83 f8 2f             	cmp    $0x2f,%eax
  101211:	0f 85 11 00 00 00    	jne    101228 <_ZN4acos7storage15FAT32FileSystem4openEPKc+0x68>
  101217:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  10121b:	48 83 c0 01          	add    $0x1,%rax
  10121f:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  101223:	e9 df ff ff ff       	jmp    101207 <_ZN4acos7storage15FAT32FileSystem4openEPKc+0x47>
  101228:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  10122c:	0f be 00             	movsbl (%rax),%eax
  10122f:	83 f8 00             	cmp    $0x0,%eax
  101232:	0f 84 1c 00 00 00    	je     101254 <_ZN4acos7storage15FAT32FileSystem4openEPKc+0x94>
  101238:	48 8b 7d e0          	mov    -0x20(%rbp),%rdi
  10123c:	48 be ee f8 10 00 00 	movabs $0x10f8ee,%rsi
  101243:	00 00 00
  101246:	e8 15 f0 ff ff       	call   100260 <strcmp>
  10124b:	83 f8 00             	cmp    $0x0,%eax
  10124e:	0f 85 24 00 00 00    	jne    101278 <_ZN4acos7storage15FAT32FileSystem4openEPKc+0xb8>
  101254:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  101258:	48 8b 78 08          	mov    0x8(%rax),%rdi
  10125c:	8b 70 20             	mov    0x20(%rax),%esi
  10125f:	8b 50 24             	mov    0x24(%rax),%edx
  101262:	8b 48 28             	mov    0x28(%rax),%ecx
  101265:	44 0f b6 40 12       	movzbl 0x12(%rax),%r8d
  10126a:	e8 31 00 00 00       	call   1012a0 <_ZN4acos7storage12_GLOBAL__N_117allocate_dir_nodeEPNS0_11BlockDeviceEjjjh>
  10126f:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  101273:	e9 14 00 00 00       	jmp    10128c <_ZN4acos7storage15FAT32FileSystem4openEPKc+0xcc>
  101278:	48 8b 7d d8          	mov    -0x28(%rbp),%rdi
  10127c:	8b 77 20             	mov    0x20(%rdi),%esi
  10127f:	48 8b 55 e0          	mov    -0x20(%rbp),%rdx
  101283:	e8 f8 00 00 00       	call   101380 <_ZN4acos7storage15FAT32FileSystem13open_internalEjPKc>
  101288:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  10128c:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  101290:	48 83 c4 30          	add    $0x30,%rsp
  101294:	5d                   	pop    %rbp
  101295:	c3                   	ret
  101296:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
  10129d:	00 00 00

00000000001012a0 <_ZN4acos7storage12_GLOBAL__N_117allocate_dir_nodeEPNS0_11BlockDeviceEjjjh>:
  1012a0:	55                   	push   %rbp
  1012a1:	48 89 e5             	mov    %rsp,%rbp
  1012a4:	48 83 ec 30          	sub    $0x30,%rsp
  1012a8:	44 88 c0             	mov    %r8b,%al
  1012ab:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  1012af:	89 75 ec             	mov    %esi,-0x14(%rbp)
  1012b2:	89 55 e8             	mov    %edx,-0x18(%rbp)
  1012b5:	89 4d e4             	mov    %ecx,-0x1c(%rbp)
  1012b8:	88 45 e3             	mov    %al,-0x1d(%rbp)
  1012bb:	c7 45 dc 00 00 00 00 	movl   $0x0,-0x24(%rbp)
  1012c2:	83 7d dc 10          	cmpl   $0x10,-0x24(%rbp)
  1012c6:	0f 8d 96 00 00 00    	jge    101362 <_ZN4acos7storage12_GLOBAL__N_117allocate_dir_nodeEPNS0_11BlockDeviceEjjjh+0xc2>
  1012cc:	48 63 4d dc          	movslq -0x24(%rbp),%rcx
  1012d0:	48 b8 90 52 15 00 00 	movabs $0x155290,%rax
  1012d7:	00 00 00
  1012da:	48 6b c9 28          	imul   $0x28,%rcx,%rcx
  1012de:	48 01 c8             	add    %rcx,%rax
  1012e1:	f6 40 08 01          	testb  $0x1,0x8(%rax)
  1012e5:	0f 85 64 00 00 00    	jne    10134f <_ZN4acos7storage12_GLOBAL__N_117allocate_dir_nodeEPNS0_11BlockDeviceEjjjh+0xaf>
  1012eb:	48 63 4d dc          	movslq -0x24(%rbp),%rcx
  1012ef:	48 b8 90 52 15 00 00 	movabs $0x155290,%rax
  1012f6:	00 00 00
  1012f9:	48 6b c9 28          	imul   $0x28,%rcx,%rcx
  1012fd:	48 01 c8             	add    %rcx,%rax
  101300:	c6 40 08 01          	movb   $0x1,0x8(%rax)
  101304:	48 63 45 dc          	movslq -0x24(%rbp),%rax
  101308:	48 bf 90 52 15 00 00 	movabs $0x155290,%rdi
  10130f:	00 00 00
  101312:	48 6b c0 28          	imul   $0x28,%rax,%rax
  101316:	48 01 c7             	add    %rax,%rdi
  101319:	48 8b 75 f0          	mov    -0x10(%rbp),%rsi
  10131d:	8b 55 ec             	mov    -0x14(%rbp),%edx
  101320:	8b 4d e8             	mov    -0x18(%rbp),%ecx
  101323:	44 8b 45 e4          	mov    -0x1c(%rbp),%r8d
  101327:	44 0f b6 4d e3       	movzbl -0x1d(%rbp),%r9d
  10132c:	e8 6f 16 00 00       	call   1029a0 <_ZN4acos7storage12_GLOBAL__N_112FAT32DirNode10initializeEPNS0_11BlockDeviceEjjjh>
  101331:	48 63 4d dc          	movslq -0x24(%rbp),%rcx
  101335:	48 b8 90 52 15 00 00 	movabs $0x155290,%rax
  10133c:	00 00 00
  10133f:	48 6b c9 28          	imul   $0x28,%rcx,%rcx
  101343:	48 01 c8             	add    %rcx,%rax
  101346:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  10134a:	e9 1b 00 00 00       	jmp    10136a <_ZN4acos7storage12_GLOBAL__N_117allocate_dir_nodeEPNS0_11BlockDeviceEjjjh+0xca>
  10134f:	e9 00 00 00 00       	jmp    101354 <_ZN4acos7storage12_GLOBAL__N_117allocate_dir_nodeEPNS0_11BlockDeviceEjjjh+0xb4>
  101354:	8b 45 dc             	mov    -0x24(%rbp),%eax
  101357:	83 c0 01             	add    $0x1,%eax
  10135a:	89 45 dc             	mov    %eax,-0x24(%rbp)
  10135d:	e9 60 ff ff ff       	jmp    1012c2 <_ZN4acos7storage12_GLOBAL__N_117allocate_dir_nodeEPNS0_11BlockDeviceEjjjh+0x22>
  101362:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  101369:	00
  10136a:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10136e:	48 83 c4 30          	add    $0x30,%rsp
  101372:	5d                   	pop    %rbp
  101373:	c3                   	ret
  101374:	66 66 66 2e 0f 1f 84 	data16 data16 cs nopw 0x0(%rax,%rax,1)
  10137b:	00 00 00 00 00

0000000000101380 <_ZN4acos7storage15FAT32FileSystem13open_internalEjPKc>:
  101380:	55                   	push   %rbp
  101381:	48 89 e5             	mov    %rsp,%rbp
  101384:	48 81 ec 80 03 00 00 	sub    $0x380,%rsp
  10138b:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  10138f:	89 75 ec             	mov    %esi,-0x14(%rbp)
  101392:	48 89 55 e0          	mov    %rdx,-0x20(%rbp)
  101396:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10139a:	48 89 85 88 fc ff ff 	mov    %rax,-0x378(%rbp)
  1013a1:	c7 85 dc fc ff ff 00 	movl   $0x0,-0x324(%rbp)
  1013a8:	00 00 00
  1013ab:	48 8b 4d e0          	mov    -0x20(%rbp),%rcx
  1013af:	48 63 95 dc fc ff ff 	movslq -0x324(%rbp),%rdx
  1013b6:	31 c0                	xor    %eax,%eax
  1013b8:	80 3c 11 00          	cmpb   $0x0,(%rcx,%rdx,1)
  1013bc:	88 85 87 fc ff ff    	mov    %al,-0x379(%rbp)
  1013c2:	0f 84 1b 00 00 00    	je     1013e3 <_ZN4acos7storage15FAT32FileSystem13open_internalEjPKc+0x63>
  1013c8:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  1013cc:	48 63 8d dc fc ff ff 	movslq -0x324(%rbp),%rcx
  1013d3:	0f be 04 08          	movsbl (%rax,%rcx,1),%eax
  1013d7:	83 f8 2f             	cmp    $0x2f,%eax
  1013da:	0f 95 c0             	setne  %al
  1013dd:	88 85 87 fc ff ff    	mov    %al,-0x379(%rbp)
  1013e3:	8a 85 87 fc ff ff    	mov    -0x379(%rbp),%al
  1013e9:	a8 01                	test   $0x1,%al
  1013eb:	0f 85 05 00 00 00    	jne    1013f6 <_ZN4acos7storage15FAT32FileSystem13open_internalEjPKc+0x76>
  1013f1:	e9 52 00 00 00       	jmp    101448 <_ZN4acos7storage15FAT32FileSystem13open_internalEjPKc+0xc8>
  1013f6:	81 bd dc fc ff ff ff 	cmpl   $0xff,-0x324(%rbp)
  1013fd:	00 00 00
  101400:	0f 8d 30 00 00 00    	jge    101436 <_ZN4acos7storage15FAT32FileSystem13open_internalEjPKc+0xb6>
  101406:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  10140a:	48 63 8d dc fc ff ff 	movslq -0x324(%rbp),%rcx
  101411:	8a 0c 08             	mov    (%rax,%rcx,1),%cl
  101414:	48 63 85 dc fc ff ff 	movslq -0x324(%rbp),%rax
  10141b:	88 8c 05 e0 fc ff ff 	mov    %cl,-0x320(%rbp,%rax,1)
  101422:	8b 85 dc fc ff ff    	mov    -0x324(%rbp),%eax
  101428:	83 c0 01             	add    $0x1,%eax
  10142b:	89 85 dc fc ff ff    	mov    %eax,-0x324(%rbp)
  101431:	e9 0d 00 00 00       	jmp    101443 <_ZN4acos7storage15FAT32FileSystem13open_internalEjPKc+0xc3>
  101436:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  10143d:	00
  10143e:	e9 e1 04 00 00       	jmp    101924 <_ZN4acos7storage15FAT32FileSystem13open_internalEjPKc+0x5a4>
  101443:	e9 63 ff ff ff       	jmp    1013ab <_ZN4acos7storage15FAT32FileSystem13open_internalEjPKc+0x2b>
  101448:	48 63 85 dc fc ff ff 	movslq -0x324(%rbp),%rax
  10144f:	c6 84 05 e0 fc ff ff 	movb   $0x0,-0x320(%rbp,%rax,1)
  101456:	00
  101457:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  10145b:	48 63 8d dc fc ff ff 	movslq -0x324(%rbp),%rcx
  101462:	48 01 c8             	add    %rcx,%rax
  101465:	48 89 85 d0 fc ff ff 	mov    %rax,-0x330(%rbp)
  10146c:	48 8b 85 d0 fc ff ff 	mov    -0x330(%rbp),%rax
  101473:	0f be 00             	movsbl (%rax),%eax
  101476:	83 f8 2f             	cmp    $0x2f,%eax
  101479:	0f 85 17 00 00 00    	jne    101496 <_ZN4acos7storage15FAT32FileSystem13open_internalEjPKc+0x116>
  10147f:	48 8b 85 d0 fc ff ff 	mov    -0x330(%rbp),%rax
  101486:	48 83 c0 01          	add    $0x1,%rax
  10148a:	48 89 85 d0 fc ff ff 	mov    %rax,-0x330(%rbp)
  101491:	e9 d6 ff ff ff       	jmp    10146c <_ZN4acos7storage15FAT32FileSystem13open_internalEjPKc+0xec>
  101496:	83 bd dc fc ff ff 00 	cmpl   $0x0,-0x324(%rbp)
  10149d:	0f 85 27 00 00 00    	jne    1014ca <_ZN4acos7storage15FAT32FileSystem13open_internalEjPKc+0x14a>
  1014a3:	48 8b 85 88 fc ff ff 	mov    -0x378(%rbp),%rax
  1014aa:	48 8b 78 08          	mov    0x8(%rax),%rdi
  1014ae:	8b 75 ec             	mov    -0x14(%rbp),%esi
  1014b1:	8b 50 24             	mov    0x24(%rax),%edx
  1014b4:	8b 48 28             	mov    0x28(%rax),%ecx
  1014b7:	44 0f b6 40 12       	movzbl 0x12(%rax),%r8d
  1014bc:	e8 df fd ff ff       	call   1012a0 <_ZN4acos7storage12_GLOBAL__N_117allocate_dir_nodeEPNS0_11BlockDeviceEjjjh>
  1014c1:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  1014c5:	e9 5a 04 00 00       	jmp    101924 <_ZN4acos7storage15FAT32FileSystem13open_internalEjPKc+0x5a4>
  1014ca:	48 bf f0 f8 10 00 00 	movabs $0x10f8f0,%rdi
  1014d1:	00 00 00
  1014d4:	e8 b7 8f 00 00       	call   10a490 <_ZN4acos3hal12serial_printEPKc>
  1014d9:	48 8d bd e0 fc ff ff 	lea    -0x320(%rbp),%rdi
  1014e0:	e8 ab 8f 00 00       	call   10a490 <_ZN4acos3hal12serial_printEPKc>
  1014e5:	48 bf 03 f9 10 00 00 	movabs $0x10f903,%rdi
  1014ec:	00 00 00
  1014ef:	e8 9c 8f 00 00       	call   10a490 <_ZN4acos3hal12serial_printEPKc>
  1014f4:	31 c0                	xor    %eax,%eax
  1014f6:	83 7d ec 02          	cmpl   $0x2,-0x14(%rbp)
  1014fa:	88 85 86 fc ff ff    	mov    %al,-0x37a(%rbp)
  101500:	0f 82 10 00 00 00    	jb     101516 <_ZN4acos7storage15FAT32FileSystem13open_internalEjPKc+0x196>
  101506:	81 7d ec f8 ff ff 0f 	cmpl   $0xffffff8,-0x14(%rbp)
  10150d:	0f 92 c0             	setb   %al
  101510:	88 85 86 fc ff ff    	mov    %al,-0x37a(%rbp)
  101516:	8a 85 86 fc ff ff    	mov    -0x37a(%rbp),%al
  10151c:	a8 01                	test   $0x1,%al
  10151e:	0f 85 05 00 00 00    	jne    101529 <_ZN4acos7storage15FAT32FileSystem13open_internalEjPKc+0x1a9>
  101524:	e9 f3 03 00 00       	jmp    10191c <_ZN4acos7storage15FAT32FileSystem13open_internalEjPKc+0x59c>
  101529:	c7 85 cc fc ff ff 00 	movl   $0x0,-0x334(%rbp)
  101530:	00 00 00
  101533:	48 8b 8d 88 fc ff ff 	mov    -0x378(%rbp),%rcx
  10153a:	8b 85 cc fc ff ff    	mov    -0x334(%rbp),%eax
  101540:	0f b6 49 12          	movzbl 0x12(%rcx),%ecx
  101544:	39 c8                	cmp    %ecx,%eax
  101546:	0f 83 59 03 00 00    	jae    1018a5 <_ZN4acos7storage15FAT32FileSystem13open_internalEjPKc+0x525>
  10154c:	48 8b 85 88 fc ff ff 	mov    -0x378(%rbp),%rax
  101553:	8b 48 28             	mov    0x28(%rax),%ecx
  101556:	8b 55 ec             	mov    -0x14(%rbp),%edx
  101559:	83 ea 02             	sub    $0x2,%edx
  10155c:	0f b6 70 12          	movzbl 0x12(%rax),%esi
  101560:	0f af d6             	imul   %esi,%edx
  101563:	01 d1                	add    %edx,%ecx
  101565:	03 8d cc fc ff ff    	add    -0x334(%rbp),%ecx
  10156b:	89 8d c8 fc ff ff    	mov    %ecx,-0x338(%rbp)
  101571:	48 8b 78 08          	mov    0x8(%rax),%rdi
  101575:	8b 85 c8 fc ff ff    	mov    -0x338(%rbp),%eax
  10157b:	89 c6                	mov    %eax,%esi
  10157d:	48 8d 95 e0 fd ff ff 	lea    -0x220(%rbp),%rdx
  101584:	48 8b 07             	mov    (%rdi),%rax
  101587:	ff 50 10             	call   *0x10(%rax)
  10158a:	83 f8 00             	cmp    $0x0,%eax
  10158d:	0f 84 0d 00 00 00    	je     1015a0 <_ZN4acos7storage15FAT32FileSystem13open_internalEjPKc+0x220>
  101593:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  10159a:	00
  10159b:	e9 84 03 00 00       	jmp    101924 <_ZN4acos7storage15FAT32FileSystem13open_internalEjPKc+0x5a4>
  1015a0:	c7 85 c4 fc ff ff 00 	movl   $0x0,-0x33c(%rbp)
  1015a7:	00 00 00
  1015aa:	83 bd c4 fc ff ff 10 	cmpl   $0x10,-0x33c(%rbp)
  1015b1:	0f 8d d5 02 00 00    	jge    10188c <_ZN4acos7storage15FAT32FileSystem13open_internalEjPKc+0x50c>
  1015b7:	48 8d 85 e0 fd ff ff 	lea    -0x220(%rbp),%rax
  1015be:	8b 8d c4 fc ff ff    	mov    -0x33c(%rbp),%ecx
  1015c4:	c1 e1 05             	shl    $0x5,%ecx
  1015c7:	48 63 c9             	movslq %ecx,%rcx
  1015ca:	48 01 c8             	add    %rcx,%rax
  1015cd:	48 89 85 b8 fc ff ff 	mov    %rax,-0x348(%rbp)
  1015d4:	48 8b 85 b8 fc ff ff 	mov    -0x348(%rbp),%rax
  1015db:	0f b6 00             	movzbl (%rax),%eax
  1015de:	83 f8 00             	cmp    $0x0,%eax
  1015e1:	0f 85 0d 00 00 00    	jne    1015f4 <_ZN4acos7storage15FAT32FileSystem13open_internalEjPKc+0x274>
  1015e7:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  1015ee:	00
  1015ef:	e9 30 03 00 00       	jmp    101924 <_ZN4acos7storage15FAT32FileSystem13open_internalEjPKc+0x5a4>
  1015f4:	48 8b 85 b8 fc ff ff 	mov    -0x348(%rbp),%rax
  1015fb:	0f b6 00             	movzbl (%rax),%eax
  1015fe:	3d e5 00 00 00       	cmp    $0xe5,%eax
  101603:	0f 84 17 00 00 00    	je     101620 <_ZN4acos7storage15FAT32FileSystem13open_internalEjPKc+0x2a0>
  101609:	48 8b 85 b8 fc ff ff 	mov    -0x348(%rbp),%rax
  101610:	0f b6 40 0b          	movzbl 0xb(%rax),%eax
  101614:	83 e0 08             	and    $0x8,%eax
  101617:	83 f8 00             	cmp    $0x0,%eax
  10161a:	0f 84 05 00 00 00    	je     101625 <_ZN4acos7storage15FAT32FileSystem13open_internalEjPKc+0x2a5>
  101620:	e9 53 02 00 00       	jmp    101878 <_ZN4acos7storage15FAT32FileSystem13open_internalEjPKc+0x4f8>
  101625:	48 8d bd ab fc ff ff 	lea    -0x355(%rbp),%rdi
  10162c:	31 f6                	xor    %esi,%esi
  10162e:	ba 0d 00 00 00       	mov    $0xd,%edx
  101633:	e8 38 ea ff ff       	call   100070 <memset>
  101638:	c7 85 a4 fc ff ff 00 	movl   $0x0,-0x35c(%rbp)
  10163f:	00 00 00
  101642:	c7 85 a0 fc ff ff 00 	movl   $0x0,-0x360(%rbp)
  101649:	00 00 00
  10164c:	83 bd a0 fc ff ff 08 	cmpl   $0x8,-0x360(%rbp)
  101653:	0f 8d 5f 00 00 00    	jge    1016b8 <_ZN4acos7storage15FAT32FileSystem13open_internalEjPKc+0x338>
  101659:	48 8b 85 b8 fc ff ff 	mov    -0x348(%rbp),%rax
  101660:	48 63 8d a0 fc ff ff 	movslq -0x360(%rbp),%rcx
  101667:	0f b6 04 08          	movzbl (%rax,%rcx,1),%eax
  10166b:	83 f8 20             	cmp    $0x20,%eax
  10166e:	0f 84 2b 00 00 00    	je     10169f <_ZN4acos7storage15FAT32FileSystem13open_internalEjPKc+0x31f>
  101674:	48 8b 85 b8 fc ff ff 	mov    -0x348(%rbp),%rax
  10167b:	48 63 8d a0 fc ff ff 	movslq -0x360(%rbp),%rcx
  101682:	8a 0c 08             	mov    (%rax,%rcx,1),%cl
  101685:	8b 85 a4 fc ff ff    	mov    -0x35c(%rbp),%eax
  10168b:	89 c2                	mov    %eax,%edx
  10168d:	83 c2 01             	add    $0x1,%edx
  101690:	89 95 a4 fc ff ff    	mov    %edx,-0x35c(%rbp)
  101696:	48 98                	cltq
  101698:	88 8c 05 ab fc ff ff 	mov    %cl,-0x355(%rbp,%rax,1)
  10169f:	e9 00 00 00 00       	jmp    1016a4 <_ZN4acos7storage15FAT32FileSystem13open_internalEjPKc+0x324>
  1016a4:	8b 85 a0 fc ff ff    	mov    -0x360(%rbp),%eax
  1016aa:	83 c0 01             	add    $0x1,%eax
  1016ad:	89 85 a0 fc ff ff    	mov    %eax,-0x360(%rbp)
  1016b3:	e9 94 ff ff ff       	jmp    10164c <_ZN4acos7storage15FAT32FileSystem13open_internalEjPKc+0x2cc>
  1016b8:	48 8b 85 b8 fc ff ff 	mov    -0x348(%rbp),%rax
  1016bf:	0f b6 40 08          	movzbl 0x8(%rax),%eax
  1016c3:	83 f8 20             	cmp    $0x20,%eax
  1016c6:	0f 84 96 00 00 00    	je     101762 <_ZN4acos7storage15FAT32FileSystem13open_internalEjPKc+0x3e2>
  1016cc:	8b 85 a4 fc ff ff    	mov    -0x35c(%rbp),%eax
  1016d2:	89 c1                	mov    %eax,%ecx
  1016d4:	83 c1 01             	add    $0x1,%ecx
  1016d7:	89 8d a4 fc ff ff    	mov    %ecx,-0x35c(%rbp)
  1016dd:	48 98                	cltq
  1016df:	c6 84 05 ab fc ff ff 	movb   $0x2e,-0x355(%rbp,%rax,1)
  1016e6:	2e
  1016e7:	c7 85 9c fc ff ff 08 	movl   $0x8,-0x364(%rbp)
  1016ee:	00 00 00
  1016f1:	83 bd 9c fc ff ff 0b 	cmpl   $0xb,-0x364(%rbp)
  1016f8:	0f 8d 5f 00 00 00    	jge    10175d <_ZN4acos7storage15FAT32FileSystem13open_internalEjPKc+0x3dd>
  1016fe:	48 8b 85 b8 fc ff ff 	mov    -0x348(%rbp),%rax
  101705:	48 63 8d 9c fc ff ff 	movslq -0x364(%rbp),%rcx
  10170c:	0f b6 04 08          	movzbl (%rax,%rcx,1),%eax
  101710:	83 f8 20             	cmp    $0x20,%eax
  101713:	0f 84 2b 00 00 00    	je     101744 <_ZN4acos7storage15FAT32FileSystem13open_internalEjPKc+0x3c4>
  101719:	48 8b 85 b8 fc ff ff 	mov    -0x348(%rbp),%rax
  101720:	48 63 8d 9c fc ff ff 	movslq -0x364(%rbp),%rcx
  101727:	8a 0c 08             	mov    (%rax,%rcx,1),%cl
  10172a:	8b 85 a4 fc ff ff    	mov    -0x35c(%rbp),%eax
  101730:	89 c2                	mov    %eax,%edx
  101732:	83 c2 01             	add    $0x1,%edx
  101735:	89 95 a4 fc ff ff    	mov    %edx,-0x35c(%rbp)
  10173b:	48 98                	cltq
  10173d:	88 8c 05 ab fc ff ff 	mov    %cl,-0x355(%rbp,%rax,1)
  101744:	e9 00 00 00 00       	jmp    101749 <_ZN4acos7storage15FAT32FileSystem13open_internalEjPKc+0x3c9>
  101749:	8b 85 9c fc ff ff    	mov    -0x364(%rbp),%eax
  10174f:	83 c0 01             	add    $0x1,%eax
  101752:	89 85 9c fc ff ff    	mov    %eax,-0x364(%rbp)
  101758:	e9 94 ff ff ff       	jmp    1016f1 <_ZN4acos7storage15FAT32FileSystem13open_internalEjPKc+0x371>
  10175d:	e9 00 00 00 00       	jmp    101762 <_ZN4acos7storage15FAT32FileSystem13open_internalEjPKc+0x3e2>
  101762:	48 63 85 a4 fc ff ff 	movslq -0x35c(%rbp),%rax
  101769:	c6 84 05 ab fc ff ff 	movb   $0x0,-0x355(%rbp,%rax,1)
  101770:	00
  101771:	48 8d bd ab fc ff ff 	lea    -0x355(%rbp),%rdi
  101778:	48 8d b5 e0 fc ff ff 	lea    -0x320(%rbp),%rsi
  10177f:	e8 bc 01 00 00       	call   101940 <_ZN4acos7storage12_GLOBAL__N_111strcmp_implEPKcS3_>
  101784:	83 f8 00             	cmp    $0x0,%eax
  101787:	0f 85 e6 00 00 00    	jne    101873 <_ZN4acos7storage15FAT32FileSystem13open_internalEjPKc+0x4f3>
  10178d:	48 8b 85 b8 fc ff ff 	mov    -0x348(%rbp),%rax
  101794:	0f b7 40 1a          	movzwl 0x1a(%rax),%eax
  101798:	48 8b 8d b8 fc ff ff 	mov    -0x348(%rbp),%rcx
  10179f:	0f b7 49 14          	movzwl 0x14(%rcx),%ecx
  1017a3:	c1 e1 10             	shl    $0x10,%ecx
  1017a6:	09 c8                	or     %ecx,%eax
  1017a8:	89 85 98 fc ff ff    	mov    %eax,-0x368(%rbp)
  1017ae:	48 8b 85 b8 fc ff ff 	mov    -0x348(%rbp),%rax
  1017b5:	0f b6 40 0b          	movzbl 0xb(%rax),%eax
  1017b9:	83 e0 10             	and    $0x10,%eax
  1017bc:	83 f8 00             	cmp    $0x0,%eax
  1017bf:	0f 84 5c 00 00 00    	je     101821 <_ZN4acos7storage15FAT32FileSystem13open_internalEjPKc+0x4a1>
  1017c5:	48 8b 85 d0 fc ff ff 	mov    -0x330(%rbp),%rax
  1017cc:	80 38 00             	cmpb   $0x0,(%rax)
  1017cf:	0f 84 22 00 00 00    	je     1017f7 <_ZN4acos7storage15FAT32FileSystem13open_internalEjPKc+0x477>
  1017d5:	48 8b bd 88 fc ff ff 	mov    -0x378(%rbp),%rdi
  1017dc:	8b b5 98 fc ff ff    	mov    -0x368(%rbp),%esi
  1017e2:	48 8b 95 d0 fc ff ff 	mov    -0x330(%rbp),%rdx
  1017e9:	e8 92 fb ff ff       	call   101380 <_ZN4acos7storage15FAT32FileSystem13open_internalEjPKc>
  1017ee:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  1017f2:	e9 2d 01 00 00       	jmp    101924 <_ZN4acos7storage15FAT32FileSystem13open_internalEjPKc+0x5a4>
  1017f7:	48 8b 85 88 fc ff ff 	mov    -0x378(%rbp),%rax
  1017fe:	48 8b 78 08          	mov    0x8(%rax),%rdi
  101802:	8b b5 98 fc ff ff    	mov    -0x368(%rbp),%esi
  101808:	8b 50 24             	mov    0x24(%rax),%edx
  10180b:	8b 48 28             	mov    0x28(%rax),%ecx
  10180e:	44 0f b6 40 12       	movzbl 0x12(%rax),%r8d
  101813:	e8 88 fa ff ff       	call   1012a0 <_ZN4acos7storage12_GLOBAL__N_117allocate_dir_nodeEPNS0_11BlockDeviceEjjjh>
  101818:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  10181c:	e9 03 01 00 00       	jmp    101924 <_ZN4acos7storage15FAT32FileSystem13open_internalEjPKc+0x5a4>
  101821:	48 8b 85 d0 fc ff ff 	mov    -0x330(%rbp),%rax
  101828:	80 38 00             	cmpb   $0x0,(%rax)
  10182b:	0f 84 0d 00 00 00    	je     10183e <_ZN4acos7storage15FAT32FileSystem13open_internalEjPKc+0x4be>
  101831:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  101838:	00
  101839:	e9 e6 00 00 00       	jmp    101924 <_ZN4acos7storage15FAT32FileSystem13open_internalEjPKc+0x5a4>
  10183e:	48 8b 85 88 fc ff ff 	mov    -0x378(%rbp),%rax
  101845:	48 8b 78 08          	mov    0x8(%rax),%rdi
  101849:	8b b5 98 fc ff ff    	mov    -0x368(%rbp),%esi
  10184f:	48 8b 8d b8 fc ff ff 	mov    -0x348(%rbp),%rcx
  101856:	8b 51 1c             	mov    0x1c(%rcx),%edx
  101859:	8b 48 24             	mov    0x24(%rax),%ecx
  10185c:	44 8b 40 28          	mov    0x28(%rax),%r8d
  101860:	44 0f b6 48 12       	movzbl 0x12(%rax),%r9d
  101865:	e8 16 02 00 00       	call   101a80 <_ZN4acos7storage12_GLOBAL__N_118allocate_file_nodeEPNS0_11BlockDeviceEjjjjh>
  10186a:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  10186e:	e9 b1 00 00 00       	jmp    101924 <_ZN4acos7storage15FAT32FileSystem13open_internalEjPKc+0x5a4>
  101873:	e9 00 00 00 00       	jmp    101878 <_ZN4acos7storage15FAT32FileSystem13open_internalEjPKc+0x4f8>
  101878:	8b 85 c4 fc ff ff    	mov    -0x33c(%rbp),%eax
  10187e:	83 c0 01             	add    $0x1,%eax
  101881:	89 85 c4 fc ff ff    	mov    %eax,-0x33c(%rbp)
  101887:	e9 1e fd ff ff       	jmp    1015aa <_ZN4acos7storage15FAT32FileSystem13open_internalEjPKc+0x22a>
  10188c:	e9 00 00 00 00       	jmp    101891 <_ZN4acos7storage15FAT32FileSystem13open_internalEjPKc+0x511>
  101891:	8b 85 cc fc ff ff    	mov    -0x334(%rbp),%eax
  101897:	83 c0 01             	add    $0x1,%eax
  10189a:	89 85 cc fc ff ff    	mov    %eax,-0x334(%rbp)
  1018a0:	e9 8e fc ff ff       	jmp    101533 <_ZN4acos7storage15FAT32FileSystem13open_internalEjPKc+0x1b3>
  1018a5:	48 8b 85 88 fc ff ff 	mov    -0x378(%rbp),%rax
  1018ac:	8b 4d ec             	mov    -0x14(%rbp),%ecx
  1018af:	c1 e1 02             	shl    $0x2,%ecx
  1018b2:	89 8d 94 fc ff ff    	mov    %ecx,-0x36c(%rbp)
  1018b8:	8b 48 24             	mov    0x24(%rax),%ecx
  1018bb:	8b 95 94 fc ff ff    	mov    -0x36c(%rbp),%edx
  1018c1:	c1 ea 09             	shr    $0x9,%edx
  1018c4:	01 d1                	add    %edx,%ecx
  1018c6:	89 8d 90 fc ff ff    	mov    %ecx,-0x370(%rbp)
  1018cc:	48 8b 78 08          	mov    0x8(%rax),%rdi
  1018d0:	8b 85 90 fc ff ff    	mov    -0x370(%rbp),%eax
  1018d6:	89 c6                	mov    %eax,%esi
  1018d8:	48 8d 95 e0 fd ff ff 	lea    -0x220(%rbp),%rdx
  1018df:	48 8b 07             	mov    (%rdi),%rax
  1018e2:	ff 50 10             	call   *0x10(%rax)
  1018e5:	83 f8 00             	cmp    $0x0,%eax
  1018e8:	0f 84 0d 00 00 00    	je     1018fb <_ZN4acos7storage15FAT32FileSystem13open_internalEjPKc+0x57b>
  1018ee:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  1018f5:	00
  1018f6:	e9 29 00 00 00       	jmp    101924 <_ZN4acos7storage15FAT32FileSystem13open_internalEjPKc+0x5a4>
  1018fb:	8b 85 94 fc ff ff    	mov    -0x36c(%rbp),%eax
  101901:	25 ff 01 00 00       	and    $0x1ff,%eax
  101906:	89 c0                	mov    %eax,%eax
  101908:	8b 84 05 e0 fd ff ff 	mov    -0x220(%rbp,%rax,1),%eax
  10190f:	25 ff ff ff 0f       	and    $0xfffffff,%eax
  101914:	89 45 ec             	mov    %eax,-0x14(%rbp)
  101917:	e9 d8 fb ff ff       	jmp    1014f4 <_ZN4acos7storage15FAT32FileSystem13open_internalEjPKc+0x174>
  10191c:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  101923:	00
  101924:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  101928:	48 81 c4 80 03 00 00 	add    $0x380,%rsp
  10192f:	5d                   	pop    %rbp
  101930:	c3                   	ret
  101931:	66 66 66 66 66 66 2e 	data16 data16 data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
  101938:	0f 1f 84 00 00 00 00
  10193f:	00

0000000000101940 <_ZN4acos7storage12_GLOBAL__N_111strcmp_implEPKcS3_>:
  101940:	55                   	push   %rbp
  101941:	48 89 e5             	mov    %rsp,%rbp
  101944:	48 83 ec 18          	sub    $0x18,%rsp
  101948:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10194c:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  101950:	48 8b 4d f8          	mov    -0x8(%rbp),%rcx
  101954:	31 c0                	xor    %eax,%eax
  101956:	80 39 00             	cmpb   $0x0,(%rcx)
  101959:	88 45 eb             	mov    %al,-0x15(%rbp)
  10195c:	0f 84 0d 00 00 00    	je     10196f <_ZN4acos7storage12_GLOBAL__N_111strcmp_implEPKcS3_+0x2f>
  101962:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  101966:	80 38 00             	cmpb   $0x0,(%rax)
  101969:	0f 95 c0             	setne  %al
  10196c:	88 45 eb             	mov    %al,-0x15(%rbp)
  10196f:	8a 45 eb             	mov    -0x15(%rbp),%al
  101972:	a8 01                	test   $0x1,%al
  101974:	0f 85 05 00 00 00    	jne    10197f <_ZN4acos7storage12_GLOBAL__N_111strcmp_implEPKcS3_+0x3f>
  10197a:	e9 8c 00 00 00       	jmp    101a0b <_ZN4acos7storage12_GLOBAL__N_111strcmp_implEPKcS3_+0xcb>
  10197f:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  101983:	8a 00                	mov    (%rax),%al
  101985:	88 45 ef             	mov    %al,-0x11(%rbp)
  101988:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10198c:	8a 00                	mov    (%rax),%al
  10198e:	88 45 ee             	mov    %al,-0x12(%rbp)
  101991:	0f be 45 ef          	movsbl -0x11(%rbp),%eax
  101995:	83 f8 61             	cmp    $0x61,%eax
  101998:	0f 8c 17 00 00 00    	jl     1019b5 <_ZN4acos7storage12_GLOBAL__N_111strcmp_implEPKcS3_+0x75>
  10199e:	0f be 45 ef          	movsbl -0x11(%rbp),%eax
  1019a2:	83 f8 7a             	cmp    $0x7a,%eax
  1019a5:	0f 8f 0a 00 00 00    	jg     1019b5 <_ZN4acos7storage12_GLOBAL__N_111strcmp_implEPKcS3_+0x75>
  1019ab:	0f be 45 ef          	movsbl -0x11(%rbp),%eax
  1019af:	83 e8 20             	sub    $0x20,%eax
  1019b2:	88 45 ef             	mov    %al,-0x11(%rbp)
  1019b5:	0f be 45 ee          	movsbl -0x12(%rbp),%eax
  1019b9:	83 f8 61             	cmp    $0x61,%eax
  1019bc:	0f 8c 17 00 00 00    	jl     1019d9 <_ZN4acos7storage12_GLOBAL__N_111strcmp_implEPKcS3_+0x99>
  1019c2:	0f be 45 ee          	movsbl -0x12(%rbp),%eax
  1019c6:	83 f8 7a             	cmp    $0x7a,%eax
  1019c9:	0f 8f 0a 00 00 00    	jg     1019d9 <_ZN4acos7storage12_GLOBAL__N_111strcmp_implEPKcS3_+0x99>
  1019cf:	0f be 45 ee          	movsbl -0x12(%rbp),%eax
  1019d3:	83 e8 20             	sub    $0x20,%eax
  1019d6:	88 45 ee             	mov    %al,-0x12(%rbp)
  1019d9:	0f be 45 ef          	movsbl -0x11(%rbp),%eax
  1019dd:	0f be 4d ee          	movsbl -0x12(%rbp),%ecx
  1019e1:	39 c8                	cmp    %ecx,%eax
  1019e3:	0f 84 05 00 00 00    	je     1019ee <_ZN4acos7storage12_GLOBAL__N_111strcmp_implEPKcS3_+0xae>
  1019e9:	e9 1d 00 00 00       	jmp    101a0b <_ZN4acos7storage12_GLOBAL__N_111strcmp_implEPKcS3_+0xcb>
  1019ee:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  1019f2:	48 83 c0 01          	add    $0x1,%rax
  1019f6:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  1019fa:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  1019fe:	48 83 c0 01          	add    $0x1,%rax
  101a02:	48 89 45 f0          	mov    %rax,-0x10(%rbp)
  101a06:	e9 45 ff ff ff       	jmp    101950 <_ZN4acos7storage12_GLOBAL__N_111strcmp_implEPKcS3_+0x10>
  101a0b:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  101a0f:	8a 00                	mov    (%rax),%al
  101a11:	88 45 ed             	mov    %al,-0x13(%rbp)
  101a14:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  101a18:	8a 00                	mov    (%rax),%al
  101a1a:	88 45 ec             	mov    %al,-0x14(%rbp)
  101a1d:	0f be 45 ed          	movsbl -0x13(%rbp),%eax
  101a21:	83 f8 61             	cmp    $0x61,%eax
  101a24:	0f 8c 17 00 00 00    	jl     101a41 <_ZN4acos7storage12_GLOBAL__N_111strcmp_implEPKcS3_+0x101>
  101a2a:	0f be 45 ed          	movsbl -0x13(%rbp),%eax
  101a2e:	83 f8 7a             	cmp    $0x7a,%eax
  101a31:	0f 8f 0a 00 00 00    	jg     101a41 <_ZN4acos7storage12_GLOBAL__N_111strcmp_implEPKcS3_+0x101>
  101a37:	0f be 45 ed          	movsbl -0x13(%rbp),%eax
  101a3b:	83 e8 20             	sub    $0x20,%eax
  101a3e:	88 45 ed             	mov    %al,-0x13(%rbp)
  101a41:	0f be 45 ec          	movsbl -0x14(%rbp),%eax
  101a45:	83 f8 61             	cmp    $0x61,%eax
  101a48:	0f 8c 17 00 00 00    	jl     101a65 <_ZN4acos7storage12_GLOBAL__N_111strcmp_implEPKcS3_+0x125>
  101a4e:	0f be 45 ec          	movsbl -0x14(%rbp),%eax
  101a52:	83 f8 7a             	cmp    $0x7a,%eax
  101a55:	0f 8f 0a 00 00 00    	jg     101a65 <_ZN4acos7storage12_GLOBAL__N_111strcmp_implEPKcS3_+0x125>
  101a5b:	0f be 45 ec          	movsbl -0x14(%rbp),%eax
  101a5f:	83 e8 20             	sub    $0x20,%eax
  101a62:	88 45 ec             	mov    %al,-0x14(%rbp)
  101a65:	0f b6 45 ed          	movzbl -0x13(%rbp),%eax
  101a69:	0f b6 4d ec          	movzbl -0x14(%rbp),%ecx
  101a6d:	29 c8                	sub    %ecx,%eax
  101a6f:	48 83 c4 18          	add    $0x18,%rsp
  101a73:	5d                   	pop    %rbp
  101a74:	c3                   	ret
  101a75:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  101a7c:	00 00 00 00

0000000000101a80 <_ZN4acos7storage12_GLOBAL__N_118allocate_file_nodeEPNS0_11BlockDeviceEjjjjh>:
  101a80:	55                   	push   %rbp
  101a81:	48 89 e5             	mov    %rsp,%rbp
  101a84:	48 83 ec 30          	sub    $0x30,%rsp
  101a88:	44 88 c8             	mov    %r9b,%al
  101a8b:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  101a8f:	89 75 ec             	mov    %esi,-0x14(%rbp)
  101a92:	89 55 e8             	mov    %edx,-0x18(%rbp)
  101a95:	89 4d e4             	mov    %ecx,-0x1c(%rbp)
  101a98:	44 89 45 e0          	mov    %r8d,-0x20(%rbp)
  101a9c:	88 45 df             	mov    %al,-0x21(%rbp)
  101a9f:	c7 45 d8 00 00 00 00 	movl   $0x0,-0x28(%rbp)
  101aa6:	83 7d d8 40          	cmpl   $0x40,-0x28(%rbp)
  101aaa:	0f 8d 9c 00 00 00    	jge    101b4c <_ZN4acos7storage12_GLOBAL__N_118allocate_file_nodeEPNS0_11BlockDeviceEjjjjh+0xcc>
  101ab0:	48 63 4d d8          	movslq -0x28(%rbp),%rcx
  101ab4:	48 b8 90 46 15 00 00 	movabs $0x154690,%rax
  101abb:	00 00 00
  101abe:	48 6b c9 30          	imul   $0x30,%rcx,%rcx
  101ac2:	48 01 c8             	add    %rcx,%rax
  101ac5:	f6 40 08 01          	testb  $0x1,0x8(%rax)
  101ac9:	0f 85 6a 00 00 00    	jne    101b39 <_ZN4acos7storage12_GLOBAL__N_118allocate_file_nodeEPNS0_11BlockDeviceEjjjjh+0xb9>
  101acf:	48 63 4d d8          	movslq -0x28(%rbp),%rcx
  101ad3:	48 b8 90 46 15 00 00 	movabs $0x154690,%rax
  101ada:	00 00 00
  101add:	48 6b c9 30          	imul   $0x30,%rcx,%rcx
  101ae1:	48 01 c8             	add    %rcx,%rax
  101ae4:	c6 40 08 01          	movb   $0x1,0x8(%rax)
  101ae8:	48 63 45 d8          	movslq -0x28(%rbp),%rax
  101aec:	48 bf 90 46 15 00 00 	movabs $0x154690,%rdi
  101af3:	00 00 00
  101af6:	48 6b c0 30          	imul   $0x30,%rax,%rax
  101afa:	48 01 c7             	add    %rax,%rdi
  101afd:	48 8b 75 f0          	mov    -0x10(%rbp),%rsi
  101b01:	8b 55 ec             	mov    -0x14(%rbp),%edx
  101b04:	8b 4d e8             	mov    -0x18(%rbp),%ecx
  101b07:	44 8b 45 e4          	mov    -0x1c(%rbp),%r8d
  101b0b:	44 8b 4d e0          	mov    -0x20(%rbp),%r9d
  101b0f:	0f b6 45 df          	movzbl -0x21(%rbp),%eax
  101b13:	89 04 24             	mov    %eax,(%rsp)
  101b16:	e8 d5 0e 00 00       	call   1029f0 <_ZN4acos7storage12_GLOBAL__N_113FAT32FileNode10initializeEPNS0_11BlockDeviceEjjjjh>
  101b1b:	48 63 4d d8          	movslq -0x28(%rbp),%rcx
  101b1f:	48 b8 90 46 15 00 00 	movabs $0x154690,%rax
  101b26:	00 00 00
  101b29:	48 6b c9 30          	imul   $0x30,%rcx,%rcx
  101b2d:	48 01 c8             	add    %rcx,%rax
  101b30:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  101b34:	e9 1b 00 00 00       	jmp    101b54 <_ZN4acos7storage12_GLOBAL__N_118allocate_file_nodeEPNS0_11BlockDeviceEjjjjh+0xd4>
  101b39:	e9 00 00 00 00       	jmp    101b3e <_ZN4acos7storage12_GLOBAL__N_118allocate_file_nodeEPNS0_11BlockDeviceEjjjjh+0xbe>
  101b3e:	8b 45 d8             	mov    -0x28(%rbp),%eax
  101b41:	83 c0 01             	add    $0x1,%eax
  101b44:	89 45 d8             	mov    %eax,-0x28(%rbp)
  101b47:	e9 5a ff ff ff       	jmp    101aa6 <_ZN4acos7storage12_GLOBAL__N_118allocate_file_nodeEPNS0_11BlockDeviceEjjjjh+0x26>
  101b4c:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  101b53:	00
  101b54:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  101b58:	48 83 c4 30          	add    $0x30,%rsp
  101b5c:	5d                   	pop    %rbp
  101b5d:	c3                   	ret
  101b5e:	66 90                	xchg   %ax,%ax

0000000000101b60 <__cxx_global_var_init.4>:
  101b60:	55                   	push   %rbp
  101b61:	48 89 e5             	mov    %rsp,%rbp
  101b64:	48 83 ec 10          	sub    $0x10,%rsp
  101b68:	48 b8 10 55 15 00 00 	movabs $0x155510,%rax
  101b6f:	00 00 00
  101b72:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  101b76:	e9 00 00 00 00       	jmp    101b7b <__cxx_global_var_init.4+0x1b>
  101b7b:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  101b7f:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  101b83:	e8 88 cc 00 00       	call   10e810 <_ZN4acos7storage15FAT32FileSystemC2Ev>
  101b88:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  101b8c:	48 83 c0 30          	add    $0x30,%rax
  101b90:	48 b9 10 55 15 00 00 	movabs $0x155510,%rcx
  101b97:	00 00 00
  101b9a:	48 81 c1 c0 00 00 00 	add    $0xc0,%rcx
  101ba1:	48 39 c8             	cmp    %rcx,%rax
  101ba4:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  101ba8:	0f 85 cd ff ff ff    	jne    101b7b <__cxx_global_var_init.4+0x1b>
  101bae:	48 83 c4 10          	add    $0x10,%rsp
  101bb2:	5d                   	pop    %rbp
  101bb3:	c3                   	ret
  101bb4:	66 66 66 2e 0f 1f 84 	data16 data16 cs nopw 0x0(%rax,%rax,1)
  101bbb:	00 00 00 00 00

0000000000101bc0 <_ZN4acos7storage15FAT32FileSystem5probeEPvPKc>:
  101bc0:	55                   	push   %rbp
  101bc1:	48 89 e5             	mov    %rsp,%rbp
  101bc4:	48 81 ec 70 02 00 00 	sub    $0x270,%rsp
  101bcb:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  101bcf:	48 89 75 e8          	mov    %rsi,-0x18(%rbp)
  101bd3:	48 89 55 e0          	mov    %rdx,-0x20(%rbp)
  101bd7:	48 83 7d e8 00       	cmpq   $0x0,-0x18(%rbp)
  101bdc:	0f 85 09 00 00 00    	jne    101beb <_ZN4acos7storage15FAT32FileSystem5probeEPvPKc+0x2b>
  101be2:	c6 45 ff 00          	movb   $0x0,-0x1(%rbp)
  101be6:	e9 60 01 00 00       	jmp    101d4b <_ZN4acos7storage15FAT32FileSystem5probeEPvPKc+0x18b>
  101beb:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  101bef:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
  101bf3:	48 8b 7d d8          	mov    -0x28(%rbp),%rdi
  101bf7:	48 8d 95 d0 fd ff ff 	lea    -0x230(%rbp),%rdx
  101bfe:	48 8b 07             	mov    (%rdi),%rax
  101c01:	31 c9                	xor    %ecx,%ecx
  101c03:	89 ce                	mov    %ecx,%esi
  101c05:	ff 50 10             	call   *0x10(%rax)
  101c08:	83 f8 00             	cmp    $0x0,%eax
  101c0b:	0f 84 09 00 00 00    	je     101c1a <_ZN4acos7storage15FAT32FileSystem5probeEPvPKc+0x5a>
  101c11:	c6 45 ff 00          	movb   $0x0,-0x1(%rbp)
  101c15:	e9 31 01 00 00       	jmp    101d4b <_ZN4acos7storage15FAT32FileSystem5probeEPvPKc+0x18b>
  101c1a:	0f b6 45 ce          	movzbl -0x32(%rbp),%eax
  101c1e:	83 f8 55             	cmp    $0x55,%eax
  101c21:	0f 85 0f 00 00 00    	jne    101c36 <_ZN4acos7storage15FAT32FileSystem5probeEPvPKc+0x76>
  101c27:	0f b6 45 cf          	movzbl -0x31(%rbp),%eax
  101c2b:	3d aa 00 00 00       	cmp    $0xaa,%eax
  101c30:	0f 84 09 00 00 00    	je     101c3f <_ZN4acos7storage15FAT32FileSystem5probeEPvPKc+0x7f>
  101c36:	c6 45 ff 00          	movb   $0x0,-0x1(%rbp)
  101c3a:	e9 0c 01 00 00       	jmp    101d4b <_ZN4acos7storage15FAT32FileSystem5probeEPvPKc+0x18b>
  101c3f:	48 c7 85 c8 fd ff ff 	movq   $0x0,-0x238(%rbp)
  101c46:	00 00 00 00
  101c4a:	c7 85 c4 fd ff ff 00 	movl   $0x0,-0x23c(%rbp)
  101c51:	00 00 00
  101c54:	83 bd c4 fd ff ff 04 	cmpl   $0x4,-0x23c(%rbp)
  101c5b:	0f 8d a1 00 00 00    	jge    101d02 <_ZN4acos7storage15FAT32FileSystem5probeEPvPKc+0x142>
  101c61:	48 63 85 c4 fd ff ff 	movslq -0x23c(%rbp),%rax
  101c68:	f6 04 05 d0 55 15 00 	testb  $0x1,0x1555d0(,%rax,1)
  101c6f:	01
  101c70:	0f 85 73 00 00 00    	jne    101ce9 <_ZN4acos7storage15FAT32FileSystem5probeEPvPKc+0x129>
  101c76:	48 63 85 c4 fd ff ff 	movslq -0x23c(%rbp),%rax
  101c7d:	c6 04 05 d0 55 15 00 	movb   $0x1,0x1555d0(,%rax,1)
  101c84:	01
  101c85:	48 8b 75 d8          	mov    -0x28(%rbp),%rsi
  101c89:	48 8d bd 90 fd ff ff 	lea    -0x270(%rbp),%rdi
  101c90:	e8 eb f4 ff ff       	call   101180 <_ZN4acos7storage15FAT32FileSystemC1EPNS0_11BlockDeviceE>
  101c95:	48 63 85 c4 fd ff ff 	movslq -0x23c(%rbp),%rax
  101c9c:	48 bf 10 55 15 00 00 	movabs $0x155510,%rdi
  101ca3:	00 00 00
  101ca6:	48 6b c0 30          	imul   $0x30,%rax,%rax
  101caa:	48 01 c7             	add    %rax,%rdi
  101cad:	48 8d b5 90 fd ff ff 	lea    -0x270(%rbp),%rsi
  101cb4:	e8 97 cb 00 00       	call   10e850 <_ZN4acos7storage15FAT32FileSystemaSEOS1_>
  101cb9:	48 8d bd 90 fd ff ff 	lea    -0x270(%rbp),%rdi
  101cc0:	e8 db cb 00 00       	call   10e8a0 <_ZN4acos7storage15FAT32FileSystemD2Ev>
  101cc5:	48 63 8d c4 fd ff ff 	movslq -0x23c(%rbp),%rcx
  101ccc:	48 b8 10 55 15 00 00 	movabs $0x155510,%rax
  101cd3:	00 00 00
  101cd6:	48 6b c9 30          	imul   $0x30,%rcx,%rcx
  101cda:	48 01 c8             	add    %rcx,%rax
  101cdd:	48 89 85 c8 fd ff ff 	mov    %rax,-0x238(%rbp)
  101ce4:	e9 19 00 00 00       	jmp    101d02 <_ZN4acos7storage15FAT32FileSystem5probeEPvPKc+0x142>
  101ce9:	e9 00 00 00 00       	jmp    101cee <_ZN4acos7storage15FAT32FileSystem5probeEPvPKc+0x12e>
  101cee:	8b 85 c4 fd ff ff    	mov    -0x23c(%rbp),%eax
  101cf4:	83 c0 01             	add    $0x1,%eax
  101cf7:	89 85 c4 fd ff ff    	mov    %eax,-0x23c(%rbp)
  101cfd:	e9 52 ff ff ff       	jmp    101c54 <_ZN4acos7storage15FAT32FileSystem5probeEPvPKc+0x94>
  101d02:	48 83 bd c8 fd ff ff 	cmpq   $0x0,-0x238(%rbp)
  101d09:	00
  101d0a:	0f 84 37 00 00 00    	je     101d47 <_ZN4acos7storage15FAT32FileSystem5probeEPvPKc+0x187>
  101d10:	48 8b bd c8 fd ff ff 	mov    -0x238(%rbp),%rdi
  101d17:	48 8b 75 e0          	mov    -0x20(%rbp),%rsi
  101d1b:	48 8b 07             	mov    (%rdi),%rax
  101d1e:	ff 50 18             	call   *0x18(%rax)
  101d21:	a8 01                	test   $0x1,%al
  101d23:	0f 85 05 00 00 00    	jne    101d2e <_ZN4acos7storage15FAT32FileSystem5probeEPvPKc+0x16e>
  101d29:	e9 19 00 00 00       	jmp    101d47 <_ZN4acos7storage15FAT32FileSystem5probeEPvPKc+0x187>
  101d2e:	48 8b 7d e0          	mov    -0x20(%rbp),%rdi
  101d32:	48 8b b5 c8 fd ff ff 	mov    -0x238(%rbp),%rsi
  101d39:	e8 92 73 00 00       	call   1090d0 <_ZN4acos3vfs3VFS5mountEPKcPNS0_10FileSystemE>
  101d3e:	c6 45 ff 01          	movb   $0x1,-0x1(%rbp)
  101d42:	e9 04 00 00 00       	jmp    101d4b <_ZN4acos7storage15FAT32FileSystem5probeEPvPKc+0x18b>
  101d47:	c6 45 ff 00          	movb   $0x0,-0x1(%rbp)
  101d4b:	8a 45 ff             	mov    -0x1(%rbp),%al
  101d4e:	24 01                	and    $0x1,%al
  101d50:	0f b6 c0             	movzbl %al,%eax
  101d53:	48 81 c4 70 02 00 00 	add    $0x270,%rsp
  101d5a:	5d                   	pop    %rbp
  101d5b:	c3                   	ret
  101d5c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000101d60 <_ZN4acos7storage15FAT32FileSystem5mountEPKc>:
  101d60:	55                   	push   %rbp
  101d61:	48 89 e5             	mov    %rsp,%rbp
  101d64:	48 81 ec 30 02 00 00 	sub    $0x230,%rsp
  101d6b:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  101d6f:	48 89 75 e8          	mov    %rsi,-0x18(%rbp)
  101d73:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  101d77:	48 89 85 d8 fd ff ff 	mov    %rax,-0x228(%rbp)
  101d7e:	48 8b 78 08          	mov    0x8(%rax),%rdi
  101d82:	48 8d 95 e0 fd ff ff 	lea    -0x220(%rbp),%rdx
  101d89:	48 8b 07             	mov    (%rdi),%rax
  101d8c:	31 c9                	xor    %ecx,%ecx
  101d8e:	89 ce                	mov    %ecx,%esi
  101d90:	ff 50 10             	call   *0x10(%rax)
  101d93:	83 f8 00             	cmp    $0x0,%eax
  101d96:	0f 84 09 00 00 00    	je     101da5 <_ZN4acos7storage15FAT32FileSystem5mountEPKc+0x45>
  101d9c:	c6 45 ff 00          	movb   $0x0,-0x1(%rbp)
  101da0:	e9 85 00 00 00       	jmp    101e2a <_ZN4acos7storage15FAT32FileSystem5mountEPKc+0xca>
  101da5:	48 8b 85 d8 fd ff ff 	mov    -0x228(%rbp),%rax
  101dac:	66 8b 8d eb fd ff ff 	mov    -0x215(%rbp),%cx
  101db3:	66 89 48 10          	mov    %cx,0x10(%rax)
  101db7:	0f b7 40 10          	movzwl 0x10(%rax),%eax
  101dbb:	3d 00 02 00 00       	cmp    $0x200,%eax
  101dc0:	0f 84 09 00 00 00    	je     101dcf <_ZN4acos7storage15FAT32FileSystem5mountEPKc+0x6f>
  101dc6:	c6 45 ff 00          	movb   $0x0,-0x1(%rbp)
  101dca:	e9 5b 00 00 00       	jmp    101e2a <_ZN4acos7storage15FAT32FileSystem5mountEPKc+0xca>
  101dcf:	48 8b 85 d8 fd ff ff 	mov    -0x228(%rbp),%rax
  101dd6:	8a 8d ed fd ff ff    	mov    -0x213(%rbp),%cl
  101ddc:	88 48 12             	mov    %cl,0x12(%rax)
  101ddf:	66 8b 8d ee fd ff ff 	mov    -0x212(%rbp),%cx
  101de6:	66 89 48 14          	mov    %cx,0x14(%rax)
  101dea:	8a 8d f0 fd ff ff    	mov    -0x210(%rbp),%cl
  101df0:	88 48 16             	mov    %cl,0x16(%rax)
  101df3:	8b 8d 04 fe ff ff    	mov    -0x1fc(%rbp),%ecx
  101df9:	89 48 18             	mov    %ecx,0x18(%rax)
  101dfc:	8b 8d 00 fe ff ff    	mov    -0x200(%rbp),%ecx
  101e02:	89 48 1c             	mov    %ecx,0x1c(%rax)
  101e05:	8b 8d 0c fe ff ff    	mov    -0x1f4(%rbp),%ecx
  101e0b:	89 48 20             	mov    %ecx,0x20(%rax)
  101e0e:	0f b7 48 14          	movzwl 0x14(%rax),%ecx
  101e12:	89 48 24             	mov    %ecx,0x24(%rax)
  101e15:	0f b7 48 14          	movzwl 0x14(%rax),%ecx
  101e19:	0f b6 50 16          	movzbl 0x16(%rax),%edx
  101e1d:	0f af 50 18          	imul   0x18(%rax),%edx
  101e21:	01 d1                	add    %edx,%ecx
  101e23:	89 48 28             	mov    %ecx,0x28(%rax)
  101e26:	c6 45 ff 01          	movb   $0x1,-0x1(%rbp)
  101e2a:	8a 45 ff             	mov    -0x1(%rbp),%al
  101e2d:	24 01                	and    $0x1,%al
  101e2f:	0f b6 c0             	movzbl %al,%eax
  101e32:	48 81 c4 30 02 00 00 	add    $0x230,%rsp
  101e39:	5d                   	pop    %rbp
  101e3a:	c3                   	ret
  101e3b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000101e40 <_ZN4acos7storage12_GLOBAL__N_113FAT32FileNodeD2Ev>:
  101e40:	55                   	push   %rbp
  101e41:	48 89 e5             	mov    %rsp,%rbp
  101e44:	48 83 ec 10          	sub    $0x10,%rsp
  101e48:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  101e4c:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  101e50:	e8 cb ca 00 00       	call   10e920 <_ZN4acos3vfs4NodeD2Ev>
  101e55:	48 83 c4 10          	add    $0x10,%rsp
  101e59:	5d                   	pop    %rbp
  101e5a:	c3                   	ret
  101e5b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000101e60 <_ZN4acos7storage12_GLOBAL__N_113FAT32FileNodeD0Ev>:
  101e60:	55                   	push   %rbp
  101e61:	48 89 e5             	mov    %rsp,%rbp
  101e64:	48 83 ec 10          	sub    $0x10,%rsp
  101e68:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  101e6c:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  101e70:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  101e74:	e8 c7 ff ff ff       	call   101e40 <_ZN4acos7storage12_GLOBAL__N_113FAT32FileNodeD2Ev>
  101e79:	48 8b 7d f0          	mov    -0x10(%rbp),%rdi
  101e7d:	e8 ae e5 ff ff       	call   100430 <_ZdlPv>
  101e82:	48 83 c4 10          	add    $0x10,%rsp
  101e86:	5d                   	pop    %rbp
  101e87:	c3                   	ret
  101e88:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  101e8f:	00

0000000000101e90 <_ZN4acos7storage12_GLOBAL__N_113FAT32FileNode4readEmmPv>:
  101e90:	55                   	push   %rbp
  101e91:	48 89 e5             	mov    %rsp,%rbp
  101e94:	48 81 ec 80 02 00 00 	sub    $0x280,%rsp
  101e9b:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  101e9f:	48 89 75 e8          	mov    %rsi,-0x18(%rbp)
  101ea3:	48 89 55 e0          	mov    %rdx,-0x20(%rbp)
  101ea7:	48 89 4d d8          	mov    %rcx,-0x28(%rbp)
  101eab:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  101eaf:	48 89 85 88 fd ff ff 	mov    %rax,-0x278(%rbp)
  101eb6:	48 83 78 10 00       	cmpq   $0x0,0x10(%rax)
  101ebb:	0f 84 22 00 00 00    	je     101ee3 <_ZN4acos7storage12_GLOBAL__N_113FAT32FileNode4readEmmPv+0x53>
  101ec1:	48 83 7d d8 00       	cmpq   $0x0,-0x28(%rbp)
  101ec6:	0f 84 17 00 00 00    	je     101ee3 <_ZN4acos7storage12_GLOBAL__N_113FAT32FileNode4readEmmPv+0x53>
  101ecc:	48 8b 8d 88 fd ff ff 	mov    -0x278(%rbp),%rcx
  101ed3:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  101ed7:	8b 49 1c             	mov    0x1c(%rcx),%ecx
  101eda:	48 39 c8             	cmp    %rcx,%rax
  101edd:	0f 82 0c 00 00 00    	jb     101eef <_ZN4acos7storage12_GLOBAL__N_113FAT32FileNode4readEmmPv+0x5f>
  101ee3:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%rbp)
  101eea:	e9 49 03 00 00       	jmp    102238 <_ZN4acos7storage12_GLOBAL__N_113FAT32FileNode4readEmmPv+0x3a8>
  101eef:	48 8b 8d 88 fd ff ff 	mov    -0x278(%rbp),%rcx
  101ef6:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  101efa:	48 89 45 d0          	mov    %rax,-0x30(%rbp)
  101efe:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  101f02:	48 03 45 d0          	add    -0x30(%rbp),%rax
  101f06:	8b 49 1c             	mov    0x1c(%rcx),%ecx
  101f09:	48 39 c8             	cmp    %rcx,%rax
  101f0c:	0f 86 12 00 00 00    	jbe    101f24 <_ZN4acos7storage12_GLOBAL__N_113FAT32FileNode4readEmmPv+0x94>
  101f12:	48 8b 85 88 fd ff ff 	mov    -0x278(%rbp),%rax
  101f19:	8b 40 1c             	mov    0x1c(%rax),%eax
  101f1c:	48 2b 45 e8          	sub    -0x18(%rbp),%rax
  101f20:	48 89 45 d0          	mov    %rax,-0x30(%rbp)
  101f24:	48 8b 85 88 fd ff ff 	mov    -0x278(%rbp),%rax
  101f2b:	48 8b 4d d8          	mov    -0x28(%rbp),%rcx
  101f2f:	48 89 8d c8 fd ff ff 	mov    %rcx,-0x238(%rbp)
  101f36:	48 c7 85 c0 fd ff ff 	movq   $0x0,-0x240(%rbp)
  101f3d:	00 00 00 00
  101f41:	8b 48 18             	mov    0x18(%rax),%ecx
  101f44:	89 8d bc fd ff ff    	mov    %ecx,-0x244(%rbp)
  101f4a:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  101f4e:	48 89 8d b0 fd ff ff 	mov    %rcx,-0x250(%rbp)
  101f55:	0f b6 40 28          	movzbl 0x28(%rax),%eax
  101f59:	c1 e0 09             	shl    $0x9,%eax
  101f5c:	89 85 ac fd ff ff    	mov    %eax,-0x254(%rbp)
  101f62:	31 c0                	xor    %eax,%eax
  101f64:	83 bd bc fd ff ff 02 	cmpl   $0x2,-0x244(%rbp)
  101f6b:	88 85 87 fd ff ff    	mov    %al,-0x279(%rbp)
  101f71:	0f 82 31 00 00 00    	jb     101fa8 <_ZN4acos7storage12_GLOBAL__N_113FAT32FileNode4readEmmPv+0x118>
  101f77:	31 c0                	xor    %eax,%eax
  101f79:	81 bd bc fd ff ff f8 	cmpl   $0xffffff8,-0x244(%rbp)
  101f80:	ff ff 0f
  101f83:	88 85 87 fd ff ff    	mov    %al,-0x279(%rbp)
  101f89:	0f 83 19 00 00 00    	jae    101fa8 <_ZN4acos7storage12_GLOBAL__N_113FAT32FileNode4readEmmPv+0x118>
  101f8f:	48 8b 85 b0 fd ff ff 	mov    -0x250(%rbp),%rax
  101f96:	8b 8d ac fd ff ff    	mov    -0x254(%rbp),%ecx
  101f9c:	48 39 c8             	cmp    %rcx,%rax
  101f9f:	0f 93 c0             	setae  %al
  101fa2:	88 85 87 fd ff ff    	mov    %al,-0x279(%rbp)
  101fa8:	8a 85 87 fd ff ff    	mov    -0x279(%rbp),%al
  101fae:	a8 01                	test   $0x1,%al
  101fb0:	0f 85 05 00 00 00    	jne    101fbb <_ZN4acos7storage12_GLOBAL__N_113FAT32FileNode4readEmmPv+0x12b>
  101fb6:	e9 36 00 00 00       	jmp    101ff1 <_ZN4acos7storage12_GLOBAL__N_113FAT32FileNode4readEmmPv+0x161>
  101fbb:	48 8b bd 88 fd ff ff 	mov    -0x278(%rbp),%rdi
  101fc2:	8b 85 ac fd ff ff    	mov    -0x254(%rbp),%eax
  101fc8:	89 c1                	mov    %eax,%ecx
  101fca:	48 8b 85 b0 fd ff ff 	mov    -0x250(%rbp),%rax
  101fd1:	48 29 c8             	sub    %rcx,%rax
  101fd4:	48 89 85 b0 fd ff ff 	mov    %rax,-0x250(%rbp)
  101fdb:	8b b5 bc fd ff ff    	mov    -0x244(%rbp),%esi
  101fe1:	e8 0a 03 00 00       	call   1022f0 <_ZN4acos7storage12_GLOBAL__N_113FAT32FileNode12next_clusterEj>
  101fe6:	89 85 bc fd ff ff    	mov    %eax,-0x244(%rbp)
  101fec:	e9 71 ff ff ff       	jmp    101f62 <_ZN4acos7storage12_GLOBAL__N_113FAT32FileNode4readEmmPv+0xd2>
  101ff1:	e9 00 00 00 00       	jmp    101ff6 <_ZN4acos7storage12_GLOBAL__N_113FAT32FileNode4readEmmPv+0x166>
  101ff6:	48 8b 8d c0 fd ff ff 	mov    -0x240(%rbp),%rcx
  101ffd:	31 c0                	xor    %eax,%eax
  101fff:	48 3b 4d d0          	cmp    -0x30(%rbp),%rcx
  102003:	88 85 86 fd ff ff    	mov    %al,-0x27a(%rbp)
  102009:	0f 83 28 00 00 00    	jae    102037 <_ZN4acos7storage12_GLOBAL__N_113FAT32FileNode4readEmmPv+0x1a7>
  10200f:	31 c0                	xor    %eax,%eax
  102011:	83 bd bc fd ff ff 02 	cmpl   $0x2,-0x244(%rbp)
  102018:	88 85 86 fd ff ff    	mov    %al,-0x27a(%rbp)
  10201e:	0f 82 13 00 00 00    	jb     102037 <_ZN4acos7storage12_GLOBAL__N_113FAT32FileNode4readEmmPv+0x1a7>
  102024:	81 bd bc fd ff ff f8 	cmpl   $0xffffff8,-0x244(%rbp)
  10202b:	ff ff 0f
  10202e:	0f 92 c0             	setb   %al
  102031:	88 85 86 fd ff ff    	mov    %al,-0x27a(%rbp)
  102037:	8a 85 86 fd ff ff    	mov    -0x27a(%rbp),%al
  10203d:	a8 01                	test   $0x1,%al
  10203f:	0f 85 05 00 00 00    	jne    10204a <_ZN4acos7storage12_GLOBAL__N_113FAT32FileNode4readEmmPv+0x1ba>
  102045:	e9 e4 01 00 00       	jmp    10222e <_ZN4acos7storage12_GLOBAL__N_113FAT32FileNode4readEmmPv+0x39e>
  10204a:	c6 85 ab fd ff ff 00 	movb   $0x0,-0x255(%rbp)
  102051:	48 8b 85 88 fd ff ff 	mov    -0x278(%rbp),%rax
  102058:	0f b6 8d ab fd ff ff 	movzbl -0x255(%rbp),%ecx
  10205f:	0f b6 50 28          	movzbl 0x28(%rax),%edx
  102063:	31 c0                	xor    %eax,%eax
  102065:	39 d1                	cmp    %edx,%ecx
  102067:	88 85 85 fd ff ff    	mov    %al,-0x27b(%rbp)
  10206d:	0f 8d 14 00 00 00    	jge    102087 <_ZN4acos7storage12_GLOBAL__N_113FAT32FileNode4readEmmPv+0x1f7>
  102073:	48 8b 85 c0 fd ff ff 	mov    -0x240(%rbp),%rax
  10207a:	48 3b 45 d0          	cmp    -0x30(%rbp),%rax
  10207e:	0f 92 c0             	setb   %al
  102081:	88 85 85 fd ff ff    	mov    %al,-0x27b(%rbp)
  102087:	8a 85 85 fd ff ff    	mov    -0x27b(%rbp),%al
  10208d:	a8 01                	test   $0x1,%al
  10208f:	0f 85 05 00 00 00    	jne    10209a <_ZN4acos7storage12_GLOBAL__N_113FAT32FileNode4readEmmPv+0x20a>
  102095:	e9 77 01 00 00       	jmp    102211 <_ZN4acos7storage12_GLOBAL__N_113FAT32FileNode4readEmmPv+0x381>
  10209a:	48 8b 85 88 fd ff ff 	mov    -0x278(%rbp),%rax
  1020a1:	8b 48 24             	mov    0x24(%rax),%ecx
  1020a4:	8b 95 bc fd ff ff    	mov    -0x244(%rbp),%edx
  1020aa:	83 ea 02             	sub    $0x2,%edx
  1020ad:	0f b6 70 28          	movzbl 0x28(%rax),%esi
  1020b1:	0f af d6             	imul   %esi,%edx
  1020b4:	01 d1                	add    %edx,%ecx
  1020b6:	0f b6 95 ab fd ff ff 	movzbl -0x255(%rbp),%edx
  1020bd:	01 d1                	add    %edx,%ecx
  1020bf:	89 8d a4 fd ff ff    	mov    %ecx,-0x25c(%rbp)
  1020c5:	48 8b 78 10          	mov    0x10(%rax),%rdi
  1020c9:	8b 85 a4 fd ff ff    	mov    -0x25c(%rbp),%eax
  1020cf:	89 c6                	mov    %eax,%esi
  1020d1:	48 8d 95 d0 fd ff ff 	lea    -0x230(%rbp),%rdx
  1020d8:	48 8b 07             	mov    (%rdi),%rax
  1020db:	ff 50 10             	call   *0x10(%rax)
  1020de:	83 f8 00             	cmp    $0x0,%eax
  1020e1:	0f 84 3e 00 00 00    	je     102125 <_ZN4acos7storage12_GLOBAL__N_113FAT32FileNode4readEmmPv+0x295>
  1020e7:	48 83 bd c0 fd ff ff 	cmpq   $0x0,-0x240(%rbp)
  1020ee:	00
  1020ef:	0f 86 12 00 00 00    	jbe    102107 <_ZN4acos7storage12_GLOBAL__N_113FAT32FileNode4readEmmPv+0x277>
  1020f5:	48 8b 85 c0 fd ff ff 	mov    -0x240(%rbp),%rax
  1020fc:	89 85 80 fd ff ff    	mov    %eax,-0x280(%rbp)
  102102:	e9 10 00 00 00       	jmp    102117 <_ZN4acos7storage12_GLOBAL__N_113FAT32FileNode4readEmmPv+0x287>
  102107:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  10210c:	89 85 80 fd ff ff    	mov    %eax,-0x280(%rbp)
  102112:	e9 00 00 00 00       	jmp    102117 <_ZN4acos7storage12_GLOBAL__N_113FAT32FileNode4readEmmPv+0x287>
  102117:	8b 85 80 fd ff ff    	mov    -0x280(%rbp),%eax
  10211d:	89 45 fc             	mov    %eax,-0x4(%rbp)
  102120:	e9 13 01 00 00       	jmp    102238 <_ZN4acos7storage12_GLOBAL__N_113FAT32FileNode4readEmmPv+0x3a8>
  102125:	48 c7 85 98 fd ff ff 	movq   $0x0,-0x268(%rbp)
  10212c:	00 00 00 00
  102130:	48 81 bd b0 fd ff ff 	cmpq   $0x200,-0x250(%rbp)
  102137:	00 02 00 00
  10213b:	0f 82 19 00 00 00    	jb     10215a <_ZN4acos7storage12_GLOBAL__N_113FAT32FileNode4readEmmPv+0x2ca>
  102141:	48 8b 85 b0 fd ff ff 	mov    -0x250(%rbp),%rax
  102148:	48 2d 00 02 00 00    	sub    $0x200,%rax
  10214e:	48 89 85 b0 fd ff ff 	mov    %rax,-0x250(%rbp)
  102155:	e9 a4 00 00 00       	jmp    1021fe <_ZN4acos7storage12_GLOBAL__N_113FAT32FileNode4readEmmPv+0x36e>
  10215a:	48 83 bd b0 fd ff ff 	cmpq   $0x0,-0x250(%rbp)
  102161:	00
  102162:	0f 86 19 00 00 00    	jbe    102181 <_ZN4acos7storage12_GLOBAL__N_113FAT32FileNode4readEmmPv+0x2f1>
  102168:	48 8b 85 b0 fd ff ff 	mov    -0x250(%rbp),%rax
  10216f:	48 89 85 98 fd ff ff 	mov    %rax,-0x268(%rbp)
  102176:	48 c7 85 b0 fd ff ff 	movq   $0x0,-0x250(%rbp)
  10217d:	00 00 00 00
  102181:	b8 00 02 00 00       	mov    $0x200,%eax
  102186:	48 2b 85 98 fd ff ff 	sub    -0x268(%rbp),%rax
  10218d:	48 89 85 90 fd ff ff 	mov    %rax,-0x270(%rbp)
  102194:	48 8b 85 90 fd ff ff 	mov    -0x270(%rbp),%rax
  10219b:	48 8b 4d d0          	mov    -0x30(%rbp),%rcx
  10219f:	48 2b 8d c0 fd ff ff 	sub    -0x240(%rbp),%rcx
  1021a6:	48 39 c8             	cmp    %rcx,%rax
  1021a9:	0f 86 12 00 00 00    	jbe    1021c1 <_ZN4acos7storage12_GLOBAL__N_113FAT32FileNode4readEmmPv+0x331>
  1021af:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  1021b3:	48 2b 85 c0 fd ff ff 	sub    -0x240(%rbp),%rax
  1021ba:	48 89 85 90 fd ff ff 	mov    %rax,-0x270(%rbp)
  1021c1:	48 8b bd c8 fd ff ff 	mov    -0x238(%rbp),%rdi
  1021c8:	48 03 bd c0 fd ff ff 	add    -0x240(%rbp),%rdi
  1021cf:	48 8d b5 d0 fd ff ff 	lea    -0x230(%rbp),%rsi
  1021d6:	48 03 b5 98 fd ff ff 	add    -0x268(%rbp),%rsi
  1021dd:	48 8b 95 90 fd ff ff 	mov    -0x270(%rbp),%rdx
  1021e4:	e8 17 de ff ff       	call   100000 <memcpy>
  1021e9:	48 8b 85 90 fd ff ff 	mov    -0x270(%rbp),%rax
  1021f0:	48 03 85 c0 fd ff ff 	add    -0x240(%rbp),%rax
  1021f7:	48 89 85 c0 fd ff ff 	mov    %rax,-0x240(%rbp)
  1021fe:	8a 85 ab fd ff ff    	mov    -0x255(%rbp),%al
  102204:	04 01                	add    $0x1,%al
  102206:	88 85 ab fd ff ff    	mov    %al,-0x255(%rbp)
  10220c:	e9 40 fe ff ff       	jmp    102051 <_ZN4acos7storage12_GLOBAL__N_113FAT32FileNode4readEmmPv+0x1c1>
  102211:	48 8b bd 88 fd ff ff 	mov    -0x278(%rbp),%rdi
  102218:	8b b5 bc fd ff ff    	mov    -0x244(%rbp),%esi
  10221e:	e8 cd 00 00 00       	call   1022f0 <_ZN4acos7storage12_GLOBAL__N_113FAT32FileNode12next_clusterEj>
  102223:	89 85 bc fd ff ff    	mov    %eax,-0x244(%rbp)
  102229:	e9 c8 fd ff ff       	jmp    101ff6 <_ZN4acos7storage12_GLOBAL__N_113FAT32FileNode4readEmmPv+0x166>
  10222e:	48 8b 85 c0 fd ff ff 	mov    -0x240(%rbp),%rax
  102235:	89 45 fc             	mov    %eax,-0x4(%rbp)
  102238:	8b 45 fc             	mov    -0x4(%rbp),%eax
  10223b:	48 81 c4 80 02 00 00 	add    $0x280,%rsp
  102242:	5d                   	pop    %rbp
  102243:	c3                   	ret
  102244:	66 66 66 2e 0f 1f 84 	data16 data16 cs nopw 0x0(%rax,%rax,1)
  10224b:	00 00 00 00 00

0000000000102250 <_ZN4acos7storage12_GLOBAL__N_113FAT32FileNode5writeEmmPKv>:
  102250:	55                   	push   %rbp
  102251:	48 89 e5             	mov    %rsp,%rbp
  102254:	48 83 ec 20          	sub    $0x20,%rsp
  102258:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10225c:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  102260:	48 89 55 e8          	mov    %rdx,-0x18(%rbp)
  102264:	48 89 4d e0          	mov    %rcx,-0x20(%rbp)
  102268:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  10226d:	48 83 c4 20          	add    $0x20,%rsp
  102271:	5d                   	pop    %rbp
  102272:	c3                   	ret
  102273:	66 66 66 66 2e 0f 1f 	data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
  10227a:	84 00 00 00 00 00

0000000000102280 <_ZNK4acos7storage12_GLOBAL__N_113FAT32FileNode4sizeEv>:
  102280:	55                   	push   %rbp
  102281:	48 89 e5             	mov    %rsp,%rbp
  102284:	50                   	push   %rax
  102285:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  102289:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10228d:	8b 40 1c             	mov    0x1c(%rax),%eax
  102290:	48 83 c4 08          	add    $0x8,%rsp
  102294:	5d                   	pop    %rbp
  102295:	c3                   	ret
  102296:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
  10229d:	00 00 00

00000000001022a0 <_ZNK4acos7storage12_GLOBAL__N_113FAT32FileNode4typeEv>:
  1022a0:	55                   	push   %rbp
  1022a1:	48 89 e5             	mov    %rsp,%rbp
  1022a4:	50                   	push   %rax
  1022a5:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  1022a9:	b8 01 00 00 00       	mov    $0x1,%eax
  1022ae:	48 83 c4 08          	add    $0x8,%rsp
  1022b2:	5d                   	pop    %rbp
  1022b3:	c3                   	ret
  1022b4:	66 66 66 2e 0f 1f 84 	data16 data16 cs nopw 0x0(%rax,%rax,1)
  1022bb:	00 00 00 00 00

00000000001022c0 <_ZN4acos7storage12_GLOBAL__N_113FAT32FileNode8read_dirEmPNS_3vfs14DirectoryEntryEm>:
  1022c0:	55                   	push   %rbp
  1022c1:	48 89 e5             	mov    %rsp,%rbp
  1022c4:	48 83 ec 20          	sub    $0x20,%rsp
  1022c8:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  1022cc:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  1022d0:	48 89 55 e8          	mov    %rdx,-0x18(%rbp)
  1022d4:	48 89 4d e0          	mov    %rcx,-0x20(%rbp)
  1022d8:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  1022dd:	48 83 c4 20          	add    $0x20,%rsp
  1022e1:	5d                   	pop    %rbp
  1022e2:	c3                   	ret
  1022e3:	66 66 66 66 2e 0f 1f 	data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
  1022ea:	84 00 00 00 00 00

00000000001022f0 <_ZN4acos7storage12_GLOBAL__N_113FAT32FileNode12next_clusterEj>:
  1022f0:	55                   	push   %rbp
  1022f1:	48 89 e5             	mov    %rsp,%rbp
  1022f4:	48 81 ec 30 02 00 00 	sub    $0x230,%rsp
  1022fb:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  1022ff:	89 75 ec             	mov    %esi,-0x14(%rbp)
  102302:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  102306:	48 89 85 d0 fd ff ff 	mov    %rax,-0x230(%rbp)
  10230d:	8b 4d ec             	mov    -0x14(%rbp),%ecx
  102310:	c1 e1 02             	shl    $0x2,%ecx
  102313:	89 8d dc fd ff ff    	mov    %ecx,-0x224(%rbp)
  102319:	8b 48 20             	mov    0x20(%rax),%ecx
  10231c:	8b 95 dc fd ff ff    	mov    -0x224(%rbp),%edx
  102322:	c1 ea 09             	shr    $0x9,%edx
  102325:	01 d1                	add    %edx,%ecx
  102327:	89 8d d8 fd ff ff    	mov    %ecx,-0x228(%rbp)
  10232d:	48 83 78 10 00       	cmpq   $0x0,0x10(%rax)
  102332:	0f 84 29 00 00 00    	je     102361 <_ZN4acos7storage12_GLOBAL__N_113FAT32FileNode12next_clusterEj+0x71>
  102338:	48 8b 85 d0 fd ff ff 	mov    -0x230(%rbp),%rax
  10233f:	48 8b 78 10          	mov    0x10(%rax),%rdi
  102343:	8b 85 d8 fd ff ff    	mov    -0x228(%rbp),%eax
  102349:	89 c6                	mov    %eax,%esi
  10234b:	48 8d 95 e0 fd ff ff 	lea    -0x220(%rbp),%rdx
  102352:	48 8b 07             	mov    (%rdi),%rax
  102355:	ff 50 10             	call   *0x10(%rax)
  102358:	83 f8 00             	cmp    $0x0,%eax
  10235b:	0f 84 0c 00 00 00    	je     10236d <_ZN4acos7storage12_GLOBAL__N_113FAT32FileNode12next_clusterEj+0x7d>
  102361:	c7 45 fc ff ff ff 0f 	movl   $0xfffffff,-0x4(%rbp)
  102368:	e9 1c 00 00 00       	jmp    102389 <_ZN4acos7storage12_GLOBAL__N_113FAT32FileNode12next_clusterEj+0x99>
  10236d:	8b 85 dc fd ff ff    	mov    -0x224(%rbp),%eax
  102373:	25 ff 01 00 00       	and    $0x1ff,%eax
  102378:	89 c0                	mov    %eax,%eax
  10237a:	8b 84 05 e0 fd ff ff 	mov    -0x220(%rbp,%rax,1),%eax
  102381:	25 ff ff ff 0f       	and    $0xfffffff,%eax
  102386:	89 45 fc             	mov    %eax,-0x4(%rbp)
  102389:	8b 45 fc             	mov    -0x4(%rbp),%eax
  10238c:	48 81 c4 30 02 00 00 	add    $0x230,%rsp
  102393:	5d                   	pop    %rbp
  102394:	c3                   	ret
  102395:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  10239c:	00 00 00 00

00000000001023a0 <_ZN4acos7storage12_GLOBAL__N_112FAT32DirNodeD2Ev>:
  1023a0:	55                   	push   %rbp
  1023a1:	48 89 e5             	mov    %rsp,%rbp
  1023a4:	48 83 ec 10          	sub    $0x10,%rsp
  1023a8:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  1023ac:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  1023b0:	e8 6b c5 00 00       	call   10e920 <_ZN4acos3vfs4NodeD2Ev>
  1023b5:	48 83 c4 10          	add    $0x10,%rsp
  1023b9:	5d                   	pop    %rbp
  1023ba:	c3                   	ret
  1023bb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000001023c0 <_ZN4acos7storage12_GLOBAL__N_112FAT32DirNodeD0Ev>:
  1023c0:	55                   	push   %rbp
  1023c1:	48 89 e5             	mov    %rsp,%rbp
  1023c4:	48 83 ec 10          	sub    $0x10,%rsp
  1023c8:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  1023cc:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  1023d0:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  1023d4:	e8 c7 ff ff ff       	call   1023a0 <_ZN4acos7storage12_GLOBAL__N_112FAT32DirNodeD2Ev>
  1023d9:	48 8b 7d f0          	mov    -0x10(%rbp),%rdi
  1023dd:	e8 4e e0 ff ff       	call   100430 <_ZdlPv>
  1023e2:	48 83 c4 10          	add    $0x10,%rsp
  1023e6:	5d                   	pop    %rbp
  1023e7:	c3                   	ret
  1023e8:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  1023ef:	00

00000000001023f0 <_ZN4acos7storage12_GLOBAL__N_112FAT32DirNode4readEmmPv>:
  1023f0:	55                   	push   %rbp
  1023f1:	48 89 e5             	mov    %rsp,%rbp
  1023f4:	48 83 ec 20          	sub    $0x20,%rsp
  1023f8:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  1023fc:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  102400:	48 89 55 e8          	mov    %rdx,-0x18(%rbp)
  102404:	48 89 4d e0          	mov    %rcx,-0x20(%rbp)
  102408:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  10240d:	48 83 c4 20          	add    $0x20,%rsp
  102411:	5d                   	pop    %rbp
  102412:	c3                   	ret
  102413:	66 66 66 66 2e 0f 1f 	data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
  10241a:	84 00 00 00 00 00

0000000000102420 <_ZN4acos7storage12_GLOBAL__N_112FAT32DirNode5writeEmmPKv>:
  102420:	55                   	push   %rbp
  102421:	48 89 e5             	mov    %rsp,%rbp
  102424:	48 83 ec 20          	sub    $0x20,%rsp
  102428:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10242c:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  102430:	48 89 55 e8          	mov    %rdx,-0x18(%rbp)
  102434:	48 89 4d e0          	mov    %rcx,-0x20(%rbp)
  102438:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  10243d:	48 83 c4 20          	add    $0x20,%rsp
  102441:	5d                   	pop    %rbp
  102442:	c3                   	ret
  102443:	66 66 66 66 2e 0f 1f 	data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
  10244a:	84 00 00 00 00 00

0000000000102450 <_ZNK4acos7storage12_GLOBAL__N_112FAT32DirNode4sizeEv>:
  102450:	55                   	push   %rbp
  102451:	48 89 e5             	mov    %rsp,%rbp
  102454:	50                   	push   %rax
  102455:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  102459:	31 c0                	xor    %eax,%eax
  10245b:	48 83 c4 08          	add    $0x8,%rsp
  10245f:	5d                   	pop    %rbp
  102460:	c3                   	ret
  102461:	66 66 66 66 66 66 2e 	data16 data16 data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
  102468:	0f 1f 84 00 00 00 00
  10246f:	00

0000000000102470 <_ZNK4acos7storage12_GLOBAL__N_112FAT32DirNode4typeEv>:
  102470:	55                   	push   %rbp
  102471:	48 89 e5             	mov    %rsp,%rbp
  102474:	50                   	push   %rax
  102475:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  102479:	b8 02 00 00 00       	mov    $0x2,%eax
  10247e:	48 83 c4 08          	add    $0x8,%rsp
  102482:	5d                   	pop    %rbp
  102483:	c3                   	ret
  102484:	66 66 66 2e 0f 1f 84 	data16 data16 cs nopw 0x0(%rax,%rax,1)
  10248b:	00 00 00 00 00

0000000000102490 <_ZN4acos7storage12_GLOBAL__N_112FAT32DirNode8read_dirEmPNS_3vfs14DirectoryEntryEm>:
  102490:	55                   	push   %rbp
  102491:	48 89 e5             	mov    %rsp,%rbp
  102494:	48 81 ec 90 02 00 00 	sub    $0x290,%rsp
  10249b:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  10249f:	48 89 75 e8          	mov    %rsi,-0x18(%rbp)
  1024a3:	48 89 55 e0          	mov    %rdx,-0x20(%rbp)
  1024a7:	48 89 4d d8          	mov    %rcx,-0x28(%rbp)
  1024ab:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  1024af:	48 89 85 78 fd ff ff 	mov    %rax,-0x288(%rbp)
  1024b6:	8b 40 18             	mov    0x18(%rax),%eax
  1024b9:	89 85 cc fd ff ff    	mov    %eax,-0x234(%rbp)
  1024bf:	48 c7 85 c0 fd ff ff 	movq   $0x0,-0x240(%rbp)
  1024c6:	00 00 00 00
  1024ca:	48 c7 85 b8 fd ff ff 	movq   $0x0,-0x248(%rbp)
  1024d1:	00 00 00 00
  1024d5:	31 c0                	xor    %eax,%eax
  1024d7:	83 bd cc fd ff ff 02 	cmpl   $0x2,-0x234(%rbp)
  1024de:	88 85 77 fd ff ff    	mov    %al,-0x289(%rbp)
  1024e4:	0f 82 2c 00 00 00    	jb     102516 <_ZN4acos7storage12_GLOBAL__N_112FAT32DirNode8read_dirEmPNS_3vfs14DirectoryEntryEm+0x86>
  1024ea:	31 c0                	xor    %eax,%eax
  1024ec:	81 bd cc fd ff ff f8 	cmpl   $0xffffff8,-0x234(%rbp)
  1024f3:	ff ff 0f
  1024f6:	88 85 77 fd ff ff    	mov    %al,-0x289(%rbp)
  1024fc:	0f 83 14 00 00 00    	jae    102516 <_ZN4acos7storage12_GLOBAL__N_112FAT32DirNode8read_dirEmPNS_3vfs14DirectoryEntryEm+0x86>
  102502:	48 8b 85 c0 fd ff ff 	mov    -0x240(%rbp),%rax
  102509:	48 3b 45 d8          	cmp    -0x28(%rbp),%rax
  10250d:	0f 92 c0             	setb   %al
  102510:	88 85 77 fd ff ff    	mov    %al,-0x289(%rbp)
  102516:	8a 85 77 fd ff ff    	mov    -0x289(%rbp),%al
  10251c:	a8 01                	test   $0x1,%al
  10251e:	0f 85 05 00 00 00    	jne    102529 <_ZN4acos7storage12_GLOBAL__N_112FAT32DirNode8read_dirEmPNS_3vfs14DirectoryEntryEm+0x99>
  102524:	e9 ac 03 00 00       	jmp    1028d5 <_ZN4acos7storage12_GLOBAL__N_112FAT32DirNode8read_dirEmPNS_3vfs14DirectoryEntryEm+0x445>
  102529:	c6 85 b7 fd ff ff 00 	movb   $0x0,-0x249(%rbp)
  102530:	48 8b 85 78 fd ff ff 	mov    -0x288(%rbp),%rax
  102537:	0f b6 8d b7 fd ff ff 	movzbl -0x249(%rbp),%ecx
  10253e:	0f b6 50 24          	movzbl 0x24(%rax),%edx
  102542:	31 c0                	xor    %eax,%eax
  102544:	39 d1                	cmp    %edx,%ecx
  102546:	88 85 76 fd ff ff    	mov    %al,-0x28a(%rbp)
  10254c:	0f 8d 14 00 00 00    	jge    102566 <_ZN4acos7storage12_GLOBAL__N_112FAT32DirNode8read_dirEmPNS_3vfs14DirectoryEntryEm+0xd6>
  102552:	48 8b 85 c0 fd ff ff 	mov    -0x240(%rbp),%rax
  102559:	48 3b 45 d8          	cmp    -0x28(%rbp),%rax
  10255d:	0f 92 c0             	setb   %al
  102560:	88 85 76 fd ff ff    	mov    %al,-0x28a(%rbp)
  102566:	8a 85 76 fd ff ff    	mov    -0x28a(%rbp),%al
  10256c:	a8 01                	test   $0x1,%al
  10256e:	0f 85 05 00 00 00    	jne    102579 <_ZN4acos7storage12_GLOBAL__N_112FAT32DirNode8read_dirEmPNS_3vfs14DirectoryEntryEm+0xe9>
  102574:	e9 3f 03 00 00       	jmp    1028b8 <_ZN4acos7storage12_GLOBAL__N_112FAT32DirNode8read_dirEmPNS_3vfs14DirectoryEntryEm+0x428>
  102579:	48 8b 85 78 fd ff ff 	mov    -0x288(%rbp),%rax
  102580:	8b 48 20             	mov    0x20(%rax),%ecx
  102583:	8b 95 cc fd ff ff    	mov    -0x234(%rbp),%edx
  102589:	83 ea 02             	sub    $0x2,%edx
  10258c:	0f b6 70 24          	movzbl 0x24(%rax),%esi
  102590:	0f af d6             	imul   %esi,%edx
  102593:	01 d1                	add    %edx,%ecx
  102595:	0f b6 95 b7 fd ff ff 	movzbl -0x249(%rbp),%edx
  10259c:	01 d1                	add    %edx,%ecx
  10259e:	89 8d b0 fd ff ff    	mov    %ecx,-0x250(%rbp)
  1025a4:	48 8b 78 10          	mov    0x10(%rax),%rdi
  1025a8:	8b 85 b0 fd ff ff    	mov    -0x250(%rbp),%eax
  1025ae:	89 c6                	mov    %eax,%esi
  1025b0:	48 8d 95 d0 fd ff ff 	lea    -0x230(%rbp),%rdx
  1025b7:	48 8b 07             	mov    (%rdi),%rax
  1025ba:	ff 50 10             	call   *0x10(%rax)
  1025bd:	83 f8 00             	cmp    $0x0,%eax
  1025c0:	0f 84 0f 00 00 00    	je     1025d5 <_ZN4acos7storage12_GLOBAL__N_112FAT32DirNode8read_dirEmPNS_3vfs14DirectoryEntryEm+0x145>
  1025c6:	48 8b 85 c0 fd ff ff 	mov    -0x240(%rbp),%rax
  1025cd:	89 45 fc             	mov    %eax,-0x4(%rbp)
  1025d0:	e9 0a 03 00 00       	jmp    1028df <_ZN4acos7storage12_GLOBAL__N_112FAT32DirNode8read_dirEmPNS_3vfs14DirectoryEntryEm+0x44f>
  1025d5:	c7 85 ac fd ff ff 00 	movl   $0x0,-0x254(%rbp)
  1025dc:	00 00 00
  1025df:	83 bd ac fd ff ff 10 	cmpl   $0x10,-0x254(%rbp)
  1025e6:	0f 8d b4 02 00 00    	jge    1028a0 <_ZN4acos7storage12_GLOBAL__N_112FAT32DirNode8read_dirEmPNS_3vfs14DirectoryEntryEm+0x410>
  1025ec:	48 8d 85 d0 fd ff ff 	lea    -0x230(%rbp),%rax
  1025f3:	8b 8d ac fd ff ff    	mov    -0x254(%rbp),%ecx
  1025f9:	c1 e1 05             	shl    $0x5,%ecx
  1025fc:	48 63 c9             	movslq %ecx,%rcx
  1025ff:	48 01 c8             	add    %rcx,%rax
  102602:	48 89 85 a0 fd ff ff 	mov    %rax,-0x260(%rbp)
  102609:	48 8b 85 a0 fd ff ff 	mov    -0x260(%rbp),%rax
  102610:	0f b6 00             	movzbl (%rax),%eax
  102613:	83 f8 00             	cmp    $0x0,%eax
  102616:	0f 85 0f 00 00 00    	jne    10262b <_ZN4acos7storage12_GLOBAL__N_112FAT32DirNode8read_dirEmPNS_3vfs14DirectoryEntryEm+0x19b>
  10261c:	48 8b 85 c0 fd ff ff 	mov    -0x240(%rbp),%rax
  102623:	89 45 fc             	mov    %eax,-0x4(%rbp)
  102626:	e9 b4 02 00 00       	jmp    1028df <_ZN4acos7storage12_GLOBAL__N_112FAT32DirNode8read_dirEmPNS_3vfs14DirectoryEntryEm+0x44f>
  10262b:	48 8b 85 a0 fd ff ff 	mov    -0x260(%rbp),%rax
  102632:	0f b6 00             	movzbl (%rax),%eax
  102635:	3d e5 00 00 00       	cmp    $0xe5,%eax
  10263a:	0f 84 17 00 00 00    	je     102657 <_ZN4acos7storage12_GLOBAL__N_112FAT32DirNode8read_dirEmPNS_3vfs14DirectoryEntryEm+0x1c7>
  102640:	48 8b 85 a0 fd ff ff 	mov    -0x260(%rbp),%rax
  102647:	0f b6 40 0b          	movzbl 0xb(%rax),%eax
  10264b:	83 e0 08             	and    $0x8,%eax
  10264e:	83 f8 00             	cmp    $0x0,%eax
  102651:	0f 84 05 00 00 00    	je     10265c <_ZN4acos7storage12_GLOBAL__N_112FAT32DirNode8read_dirEmPNS_3vfs14DirectoryEntryEm+0x1cc>
  102657:	e9 30 02 00 00       	jmp    10288c <_ZN4acos7storage12_GLOBAL__N_112FAT32DirNode8read_dirEmPNS_3vfs14DirectoryEntryEm+0x3fc>
  10265c:	48 8b 85 b8 fd ff ff 	mov    -0x248(%rbp),%rax
  102663:	48 3b 45 e8          	cmp    -0x18(%rbp),%rax
  102667:	0f 83 17 00 00 00    	jae    102684 <_ZN4acos7storage12_GLOBAL__N_112FAT32DirNode8read_dirEmPNS_3vfs14DirectoryEntryEm+0x1f4>
  10266d:	48 8b 85 b8 fd ff ff 	mov    -0x248(%rbp),%rax
  102674:	48 83 c0 01          	add    $0x1,%rax
  102678:	48 89 85 b8 fd ff ff 	mov    %rax,-0x248(%rbp)
  10267f:	e9 08 02 00 00       	jmp    10288c <_ZN4acos7storage12_GLOBAL__N_112FAT32DirNode8read_dirEmPNS_3vfs14DirectoryEntryEm+0x3fc>
  102684:	48 8d bd 93 fd ff ff 	lea    -0x26d(%rbp),%rdi
  10268b:	31 f6                	xor    %esi,%esi
  10268d:	ba 0d 00 00 00       	mov    $0xd,%edx
  102692:	e8 d9 d9 ff ff       	call   100070 <memset>
  102697:	c7 85 8c fd ff ff 00 	movl   $0x0,-0x274(%rbp)
  10269e:	00 00 00
  1026a1:	c7 85 88 fd ff ff 00 	movl   $0x0,-0x278(%rbp)
  1026a8:	00 00 00
  1026ab:	83 bd 88 fd ff ff 08 	cmpl   $0x8,-0x278(%rbp)
  1026b2:	0f 8d 5f 00 00 00    	jge    102717 <_ZN4acos7storage12_GLOBAL__N_112FAT32DirNode8read_dirEmPNS_3vfs14DirectoryEntryEm+0x287>
  1026b8:	48 8b 85 a0 fd ff ff 	mov    -0x260(%rbp),%rax
  1026bf:	48 63 8d 88 fd ff ff 	movslq -0x278(%rbp),%rcx
  1026c6:	0f b6 04 08          	movzbl (%rax,%rcx,1),%eax
  1026ca:	83 f8 20             	cmp    $0x20,%eax
  1026cd:	0f 84 2b 00 00 00    	je     1026fe <_ZN4acos7storage12_GLOBAL__N_112FAT32DirNode8read_dirEmPNS_3vfs14DirectoryEntryEm+0x26e>
  1026d3:	48 8b 85 a0 fd ff ff 	mov    -0x260(%rbp),%rax
  1026da:	48 63 8d 88 fd ff ff 	movslq -0x278(%rbp),%rcx
  1026e1:	8a 0c 08             	mov    (%rax,%rcx,1),%cl
  1026e4:	8b 85 8c fd ff ff    	mov    -0x274(%rbp),%eax
  1026ea:	89 c2                	mov    %eax,%edx
  1026ec:	83 c2 01             	add    $0x1,%edx
  1026ef:	89 95 8c fd ff ff    	mov    %edx,-0x274(%rbp)
  1026f5:	48 98                	cltq
  1026f7:	88 8c 05 93 fd ff ff 	mov    %cl,-0x26d(%rbp,%rax,1)
  1026fe:	e9 00 00 00 00       	jmp    102703 <_ZN4acos7storage12_GLOBAL__N_112FAT32DirNode8read_dirEmPNS_3vfs14DirectoryEntryEm+0x273>
  102703:	8b 85 88 fd ff ff    	mov    -0x278(%rbp),%eax
  102709:	83 c0 01             	add    $0x1,%eax
  10270c:	89 85 88 fd ff ff    	mov    %eax,-0x278(%rbp)
  102712:	e9 94 ff ff ff       	jmp    1026ab <_ZN4acos7storage12_GLOBAL__N_112FAT32DirNode8read_dirEmPNS_3vfs14DirectoryEntryEm+0x21b>
  102717:	48 8b 85 a0 fd ff ff 	mov    -0x260(%rbp),%rax
  10271e:	0f b6 40 08          	movzbl 0x8(%rax),%eax
  102722:	83 f8 20             	cmp    $0x20,%eax
  102725:	0f 84 96 00 00 00    	je     1027c1 <_ZN4acos7storage12_GLOBAL__N_112FAT32DirNode8read_dirEmPNS_3vfs14DirectoryEntryEm+0x331>
  10272b:	8b 85 8c fd ff ff    	mov    -0x274(%rbp),%eax
  102731:	89 c1                	mov    %eax,%ecx
  102733:	83 c1 01             	add    $0x1,%ecx
  102736:	89 8d 8c fd ff ff    	mov    %ecx,-0x274(%rbp)
  10273c:	48 98                	cltq
  10273e:	c6 84 05 93 fd ff ff 	movb   $0x2e,-0x26d(%rbp,%rax,1)
  102745:	2e
  102746:	c7 85 84 fd ff ff 08 	movl   $0x8,-0x27c(%rbp)
  10274d:	00 00 00
  102750:	83 bd 84 fd ff ff 0b 	cmpl   $0xb,-0x27c(%rbp)
  102757:	0f 8d 5f 00 00 00    	jge    1027bc <_ZN4acos7storage12_GLOBAL__N_112FAT32DirNode8read_dirEmPNS_3vfs14DirectoryEntryEm+0x32c>
  10275d:	48 8b 85 a0 fd ff ff 	mov    -0x260(%rbp),%rax
  102764:	48 63 8d 84 fd ff ff 	movslq -0x27c(%rbp),%rcx
  10276b:	0f b6 04 08          	movzbl (%rax,%rcx,1),%eax
  10276f:	83 f8 20             	cmp    $0x20,%eax
  102772:	0f 84 2b 00 00 00    	je     1027a3 <_ZN4acos7storage12_GLOBAL__N_112FAT32DirNode8read_dirEmPNS_3vfs14DirectoryEntryEm+0x313>
  102778:	48 8b 85 a0 fd ff ff 	mov    -0x260(%rbp),%rax
  10277f:	48 63 8d 84 fd ff ff 	movslq -0x27c(%rbp),%rcx
  102786:	8a 0c 08             	mov    (%rax,%rcx,1),%cl
  102789:	8b 85 8c fd ff ff    	mov    -0x274(%rbp),%eax
  10278f:	89 c2                	mov    %eax,%edx
  102791:	83 c2 01             	add    $0x1,%edx
  102794:	89 95 8c fd ff ff    	mov    %edx,-0x274(%rbp)
  10279a:	48 98                	cltq
  10279c:	88 8c 05 93 fd ff ff 	mov    %cl,-0x26d(%rbp,%rax,1)
  1027a3:	e9 00 00 00 00       	jmp    1027a8 <_ZN4acos7storage12_GLOBAL__N_112FAT32DirNode8read_dirEmPNS_3vfs14DirectoryEntryEm+0x318>
  1027a8:	8b 85 84 fd ff ff    	mov    -0x27c(%rbp),%eax
  1027ae:	83 c0 01             	add    $0x1,%eax
  1027b1:	89 85 84 fd ff ff    	mov    %eax,-0x27c(%rbp)
  1027b7:	e9 94 ff ff ff       	jmp    102750 <_ZN4acos7storage12_GLOBAL__N_112FAT32DirNode8read_dirEmPNS_3vfs14DirectoryEntryEm+0x2c0>
  1027bc:	e9 00 00 00 00       	jmp    1027c1 <_ZN4acos7storage12_GLOBAL__N_112FAT32DirNode8read_dirEmPNS_3vfs14DirectoryEntryEm+0x331>
  1027c1:	48 63 85 8c fd ff ff 	movslq -0x274(%rbp),%rax
  1027c8:	c6 84 05 93 fd ff ff 	movb   $0x0,-0x26d(%rbp,%rax,1)
  1027cf:	00
  1027d0:	48 8b 7d e0          	mov    -0x20(%rbp),%rdi
  1027d4:	48 69 85 c0 fd ff ff 	imul   $0x118,-0x240(%rbp),%rax
  1027db:	18 01 00 00
  1027df:	48 01 c7             	add    %rax,%rdi
  1027e2:	48 8d b5 93 fd ff ff 	lea    -0x26d(%rbp),%rsi
  1027e9:	8b 85 8c fd ff ff    	mov    -0x274(%rbp),%eax
  1027ef:	83 c0 01             	add    $0x1,%eax
  1027f2:	48 63 d0             	movslq %eax,%rdx
  1027f5:	e8 06 d8 ff ff       	call   100000 <memcpy>
  1027fa:	48 8b 85 a0 fd ff ff 	mov    -0x260(%rbp),%rax
  102801:	0f b6 50 0b          	movzbl 0xb(%rax),%edx
  102805:	83 e2 10             	and    $0x10,%edx
  102808:	b9 01 00 00 00       	mov    $0x1,%ecx
  10280d:	b8 02 00 00 00       	mov    $0x2,%eax
  102812:	83 fa 00             	cmp    $0x0,%edx
  102815:	0f 45 c8             	cmovne %eax,%ecx
  102818:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  10281c:	48 69 95 c0 fd ff ff 	imul   $0x118,-0x240(%rbp),%rdx
  102823:	18 01 00 00
  102827:	48 01 d0             	add    %rdx,%rax
  10282a:	89 88 00 01 00 00    	mov    %ecx,0x100(%rax)
  102830:	48 8b 85 a0 fd ff ff 	mov    -0x260(%rbp),%rax
  102837:	8b 40 1c             	mov    0x1c(%rax),%eax
  10283a:	89 c1                	mov    %eax,%ecx
  10283c:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  102840:	48 69 95 c0 fd ff ff 	imul   $0x118,-0x240(%rbp),%rdx
  102847:	18 01 00 00
  10284b:	48 01 d0             	add    %rdx,%rax
  10284e:	48 89 88 08 01 00 00 	mov    %rcx,0x108(%rax)
  102855:	48 8b 85 c0 fd ff ff 	mov    -0x240(%rbp),%rax
  10285c:	48 83 c0 01          	add    $0x1,%rax
  102860:	48 89 85 c0 fd ff ff 	mov    %rax,-0x240(%rbp)
  102867:	48 8b 85 c0 fd ff ff 	mov    -0x240(%rbp),%rax
  10286e:	48 3b 45 d8          	cmp    -0x28(%rbp),%rax
  102872:	0f 82 0f 00 00 00    	jb     102887 <_ZN4acos7storage12_GLOBAL__N_112FAT32DirNode8read_dirEmPNS_3vfs14DirectoryEntryEm+0x3f7>
  102878:	48 8b 85 c0 fd ff ff 	mov    -0x240(%rbp),%rax
  10287f:	89 45 fc             	mov    %eax,-0x4(%rbp)
  102882:	e9 58 00 00 00       	jmp    1028df <_ZN4acos7storage12_GLOBAL__N_112FAT32DirNode8read_dirEmPNS_3vfs14DirectoryEntryEm+0x44f>
  102887:	e9 00 00 00 00       	jmp    10288c <_ZN4acos7storage12_GLOBAL__N_112FAT32DirNode8read_dirEmPNS_3vfs14DirectoryEntryEm+0x3fc>
  10288c:	8b 85 ac fd ff ff    	mov    -0x254(%rbp),%eax
  102892:	83 c0 01             	add    $0x1,%eax
  102895:	89 85 ac fd ff ff    	mov    %eax,-0x254(%rbp)
  10289b:	e9 3f fd ff ff       	jmp    1025df <_ZN4acos7storage12_GLOBAL__N_112FAT32DirNode8read_dirEmPNS_3vfs14DirectoryEntryEm+0x14f>
  1028a0:	e9 00 00 00 00       	jmp    1028a5 <_ZN4acos7storage12_GLOBAL__N_112FAT32DirNode8read_dirEmPNS_3vfs14DirectoryEntryEm+0x415>
  1028a5:	8a 85 b7 fd ff ff    	mov    -0x249(%rbp),%al
  1028ab:	04 01                	add    $0x1,%al
  1028ad:	88 85 b7 fd ff ff    	mov    %al,-0x249(%rbp)
  1028b3:	e9 78 fc ff ff       	jmp    102530 <_ZN4acos7storage12_GLOBAL__N_112FAT32DirNode8read_dirEmPNS_3vfs14DirectoryEntryEm+0xa0>
  1028b8:	48 8b bd 78 fd ff ff 	mov    -0x288(%rbp),%rdi
  1028bf:	8b b5 cc fd ff ff    	mov    -0x234(%rbp),%esi
  1028c5:	e8 26 00 00 00       	call   1028f0 <_ZN4acos7storage12_GLOBAL__N_112FAT32DirNode12next_clusterEj>
  1028ca:	89 85 cc fd ff ff    	mov    %eax,-0x234(%rbp)
  1028d0:	e9 00 fc ff ff       	jmp    1024d5 <_ZN4acos7storage12_GLOBAL__N_112FAT32DirNode8read_dirEmPNS_3vfs14DirectoryEntryEm+0x45>
  1028d5:	48 8b 85 c0 fd ff ff 	mov    -0x240(%rbp),%rax
  1028dc:	89 45 fc             	mov    %eax,-0x4(%rbp)
  1028df:	8b 45 fc             	mov    -0x4(%rbp),%eax
  1028e2:	48 81 c4 90 02 00 00 	add    $0x290,%rsp
  1028e9:	5d                   	pop    %rbp
  1028ea:	c3                   	ret
  1028eb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000001028f0 <_ZN4acos7storage12_GLOBAL__N_112FAT32DirNode12next_clusterEj>:
  1028f0:	55                   	push   %rbp
  1028f1:	48 89 e5             	mov    %rsp,%rbp
  1028f4:	48 81 ec 30 02 00 00 	sub    $0x230,%rsp
  1028fb:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  1028ff:	89 75 ec             	mov    %esi,-0x14(%rbp)
  102902:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  102906:	48 89 85 d0 fd ff ff 	mov    %rax,-0x230(%rbp)
  10290d:	8b 4d ec             	mov    -0x14(%rbp),%ecx
  102910:	c1 e1 02             	shl    $0x2,%ecx
  102913:	89 8d dc fd ff ff    	mov    %ecx,-0x224(%rbp)
  102919:	8b 48 1c             	mov    0x1c(%rax),%ecx
  10291c:	8b 95 dc fd ff ff    	mov    -0x224(%rbp),%edx
  102922:	c1 ea 09             	shr    $0x9,%edx
  102925:	01 d1                	add    %edx,%ecx
  102927:	89 8d d8 fd ff ff    	mov    %ecx,-0x228(%rbp)
  10292d:	48 83 78 10 00       	cmpq   $0x0,0x10(%rax)
  102932:	0f 84 29 00 00 00    	je     102961 <_ZN4acos7storage12_GLOBAL__N_112FAT32DirNode12next_clusterEj+0x71>
  102938:	48 8b 85 d0 fd ff ff 	mov    -0x230(%rbp),%rax
  10293f:	48 8b 78 10          	mov    0x10(%rax),%rdi
  102943:	8b 85 d8 fd ff ff    	mov    -0x228(%rbp),%eax
  102949:	89 c6                	mov    %eax,%esi
  10294b:	48 8d 95 e0 fd ff ff 	lea    -0x220(%rbp),%rdx
  102952:	48 8b 07             	mov    (%rdi),%rax
  102955:	ff 50 10             	call   *0x10(%rax)
  102958:	83 f8 00             	cmp    $0x0,%eax
  10295b:	0f 84 0c 00 00 00    	je     10296d <_ZN4acos7storage12_GLOBAL__N_112FAT32DirNode12next_clusterEj+0x7d>
  102961:	c7 45 fc ff ff ff 0f 	movl   $0xfffffff,-0x4(%rbp)
  102968:	e9 1c 00 00 00       	jmp    102989 <_ZN4acos7storage12_GLOBAL__N_112FAT32DirNode12next_clusterEj+0x99>
  10296d:	8b 85 dc fd ff ff    	mov    -0x224(%rbp),%eax
  102973:	25 ff 01 00 00       	and    $0x1ff,%eax
  102978:	89 c0                	mov    %eax,%eax
  10297a:	8b 84 05 e0 fd ff ff 	mov    -0x220(%rbp,%rax,1),%eax
  102981:	25 ff ff ff 0f       	and    $0xfffffff,%eax
  102986:	89 45 fc             	mov    %eax,-0x4(%rbp)
  102989:	8b 45 fc             	mov    -0x4(%rbp),%eax
  10298c:	48 81 c4 30 02 00 00 	add    $0x230,%rsp
  102993:	5d                   	pop    %rbp
  102994:	c3                   	ret
  102995:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  10299c:	00 00 00 00

00000000001029a0 <_ZN4acos7storage12_GLOBAL__N_112FAT32DirNode10initializeEPNS0_11BlockDeviceEjjjh>:
  1029a0:	55                   	push   %rbp
  1029a1:	48 89 e5             	mov    %rsp,%rbp
  1029a4:	48 83 ec 20          	sub    $0x20,%rsp
  1029a8:	44 88 c8             	mov    %r9b,%al
  1029ab:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  1029af:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  1029b3:	89 55 ec             	mov    %edx,-0x14(%rbp)
  1029b6:	89 4d e8             	mov    %ecx,-0x18(%rbp)
  1029b9:	44 89 45 e4          	mov    %r8d,-0x1c(%rbp)
  1029bd:	88 45 e3             	mov    %al,-0x1d(%rbp)
  1029c0:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  1029c4:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
  1029c8:	48 89 48 10          	mov    %rcx,0x10(%rax)
  1029cc:	8b 4d ec             	mov    -0x14(%rbp),%ecx
  1029cf:	89 48 18             	mov    %ecx,0x18(%rax)
  1029d2:	8b 4d e8             	mov    -0x18(%rbp),%ecx
  1029d5:	89 48 1c             	mov    %ecx,0x1c(%rax)
  1029d8:	8b 4d e4             	mov    -0x1c(%rbp),%ecx
  1029db:	89 48 20             	mov    %ecx,0x20(%rax)
  1029de:	8a 4d e3             	mov    -0x1d(%rbp),%cl
  1029e1:	88 48 24             	mov    %cl,0x24(%rax)
  1029e4:	48 83 c4 20          	add    $0x20,%rsp
  1029e8:	5d                   	pop    %rbp
  1029e9:	c3                   	ret
  1029ea:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

00000000001029f0 <_ZN4acos7storage12_GLOBAL__N_113FAT32FileNode10initializeEPNS0_11BlockDeviceEjjjjh>:
  1029f0:	55                   	push   %rbp
  1029f1:	48 89 e5             	mov    %rsp,%rbp
  1029f4:	48 83 ec 20          	sub    $0x20,%rsp
  1029f8:	8a 45 10             	mov    0x10(%rbp),%al
  1029fb:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  1029ff:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  102a03:	89 55 ec             	mov    %edx,-0x14(%rbp)
  102a06:	89 4d e8             	mov    %ecx,-0x18(%rbp)
  102a09:	44 89 45 e4          	mov    %r8d,-0x1c(%rbp)
  102a0d:	44 89 4d e0          	mov    %r9d,-0x20(%rbp)
  102a11:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  102a15:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
  102a19:	48 89 48 10          	mov    %rcx,0x10(%rax)
  102a1d:	8b 4d ec             	mov    -0x14(%rbp),%ecx
  102a20:	89 48 18             	mov    %ecx,0x18(%rax)
  102a23:	8b 4d e8             	mov    -0x18(%rbp),%ecx
  102a26:	89 48 1c             	mov    %ecx,0x1c(%rax)
  102a29:	8b 4d e4             	mov    -0x1c(%rbp),%ecx
  102a2c:	89 48 20             	mov    %ecx,0x20(%rax)
  102a2f:	8b 4d e0             	mov    -0x20(%rbp),%ecx
  102a32:	89 48 24             	mov    %ecx,0x24(%rax)
  102a35:	8a 4d 10             	mov    0x10(%rbp),%cl
  102a38:	88 48 28             	mov    %cl,0x28(%rax)
  102a3b:	48 83 c4 20          	add    $0x20,%rsp
  102a3f:	5d                   	pop    %rbp
  102a40:	c3                   	ret
  102a41:	66 66 66 66 66 66 2e 	data16 data16 data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
  102a48:	0f 1f 84 00 00 00 00
  102a4f:	00

0000000000102a50 <_GLOBAL__sub_I_fat32.cpp>:
  102a50:	55                   	push   %rbp
  102a51:	48 89 e5             	mov    %rsp,%rbp
  102a54:	e8 a7 e5 ff ff       	call   101000 <__cxx_global_var_init>
  102a59:	e8 62 e6 ff ff       	call   1010c0 <__cxx_global_var_init.1>
  102a5e:	e8 fd f0 ff ff       	call   101b60 <__cxx_global_var_init.4>
  102a63:	5d                   	pop    %rbp
  102a64:	c3                   	ret
  102a65:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
  102a6c:	00 00 00
  102a6f:	90                   	nop

0000000000102a70 <_ZN4acos7storage7RamDiskC1EPvmm>:
  102a70:	55                   	push   %rbp
  102a71:	48 89 e5             	mov    %rsp,%rbp
  102a74:	48 83 ec 30          	sub    $0x30,%rsp
  102a78:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  102a7c:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  102a80:	48 89 55 e8          	mov    %rdx,-0x18(%rbp)
  102a84:	48 89 4d e0          	mov    %rcx,-0x20(%rbp)
  102a88:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  102a8c:	48 89 7d d8          	mov    %rdi,-0x28(%rbp)
  102a90:	e8 cb bb 00 00       	call   10e660 <_ZN4acos7storage11BlockDeviceC2Ev>
  102a95:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  102a99:	48 b9 28 f4 10 00 00 	movabs $0x10f428,%rcx
  102aa0:	00 00 00
  102aa3:	48 83 c1 10          	add    $0x10,%rcx
  102aa7:	48 89 08             	mov    %rcx,(%rax)
  102aaa:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
  102aae:	48 89 48 08          	mov    %rcx,0x8(%rax)
  102ab2:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  102ab6:	48 89 48 10          	mov    %rcx,0x10(%rax)
  102aba:	48 8b 4d e0          	mov    -0x20(%rbp),%rcx
  102abe:	48 89 48 18          	mov    %rcx,0x18(%rax)
  102ac2:	48 83 c4 30          	add    $0x30,%rsp
  102ac6:	5d                   	pop    %rbp
  102ac7:	c3                   	ret
  102ac8:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  102acf:	00

0000000000102ad0 <_ZN4acos7storage7RamDisk10read_blockEmPv>:
  102ad0:	55                   	push   %rbp
  102ad1:	48 89 e5             	mov    %rsp,%rbp
  102ad4:	48 83 ec 30          	sub    $0x30,%rsp
  102ad8:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  102adc:	48 89 75 e8          	mov    %rsi,-0x18(%rbp)
  102ae0:	48 89 55 e0          	mov    %rdx,-0x20(%rbp)
  102ae4:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
  102ae8:	48 89 4d d0          	mov    %rcx,-0x30(%rbp)
  102aec:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  102af0:	48 0f af 41 18       	imul   0x18(%rcx),%rax
  102af5:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
  102af9:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  102afd:	48 03 41 18          	add    0x18(%rcx),%rax
  102b01:	48 3b 41 10          	cmp    0x10(%rcx),%rax
  102b05:	0f 86 0c 00 00 00    	jbe    102b17 <_ZN4acos7storage7RamDisk10read_blockEmPv+0x47>
  102b0b:	c7 45 fc ff ff ff ff 	movl   $0xffffffff,-0x4(%rbp)
  102b12:	e9 20 00 00 00       	jmp    102b37 <_ZN4acos7storage7RamDisk10read_blockEmPv+0x67>
  102b17:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  102b1b:	48 8b 7d e0          	mov    -0x20(%rbp),%rdi
  102b1f:	48 8b 70 08          	mov    0x8(%rax),%rsi
  102b23:	48 03 75 d8          	add    -0x28(%rbp),%rsi
  102b27:	48 8b 50 18          	mov    0x18(%rax),%rdx
  102b2b:	e8 d0 d4 ff ff       	call   100000 <memcpy>
  102b30:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%rbp)
  102b37:	8b 45 fc             	mov    -0x4(%rbp),%eax
  102b3a:	48 83 c4 30          	add    $0x30,%rsp
  102b3e:	5d                   	pop    %rbp
  102b3f:	c3                   	ret

0000000000102b40 <_ZN4acos7storage7RamDisk11write_blockEmPKv>:
  102b40:	55                   	push   %rbp
  102b41:	48 89 e5             	mov    %rsp,%rbp
  102b44:	48 83 ec 30          	sub    $0x30,%rsp
  102b48:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  102b4c:	48 89 75 e8          	mov    %rsi,-0x18(%rbp)
  102b50:	48 89 55 e0          	mov    %rdx,-0x20(%rbp)
  102b54:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
  102b58:	48 89 4d d0          	mov    %rcx,-0x30(%rbp)
  102b5c:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  102b60:	48 0f af 41 18       	imul   0x18(%rcx),%rax
  102b65:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
  102b69:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  102b6d:	48 03 41 18          	add    0x18(%rcx),%rax
  102b71:	48 3b 41 10          	cmp    0x10(%rcx),%rax
  102b75:	0f 86 0c 00 00 00    	jbe    102b87 <_ZN4acos7storage7RamDisk11write_blockEmPKv+0x47>
  102b7b:	c7 45 fc ff ff ff ff 	movl   $0xffffffff,-0x4(%rbp)
  102b82:	e9 20 00 00 00       	jmp    102ba7 <_ZN4acos7storage7RamDisk11write_blockEmPKv+0x67>
  102b87:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  102b8b:	48 8b 78 08          	mov    0x8(%rax),%rdi
  102b8f:	48 03 7d d8          	add    -0x28(%rbp),%rdi
  102b93:	48 8b 75 e0          	mov    -0x20(%rbp),%rsi
  102b97:	48 8b 50 18          	mov    0x18(%rax),%rdx
  102b9b:	e8 60 d4 ff ff       	call   100000 <memcpy>
  102ba0:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%rbp)
  102ba7:	8b 45 fc             	mov    -0x4(%rbp),%eax
  102baa:	48 83 c4 30          	add    $0x30,%rsp
  102bae:	5d                   	pop    %rbp
  102baf:	c3                   	ret

0000000000102bb0 <_ZN4acos7storage7RamDisk5flushEv>:
  102bb0:	55                   	push   %rbp
  102bb1:	48 89 e5             	mov    %rsp,%rbp
  102bb4:	50                   	push   %rax
  102bb5:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  102bb9:	48 83 c4 08          	add    $0x8,%rsp
  102bbd:	5d                   	pop    %rbp
  102bbe:	c3                   	ret
  102bbf:	90                   	nop

0000000000102bc0 <_ZN4acos7storage14StorageManager15register_deviceEmPNS0_11BlockDeviceE>:
  102bc0:	55                   	push   %rbp
  102bc1:	48 89 e5             	mov    %rsp,%rbp
  102bc4:	48 83 ec 20          	sub    $0x20,%rsp
  102bc8:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  102bcc:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  102bd0:	48 83 3c 25 e0 56 15 	cmpq   $0x10,0x1556e0
  102bd7:	00 10
  102bd9:	0f 83 50 00 00 00    	jae    102c2f <_ZN4acos7storage14StorageManager15register_deviceEmPNS0_11BlockDeviceE+0x6f>
  102bdf:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  102be3:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  102be7:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  102beb:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
  102bef:	48 8b 0c 25 e0 56 15 	mov    0x1556e0,%rcx
  102bf6:	00
  102bf7:	48 89 c8             	mov    %rcx,%rax
  102bfa:	48 83 c0 01          	add    $0x1,%rax
  102bfe:	48 89 04 25 e0 56 15 	mov    %rax,0x1556e0
  102c05:	00
  102c06:	48 b8 e0 55 15 00 00 	movabs $0x1555e0,%rax
  102c0d:	00 00 00
  102c10:	48 c1 e1 04          	shl    $0x4,%rcx
  102c14:	48 01 c8             	add    %rcx,%rax
  102c17:	48 8b 4d e0          	mov    -0x20(%rbp),%rcx
  102c1b:	48 89 08             	mov    %rcx,(%rax)
  102c1e:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  102c22:	48 89 48 08          	mov    %rcx,0x8(%rax)
  102c26:	48 8b 7d f0          	mov    -0x10(%rbp),%rdi
  102c2a:	e8 01 e0 ff ff       	call   100c30 <_ZN4acos7storage16PartitionManager9enumerateEPNS0_11BlockDeviceE>
  102c2f:	48 83 c4 20          	add    $0x20,%rsp
  102c33:	5d                   	pop    %rbp
  102c34:	c3                   	ret
  102c35:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  102c3c:	00 00 00 00

0000000000102c40 <_ZN4acos7storage14StorageManager10get_deviceEm>:
  102c40:	55                   	push   %rbp
  102c41:	48 89 e5             	mov    %rsp,%rbp
  102c44:	48 83 ec 18          	sub    $0x18,%rsp
  102c48:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  102c4c:	48 c7 45 e8 00 00 00 	movq   $0x0,-0x18(%rbp)
  102c53:	00
  102c54:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  102c58:	48 3b 04 25 e0 56 15 	cmp    0x1556e0,%rax
  102c5f:	00
  102c60:	0f 83 5a 00 00 00    	jae    102cc0 <_ZN4acos7storage14StorageManager10get_deviceEm+0x80>
  102c66:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  102c6a:	48 b8 e0 55 15 00 00 	movabs $0x1555e0,%rax
  102c71:	00 00 00
  102c74:	48 c1 e1 04          	shl    $0x4,%rcx
  102c78:	48 01 c8             	add    %rcx,%rax
  102c7b:	48 8b 00             	mov    (%rax),%rax
  102c7e:	48 3b 45 f0          	cmp    -0x10(%rbp),%rax
  102c82:	0f 85 22 00 00 00    	jne    102caa <_ZN4acos7storage14StorageManager10get_deviceEm+0x6a>
  102c88:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  102c8c:	48 b8 e0 55 15 00 00 	movabs $0x1555e0,%rax
  102c93:	00 00 00
  102c96:	48 c1 e1 04          	shl    $0x4,%rcx
  102c9a:	48 01 c8             	add    %rcx,%rax
  102c9d:	48 8b 40 08          	mov    0x8(%rax),%rax
  102ca1:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  102ca5:	e9 1e 00 00 00       	jmp    102cc8 <_ZN4acos7storage14StorageManager10get_deviceEm+0x88>
  102caa:	e9 00 00 00 00       	jmp    102caf <_ZN4acos7storage14StorageManager10get_deviceEm+0x6f>
  102caf:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  102cb3:	48 83 c0 01          	add    $0x1,%rax
  102cb7:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
  102cbb:	e9 94 ff ff ff       	jmp    102c54 <_ZN4acos7storage14StorageManager10get_deviceEm+0x14>
  102cc0:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  102cc7:	00
  102cc8:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  102ccc:	48 83 c4 18          	add    $0x18,%rsp
  102cd0:	5d                   	pop    %rbp
  102cd1:	c3                   	ret
  102cd2:	66 66 66 66 66 2e 0f 	data16 data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
  102cd9:	1f 84 00 00 00 00 00

0000000000102ce0 <_ZN4acos7storage14StorageManager4initEv>:
  102ce0:	55                   	push   %rbp
  102ce1:	48 89 e5             	mov    %rsp,%rbp
  102ce4:	5d                   	pop    %rbp
  102ce5:	c3                   	ret
  102ce6:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
  102ced:	00 00 00

0000000000102cf0 <_ZN4acos6loader23create_process_from_elfEPKcPKvm>:
  102cf0:	55                   	push   %rbp
  102cf1:	48 89 e5             	mov    %rsp,%rbp
  102cf4:	48 83 ec 60          	sub    $0x60,%rsp
  102cf8:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  102cfc:	48 89 75 e8          	mov    %rsi,-0x18(%rbp)
  102d00:	48 89 55 e0          	mov    %rdx,-0x20(%rbp)
  102d04:	e8 57 2b 00 00       	call   105860 <_ZN4acos9scheduler7Process6createEv>
  102d09:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
  102d0d:	48 83 7d d8 00       	cmpq   $0x0,-0x28(%rbp)
  102d12:	0f 85 0d 00 00 00    	jne    102d25 <_ZN4acos6loader23create_process_from_elfEPKcPKvm+0x35>
  102d18:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  102d1f:	00
  102d20:	e9 f4 00 00 00       	jmp    102e19 <_ZN4acos6loader23create_process_from_elfEPKcPKvm+0x129>
  102d25:	48 c7 45 d0 00 00 00 	movq   $0x0,-0x30(%rbp)
  102d2c:	00
  102d2d:	48 83 7d e8 00       	cmpq   $0x0,-0x18(%rbp)
  102d32:	0f 84 43 00 00 00    	je     102d7b <_ZN4acos6loader23create_process_from_elfEPKcPKvm+0x8b>
  102d38:	48 83 7d e0 00       	cmpq   $0x0,-0x20(%rbp)
  102d3d:	0f 86 38 00 00 00    	jbe    102d7b <_ZN4acos6loader23create_process_from_elfEPKcPKvm+0x8b>
  102d43:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  102d47:	48 8b 70 08          	mov    0x8(%rax),%rsi
  102d4b:	48 8b 55 e8          	mov    -0x18(%rbp),%rdx
  102d4f:	48 8b 4d e0          	mov    -0x20(%rbp),%rcx
  102d53:	48 8d 7d b8          	lea    -0x48(%rbp),%rdi
  102d57:	e8 14 01 00 00       	call   102e70 <_ZN4acos6loader9ElfLoader15load_executableEPNS_6memory12AddressSpaceEPKvm>
  102d5c:	f6 45 b8 01          	testb  $0x1,-0x48(%rbp)
  102d60:	0f 85 0d 00 00 00    	jne    102d73 <_ZN4acos6loader23create_process_from_elfEPKcPKvm+0x83>
  102d66:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  102d6d:	00
  102d6e:	e9 a6 00 00 00       	jmp    102e19 <_ZN4acos6loader23create_process_from_elfEPKcPKvm+0x129>
  102d73:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  102d77:	48 89 45 d0          	mov    %rax,-0x30(%rbp)
  102d7b:	e8 20 48 00 00       	call   1075a0 <_ZN4acos6memory9pmm_allocEv>
  102d80:	48 89 45 b0          	mov    %rax,-0x50(%rbp)
  102d84:	48 b8 00 00 00 00 00 	movabs $0x700000000000,%rax
  102d8b:	70 00 00
  102d8e:	48 89 45 a8          	mov    %rax,-0x58(%rbp)
  102d92:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  102d96:	48 8b 78 08          	mov    0x8(%rax),%rdi
  102d9a:	48 8b 75 a8          	mov    -0x58(%rbp),%rsi
  102d9e:	48 81 ee 00 10 00 00 	sub    $0x1000,%rsi
  102da5:	48 8b 55 b0          	mov    -0x50(%rbp),%rdx
  102da9:	b9 07 00 00 00       	mov    $0x7,%ecx
  102dae:	e8 8d 53 00 00       	call   108140 <_ZN4acos6memory12AddressSpace3mapEmmm>
  102db3:	48 bf 30 2e 10 00 00 	movabs $0x102e30,%rdi
  102dba:	00 00 00
  102dbd:	31 c0                	xor    %eax,%eax
  102dbf:	89 c6                	mov    %eax,%esi
  102dc1:	e8 3a 3c 00 00       	call   106a00 <_ZN4acos9scheduler13create_threadEPFPvS1_ES1_>
  102dc6:	48 89 45 a0          	mov    %rax,-0x60(%rbp)
  102dca:	48 83 7d a0 00       	cmpq   $0x0,-0x60(%rbp)
  102dcf:	0f 85 0d 00 00 00    	jne    102de2 <_ZN4acos6loader23create_process_from_elfEPKcPKvm+0xf2>
  102dd5:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  102ddc:	00
  102ddd:	e9 37 00 00 00       	jmp    102e19 <_ZN4acos6loader23create_process_from_elfEPKcPKvm+0x129>
  102de2:	48 8b 4d d8          	mov    -0x28(%rbp),%rcx
  102de6:	48 8b 45 a0          	mov    -0x60(%rbp),%rax
  102dea:	48 89 48 20          	mov    %rcx,0x20(%rax)
  102dee:	48 8b 45 a0          	mov    -0x60(%rbp),%rax
  102df2:	c6 40 28 01          	movb   $0x1,0x28(%rax)
  102df6:	48 8b 4d d0          	mov    -0x30(%rbp),%rcx
  102dfa:	48 8b 45 a0          	mov    -0x60(%rbp),%rax
  102dfe:	48 89 48 08          	mov    %rcx,0x8(%rax)
  102e02:	48 8b 4d a0          	mov    -0x60(%rbp),%rcx
  102e06:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  102e0a:	48 89 88 10 3b 00 00 	mov    %rcx,0x3b10(%rax)
  102e11:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  102e15:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  102e19:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  102e1d:	48 83 c4 60          	add    $0x60,%rsp
  102e21:	5d                   	pop    %rbp
  102e22:	c3                   	ret
  102e23:	66 66 66 66 2e 0f 1f 	data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
  102e2a:	84 00 00 00 00 00

0000000000102e30 <_ZN4acos6loaderL18kernel_thread_stubEPv>:
  102e30:	55                   	push   %rbp
  102e31:	48 89 e5             	mov    %rsp,%rbp
  102e34:	48 83 ec 10          	sub    $0x10,%rsp
  102e38:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  102e3c:	e8 bf 3a 00 00       	call   106900 <_ZN4acos9scheduler14current_threadEv>
  102e41:	48 89 45 f0          	mov    %rax,-0x10(%rbp)
  102e45:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  102e49:	48 8b 40 20          	mov    0x20(%rax),%rax
  102e4d:	48 8b 78 08          	mov    0x8(%rax),%rdi
  102e51:	e8 1a bc 00 00       	call   10ea70 <_ZNK4acos6memory12AddressSpace9pml4_physEv>
  102e56:	0f 22 d8             	mov    %rax,%cr3
  102e59:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  102e5d:	48 8b 78 08          	mov    0x8(%rax),%rdi
  102e61:	48 be 00 00 00 00 00 	movabs $0x700000000000,%rsi
  102e68:	70 00 00
  102e6b:	e8 5f b7 00 00       	call   10e5cf <enter_user_mode>

0000000000102e70 <_ZN4acos6loader9ElfLoader15load_executableEPNS_6memory12AddressSpaceEPKvm>:
  102e70:	55                   	push   %rbp
  102e71:	48 89 e5             	mov    %rsp,%rbp
  102e74:	48 81 ec 00 01 00 00 	sub    $0x100,%rsp
  102e7b:	48 89 bd 28 ff ff ff 	mov    %rdi,-0xd8(%rbp)
  102e82:	48 89 bd 30 ff ff ff 	mov    %rdi,-0xd0(%rbp)
  102e89:	48 89 75 f8          	mov    %rsi,-0x8(%rbp)
  102e8d:	48 89 55 f0          	mov    %rdx,-0x10(%rbp)
  102e91:	48 89 4d e8          	mov    %rcx,-0x18(%rbp)
  102e95:	48 83 7d f8 00       	cmpq   $0x0,-0x8(%rbp)
  102e9a:	0f 84 0b 00 00 00    	je     102eab <_ZN4acos6loader9ElfLoader15load_executableEPNS_6memory12AddressSpaceEPKvm+0x3b>
  102ea0:	48 83 7d f0 00       	cmpq   $0x0,-0x10(%rbp)
  102ea5:	0f 85 22 00 00 00    	jne    102ecd <_ZN4acos6loader9ElfLoader15load_executableEPNS_6memory12AddressSpaceEPKvm+0x5d>
  102eab:	48 8b bd 28 ff ff ff 	mov    -0xd8(%rbp),%rdi
  102eb2:	31 f6                	xor    %esi,%esi
  102eb4:	ba 18 00 00 00       	mov    $0x18,%edx
  102eb9:	e8 b2 d1 ff ff       	call   100070 <memset>
  102ebe:	48 8b 85 28 ff ff ff 	mov    -0xd8(%rbp),%rax
  102ec5:	c6 00 00             	movb   $0x0,(%rax)
  102ec8:	e9 c5 04 00 00       	jmp    103392 <_ZN4acos6loader9ElfLoader15load_executableEPNS_6memory12AddressSpaceEPKvm+0x522>
  102ecd:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  102ed1:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  102ed5:	48 8b 7d e0          	mov    -0x20(%rbp),%rdi
  102ed9:	48 8b 75 e8          	mov    -0x18(%rbp),%rsi
  102edd:	e8 ce 04 00 00       	call   1033b0 <_ZN4acos6loader12_GLOBAL__N_112valid_headerEPKNS0_10Elf64_EhdrEm>
  102ee2:	a8 01                	test   $0x1,%al
  102ee4:	0f 85 22 00 00 00    	jne    102f0c <_ZN4acos6loader9ElfLoader15load_executableEPNS_6memory12AddressSpaceEPKvm+0x9c>
  102eea:	48 8b bd 28 ff ff ff 	mov    -0xd8(%rbp),%rdi
  102ef1:	31 f6                	xor    %esi,%esi
  102ef3:	ba 18 00 00 00       	mov    $0x18,%edx
  102ef8:	e8 73 d1 ff ff       	call   100070 <memset>
  102efd:	48 8b 85 28 ff ff ff 	mov    -0xd8(%rbp),%rax
  102f04:	c6 00 00             	movb   $0x0,(%rax)
  102f07:	e9 86 04 00 00       	jmp    103392 <_ZN4acos6loader9ElfLoader15load_executableEPNS_6memory12AddressSpaceEPKvm+0x522>
  102f0c:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  102f10:	0f b7 50 10          	movzwl 0x10(%rax),%edx
  102f14:	31 c0                	xor    %eax,%eax
  102f16:	b9 00 00 00 40       	mov    $0x40000000,%ecx
  102f1b:	83 fa 03             	cmp    $0x3,%edx
  102f1e:	0f 44 c1             	cmove  %ecx,%eax
  102f21:	48 98                	cltq
  102f23:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
  102f27:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  102f2b:	48 8b 4d e0          	mov    -0x20(%rbp),%rcx
  102f2f:	48 03 41 20          	add    0x20(%rcx),%rax
  102f33:	48 89 45 d0          	mov    %rax,-0x30(%rbp)
  102f37:	66 c7 45 ce 00 00    	movw   $0x0,-0x32(%rbp)
  102f3d:	0f b7 45 ce          	movzwl -0x32(%rbp),%eax
  102f41:	48 8b 4d e0          	mov    -0x20(%rbp),%rcx
  102f45:	0f b7 49 38          	movzwl 0x38(%rcx),%ecx
  102f49:	39 c8                	cmp    %ecx,%eax
  102f4b:	0f 8d 1f 04 00 00    	jge    103370 <_ZN4acos6loader9ElfLoader15load_executableEPNS_6memory12AddressSpaceEPKvm+0x500>
  102f51:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  102f55:	0f b7 4d ce          	movzwl -0x32(%rbp),%ecx
  102f59:	48 6b c9 38          	imul   $0x38,%rcx,%rcx
  102f5d:	48 01 c8             	add    %rcx,%rax
  102f60:	83 38 01             	cmpl   $0x1,(%rax)
  102f63:	0f 84 05 00 00 00    	je     102f6e <_ZN4acos6loader9ElfLoader15load_executableEPNS_6memory12AddressSpaceEPKvm+0xfe>
  102f69:	e9 f1 03 00 00       	jmp    10335f <_ZN4acos6loader9ElfLoader15load_executableEPNS_6memory12AddressSpaceEPKvm+0x4ef>
  102f6e:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  102f72:	0f b7 4d ce          	movzwl -0x32(%rbp),%ecx
  102f76:	48 6b c9 38          	imul   $0x38,%rcx,%rcx
  102f7a:	48 01 c8             	add    %rcx,%rax
  102f7d:	48 8b 40 08          	mov    0x8(%rax),%rax
  102f81:	48 8b 4d d0          	mov    -0x30(%rbp),%rcx
  102f85:	0f b7 55 ce          	movzwl -0x32(%rbp),%edx
  102f89:	48 6b d2 38          	imul   $0x38,%rdx,%rdx
  102f8d:	48 01 d1             	add    %rdx,%rcx
  102f90:	48 03 41 20          	add    0x20(%rcx),%rax
  102f94:	48 3b 45 e8          	cmp    -0x18(%rbp),%rax
  102f98:	0f 87 2c 00 00 00    	ja     102fca <_ZN4acos6loader9ElfLoader15load_executableEPNS_6memory12AddressSpaceEPKvm+0x15a>
  102f9e:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  102fa2:	0f b7 4d ce          	movzwl -0x32(%rbp),%ecx
  102fa6:	48 6b c9 38          	imul   $0x38,%rcx,%rcx
  102faa:	48 01 c8             	add    %rcx,%rax
  102fad:	48 8b 40 28          	mov    0x28(%rax),%rax
  102fb1:	48 8b 4d d0          	mov    -0x30(%rbp),%rcx
  102fb5:	0f b7 55 ce          	movzwl -0x32(%rbp),%edx
  102fb9:	48 6b d2 38          	imul   $0x38,%rdx,%rdx
  102fbd:	48 01 d1             	add    %rdx,%rcx
  102fc0:	48 3b 41 20          	cmp    0x20(%rcx),%rax
  102fc4:	0f 83 22 00 00 00    	jae    102fec <_ZN4acos6loader9ElfLoader15load_executableEPNS_6memory12AddressSpaceEPKvm+0x17c>
  102fca:	48 8b bd 28 ff ff ff 	mov    -0xd8(%rbp),%rdi
  102fd1:	31 f6                	xor    %esi,%esi
  102fd3:	ba 18 00 00 00       	mov    $0x18,%edx
  102fd8:	e8 93 d0 ff ff       	call   100070 <memset>
  102fdd:	48 8b 85 28 ff ff ff 	mov    -0xd8(%rbp),%rax
  102fe4:	c6 00 00             	movb   $0x0,(%rax)
  102fe7:	e9 a6 03 00 00       	jmp    103392 <_ZN4acos6loader9ElfLoader15load_executableEPNS_6memory12AddressSpaceEPKvm+0x522>
  102fec:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  102ff0:	0f b7 4d ce          	movzwl -0x32(%rbp),%ecx
  102ff4:	48 6b c9 38          	imul   $0x38,%rcx,%rcx
  102ff8:	48 01 c8             	add    %rcx,%rax
  102ffb:	48 8b 40 10          	mov    0x10(%rax),%rax
  102fff:	48 03 45 d8          	add    -0x28(%rbp),%rax
  103003:	48 89 45 c0          	mov    %rax,-0x40(%rbp)
  103007:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  10300b:	0f b7 4d ce          	movzwl -0x32(%rbp),%ecx
  10300f:	48 6b c9 38          	imul   $0x38,%rcx,%rcx
  103013:	48 01 c8             	add    %rcx,%rax
  103016:	48 8b 40 28          	mov    0x28(%rax),%rax
  10301a:	48 89 45 b8          	mov    %rax,-0x48(%rbp)
  10301e:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  103022:	0f b7 4d ce          	movzwl -0x32(%rbp),%ecx
  103026:	48 6b c9 38          	imul   $0x38,%rcx,%rcx
  10302a:	48 01 c8             	add    %rcx,%rax
  10302d:	48 8b 40 20          	mov    0x20(%rax),%rax
  103031:	48 89 45 b0          	mov    %rax,-0x50(%rbp)
  103035:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  103039:	0f b7 4d ce          	movzwl -0x32(%rbp),%ecx
  10303d:	48 6b c9 38          	imul   $0x38,%rcx,%rcx
  103041:	48 01 c8             	add    %rcx,%rax
  103044:	48 8b 40 08          	mov    0x8(%rax),%rax
  103048:	48 89 45 a8          	mov    %rax,-0x58(%rbp)
  10304c:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  103050:	48 25 00 f0 ff ff    	and    $0xfffffffffffff000,%rax
  103056:	48 89 45 a0          	mov    %rax,-0x60(%rbp)
  10305a:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  10305e:	48 03 45 b8          	add    -0x48(%rbp),%rax
  103062:	48 05 ff 0f 00 00    	add    $0xfff,%rax
  103068:	48 25 00 f0 ff ff    	and    $0xfffffffffffff000,%rax
  10306e:	48 89 45 98          	mov    %rax,-0x68(%rbp)
  103072:	c7 45 94 05 00 00 00 	movl   $0x5,-0x6c(%rbp)
  103079:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  10307d:	0f b7 4d ce          	movzwl -0x32(%rbp),%ecx
  103081:	48 6b c9 38          	imul   $0x38,%rcx,%rcx
  103085:	48 01 c8             	add    %rcx,%rax
  103088:	8b 40 04             	mov    0x4(%rax),%eax
  10308b:	83 e0 02             	and    $0x2,%eax
  10308e:	83 f8 00             	cmp    $0x0,%eax
  103091:	0f 84 0a 00 00 00    	je     1030a1 <_ZN4acos6loader9ElfLoader15load_executableEPNS_6memory12AddressSpaceEPKvm+0x231>
  103097:	8b 45 94             	mov    -0x6c(%rbp),%eax
  10309a:	48 83 c8 02          	or     $0x2,%rax
  10309e:	89 45 94             	mov    %eax,-0x6c(%rbp)
  1030a1:	48 8b 45 a0          	mov    -0x60(%rbp),%rax
  1030a5:	48 89 45 88          	mov    %rax,-0x78(%rbp)
  1030a9:	48 8b 45 88          	mov    -0x78(%rbp),%rax
  1030ad:	48 3b 45 98          	cmp    -0x68(%rbp),%rax
  1030b1:	0f 83 a3 02 00 00    	jae    10335a <_ZN4acos6loader9ElfLoader15load_executableEPNS_6memory12AddressSpaceEPKvm+0x4ea>
  1030b7:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  1030bb:	48 8b 75 88          	mov    -0x78(%rbp),%rsi
  1030bf:	e8 ec 54 00 00       	call   1085b0 <_ZN4acos6memory12AddressSpace9translateEm>
  1030c4:	48 89 45 80          	mov    %rax,-0x80(%rbp)
  1030c8:	48 83 7d 80 00       	cmpq   $0x0,-0x80(%rbp)
  1030cd:	0f 84 0e 00 00 00    	je     1030e1 <_ZN4acos6loader9ElfLoader15load_executableEPNS_6memory12AddressSpaceEPKvm+0x271>
  1030d3:	48 8b 45 80          	mov    -0x80(%rbp),%rax
  1030d7:	48 3b 45 88          	cmp    -0x78(%rbp),%rax
  1030db:	0f 85 86 00 00 00    	jne    103167 <_ZN4acos6loader9ElfLoader15load_executableEPNS_6memory12AddressSpaceEPKvm+0x2f7>
  1030e1:	e8 ba 44 00 00       	call   1075a0 <_ZN4acos6memory9pmm_allocEv>
  1030e6:	48 89 45 80          	mov    %rax,-0x80(%rbp)
  1030ea:	48 83 7d 80 00       	cmpq   $0x0,-0x80(%rbp)
  1030ef:	0f 85 22 00 00 00    	jne    103117 <_ZN4acos6loader9ElfLoader15load_executableEPNS_6memory12AddressSpaceEPKvm+0x2a7>
  1030f5:	48 8b bd 28 ff ff ff 	mov    -0xd8(%rbp),%rdi
  1030fc:	31 f6                	xor    %esi,%esi
  1030fe:	ba 18 00 00 00       	mov    $0x18,%edx
  103103:	e8 68 cf ff ff       	call   100070 <memset>
  103108:	48 8b 85 28 ff ff ff 	mov    -0xd8(%rbp),%rax
  10310f:	c6 00 00             	movb   $0x0,(%rax)
  103112:	e9 7b 02 00 00       	jmp    103392 <_ZN4acos6loader9ElfLoader15load_executableEPNS_6memory12AddressSpaceEPKvm+0x522>
  103117:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  10311b:	48 8b 75 88          	mov    -0x78(%rbp),%rsi
  10311f:	48 8b 55 80          	mov    -0x80(%rbp),%rdx
  103123:	8b 45 94             	mov    -0x6c(%rbp),%eax
  103126:	89 c1                	mov    %eax,%ecx
  103128:	e8 13 50 00 00       	call   108140 <_ZN4acos6memory12AddressSpace3mapEmmm>
  10312d:	a8 01                	test   $0x1,%al
  10312f:	0f 85 22 00 00 00    	jne    103157 <_ZN4acos6loader9ElfLoader15load_executableEPNS_6memory12AddressSpaceEPKvm+0x2e7>
  103135:	48 8b bd 28 ff ff ff 	mov    -0xd8(%rbp),%rdi
  10313c:	31 f6                	xor    %esi,%esi
  10313e:	ba 18 00 00 00       	mov    $0x18,%edx
  103143:	e8 28 cf ff ff       	call   100070 <memset>
  103148:	48 8b 85 28 ff ff ff 	mov    -0xd8(%rbp),%rax
  10314f:	c6 00 00             	movb   $0x0,(%rax)
  103152:	e9 3b 02 00 00       	jmp    103392 <_ZN4acos6loader9ElfLoader15load_executableEPNS_6memory12AddressSpaceEPKvm+0x522>
  103157:	48 8b 7d 80          	mov    -0x80(%rbp),%rdi
  10315b:	31 f6                	xor    %esi,%esi
  10315d:	ba 00 10 00 00       	mov    $0x1000,%edx
  103162:	e8 09 cf ff ff       	call   100070 <memset>
  103167:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  10316b:	48 3b 45 88          	cmp    -0x78(%rbp),%rax
  10316f:	0f 86 10 00 00 00    	jbe    103185 <_ZN4acos6loader9ElfLoader15load_executableEPNS_6memory12AddressSpaceEPKvm+0x315>
  103175:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  103179:	48 89 85 20 ff ff ff 	mov    %rax,-0xe0(%rbp)
  103180:	e9 0b 00 00 00       	jmp    103190 <_ZN4acos6loader9ElfLoader15load_executableEPNS_6memory12AddressSpaceEPKvm+0x320>
  103185:	48 8b 45 88          	mov    -0x78(%rbp),%rax
  103189:	48 89 85 20 ff ff ff 	mov    %rax,-0xe0(%rbp)
  103190:	48 8b 85 20 ff ff ff 	mov    -0xe0(%rbp),%rax
  103197:	48 89 85 78 ff ff ff 	mov    %rax,-0x88(%rbp)
  10319e:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  1031a2:	48 03 45 b0          	add    -0x50(%rbp),%rax
  1031a6:	48 8b 4d 88          	mov    -0x78(%rbp),%rcx
  1031aa:	48 81 c1 00 10 00 00 	add    $0x1000,%rcx
  1031b1:	48 39 c8             	cmp    %rcx,%rax
  1031b4:	0f 83 14 00 00 00    	jae    1031ce <_ZN4acos6loader9ElfLoader15load_executableEPNS_6memory12AddressSpaceEPKvm+0x35e>
  1031ba:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  1031be:	48 03 45 b0          	add    -0x50(%rbp),%rax
  1031c2:	48 89 85 18 ff ff ff 	mov    %rax,-0xe8(%rbp)
  1031c9:	e9 11 00 00 00       	jmp    1031df <_ZN4acos6loader9ElfLoader15load_executableEPNS_6memory12AddressSpaceEPKvm+0x36f>
  1031ce:	48 8b 45 88          	mov    -0x78(%rbp),%rax
  1031d2:	48 05 00 10 00 00    	add    $0x1000,%rax
  1031d8:	48 89 85 18 ff ff ff 	mov    %rax,-0xe8(%rbp)
  1031df:	48 8b 85 18 ff ff ff 	mov    -0xe8(%rbp),%rax
  1031e6:	48 89 85 70 ff ff ff 	mov    %rax,-0x90(%rbp)
  1031ed:	48 8b 85 78 ff ff ff 	mov    -0x88(%rbp),%rax
  1031f4:	48 3b 85 70 ff ff ff 	cmp    -0x90(%rbp),%rax
  1031fb:	0f 83 5f 00 00 00    	jae    103260 <_ZN4acos6loader9ElfLoader15load_executableEPNS_6memory12AddressSpaceEPKvm+0x3f0>
  103201:	48 8b 85 78 ff ff ff 	mov    -0x88(%rbp),%rax
  103208:	48 2b 45 88          	sub    -0x78(%rbp),%rax
  10320c:	48 89 85 68 ff ff ff 	mov    %rax,-0x98(%rbp)
  103213:	48 8b 85 78 ff ff ff 	mov    -0x88(%rbp),%rax
  10321a:	48 2b 45 c0          	sub    -0x40(%rbp),%rax
  10321e:	48 89 85 60 ff ff ff 	mov    %rax,-0xa0(%rbp)
  103225:	48 8b 85 70 ff ff ff 	mov    -0x90(%rbp),%rax
  10322c:	48 2b 85 78 ff ff ff 	sub    -0x88(%rbp),%rax
  103233:	48 89 85 58 ff ff ff 	mov    %rax,-0xa8(%rbp)
  10323a:	48 8b 7d 80          	mov    -0x80(%rbp),%rdi
  10323e:	48 03 bd 68 ff ff ff 	add    -0x98(%rbp),%rdi
  103245:	48 8b 75 f0          	mov    -0x10(%rbp),%rsi
  103249:	48 03 75 a8          	add    -0x58(%rbp),%rsi
  10324d:	48 03 b5 60 ff ff ff 	add    -0xa0(%rbp),%rsi
  103254:	48 8b 95 58 ff ff ff 	mov    -0xa8(%rbp),%rdx
  10325b:	e8 a0 cd ff ff       	call   100000 <memcpy>
  103260:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  103264:	48 03 45 b0          	add    -0x50(%rbp),%rax
  103268:	48 3b 45 88          	cmp    -0x78(%rbp),%rax
  10326c:	0f 86 14 00 00 00    	jbe    103286 <_ZN4acos6loader9ElfLoader15load_executableEPNS_6memory12AddressSpaceEPKvm+0x416>
  103272:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  103276:	48 03 45 b0          	add    -0x50(%rbp),%rax
  10327a:	48 89 85 10 ff ff ff 	mov    %rax,-0xf0(%rbp)
  103281:	e9 0b 00 00 00       	jmp    103291 <_ZN4acos6loader9ElfLoader15load_executableEPNS_6memory12AddressSpaceEPKvm+0x421>
  103286:	48 8b 45 88          	mov    -0x78(%rbp),%rax
  10328a:	48 89 85 10 ff ff ff 	mov    %rax,-0xf0(%rbp)
  103291:	48 8b 85 10 ff ff ff 	mov    -0xf0(%rbp),%rax
  103298:	48 89 85 50 ff ff ff 	mov    %rax,-0xb0(%rbp)
  10329f:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  1032a3:	48 03 45 b8          	add    -0x48(%rbp),%rax
  1032a7:	48 8b 4d 88          	mov    -0x78(%rbp),%rcx
  1032ab:	48 81 c1 00 10 00 00 	add    $0x1000,%rcx
  1032b2:	48 39 c8             	cmp    %rcx,%rax
  1032b5:	0f 83 14 00 00 00    	jae    1032cf <_ZN4acos6loader9ElfLoader15load_executableEPNS_6memory12AddressSpaceEPKvm+0x45f>
  1032bb:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  1032bf:	48 03 45 b8          	add    -0x48(%rbp),%rax
  1032c3:	48 89 85 08 ff ff ff 	mov    %rax,-0xf8(%rbp)
  1032ca:	e9 11 00 00 00       	jmp    1032e0 <_ZN4acos6loader9ElfLoader15load_executableEPNS_6memory12AddressSpaceEPKvm+0x470>
  1032cf:	48 8b 45 88          	mov    -0x78(%rbp),%rax
  1032d3:	48 05 00 10 00 00    	add    $0x1000,%rax
  1032d9:	48 89 85 08 ff ff ff 	mov    %rax,-0xf8(%rbp)
  1032e0:	48 8b 85 08 ff ff ff 	mov    -0xf8(%rbp),%rax
  1032e7:	48 89 85 48 ff ff ff 	mov    %rax,-0xb8(%rbp)
  1032ee:	48 8b 85 50 ff ff ff 	mov    -0xb0(%rbp),%rax
  1032f5:	48 3b 85 48 ff ff ff 	cmp    -0xb8(%rbp),%rax
  1032fc:	0f 83 40 00 00 00    	jae    103342 <_ZN4acos6loader9ElfLoader15load_executableEPNS_6memory12AddressSpaceEPKvm+0x4d2>
  103302:	48 8b 85 50 ff ff ff 	mov    -0xb0(%rbp),%rax
  103309:	48 2b 45 88          	sub    -0x78(%rbp),%rax
  10330d:	48 89 85 40 ff ff ff 	mov    %rax,-0xc0(%rbp)
  103314:	48 8b 85 48 ff ff ff 	mov    -0xb8(%rbp),%rax
  10331b:	48 2b 85 50 ff ff ff 	sub    -0xb0(%rbp),%rax
  103322:	48 89 85 38 ff ff ff 	mov    %rax,-0xc8(%rbp)
  103329:	48 8b 7d 80          	mov    -0x80(%rbp),%rdi
  10332d:	48 03 bd 40 ff ff ff 	add    -0xc0(%rbp),%rdi
  103334:	48 8b 95 38 ff ff ff 	mov    -0xc8(%rbp),%rdx
  10333b:	31 f6                	xor    %esi,%esi
  10333d:	e8 2e cd ff ff       	call   100070 <memset>
  103342:	e9 00 00 00 00       	jmp    103347 <_ZN4acos6loader9ElfLoader15load_executableEPNS_6memory12AddressSpaceEPKvm+0x4d7>
  103347:	48 8b 45 88          	mov    -0x78(%rbp),%rax
  10334b:	48 05 00 10 00 00    	add    $0x1000,%rax
  103351:	48 89 45 88          	mov    %rax,-0x78(%rbp)
  103355:	e9 4f fd ff ff       	jmp    1030a9 <_ZN4acos6loader9ElfLoader15load_executableEPNS_6memory12AddressSpaceEPKvm+0x239>
  10335a:	e9 00 00 00 00       	jmp    10335f <_ZN4acos6loader9ElfLoader15load_executableEPNS_6memory12AddressSpaceEPKvm+0x4ef>
  10335f:	66 8b 45 ce          	mov    -0x32(%rbp),%ax
  103363:	66 83 c0 01          	add    $0x1,%ax
  103367:	66 89 45 ce          	mov    %ax,-0x32(%rbp)
  10336b:	e9 cd fb ff ff       	jmp    102f3d <_ZN4acos6loader9ElfLoader15load_executableEPNS_6memory12AddressSpaceEPKvm+0xcd>
  103370:	48 8b 85 28 ff ff ff 	mov    -0xd8(%rbp),%rax
  103377:	c6 00 01             	movb   $0x1,(%rax)
  10337a:	48 8b 4d e0          	mov    -0x20(%rbp),%rcx
  10337e:	48 8b 49 18          	mov    0x18(%rcx),%rcx
  103382:	48 03 4d d8          	add    -0x28(%rbp),%rcx
  103386:	48 89 48 08          	mov    %rcx,0x8(%rax)
  10338a:	48 8b 4d d8          	mov    -0x28(%rbp),%rcx
  10338e:	48 89 48 10          	mov    %rcx,0x10(%rax)
  103392:	48 8b 85 30 ff ff ff 	mov    -0xd0(%rbp),%rax
  103399:	48 81 c4 00 01 00 00 	add    $0x100,%rsp
  1033a0:	5d                   	pop    %rbp
  1033a1:	c3                   	ret
  1033a2:	66 66 66 66 66 2e 0f 	data16 data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
  1033a9:	1f 84 00 00 00 00 00

00000000001033b0 <_ZN4acos6loader12_GLOBAL__N_112valid_headerEPKNS0_10Elf64_EhdrEm>:
  1033b0:	55                   	push   %rbp
  1033b1:	48 89 e5             	mov    %rsp,%rbp
  1033b4:	48 83 ec 18          	sub    $0x18,%rsp
  1033b8:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  1033bc:	48 89 75 e8          	mov    %rsi,-0x18(%rbp)
  1033c0:	48 83 7d f0 00       	cmpq   $0x0,-0x10(%rbp)
  1033c5:	0f 84 0b 00 00 00    	je     1033d6 <_ZN4acos6loader12_GLOBAL__N_112valid_headerEPKNS0_10Elf64_EhdrEm+0x26>
  1033cb:	48 83 7d e8 40       	cmpq   $0x40,-0x18(%rbp)
  1033d0:	0f 83 09 00 00 00    	jae    1033df <_ZN4acos6loader12_GLOBAL__N_112valid_headerEPKNS0_10Elf64_EhdrEm+0x2f>
  1033d6:	c6 45 ff 00          	movb   $0x0,-0x1(%rbp)
  1033da:	e9 f1 00 00 00       	jmp    1034d0 <_ZN4acos6loader12_GLOBAL__N_112valid_headerEPKNS0_10Elf64_EhdrEm+0x120>
  1033df:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  1033e3:	0f b6 00             	movzbl (%rax),%eax
  1033e6:	83 f8 7f             	cmp    $0x7f,%eax
  1033e9:	0f 85 33 00 00 00    	jne    103422 <_ZN4acos6loader12_GLOBAL__N_112valid_headerEPKNS0_10Elf64_EhdrEm+0x72>
  1033ef:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  1033f3:	0f b6 40 01          	movzbl 0x1(%rax),%eax
  1033f7:	83 f8 45             	cmp    $0x45,%eax
  1033fa:	0f 85 22 00 00 00    	jne    103422 <_ZN4acos6loader12_GLOBAL__N_112valid_headerEPKNS0_10Elf64_EhdrEm+0x72>
  103400:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  103404:	0f b6 40 02          	movzbl 0x2(%rax),%eax
  103408:	83 f8 4c             	cmp    $0x4c,%eax
  10340b:	0f 85 11 00 00 00    	jne    103422 <_ZN4acos6loader12_GLOBAL__N_112valid_headerEPKNS0_10Elf64_EhdrEm+0x72>
  103411:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  103415:	0f b6 40 03          	movzbl 0x3(%rax),%eax
  103419:	83 f8 46             	cmp    $0x46,%eax
  10341c:	0f 84 09 00 00 00    	je     10342b <_ZN4acos6loader12_GLOBAL__N_112valid_headerEPKNS0_10Elf64_EhdrEm+0x7b>
  103422:	c6 45 ff 00          	movb   $0x0,-0x1(%rbp)
  103426:	e9 a5 00 00 00       	jmp    1034d0 <_ZN4acos6loader12_GLOBAL__N_112valid_headerEPKNS0_10Elf64_EhdrEm+0x120>
  10342b:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10342f:	0f b6 40 04          	movzbl 0x4(%rax),%eax
  103433:	83 f8 02             	cmp    $0x2,%eax
  103436:	0f 85 11 00 00 00    	jne    10344d <_ZN4acos6loader12_GLOBAL__N_112valid_headerEPKNS0_10Elf64_EhdrEm+0x9d>
  10343c:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  103440:	0f b6 40 05          	movzbl 0x5(%rax),%eax
  103444:	83 f8 01             	cmp    $0x1,%eax
  103447:	0f 84 09 00 00 00    	je     103456 <_ZN4acos6loader12_GLOBAL__N_112valid_headerEPKNS0_10Elf64_EhdrEm+0xa6>
  10344d:	c6 45 ff 00          	movb   $0x0,-0x1(%rbp)
  103451:	e9 7a 00 00 00       	jmp    1034d0 <_ZN4acos6loader12_GLOBAL__N_112valid_headerEPKNS0_10Elf64_EhdrEm+0x120>
  103456:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10345a:	0f b7 40 12          	movzwl 0x12(%rax),%eax
  10345e:	83 f8 3e             	cmp    $0x3e,%eax
  103461:	0f 85 22 00 00 00    	jne    103489 <_ZN4acos6loader12_GLOBAL__N_112valid_headerEPKNS0_10Elf64_EhdrEm+0xd9>
  103467:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10346b:	0f b7 40 10          	movzwl 0x10(%rax),%eax
  10346f:	83 f8 02             	cmp    $0x2,%eax
  103472:	0f 84 1a 00 00 00    	je     103492 <_ZN4acos6loader12_GLOBAL__N_112valid_headerEPKNS0_10Elf64_EhdrEm+0xe2>
  103478:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10347c:	0f b7 40 10          	movzwl 0x10(%rax),%eax
  103480:	83 f8 03             	cmp    $0x3,%eax
  103483:	0f 84 09 00 00 00    	je     103492 <_ZN4acos6loader12_GLOBAL__N_112valid_headerEPKNS0_10Elf64_EhdrEm+0xe2>
  103489:	c6 45 ff 00          	movb   $0x0,-0x1(%rbp)
  10348d:	e9 3e 00 00 00       	jmp    1034d0 <_ZN4acos6loader12_GLOBAL__N_112valid_headerEPKNS0_10Elf64_EhdrEm+0x120>
  103492:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  103496:	0f b7 40 36          	movzwl 0x36(%rax),%eax
  10349a:	48 83 f8 38          	cmp    $0x38,%rax
  10349e:	0f 84 09 00 00 00    	je     1034ad <_ZN4acos6loader12_GLOBAL__N_112valid_headerEPKNS0_10Elf64_EhdrEm+0xfd>
  1034a4:	c6 45 ff 00          	movb   $0x0,-0x1(%rbp)
  1034a8:	e9 23 00 00 00       	jmp    1034d0 <_ZN4acos6loader12_GLOBAL__N_112valid_headerEPKNS0_10Elf64_EhdrEm+0x120>
  1034ad:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  1034b1:	48 8b 40 20          	mov    0x20(%rax),%rax
  1034b5:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
  1034b9:	0f b7 49 38          	movzwl 0x38(%rcx),%ecx
  1034bd:	48 6b c9 38          	imul   $0x38,%rcx,%rcx
  1034c1:	48 01 c8             	add    %rcx,%rax
  1034c4:	48 3b 45 e8          	cmp    -0x18(%rbp),%rax
  1034c8:	0f 96 c0             	setbe  %al
  1034cb:	24 01                	and    $0x1,%al
  1034cd:	88 45 ff             	mov    %al,-0x1(%rbp)
  1034d0:	8a 45 ff             	mov    -0x1(%rbp),%al
  1034d3:	24 01                	and    $0x1,%al
  1034d5:	0f b6 c0             	movzbl %al,%eax
  1034d8:	48 83 c4 18          	add    $0x18,%rsp
  1034dc:	5d                   	pop    %rbp
  1034dd:	c3                   	ret
  1034de:	66 90                	xchg   %ax,%ax

00000000001034e0 <_ZN4acos6loader9ElfLoader4loadEPNS_6memory12AddressSpaceEPKvm>:
  1034e0:	55                   	push   %rbp
  1034e1:	48 89 e5             	mov    %rsp,%rbp
  1034e4:	48 83 ec 30          	sub    $0x30,%rsp
  1034e8:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  1034ec:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  1034f0:	48 89 55 e8          	mov    %rdx,-0x18(%rbp)
  1034f4:	48 8b 75 f8          	mov    -0x8(%rbp),%rsi
  1034f8:	48 8b 55 f0          	mov    -0x10(%rbp),%rdx
  1034fc:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  103500:	48 8d 7d d0          	lea    -0x30(%rbp),%rdi
  103504:	e8 67 f9 ff ff       	call   102e70 <_ZN4acos6loader9ElfLoader15load_executableEPNS_6memory12AddressSpaceEPKvm>
  103509:	8a 45 d0             	mov    -0x30(%rbp),%al
  10350c:	24 01                	and    $0x1,%al
  10350e:	0f b6 c0             	movzbl %al,%eax
  103511:	48 83 c4 30          	add    $0x30,%rsp
  103515:	5d                   	pop    %rbp
  103516:	c3                   	ret
  103517:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
  10351e:	00 00

0000000000103520 <_ZN4acos6loader12validate_elfEPKNS0_10Elf64_EhdrE>:
  103520:	55                   	push   %rbp
  103521:	48 89 e5             	mov    %rsp,%rbp
  103524:	48 83 ec 10          	sub    $0x10,%rsp
  103528:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  10352c:	48 83 7d f0 00       	cmpq   $0x0,-0x10(%rbp)
  103531:	0f 85 09 00 00 00    	jne    103540 <_ZN4acos6loader12validate_elfEPKNS0_10Elf64_EhdrE+0x20>
  103537:	c6 45 ff 00          	movb   $0x0,-0x1(%rbp)
  10353b:	e9 95 00 00 00       	jmp    1035d5 <_ZN4acos6loader12validate_elfEPKNS0_10Elf64_EhdrE+0xb5>
  103540:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  103544:	0f b6 00             	movzbl (%rax),%eax
  103547:	83 f8 7f             	cmp    $0x7f,%eax
  10354a:	0f 85 33 00 00 00    	jne    103583 <_ZN4acos6loader12validate_elfEPKNS0_10Elf64_EhdrE+0x63>
  103550:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  103554:	0f b6 40 01          	movzbl 0x1(%rax),%eax
  103558:	83 f8 45             	cmp    $0x45,%eax
  10355b:	0f 85 22 00 00 00    	jne    103583 <_ZN4acos6loader12validate_elfEPKNS0_10Elf64_EhdrE+0x63>
  103561:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  103565:	0f b6 40 02          	movzbl 0x2(%rax),%eax
  103569:	83 f8 4c             	cmp    $0x4c,%eax
  10356c:	0f 85 11 00 00 00    	jne    103583 <_ZN4acos6loader12validate_elfEPKNS0_10Elf64_EhdrE+0x63>
  103572:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  103576:	0f b6 40 03          	movzbl 0x3(%rax),%eax
  10357a:	83 f8 46             	cmp    $0x46,%eax
  10357d:	0f 84 09 00 00 00    	je     10358c <_ZN4acos6loader12validate_elfEPKNS0_10Elf64_EhdrE+0x6c>
  103583:	c6 45 ff 00          	movb   $0x0,-0x1(%rbp)
  103587:	e9 49 00 00 00       	jmp    1035d5 <_ZN4acos6loader12validate_elfEPKNS0_10Elf64_EhdrE+0xb5>
  10358c:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  103590:	0f b6 40 04          	movzbl 0x4(%rax),%eax
  103594:	83 f8 02             	cmp    $0x2,%eax
  103597:	0f 85 11 00 00 00    	jne    1035ae <_ZN4acos6loader12validate_elfEPKNS0_10Elf64_EhdrE+0x8e>
  10359d:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  1035a1:	0f b6 40 05          	movzbl 0x5(%rax),%eax
  1035a5:	83 f8 01             	cmp    $0x1,%eax
  1035a8:	0f 84 09 00 00 00    	je     1035b7 <_ZN4acos6loader12validate_elfEPKNS0_10Elf64_EhdrE+0x97>
  1035ae:	c6 45 ff 00          	movb   $0x0,-0x1(%rbp)
  1035b2:	e9 1e 00 00 00       	jmp    1035d5 <_ZN4acos6loader12validate_elfEPKNS0_10Elf64_EhdrE+0xb5>
  1035b7:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  1035bb:	0f b7 40 12          	movzwl 0x12(%rax),%eax
  1035bf:	83 f8 3e             	cmp    $0x3e,%eax
  1035c2:	0f 84 09 00 00 00    	je     1035d1 <_ZN4acos6loader12validate_elfEPKNS0_10Elf64_EhdrE+0xb1>
  1035c8:	c6 45 ff 00          	movb   $0x0,-0x1(%rbp)
  1035cc:	e9 04 00 00 00       	jmp    1035d5 <_ZN4acos6loader12validate_elfEPKNS0_10Elf64_EhdrE+0xb5>
  1035d1:	c6 45 ff 01          	movb   $0x1,-0x1(%rbp)
  1035d5:	8a 45 ff             	mov    -0x1(%rbp),%al
  1035d8:	24 01                	and    $0x1,%al
  1035da:	0f b6 c0             	movzbl %al,%eax
  1035dd:	48 83 c4 10          	add    $0x10,%rsp
  1035e1:	5d                   	pop    %rbp
  1035e2:	c3                   	ret
  1035e3:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
  1035ea:	00 00 00
  1035ed:	0f 1f 00             	nopl   (%rax)

00000000001035f0 <_ZN4acos8services14ServiceManager16register_serviceENS0_9ServiceIdEm>:
  1035f0:	55                   	push   %rbp
  1035f1:	48 89 e5             	mov    %rsp,%rbp
  1035f4:	48 83 ec 40          	sub    $0x40,%rsp
  1035f8:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  1035fc:	48 89 75 e8          	mov    %rsi,-0x18(%rbp)
  103600:	48 8d 7d e0          	lea    -0x20(%rbp),%rdi
  103604:	48 be 78 58 15 00 00 	movabs $0x155878,%rsi
  10360b:	00 00 00
  10360e:	e8 7d b4 00 00       	call   10ea90 <_ZN4acos3hal10ScopedLockC2ERNS0_8SpinLockE>
  103613:	48 83 3c 25 70 58 15 	cmpq   $0x10,0x155870
  10361a:	00 10
  10361c:	0f 82 10 00 00 00    	jb     103632 <_ZN4acos8services14ServiceManager16register_serviceENS0_9ServiceIdEm+0x42>
  103622:	c6 45 ff 00          	movb   $0x0,-0x1(%rbp)
  103626:	c7 45 dc 01 00 00 00 	movl   $0x1,-0x24(%rbp)
  10362d:	e9 61 00 00 00       	jmp    103693 <_ZN4acos8services14ServiceManager16register_serviceENS0_9ServiceIdEm+0xa3>
  103632:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  103636:	48 89 45 c0          	mov    %rax,-0x40(%rbp)
  10363a:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  10363e:	48 89 45 c8          	mov    %rax,-0x38(%rbp)
  103642:	c7 45 d0 00 00 00 00 	movl   $0x0,-0x30(%rbp)
  103649:	48 8b 0c 25 70 58 15 	mov    0x155870,%rcx
  103650:	00
  103651:	48 89 c8             	mov    %rcx,%rax
  103654:	48 83 c0 01          	add    $0x1,%rax
  103658:	48 89 04 25 70 58 15 	mov    %rax,0x155870
  10365f:	00
  103660:	48 b8 f0 56 15 00 00 	movabs $0x1556f0,%rax
  103667:	00 00 00
  10366a:	48 6b c9 18          	imul   $0x18,%rcx,%rcx
  10366e:	48 01 c8             	add    %rcx,%rax
  103671:	48 8b 4d c0          	mov    -0x40(%rbp),%rcx
  103675:	48 89 08             	mov    %rcx,(%rax)
  103678:	48 8b 4d c8          	mov    -0x38(%rbp),%rcx
  10367c:	48 89 48 08          	mov    %rcx,0x8(%rax)
  103680:	48 8b 4d d0          	mov    -0x30(%rbp),%rcx
  103684:	48 89 48 10          	mov    %rcx,0x10(%rax)
  103688:	c6 45 ff 01          	movb   $0x1,-0x1(%rbp)
  10368c:	c7 45 dc 01 00 00 00 	movl   $0x1,-0x24(%rbp)
  103693:	48 8d 7d e0          	lea    -0x20(%rbp),%rdi
  103697:	e8 24 b4 00 00       	call   10eac0 <_ZN4acos3hal10ScopedLockD2Ev>
  10369c:	8a 45 ff             	mov    -0x1(%rbp),%al
  10369f:	24 01                	and    $0x1,%al
  1036a1:	0f b6 c0             	movzbl %al,%eax
  1036a4:	48 83 c4 40          	add    $0x40,%rsp
  1036a8:	5d                   	pop    %rbp
  1036a9:	c3                   	ret
  1036aa:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

00000000001036b0 <_ZN4acos8services14ServiceManager18unregister_serviceENS0_9ServiceIdE>:
  1036b0:	55                   	push   %rbp
  1036b1:	48 89 e5             	mov    %rsp,%rbp
  1036b4:	48 83 ec 30          	sub    $0x30,%rsp
  1036b8:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  1036bc:	48 8d 7d e8          	lea    -0x18(%rbp),%rdi
  1036c0:	48 be 78 58 15 00 00 	movabs $0x155878,%rsi
  1036c7:	00 00 00
  1036ca:	e8 c1 b3 00 00       	call   10ea90 <_ZN4acos3hal10ScopedLockC2ERNS0_8SpinLockE>
  1036cf:	48 c7 45 e0 00 00 00 	movq   $0x0,-0x20(%rbp)
  1036d6:	00
  1036d7:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  1036db:	48 3b 04 25 70 58 15 	cmp    0x155870,%rax
  1036e2:	00
  1036e3:	0f 83 92 00 00 00    	jae    10377b <_ZN4acos8services14ServiceManager18unregister_serviceENS0_9ServiceIdE+0xcb>
  1036e9:	48 b8 f0 56 15 00 00 	movabs $0x1556f0,%rax
  1036f0:	00 00 00
  1036f3:	48 6b 4d e0 18       	imul   $0x18,-0x20(%rbp),%rcx
  1036f8:	48 01 c8             	add    %rcx,%rax
  1036fb:	48 8b 00             	mov    (%rax),%rax
  1036fe:	48 3b 45 f0          	cmp    -0x10(%rbp),%rax
  103702:	0f 85 5d 00 00 00    	jne    103765 <_ZN4acos8services14ServiceManager18unregister_serviceENS0_9ServiceIdE+0xb5>
  103708:	48 8b 04 25 70 58 15 	mov    0x155870,%rax
  10370f:	00
  103710:	48 83 c0 ff          	add    $0xffffffffffffffff,%rax
  103714:	48 89 04 25 70 58 15 	mov    %rax,0x155870
  10371b:	00
  10371c:	48 b9 f0 56 15 00 00 	movabs $0x1556f0,%rcx
  103723:	00 00 00
  103726:	48 6b c0 18          	imul   $0x18,%rax,%rax
  10372a:	48 01 c1             	add    %rax,%rcx
  10372d:	48 b8 f0 56 15 00 00 	movabs $0x1556f0,%rax
  103734:	00 00 00
  103737:	48 6b 55 e0 18       	imul   $0x18,-0x20(%rbp),%rdx
  10373c:	48 01 d0             	add    %rdx,%rax
  10373f:	48 8b 11             	mov    (%rcx),%rdx
  103742:	48 89 10             	mov    %rdx,(%rax)
  103745:	48 8b 51 08          	mov    0x8(%rcx),%rdx
  103749:	48 89 50 08          	mov    %rdx,0x8(%rax)
  10374d:	48 8b 49 10          	mov    0x10(%rcx),%rcx
  103751:	48 89 48 10          	mov    %rcx,0x10(%rax)
  103755:	c6 45 ff 01          	movb   $0x1,-0x1(%rbp)
  103759:	c7 45 dc 01 00 00 00 	movl   $0x1,-0x24(%rbp)
  103760:	e9 21 00 00 00       	jmp    103786 <_ZN4acos8services14ServiceManager18unregister_serviceENS0_9ServiceIdE+0xd6>
  103765:	e9 00 00 00 00       	jmp    10376a <_ZN4acos8services14ServiceManager18unregister_serviceENS0_9ServiceIdE+0xba>
  10376a:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  10376e:	48 83 c0 01          	add    $0x1,%rax
  103772:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  103776:	e9 5c ff ff ff       	jmp    1036d7 <_ZN4acos8services14ServiceManager18unregister_serviceENS0_9ServiceIdE+0x27>
  10377b:	c6 45 ff 00          	movb   $0x0,-0x1(%rbp)
  10377f:	c7 45 dc 01 00 00 00 	movl   $0x1,-0x24(%rbp)
  103786:	48 8d 7d e8          	lea    -0x18(%rbp),%rdi
  10378a:	e8 31 b3 00 00       	call   10eac0 <_ZN4acos3hal10ScopedLockD2Ev>
  10378f:	8a 45 ff             	mov    -0x1(%rbp),%al
  103792:	24 01                	and    $0x1,%al
  103794:	0f b6 c0             	movzbl %al,%eax
  103797:	48 83 c4 30          	add    $0x30,%rsp
  10379b:	5d                   	pop    %rbp
  10379c:	c3                   	ret
  10379d:	0f 1f 00             	nopl   (%rax)

00000000001037a0 <_ZN4acos8services14ServiceManager14lookup_serviceENS0_9ServiceIdE>:
  1037a0:	55                   	push   %rbp
  1037a1:	48 89 e5             	mov    %rsp,%rbp
  1037a4:	48 83 ec 30          	sub    $0x30,%rsp
  1037a8:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  1037ac:	48 8d 7d e8          	lea    -0x18(%rbp),%rdi
  1037b0:	48 be 78 58 15 00 00 	movabs $0x155878,%rsi
  1037b7:	00 00 00
  1037ba:	e8 d1 b2 00 00       	call   10ea90 <_ZN4acos3hal10ScopedLockC2ERNS0_8SpinLockE>
  1037bf:	48 c7 45 e0 00 00 00 	movq   $0x0,-0x20(%rbp)
  1037c6:	00
  1037c7:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  1037cb:	48 3b 04 25 70 58 15 	cmp    0x155870,%rax
  1037d2:	00
  1037d3:	0f 83 5b 00 00 00    	jae    103834 <_ZN4acos8services14ServiceManager14lookup_serviceENS0_9ServiceIdE+0x94>
  1037d9:	48 b8 f0 56 15 00 00 	movabs $0x1556f0,%rax
  1037e0:	00 00 00
  1037e3:	48 6b 4d e0 18       	imul   $0x18,-0x20(%rbp),%rcx
  1037e8:	48 01 c8             	add    %rcx,%rax
  1037eb:	48 8b 00             	mov    (%rax),%rax
  1037ee:	48 3b 45 f0          	cmp    -0x10(%rbp),%rax
  1037f2:	0f 85 26 00 00 00    	jne    10381e <_ZN4acos8services14ServiceManager14lookup_serviceENS0_9ServiceIdE+0x7e>
  1037f8:	48 b8 f0 56 15 00 00 	movabs $0x1556f0,%rax
  1037ff:	00 00 00
  103802:	48 6b 4d e0 18       	imul   $0x18,-0x20(%rbp),%rcx
  103807:	48 01 c8             	add    %rcx,%rax
  10380a:	48 8b 40 08          	mov    0x8(%rax),%rax
  10380e:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  103812:	c7 45 dc 01 00 00 00 	movl   $0x1,-0x24(%rbp)
  103819:	e9 25 00 00 00       	jmp    103843 <_ZN4acos8services14ServiceManager14lookup_serviceENS0_9ServiceIdE+0xa3>
  10381e:	e9 00 00 00 00       	jmp    103823 <_ZN4acos8services14ServiceManager14lookup_serviceENS0_9ServiceIdE+0x83>
  103823:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  103827:	48 83 c0 01          	add    $0x1,%rax
  10382b:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  10382f:	e9 93 ff ff ff       	jmp    1037c7 <_ZN4acos8services14ServiceManager14lookup_serviceENS0_9ServiceIdE+0x27>
  103834:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  10383b:	00
  10383c:	c7 45 dc 01 00 00 00 	movl   $0x1,-0x24(%rbp)
  103843:	48 8d 7d e8          	lea    -0x18(%rbp),%rdi
  103847:	e8 74 b2 00 00       	call   10eac0 <_ZN4acos3hal10ScopedLockD2Ev>
  10384c:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  103850:	48 83 c4 30          	add    $0x30,%rsp
  103854:	5d                   	pop    %rbp
  103855:	c3                   	ret
  103856:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
  10385d:	00 00 00

0000000000103860 <_ZN4acos8services14ServiceManager13start_serviceENS0_9ServiceIdE>:
  103860:	55                   	push   %rbp
  103861:	48 89 e5             	mov    %rsp,%rbp
  103864:	48 83 ec 30          	sub    $0x30,%rsp
  103868:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  10386c:	48 8d 7d e8          	lea    -0x18(%rbp),%rdi
  103870:	48 be 78 58 15 00 00 	movabs $0x155878,%rsi
  103877:	00 00 00
  10387a:	e8 11 b2 00 00       	call   10ea90 <_ZN4acos3hal10ScopedLockC2ERNS0_8SpinLockE>
  10387f:	48 c7 45 e0 00 00 00 	movq   $0x0,-0x20(%rbp)
  103886:	00
  103887:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  10388b:	48 3b 04 25 70 58 15 	cmp    0x155870,%rax
  103892:	00
  103893:	0f 83 5e 00 00 00    	jae    1038f7 <_ZN4acos8services14ServiceManager13start_serviceENS0_9ServiceIdE+0x97>
  103899:	48 b8 f0 56 15 00 00 	movabs $0x1556f0,%rax
  1038a0:	00 00 00
  1038a3:	48 6b 4d e0 18       	imul   $0x18,-0x20(%rbp),%rcx
  1038a8:	48 01 c8             	add    %rcx,%rax
  1038ab:	48 8b 00             	mov    (%rax),%rax
  1038ae:	48 3b 45 f0          	cmp    -0x10(%rbp),%rax
  1038b2:	0f 85 29 00 00 00    	jne    1038e1 <_ZN4acos8services14ServiceManager13start_serviceENS0_9ServiceIdE+0x81>
  1038b8:	48 b8 f0 56 15 00 00 	movabs $0x1556f0,%rax
  1038bf:	00 00 00
  1038c2:	48 6b 4d e0 18       	imul   $0x18,-0x20(%rbp),%rcx
  1038c7:	48 01 c8             	add    %rcx,%rax
  1038ca:	c7 40 10 02 00 00 00 	movl   $0x2,0x10(%rax)
  1038d1:	c6 45 ff 01          	movb   $0x1,-0x1(%rbp)
  1038d5:	c7 45 dc 01 00 00 00 	movl   $0x1,-0x24(%rbp)
  1038dc:	e9 21 00 00 00       	jmp    103902 <_ZN4acos8services14ServiceManager13start_serviceENS0_9ServiceIdE+0xa2>
  1038e1:	e9 00 00 00 00       	jmp    1038e6 <_ZN4acos8services14ServiceManager13start_serviceENS0_9ServiceIdE+0x86>
  1038e6:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  1038ea:	48 83 c0 01          	add    $0x1,%rax
  1038ee:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  1038f2:	e9 90 ff ff ff       	jmp    103887 <_ZN4acos8services14ServiceManager13start_serviceENS0_9ServiceIdE+0x27>
  1038f7:	c6 45 ff 00          	movb   $0x0,-0x1(%rbp)
  1038fb:	c7 45 dc 01 00 00 00 	movl   $0x1,-0x24(%rbp)
  103902:	48 8d 7d e8          	lea    -0x18(%rbp),%rdi
  103906:	e8 b5 b1 00 00       	call   10eac0 <_ZN4acos3hal10ScopedLockD2Ev>
  10390b:	8a 45 ff             	mov    -0x1(%rbp),%al
  10390e:	24 01                	and    $0x1,%al
  103910:	0f b6 c0             	movzbl %al,%eax
  103913:	48 83 c4 30          	add    $0x30,%rsp
  103917:	5d                   	pop    %rbp
  103918:	c3                   	ret
  103919:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000103920 <_ZN4acos8services14ServiceManager12stop_serviceENS0_9ServiceIdE>:
  103920:	55                   	push   %rbp
  103921:	48 89 e5             	mov    %rsp,%rbp
  103924:	48 83 ec 30          	sub    $0x30,%rsp
  103928:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  10392c:	48 8d 7d e8          	lea    -0x18(%rbp),%rdi
  103930:	48 be 78 58 15 00 00 	movabs $0x155878,%rsi
  103937:	00 00 00
  10393a:	e8 51 b1 00 00       	call   10ea90 <_ZN4acos3hal10ScopedLockC2ERNS0_8SpinLockE>
  10393f:	48 c7 45 e0 00 00 00 	movq   $0x0,-0x20(%rbp)
  103946:	00
  103947:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  10394b:	48 3b 04 25 70 58 15 	cmp    0x155870,%rax
  103952:	00
  103953:	0f 83 5e 00 00 00    	jae    1039b7 <_ZN4acos8services14ServiceManager12stop_serviceENS0_9ServiceIdE+0x97>
  103959:	48 b8 f0 56 15 00 00 	movabs $0x1556f0,%rax
  103960:	00 00 00
  103963:	48 6b 4d e0 18       	imul   $0x18,-0x20(%rbp),%rcx
  103968:	48 01 c8             	add    %rcx,%rax
  10396b:	48 8b 00             	mov    (%rax),%rax
  10396e:	48 3b 45 f0          	cmp    -0x10(%rbp),%rax
  103972:	0f 85 29 00 00 00    	jne    1039a1 <_ZN4acos8services14ServiceManager12stop_serviceENS0_9ServiceIdE+0x81>
  103978:	48 b8 f0 56 15 00 00 	movabs $0x1556f0,%rax
  10397f:	00 00 00
  103982:	48 6b 4d e0 18       	imul   $0x18,-0x20(%rbp),%rcx
  103987:	48 01 c8             	add    %rcx,%rax
  10398a:	c7 40 10 00 00 00 00 	movl   $0x0,0x10(%rax)
  103991:	c6 45 ff 01          	movb   $0x1,-0x1(%rbp)
  103995:	c7 45 dc 01 00 00 00 	movl   $0x1,-0x24(%rbp)
  10399c:	e9 21 00 00 00       	jmp    1039c2 <_ZN4acos8services14ServiceManager12stop_serviceENS0_9ServiceIdE+0xa2>
  1039a1:	e9 00 00 00 00       	jmp    1039a6 <_ZN4acos8services14ServiceManager12stop_serviceENS0_9ServiceIdE+0x86>
  1039a6:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  1039aa:	48 83 c0 01          	add    $0x1,%rax
  1039ae:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  1039b2:	e9 90 ff ff ff       	jmp    103947 <_ZN4acos8services14ServiceManager12stop_serviceENS0_9ServiceIdE+0x27>
  1039b7:	c6 45 ff 00          	movb   $0x0,-0x1(%rbp)
  1039bb:	c7 45 dc 01 00 00 00 	movl   $0x1,-0x24(%rbp)
  1039c2:	48 8d 7d e8          	lea    -0x18(%rbp),%rdi
  1039c6:	e8 f5 b0 00 00       	call   10eac0 <_ZN4acos3hal10ScopedLockD2Ev>
  1039cb:	8a 45 ff             	mov    -0x1(%rbp),%al
  1039ce:	24 01                	and    $0x1,%al
  1039d0:	0f b6 c0             	movzbl %al,%eax
  1039d3:	48 83 c4 30          	add    $0x30,%rsp
  1039d7:	5d                   	pop    %rbp
  1039d8:	c3                   	ret
  1039d9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

00000000001039e0 <_ZN4acos8services14ServiceManager15restart_serviceENS0_9ServiceIdE>:
  1039e0:	55                   	push   %rbp
  1039e1:	48 89 e5             	mov    %rsp,%rbp
  1039e4:	48 83 ec 30          	sub    $0x30,%rsp
  1039e8:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  1039ec:	48 8d 7d e8          	lea    -0x18(%rbp),%rdi
  1039f0:	48 be 78 58 15 00 00 	movabs $0x155878,%rsi
  1039f7:	00 00 00
  1039fa:	e8 91 b0 00 00       	call   10ea90 <_ZN4acos3hal10ScopedLockC2ERNS0_8SpinLockE>
  1039ff:	48 c7 45 e0 00 00 00 	movq   $0x0,-0x20(%rbp)
  103a06:	00
  103a07:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  103a0b:	48 3b 04 25 70 58 15 	cmp    0x155870,%rax
  103a12:	00
  103a13:	0f 83 77 00 00 00    	jae    103a90 <_ZN4acos8services14ServiceManager15restart_serviceENS0_9ServiceIdE+0xb0>
  103a19:	48 b8 f0 56 15 00 00 	movabs $0x1556f0,%rax
  103a20:	00 00 00
  103a23:	48 6b 4d e0 18       	imul   $0x18,-0x20(%rbp),%rcx
  103a28:	48 01 c8             	add    %rcx,%rax
  103a2b:	48 8b 00             	mov    (%rax),%rax
  103a2e:	48 3b 45 f0          	cmp    -0x10(%rbp),%rax
  103a32:	0f 85 42 00 00 00    	jne    103a7a <_ZN4acos8services14ServiceManager15restart_serviceENS0_9ServiceIdE+0x9a>
  103a38:	48 b8 f0 56 15 00 00 	movabs $0x1556f0,%rax
  103a3f:	00 00 00
  103a42:	48 6b 4d e0 18       	imul   $0x18,-0x20(%rbp),%rcx
  103a47:	48 01 c8             	add    %rcx,%rax
  103a4a:	c7 40 10 01 00 00 00 	movl   $0x1,0x10(%rax)
  103a51:	48 b8 f0 56 15 00 00 	movabs $0x1556f0,%rax
  103a58:	00 00 00
  103a5b:	48 6b 4d e0 18       	imul   $0x18,-0x20(%rbp),%rcx
  103a60:	48 01 c8             	add    %rcx,%rax
  103a63:	c7 40 10 02 00 00 00 	movl   $0x2,0x10(%rax)
  103a6a:	c6 45 ff 01          	movb   $0x1,-0x1(%rbp)
  103a6e:	c7 45 dc 01 00 00 00 	movl   $0x1,-0x24(%rbp)
  103a75:	e9 21 00 00 00       	jmp    103a9b <_ZN4acos8services14ServiceManager15restart_serviceENS0_9ServiceIdE+0xbb>
  103a7a:	e9 00 00 00 00       	jmp    103a7f <_ZN4acos8services14ServiceManager15restart_serviceENS0_9ServiceIdE+0x9f>
  103a7f:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  103a83:	48 83 c0 01          	add    $0x1,%rax
  103a87:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  103a8b:	e9 77 ff ff ff       	jmp    103a07 <_ZN4acos8services14ServiceManager15restart_serviceENS0_9ServiceIdE+0x27>
  103a90:	c6 45 ff 00          	movb   $0x0,-0x1(%rbp)
  103a94:	c7 45 dc 01 00 00 00 	movl   $0x1,-0x24(%rbp)
  103a9b:	48 8d 7d e8          	lea    -0x18(%rbp),%rdi
  103a9f:	e8 1c b0 00 00       	call   10eac0 <_ZN4acos3hal10ScopedLockD2Ev>
  103aa4:	8a 45 ff             	mov    -0x1(%rbp),%al
  103aa7:	24 01                	and    $0x1,%al
  103aa9:	0f b6 c0             	movzbl %al,%eax
  103aac:	48 83 c4 30          	add    $0x30,%rsp
  103ab0:	5d                   	pop    %rbp
  103ab1:	c3                   	ret
  103ab2:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
  103ab9:	00 00 00
  103abc:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000103ac0 <_ZN4acos8services4initEv>:
  103ac0:	55                   	push   %rbp
  103ac1:	48 89 e5             	mov    %rsp,%rbp
  103ac4:	48 83 ec 10          	sub    $0x10,%rsp
  103ac8:	48 8d 7d f8          	lea    -0x8(%rbp),%rdi
  103acc:	48 be 80 58 15 00 00 	movabs $0x155880,%rsi
  103ad3:	00 00 00
  103ad6:	e8 b5 af 00 00       	call   10ea90 <_ZN4acos3hal10ScopedLockC2ERNS0_8SpinLockE>
  103adb:	48 c7 45 f0 00 00 00 	movq   $0x0,-0x10(%rbp)
  103ae2:	00
  103ae3:	48 83 7d f0 40       	cmpq   $0x40,-0x10(%rbp)
  103ae8:	0f 83 5a 00 00 00    	jae    103b48 <_ZN4acos8services4initEv+0x88>
  103aee:	48 b8 90 58 15 00 00 	movabs $0x155890,%rax
  103af5:	00 00 00
  103af8:	48 6b 4d f0 30       	imul   $0x30,-0x10(%rbp),%rcx
  103afd:	48 01 c8             	add    %rcx,%rax
  103b00:	c6 00 00             	movb   $0x0,(%rax)
  103b03:	48 b8 90 58 15 00 00 	movabs $0x155890,%rax
  103b0a:	00 00 00
  103b0d:	48 6b 4d f0 30       	imul   $0x30,-0x10(%rbp),%rcx
  103b12:	48 01 c8             	add    %rcx,%rax
  103b15:	48 c7 40 20 00 00 00 	movq   $0x0,0x20(%rax)
  103b1c:	00
  103b1d:	48 b8 90 58 15 00 00 	movabs $0x155890,%rax
  103b24:	00 00 00
  103b27:	48 6b 4d f0 30       	imul   $0x30,-0x10(%rbp),%rcx
  103b2c:	48 01 c8             	add    %rcx,%rax
  103b2f:	48 c7 40 28 00 00 00 	movq   $0x0,0x28(%rax)
  103b36:	00
  103b37:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  103b3b:	48 83 c0 01          	add    $0x1,%rax
  103b3f:	48 89 45 f0          	mov    %rax,-0x10(%rbp)
  103b43:	e9 9b ff ff ff       	jmp    103ae3 <_ZN4acos8services4initEv+0x23>
  103b48:	48 8d 7d f8          	lea    -0x8(%rbp),%rdi
  103b4c:	e8 6f af 00 00       	call   10eac0 <_ZN4acos3hal10ScopedLockD2Ev>
  103b51:	48 83 c4 10          	add    $0x10,%rsp
  103b55:	5d                   	pop    %rbp
  103b56:	c3                   	ret
  103b57:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
  103b5e:	00 00

0000000000103b60 <_ZN4acos8services16register_serviceEPKcPNS_3ipc7ChannelEm>:
  103b60:	55                   	push   %rbp
  103b61:	48 89 e5             	mov    %rsp,%rbp
  103b64:	48 83 ec 50          	sub    $0x50,%rsp
  103b68:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  103b6c:	48 89 75 e8          	mov    %rsi,-0x18(%rbp)
  103b70:	48 89 55 e0          	mov    %rdx,-0x20(%rbp)
  103b74:	48 8d 7d d8          	lea    -0x28(%rbp),%rdi
  103b78:	48 be 80 58 15 00 00 	movabs $0x155880,%rsi
  103b7f:	00 00 00
  103b82:	e8 09 af 00 00       	call   10ea90 <_ZN4acos3hal10ScopedLockC2ERNS0_8SpinLockE>
  103b87:	48 83 7d f0 00       	cmpq   $0x0,-0x10(%rbp)
  103b8c:	0f 84 1a 00 00 00    	je     103bac <_ZN4acos8services16register_serviceEPKcPNS_3ipc7ChannelEm+0x4c>
  103b92:	48 83 7d e8 00       	cmpq   $0x0,-0x18(%rbp)
  103b97:	0f 84 0f 00 00 00    	je     103bac <_ZN4acos8services16register_serviceEPKcPNS_3ipc7ChannelEm+0x4c>
  103b9d:	48 83 3c 25 90 64 15 	cmpq   $0x40,0x156490
  103ba4:	00 40
  103ba6:	0f 82 10 00 00 00    	jb     103bbc <_ZN4acos8services16register_serviceEPKcPNS_3ipc7ChannelEm+0x5c>
  103bac:	c6 45 ff 00          	movb   $0x0,-0x1(%rbp)
  103bb0:	c7 45 d4 01 00 00 00 	movl   $0x1,-0x2c(%rbp)
  103bb7:	e9 f0 00 00 00       	jmp    103cac <_ZN4acos8services16register_serviceEPKcPNS_3ipc7ChannelEm+0x14c>
  103bbc:	48 c7 45 c8 00 00 00 	movq   $0x0,-0x38(%rbp)
  103bc3:	00
  103bc4:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  103bc8:	48 3b 04 25 90 64 15 	cmp    0x156490,%rax
  103bcf:	00
  103bd0:	0f 83 4a 00 00 00    	jae    103c20 <_ZN4acos8services16register_serviceEPKcPNS_3ipc7ChannelEm+0xc0>
  103bd6:	48 bf 90 58 15 00 00 	movabs $0x155890,%rdi
  103bdd:	00 00 00
  103be0:	48 6b 45 c8 30       	imul   $0x30,-0x38(%rbp),%rax
  103be5:	48 01 c7             	add    %rax,%rdi
  103be8:	48 8b 75 f0          	mov    -0x10(%rbp),%rsi
  103bec:	e8 6f c6 ff ff       	call   100260 <strcmp>
  103bf1:	83 f8 00             	cmp    $0x0,%eax
  103bf4:	0f 85 10 00 00 00    	jne    103c0a <_ZN4acos8services16register_serviceEPKcPNS_3ipc7ChannelEm+0xaa>
  103bfa:	c6 45 ff 00          	movb   $0x0,-0x1(%rbp)
  103bfe:	c7 45 d4 01 00 00 00 	movl   $0x1,-0x2c(%rbp)
  103c05:	e9 a2 00 00 00       	jmp    103cac <_ZN4acos8services16register_serviceEPKcPNS_3ipc7ChannelEm+0x14c>
  103c0a:	e9 00 00 00 00       	jmp    103c0f <_ZN4acos8services16register_serviceEPKcPNS_3ipc7ChannelEm+0xaf>
  103c0f:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  103c13:	48 83 c0 01          	add    $0x1,%rax
  103c17:	48 89 45 c8          	mov    %rax,-0x38(%rbp)
  103c1b:	e9 a4 ff ff ff       	jmp    103bc4 <_ZN4acos8services16register_serviceEPKcPNS_3ipc7ChannelEm+0x64>
  103c20:	48 8b 0c 25 90 64 15 	mov    0x156490,%rcx
  103c27:	00
  103c28:	48 89 c8             	mov    %rcx,%rax
  103c2b:	48 83 c0 01          	add    $0x1,%rax
  103c2f:	48 89 04 25 90 64 15 	mov    %rax,0x156490
  103c36:	00
  103c37:	48 b8 90 58 15 00 00 	movabs $0x155890,%rax
  103c3e:	00 00 00
  103c41:	48 6b c9 30          	imul   $0x30,%rcx,%rcx
  103c45:	48 01 c8             	add    %rcx,%rax
  103c48:	48 89 45 c0          	mov    %rax,-0x40(%rbp)
  103c4c:	48 8b 7d f0          	mov    -0x10(%rbp),%rdi
  103c50:	e8 3b c7 ff ff       	call   100390 <strlen>
  103c55:	48 89 45 b8          	mov    %rax,-0x48(%rbp)
  103c59:	48 83 7d b8 20       	cmpq   $0x20,-0x48(%rbp)
  103c5e:	0f 82 08 00 00 00    	jb     103c6c <_ZN4acos8services16register_serviceEPKcPNS_3ipc7ChannelEm+0x10c>
  103c64:	48 c7 45 b8 1f 00 00 	movq   $0x1f,-0x48(%rbp)
  103c6b:	00
  103c6c:	48 8b 7d c0          	mov    -0x40(%rbp),%rdi
  103c70:	48 8b 75 f0          	mov    -0x10(%rbp),%rsi
  103c74:	48 8b 55 b8          	mov    -0x48(%rbp),%rdx
  103c78:	e8 83 c3 ff ff       	call   100000 <memcpy>
  103c7d:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  103c81:	48 8b 4d b8          	mov    -0x48(%rbp),%rcx
  103c85:	c6 04 08 00          	movb   $0x0,(%rax,%rcx,1)
  103c89:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  103c8d:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  103c91:	48 89 48 20          	mov    %rcx,0x20(%rax)
  103c95:	48 8b 4d e0          	mov    -0x20(%rbp),%rcx
  103c99:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  103c9d:	48 89 48 28          	mov    %rcx,0x28(%rax)
  103ca1:	c6 45 ff 01          	movb   $0x1,-0x1(%rbp)
  103ca5:	c7 45 d4 01 00 00 00 	movl   $0x1,-0x2c(%rbp)
  103cac:	48 8d 7d d8          	lea    -0x28(%rbp),%rdi
  103cb0:	e8 0b ae 00 00       	call   10eac0 <_ZN4acos3hal10ScopedLockD2Ev>
  103cb5:	8a 45 ff             	mov    -0x1(%rbp),%al
  103cb8:	24 01                	and    $0x1,%al
  103cba:	0f b6 c0             	movzbl %al,%eax
  103cbd:	48 83 c4 50          	add    $0x50,%rsp
  103cc1:	5d                   	pop    %rbp
  103cc2:	c3                   	ret
  103cc3:	66 66 66 66 2e 0f 1f 	data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
  103cca:	84 00 00 00 00 00

0000000000103cd0 <_ZN4acos8services14locate_serviceEPKc>:
  103cd0:	55                   	push   %rbp
  103cd1:	48 89 e5             	mov    %rsp,%rbp
  103cd4:	48 83 ec 30          	sub    $0x30,%rsp
  103cd8:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  103cdc:	48 8d 7d e8          	lea    -0x18(%rbp),%rdi
  103ce0:	48 be 80 58 15 00 00 	movabs $0x155880,%rsi
  103ce7:	00 00 00
  103cea:	e8 a1 ad 00 00       	call   10ea90 <_ZN4acos3hal10ScopedLockC2ERNS0_8SpinLockE>
  103cef:	48 83 7d f0 00       	cmpq   $0x0,-0x10(%rbp)
  103cf4:	0f 85 14 00 00 00    	jne    103d0e <_ZN4acos8services14locate_serviceEPKc+0x3e>
  103cfa:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  103d01:	00
  103d02:	c7 45 e4 01 00 00 00 	movl   $0x1,-0x1c(%rbp)
  103d09:	e9 89 00 00 00       	jmp    103d97 <_ZN4acos8services14locate_serviceEPKc+0xc7>
  103d0e:	48 c7 45 d8 00 00 00 	movq   $0x0,-0x28(%rbp)
  103d15:	00
  103d16:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  103d1a:	48 3b 04 25 90 64 15 	cmp    0x156490,%rax
  103d21:	00
  103d22:	0f 83 60 00 00 00    	jae    103d88 <_ZN4acos8services14locate_serviceEPKc+0xb8>
  103d28:	48 bf 90 58 15 00 00 	movabs $0x155890,%rdi
  103d2f:	00 00 00
  103d32:	48 6b 45 d8 30       	imul   $0x30,-0x28(%rbp),%rax
  103d37:	48 01 c7             	add    %rax,%rdi
  103d3a:	48 8b 75 f0          	mov    -0x10(%rbp),%rsi
  103d3e:	e8 1d c5 ff ff       	call   100260 <strcmp>
  103d43:	83 f8 00             	cmp    $0x0,%eax
  103d46:	0f 85 26 00 00 00    	jne    103d72 <_ZN4acos8services14locate_serviceEPKc+0xa2>
  103d4c:	48 b8 90 58 15 00 00 	movabs $0x155890,%rax
  103d53:	00 00 00
  103d56:	48 6b 4d d8 30       	imul   $0x30,-0x28(%rbp),%rcx
  103d5b:	48 01 c8             	add    %rcx,%rax
  103d5e:	48 8b 40 20          	mov    0x20(%rax),%rax
  103d62:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  103d66:	c7 45 e4 01 00 00 00 	movl   $0x1,-0x1c(%rbp)
  103d6d:	e9 25 00 00 00       	jmp    103d97 <_ZN4acos8services14locate_serviceEPKc+0xc7>
  103d72:	e9 00 00 00 00       	jmp    103d77 <_ZN4acos8services14locate_serviceEPKc+0xa7>
  103d77:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  103d7b:	48 83 c0 01          	add    $0x1,%rax
  103d7f:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
  103d83:	e9 8e ff ff ff       	jmp    103d16 <_ZN4acos8services14locate_serviceEPKc+0x46>
  103d88:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  103d8f:	00
  103d90:	c7 45 e4 01 00 00 00 	movl   $0x1,-0x1c(%rbp)
  103d97:	48 8d 7d e8          	lea    -0x18(%rbp),%rdi
  103d9b:	e8 20 ad 00 00       	call   10eac0 <_ZN4acos3hal10ScopedLockD2Ev>
  103da0:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  103da4:	48 83 c4 30          	add    $0x30,%rsp
  103da8:	5d                   	pop    %rbp
  103da9:	c3                   	ret
  103daa:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000103db0 <_ZN4acos6device13DriverManager15register_driverEmNS0_10DriverTierEPNS0_6DriverE>:
  103db0:	55                   	push   %rbp
  103db1:	48 89 e5             	mov    %rsp,%rbp
  103db4:	48 83 ec 50          	sub    $0x50,%rsp
  103db8:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  103dbc:	89 75 ec             	mov    %esi,-0x14(%rbp)
  103dbf:	48 89 55 e0          	mov    %rdx,-0x20(%rbp)
  103dc3:	48 8d 7d d8          	lea    -0x28(%rbp),%rdi
  103dc7:	48 be a8 67 15 00 00 	movabs $0x1567a8,%rsi
  103dce:	00 00 00
  103dd1:	e8 ba ac 00 00       	call   10ea90 <_ZN4acos3hal10ScopedLockC2ERNS0_8SpinLockE>
  103dd6:	48 83 3c 25 a0 67 15 	cmpq   $0x20,0x1567a0
  103ddd:	00 20
  103ddf:	0f 82 10 00 00 00    	jb     103df5 <_ZN4acos6device13DriverManager15register_driverEmNS0_10DriverTierEPNS0_6DriverE+0x45>
  103de5:	c6 45 ff 00          	movb   $0x0,-0x1(%rbp)
  103de9:	c7 45 d4 01 00 00 00 	movl   $0x1,-0x2c(%rbp)
  103df0:	e9 67 00 00 00       	jmp    103e5c <_ZN4acos6device13DriverManager15register_driverEmNS0_10DriverTierEPNS0_6DriverE+0xac>
  103df5:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  103df9:	48 89 45 b8          	mov    %rax,-0x48(%rbp)
  103dfd:	8b 45 ec             	mov    -0x14(%rbp),%eax
  103e00:	89 45 c0             	mov    %eax,-0x40(%rbp)
  103e03:	c7 45 c4 01 00 00 00 	movl   $0x1,-0x3c(%rbp)
  103e0a:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  103e0e:	48 89 45 c8          	mov    %rax,-0x38(%rbp)
  103e12:	48 8b 0c 25 a0 67 15 	mov    0x1567a0,%rcx
  103e19:	00
  103e1a:	48 89 c8             	mov    %rcx,%rax
  103e1d:	48 83 c0 01          	add    $0x1,%rax
  103e21:	48 89 04 25 a0 67 15 	mov    %rax,0x1567a0
  103e28:	00
  103e29:	48 b8 a0 64 15 00 00 	movabs $0x1564a0,%rax
  103e30:	00 00 00
  103e33:	48 6b c9 18          	imul   $0x18,%rcx,%rcx
  103e37:	48 01 c8             	add    %rcx,%rax
  103e3a:	48 8b 4d b8          	mov    -0x48(%rbp),%rcx
  103e3e:	48 89 08             	mov    %rcx,(%rax)
  103e41:	48 8b 4d c0          	mov    -0x40(%rbp),%rcx
  103e45:	48 89 48 08          	mov    %rcx,0x8(%rax)
  103e49:	48 8b 4d c8          	mov    -0x38(%rbp),%rcx
  103e4d:	48 89 48 10          	mov    %rcx,0x10(%rax)
  103e51:	c6 45 ff 01          	movb   $0x1,-0x1(%rbp)
  103e55:	c7 45 d4 01 00 00 00 	movl   $0x1,-0x2c(%rbp)
  103e5c:	48 8d 7d d8          	lea    -0x28(%rbp),%rdi
  103e60:	e8 5b ac 00 00       	call   10eac0 <_ZN4acos3hal10ScopedLockD2Ev>
  103e65:	8a 45 ff             	mov    -0x1(%rbp),%al
  103e68:	24 01                	and    $0x1,%al
  103e6a:	0f b6 c0             	movzbl %al,%eax
  103e6d:	48 83 c4 50          	add    $0x50,%rsp
  103e71:	5d                   	pop    %rbp
  103e72:	c3                   	ret
  103e73:	66 66 66 66 2e 0f 1f 	data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
  103e7a:	84 00 00 00 00 00

0000000000103e80 <_ZN4acos6device13DriverManager17unregister_driverEm>:
  103e80:	55                   	push   %rbp
  103e81:	48 89 e5             	mov    %rsp,%rbp
  103e84:	48 83 ec 30          	sub    $0x30,%rsp
  103e88:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  103e8c:	48 8d 7d e8          	lea    -0x18(%rbp),%rdi
  103e90:	48 be a8 67 15 00 00 	movabs $0x1567a8,%rsi
  103e97:	00 00 00
  103e9a:	e8 f1 ab 00 00       	call   10ea90 <_ZN4acos3hal10ScopedLockC2ERNS0_8SpinLockE>
  103e9f:	48 c7 45 e0 00 00 00 	movq   $0x0,-0x20(%rbp)
  103ea6:	00
  103ea7:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  103eab:	48 3b 04 25 a0 67 15 	cmp    0x1567a0,%rax
  103eb2:	00
  103eb3:	0f 83 92 00 00 00    	jae    103f4b <_ZN4acos6device13DriverManager17unregister_driverEm+0xcb>
  103eb9:	48 b8 a0 64 15 00 00 	movabs $0x1564a0,%rax
  103ec0:	00 00 00
  103ec3:	48 6b 4d e0 18       	imul   $0x18,-0x20(%rbp),%rcx
  103ec8:	48 01 c8             	add    %rcx,%rax
  103ecb:	48 8b 00             	mov    (%rax),%rax
  103ece:	48 3b 45 f0          	cmp    -0x10(%rbp),%rax
  103ed2:	0f 85 5d 00 00 00    	jne    103f35 <_ZN4acos6device13DriverManager17unregister_driverEm+0xb5>
  103ed8:	48 8b 04 25 a0 67 15 	mov    0x1567a0,%rax
  103edf:	00
  103ee0:	48 83 c0 ff          	add    $0xffffffffffffffff,%rax
  103ee4:	48 89 04 25 a0 67 15 	mov    %rax,0x1567a0
  103eeb:	00
  103eec:	48 b9 a0 64 15 00 00 	movabs $0x1564a0,%rcx
  103ef3:	00 00 00
  103ef6:	48 6b c0 18          	imul   $0x18,%rax,%rax
  103efa:	48 01 c1             	add    %rax,%rcx
  103efd:	48 b8 a0 64 15 00 00 	movabs $0x1564a0,%rax
  103f04:	00 00 00
  103f07:	48 6b 55 e0 18       	imul   $0x18,-0x20(%rbp),%rdx
  103f0c:	48 01 d0             	add    %rdx,%rax
  103f0f:	48 8b 11             	mov    (%rcx),%rdx
  103f12:	48 89 10             	mov    %rdx,(%rax)
  103f15:	48 8b 51 08          	mov    0x8(%rcx),%rdx
  103f19:	48 89 50 08          	mov    %rdx,0x8(%rax)
  103f1d:	48 8b 49 10          	mov    0x10(%rcx),%rcx
  103f21:	48 89 48 10          	mov    %rcx,0x10(%rax)
  103f25:	c6 45 ff 01          	movb   $0x1,-0x1(%rbp)
  103f29:	c7 45 dc 01 00 00 00 	movl   $0x1,-0x24(%rbp)
  103f30:	e9 21 00 00 00       	jmp    103f56 <_ZN4acos6device13DriverManager17unregister_driverEm+0xd6>
  103f35:	e9 00 00 00 00       	jmp    103f3a <_ZN4acos6device13DriverManager17unregister_driverEm+0xba>
  103f3a:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  103f3e:	48 83 c0 01          	add    $0x1,%rax
  103f42:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  103f46:	e9 5c ff ff ff       	jmp    103ea7 <_ZN4acos6device13DriverManager17unregister_driverEm+0x27>
  103f4b:	c6 45 ff 00          	movb   $0x0,-0x1(%rbp)
  103f4f:	c7 45 dc 01 00 00 00 	movl   $0x1,-0x24(%rbp)
  103f56:	48 8d 7d e8          	lea    -0x18(%rbp),%rdi
  103f5a:	e8 61 ab 00 00       	call   10eac0 <_ZN4acos3hal10ScopedLockD2Ev>
  103f5f:	8a 45 ff             	mov    -0x1(%rbp),%al
  103f62:	24 01                	and    $0x1,%al
  103f64:	0f b6 c0             	movzbl %al,%eax
  103f67:	48 83 c4 30          	add    $0x30,%rsp
  103f6b:	5d                   	pop    %rbp
  103f6c:	c3                   	ret
  103f6d:	0f 1f 00             	nopl   (%rax)

0000000000103f70 <_ZN4acos6device13DriverManager16set_driver_stateEmNS0_11DriverStateE>:
  103f70:	55                   	push   %rbp
  103f71:	48 89 e5             	mov    %rsp,%rbp
  103f74:	48 83 ec 30          	sub    $0x30,%rsp
  103f78:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  103f7c:	89 75 ec             	mov    %esi,-0x14(%rbp)
  103f7f:	48 8d 7d e0          	lea    -0x20(%rbp),%rdi
  103f83:	48 be a8 67 15 00 00 	movabs $0x1567a8,%rsi
  103f8a:	00 00 00
  103f8d:	e8 fe aa 00 00       	call   10ea90 <_ZN4acos3hal10ScopedLockC2ERNS0_8SpinLockE>
  103f92:	48 c7 45 d8 00 00 00 	movq   $0x0,-0x28(%rbp)
  103f99:	00
  103f9a:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  103f9e:	48 3b 04 25 a0 67 15 	cmp    0x1567a0,%rax
  103fa5:	00
  103fa6:	0f 83 5d 00 00 00    	jae    104009 <_ZN4acos6device13DriverManager16set_driver_stateEmNS0_11DriverStateE+0x99>
  103fac:	48 b8 a0 64 15 00 00 	movabs $0x1564a0,%rax
  103fb3:	00 00 00
  103fb6:	48 6b 4d d8 18       	imul   $0x18,-0x28(%rbp),%rcx
  103fbb:	48 01 c8             	add    %rcx,%rax
  103fbe:	48 8b 00             	mov    (%rax),%rax
  103fc1:	48 3b 45 f0          	cmp    -0x10(%rbp),%rax
  103fc5:	0f 85 28 00 00 00    	jne    103ff3 <_ZN4acos6device13DriverManager16set_driver_stateEmNS0_11DriverStateE+0x83>
  103fcb:	8b 4d ec             	mov    -0x14(%rbp),%ecx
  103fce:	48 b8 a0 64 15 00 00 	movabs $0x1564a0,%rax
  103fd5:	00 00 00
  103fd8:	48 6b 55 d8 18       	imul   $0x18,-0x28(%rbp),%rdx
  103fdd:	48 01 d0             	add    %rdx,%rax
  103fe0:	89 48 0c             	mov    %ecx,0xc(%rax)
  103fe3:	c6 45 ff 01          	movb   $0x1,-0x1(%rbp)
  103fe7:	c7 45 d4 01 00 00 00 	movl   $0x1,-0x2c(%rbp)
  103fee:	e9 21 00 00 00       	jmp    104014 <_ZN4acos6device13DriverManager16set_driver_stateEmNS0_11DriverStateE+0xa4>
  103ff3:	e9 00 00 00 00       	jmp    103ff8 <_ZN4acos6device13DriverManager16set_driver_stateEmNS0_11DriverStateE+0x88>
  103ff8:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  103ffc:	48 83 c0 01          	add    $0x1,%rax
  104000:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
  104004:	e9 91 ff ff ff       	jmp    103f9a <_ZN4acos6device13DriverManager16set_driver_stateEmNS0_11DriverStateE+0x2a>
  104009:	c6 45 ff 00          	movb   $0x0,-0x1(%rbp)
  10400d:	c7 45 d4 01 00 00 00 	movl   $0x1,-0x2c(%rbp)
  104014:	48 8d 7d e0          	lea    -0x20(%rbp),%rdi
  104018:	e8 a3 aa 00 00       	call   10eac0 <_ZN4acos3hal10ScopedLockD2Ev>
  10401d:	8a 45 ff             	mov    -0x1(%rbp),%al
  104020:	24 01                	and    $0x1,%al
  104022:	0f b6 c0             	movzbl %al,%eax
  104025:	48 83 c4 30          	add    $0x30,%rsp
  104029:	5d                   	pop    %rbp
  10402a:	c3                   	ret
  10402b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000104030 <_ZN4acos6device13DriverManager10get_driverEm>:
  104030:	55                   	push   %rbp
  104031:	48 89 e5             	mov    %rsp,%rbp
  104034:	48 83 ec 30          	sub    $0x30,%rsp
  104038:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  10403c:	48 8d 7d e8          	lea    -0x18(%rbp),%rdi
  104040:	48 be a8 67 15 00 00 	movabs $0x1567a8,%rsi
  104047:	00 00 00
  10404a:	e8 41 aa 00 00       	call   10ea90 <_ZN4acos3hal10ScopedLockC2ERNS0_8SpinLockE>
  10404f:	48 c7 45 e0 00 00 00 	movq   $0x0,-0x20(%rbp)
  104056:	00
  104057:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  10405b:	48 3b 04 25 a0 67 15 	cmp    0x1567a0,%rax
  104062:	00
  104063:	0f 83 5b 00 00 00    	jae    1040c4 <_ZN4acos6device13DriverManager10get_driverEm+0x94>
  104069:	48 b8 a0 64 15 00 00 	movabs $0x1564a0,%rax
  104070:	00 00 00
  104073:	48 6b 4d e0 18       	imul   $0x18,-0x20(%rbp),%rcx
  104078:	48 01 c8             	add    %rcx,%rax
  10407b:	48 8b 00             	mov    (%rax),%rax
  10407e:	48 3b 45 f0          	cmp    -0x10(%rbp),%rax
  104082:	0f 85 26 00 00 00    	jne    1040ae <_ZN4acos6device13DriverManager10get_driverEm+0x7e>
  104088:	48 b8 a0 64 15 00 00 	movabs $0x1564a0,%rax
  10408f:	00 00 00
  104092:	48 6b 4d e0 18       	imul   $0x18,-0x20(%rbp),%rcx
  104097:	48 01 c8             	add    %rcx,%rax
  10409a:	48 8b 40 10          	mov    0x10(%rax),%rax
  10409e:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  1040a2:	c7 45 dc 01 00 00 00 	movl   $0x1,-0x24(%rbp)
  1040a9:	e9 25 00 00 00       	jmp    1040d3 <_ZN4acos6device13DriverManager10get_driverEm+0xa3>
  1040ae:	e9 00 00 00 00       	jmp    1040b3 <_ZN4acos6device13DriverManager10get_driverEm+0x83>
  1040b3:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  1040b7:	48 83 c0 01          	add    $0x1,%rax
  1040bb:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  1040bf:	e9 93 ff ff ff       	jmp    104057 <_ZN4acos6device13DriverManager10get_driverEm+0x27>
  1040c4:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  1040cb:	00
  1040cc:	c7 45 dc 01 00 00 00 	movl   $0x1,-0x24(%rbp)
  1040d3:	48 8d 7d e8          	lea    -0x18(%rbp),%rdi
  1040d7:	e8 e4 a9 00 00       	call   10eac0 <_ZN4acos3hal10ScopedLockD2Ev>
  1040dc:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  1040e0:	48 83 c4 30          	add    $0x30,%rsp
  1040e4:	5d                   	pop    %rbp
  1040e5:	c3                   	ret
  1040e6:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
  1040ed:	00 00 00

00000000001040f0 <syscall_dispatch>:
  1040f0:	55                   	push   %rbp
  1040f1:	48 89 e5             	mov    %rsp,%rbp
  1040f4:	48 81 ec a0 02 00 00 	sub    $0x2a0,%rsp
  1040fb:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  1040ff:	48 89 75 e8          	mov    %rsi,-0x18(%rbp)
  104103:	48 89 55 e0          	mov    %rdx,-0x20(%rbp)
  104107:	48 89 4d d8          	mov    %rcx,-0x28(%rbp)
  10410b:	4c 89 45 d0          	mov    %r8,-0x30(%rbp)
  10410f:	4c 89 4d c8          	mov    %r9,-0x38(%rbp)
  104113:	e8 e8 27 00 00       	call   106900 <_ZN4acos9scheduler14current_threadEv>
  104118:	48 89 45 c0          	mov    %rax,-0x40(%rbp)
  10411c:	48 83 7d c0 00       	cmpq   $0x0,-0x40(%rbp)
  104121:	0f 85 18 00 00 00    	jne    10413f <syscall_dispatch+0x4f>
  104127:	48 83 7d f0 02       	cmpq   $0x2,-0x10(%rbp)
  10412c:	0f 84 0d 00 00 00    	je     10413f <syscall_dispatch+0x4f>
  104132:	48 c7 45 f8 ff ff ff 	movq   $0xffffffffffffffff,-0x8(%rbp)
  104139:	ff
  10413a:	e9 32 14 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  10413f:	48 83 7d c0 00       	cmpq   $0x0,-0x40(%rbp)
  104144:	0f 84 14 00 00 00    	je     10415e <syscall_dispatch+0x6e>
  10414a:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  10414e:	48 8b 40 20          	mov    0x20(%rax),%rax
  104152:	48 89 85 b8 fd ff ff 	mov    %rax,-0x248(%rbp)
  104159:	e9 0e 00 00 00       	jmp    10416c <syscall_dispatch+0x7c>
  10415e:	31 c0                	xor    %eax,%eax
  104160:	48 89 85 b8 fd ff ff 	mov    %rax,-0x248(%rbp)
  104167:	e9 00 00 00 00       	jmp    10416c <syscall_dispatch+0x7c>
  10416c:	48 8b 85 b8 fd ff ff 	mov    -0x248(%rbp),%rax
  104173:	48 89 45 b8          	mov    %rax,-0x48(%rbp)
  104177:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10417b:	48 89 85 b0 fd ff ff 	mov    %rax,-0x250(%rbp)
  104182:	48 83 e8 01          	sub    $0x1,%rax
  104186:	0f 84 af 02 00 00    	je     10443b <syscall_dispatch+0x34b>
  10418c:	e9 00 00 00 00       	jmp    104191 <syscall_dispatch+0xa1>
  104191:	48 8b 85 b0 fd ff ff 	mov    -0x250(%rbp),%rax
  104198:	48 83 e8 02          	sub    $0x2,%rax
  10419c:	0f 84 c1 02 00 00    	je     104463 <syscall_dispatch+0x373>
  1041a2:	e9 00 00 00 00       	jmp    1041a7 <syscall_dispatch+0xb7>
  1041a7:	48 8b 85 b0 fd ff ff 	mov    -0x250(%rbp),%rax
  1041ae:	48 83 e8 03          	sub    $0x3,%rax
  1041b2:	0f 84 bd 02 00 00    	je     104475 <syscall_dispatch+0x385>
  1041b8:	e9 00 00 00 00       	jmp    1041bd <syscall_dispatch+0xcd>
  1041bd:	48 8b 85 b0 fd ff ff 	mov    -0x250(%rbp),%rax
  1041c4:	48 83 e8 04          	sub    $0x4,%rax
  1041c8:	0f 84 e3 02 00 00    	je     1044b1 <syscall_dispatch+0x3c1>
  1041ce:	e9 00 00 00 00       	jmp    1041d3 <syscall_dispatch+0xe3>
  1041d3:	48 8b 85 b0 fd ff ff 	mov    -0x250(%rbp),%rax
  1041da:	48 83 e8 05          	sub    $0x5,%rax
  1041de:	0f 84 5e 04 00 00    	je     104642 <syscall_dispatch+0x552>
  1041e4:	e9 00 00 00 00       	jmp    1041e9 <syscall_dispatch+0xf9>
  1041e9:	48 8b 85 b0 fd ff ff 	mov    -0x250(%rbp),%rax
  1041f0:	48 83 e8 06          	sub    $0x6,%rax
  1041f4:	0f 84 c4 04 00 00    	je     1046be <syscall_dispatch+0x5ce>
  1041fa:	e9 00 00 00 00       	jmp    1041ff <syscall_dispatch+0x10f>
  1041ff:	48 8b 85 b0 fd ff ff 	mov    -0x250(%rbp),%rax
  104206:	48 83 e8 0a          	sub    $0xa,%rax
  10420a:	0f 84 1c 05 00 00    	je     10472c <syscall_dispatch+0x63c>
  104210:	e9 00 00 00 00       	jmp    104215 <syscall_dispatch+0x125>
  104215:	48 8b 85 b0 fd ff ff 	mov    -0x250(%rbp),%rax
  10421c:	48 83 e8 0c          	sub    $0xc,%rax
  104220:	0f 84 d5 05 00 00    	je     1047fb <syscall_dispatch+0x70b>
  104226:	e9 00 00 00 00       	jmp    10422b <syscall_dispatch+0x13b>
  10422b:	48 8b 85 b0 fd ff ff 	mov    -0x250(%rbp),%rax
  104232:	48 83 e8 0d          	sub    $0xd,%rax
  104236:	0f 84 47 06 00 00    	je     104883 <syscall_dispatch+0x793>
  10423c:	e9 00 00 00 00       	jmp    104241 <syscall_dispatch+0x151>
  104241:	48 8b 85 b0 fd ff ff 	mov    -0x250(%rbp),%rax
  104248:	48 83 e8 14          	sub    $0x14,%rax
  10424c:	0f 84 c1 06 00 00    	je     104913 <syscall_dispatch+0x823>
  104252:	e9 00 00 00 00       	jmp    104257 <syscall_dispatch+0x167>
  104257:	48 8b 85 b0 fd ff ff 	mov    -0x250(%rbp),%rax
  10425e:	48 83 e8 15          	sub    $0x15,%rax
  104262:	0f 84 f0 06 00 00    	je     104958 <syscall_dispatch+0x868>
  104268:	e9 00 00 00 00       	jmp    10426d <syscall_dispatch+0x17d>
  10426d:	48 8b 85 b0 fd ff ff 	mov    -0x250(%rbp),%rax
  104274:	48 83 e8 16          	sub    $0x16,%rax
  104278:	0f 84 94 08 00 00    	je     104b12 <syscall_dispatch+0xa22>
  10427e:	e9 00 00 00 00       	jmp    104283 <syscall_dispatch+0x193>
  104283:	48 8b 85 b0 fd ff ff 	mov    -0x250(%rbp),%rax
  10428a:	48 83 e8 17          	sub    $0x17,%rax
  10428e:	0f 84 f4 08 00 00    	je     104b88 <syscall_dispatch+0xa98>
  104294:	e9 00 00 00 00       	jmp    104299 <syscall_dispatch+0x1a9>
  104299:	48 8b 85 b0 fd ff ff 	mov    -0x250(%rbp),%rax
  1042a0:	48 83 e8 18          	sub    $0x18,%rax
  1042a4:	0f 84 69 06 00 00    	je     104913 <syscall_dispatch+0x823>
  1042aa:	e9 00 00 00 00       	jmp    1042af <syscall_dispatch+0x1bf>
  1042af:	48 8b 85 b0 fd ff ff 	mov    -0x250(%rbp),%rax
  1042b6:	48 83 e8 64          	sub    $0x64,%rax
  1042ba:	0f 84 ec 0a 00 00    	je     104dac <syscall_dispatch+0xcbc>
  1042c0:	e9 00 00 00 00       	jmp    1042c5 <syscall_dispatch+0x1d5>
  1042c5:	48 8b 85 b0 fd ff ff 	mov    -0x250(%rbp),%rax
  1042cc:	48 83 e8 65          	sub    $0x65,%rax
  1042d0:	0f 84 8f 0b 00 00    	je     104e65 <syscall_dispatch+0xd75>
  1042d6:	e9 00 00 00 00       	jmp    1042db <syscall_dispatch+0x1eb>
  1042db:	48 8b 85 b0 fd ff ff 	mov    -0x250(%rbp),%rax
  1042e2:	48 83 e8 67          	sub    $0x67,%rax
  1042e6:	0f 84 40 09 00 00    	je     104c2c <syscall_dispatch+0xb3c>
  1042ec:	e9 00 00 00 00       	jmp    1042f1 <syscall_dispatch+0x201>
  1042f1:	48 8b 85 b0 fd ff ff 	mov    -0x250(%rbp),%rax
  1042f8:	48 83 e8 6d          	sub    $0x6d,%rax
  1042fc:	0f 84 ea 09 00 00    	je     104cec <syscall_dispatch+0xbfc>
  104302:	e9 00 00 00 00       	jmp    104307 <syscall_dispatch+0x217>
  104307:	48 8b 85 b0 fd ff ff 	mov    -0x250(%rbp),%rax
  10430e:	48 83 e8 6e          	sub    $0x6e,%rax
  104312:	0f 84 0b 0c 00 00    	je     104f23 <syscall_dispatch+0xe33>
  104318:	e9 00 00 00 00       	jmp    10431d <syscall_dispatch+0x22d>
  10431d:	48 8b 85 b0 fd ff ff 	mov    -0x250(%rbp),%rax
  104324:	48 83 e8 6f          	sub    $0x6f,%rax
  104328:	0f 84 8d 0c 00 00    	je     104fbb <syscall_dispatch+0xecb>
  10432e:	e9 00 00 00 00       	jmp    104333 <syscall_dispatch+0x243>
  104333:	48 8b 85 b0 fd ff ff 	mov    -0x250(%rbp),%rax
  10433a:	48 2d 2c 01 00 00    	sub    $0x12c,%rax
  104340:	0f 84 0d 0d 00 00    	je     105053 <syscall_dispatch+0xf63>
  104346:	e9 00 00 00 00       	jmp    10434b <syscall_dispatch+0x25b>
  10434b:	48 8b 85 b0 fd ff ff 	mov    -0x250(%rbp),%rax
  104352:	48 2d 2d 01 00 00    	sub    $0x12d,%rax
  104358:	0f 84 41 0d 00 00    	je     10509f <syscall_dispatch+0xfaf>
  10435e:	e9 00 00 00 00       	jmp    104363 <syscall_dispatch+0x273>
  104363:	48 8b 85 b0 fd ff ff 	mov    -0x250(%rbp),%rax
  10436a:	48 2d 2e 01 00 00    	sub    $0x12e,%rax
  104370:	0f 84 63 0d 00 00    	je     1050d9 <syscall_dispatch+0xfe9>
  104376:	e9 00 00 00 00       	jmp    10437b <syscall_dispatch+0x28b>
  10437b:	48 8b 85 b0 fd ff ff 	mov    -0x250(%rbp),%rax
  104382:	48 2d 2f 01 00 00    	sub    $0x12f,%rax
  104388:	0f 84 a9 0d 00 00    	je     105137 <syscall_dispatch+0x1047>
  10438e:	e9 00 00 00 00       	jmp    104393 <syscall_dispatch+0x2a3>
  104393:	48 8b 85 b0 fd ff ff 	mov    -0x250(%rbp),%rax
  10439a:	48 2d 31 01 00 00    	sub    $0x131,%rax
  1043a0:	0f 84 ef 0d 00 00    	je     105195 <syscall_dispatch+0x10a5>
  1043a6:	e9 00 00 00 00       	jmp    1043ab <syscall_dispatch+0x2bb>
  1043ab:	48 8b 85 b0 fd ff ff 	mov    -0x250(%rbp),%rax
  1043b2:	48 2d f4 01 00 00    	sub    $0x1f4,%rax
  1043b8:	0f 84 35 0e 00 00    	je     1051f3 <syscall_dispatch+0x1103>
  1043be:	e9 00 00 00 00       	jmp    1043c3 <syscall_dispatch+0x2d3>
  1043c3:	48 8b 85 b0 fd ff ff 	mov    -0x250(%rbp),%rax
  1043ca:	48 2d f5 01 00 00    	sub    $0x1f5,%rax
  1043d0:	0f 84 95 0e 00 00    	je     10526b <syscall_dispatch+0x117b>
  1043d6:	e9 00 00 00 00       	jmp    1043db <syscall_dispatch+0x2eb>
  1043db:	48 8b 85 b0 fd ff ff 	mov    -0x250(%rbp),%rax
  1043e2:	48 2d 58 02 00 00    	sub    $0x258,%rax
  1043e8:	0f 84 2c 0f 00 00    	je     10531a <syscall_dispatch+0x122a>
  1043ee:	e9 00 00 00 00       	jmp    1043f3 <syscall_dispatch+0x303>
  1043f3:	48 8b 85 b0 fd ff ff 	mov    -0x250(%rbp),%rax
  1043fa:	48 2d 59 02 00 00    	sub    $0x259,%rax
  104400:	0f 84 96 0f 00 00    	je     10539c <syscall_dispatch+0x12ac>
  104406:	e9 00 00 00 00       	jmp    10440b <syscall_dispatch+0x31b>
  10440b:	48 8b 85 b0 fd ff ff 	mov    -0x250(%rbp),%rax
  104412:	48 2d 5a 02 00 00    	sub    $0x25a,%rax
  104418:	0f 84 b6 0f 00 00    	je     1053d4 <syscall_dispatch+0x12e4>
  10441e:	e9 00 00 00 00       	jmp    104423 <syscall_dispatch+0x333>
  104423:	48 8b 85 b0 fd ff ff 	mov    -0x250(%rbp),%rax
  10442a:	48 2d 5b 02 00 00    	sub    $0x25b,%rax
  104430:	0f 84 ce 0f 00 00    	je     105404 <syscall_dispatch+0x1314>
  104436:	e9 2e 11 00 00       	jmp    105569 <syscall_dispatch+0x1479>
  10443b:	48 83 7d c0 00       	cmpq   $0x0,-0x40(%rbp)
  104440:	0f 84 10 00 00 00    	je     104456 <syscall_dispatch+0x366>
  104446:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  10444a:	c7 40 18 05 00 00 00 	movl   $0x5,0x18(%rax)
  104451:	e8 aa 22 00 00       	call   106700 <_ZN4acos9scheduler8scheduleEv>
  104456:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  10445d:	00
  10445e:	e9 0e 11 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  104463:	e8 98 22 00 00       	call   106700 <_ZN4acos9scheduler8scheduleEv>
  104468:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  10446f:	00
  104470:	e9 fc 10 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  104475:	48 83 7d b8 00       	cmpq   $0x0,-0x48(%rbp)
  10447a:	0f 84 13 00 00 00    	je     104493 <syscall_dispatch+0x3a3>
  104480:	48 8b 45 b8          	mov    -0x48(%rbp),%rax
  104484:	48 8b 00             	mov    (%rax),%rax
  104487:	48 89 85 a8 fd ff ff 	mov    %rax,-0x258(%rbp)
  10448e:	e9 0e 00 00 00       	jmp    1044a1 <syscall_dispatch+0x3b1>
  104493:	31 c0                	xor    %eax,%eax
  104495:	48 89 85 a8 fd ff ff 	mov    %rax,-0x258(%rbp)
  10449c:	e9 00 00 00 00       	jmp    1044a1 <syscall_dispatch+0x3b1>
  1044a1:	48 8b 85 a8 fd ff ff 	mov    -0x258(%rbp),%rax
  1044a8:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  1044ac:	e9 c0 10 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  1044b1:	48 83 7d b8 00       	cmpq   $0x0,-0x48(%rbp)
  1044b6:	0f 85 0d 00 00 00    	jne    1044c9 <syscall_dispatch+0x3d9>
  1044bc:	48 c7 45 f8 ff ff ff 	movq   $0xffffffffffffffff,-0x8(%rbp)
  1044c3:	ff
  1044c4:	e9 a8 10 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  1044c9:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  1044cd:	48 89 45 b0          	mov    %rax,-0x50(%rbp)
  1044d1:	48 83 7d b0 00       	cmpq   $0x0,-0x50(%rbp)
  1044d6:	0f 85 0d 00 00 00    	jne    1044e9 <syscall_dispatch+0x3f9>
  1044dc:	48 c7 45 f8 ff ff ff 	movq   $0xffffffffffffffff,-0x8(%rbp)
  1044e3:	ff
  1044e4:	e9 88 10 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  1044e9:	48 8b 7d b0          	mov    -0x50(%rbp),%rdi
  1044ed:	31 c0                	xor    %eax,%eax
  1044ef:	89 c6                	mov    %eax,%esi
  1044f1:	e8 ea 48 00 00       	call   108de0 <_ZN4acos3vfs3VFS4openEPKcm>
  1044f6:	89 45 ac             	mov    %eax,-0x54(%rbp)
  1044f9:	83 7d ac 00          	cmpl   $0x0,-0x54(%rbp)
  1044fd:	0f 8d 0d 00 00 00    	jge    104510 <syscall_dispatch+0x420>
  104503:	48 c7 45 f8 ff ff ff 	movq   $0xffffffffffffffff,-0x8(%rbp)
  10450a:	ff
  10450b:	e9 61 10 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  104510:	48 8b 7d b8          	mov    -0x48(%rbp),%rdi
  104514:	8b 75 ac             	mov    -0x54(%rbp),%esi
  104517:	e8 c4 1a 00 00       	call   105fe0 <_ZN4acos9scheduler7Process8get_fileEi>
  10451c:	48 89 45 a0          	mov    %rax,-0x60(%rbp)
  104520:	48 83 7d a0 00       	cmpq   $0x0,-0x60(%rbp)
  104525:	0f 85 16 00 00 00    	jne    104541 <syscall_dispatch+0x451>
  10452b:	48 63 7d ac          	movslq -0x54(%rbp),%rdi
  10452f:	e8 1c 4a 00 00       	call   108f50 <_ZN4acos3vfs3VFS5closeEm>
  104534:	48 c7 45 f8 ff ff ff 	movq   $0xffffffffffffffff,-0x8(%rbp)
  10453b:	ff
  10453c:	e9 30 10 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  104541:	48 8b 7d a0          	mov    -0x60(%rbp),%rdi
  104545:	e8 96 4f 00 00       	call   1094e0 <_ZNK4acos3vfs4File4sizeEv>
  10454a:	48 89 45 98          	mov    %rax,-0x68(%rbp)
  10454e:	48 8b 7d 98          	mov    -0x68(%rbp),%rdi
  104552:	e8 f9 41 00 00       	call   108750 <_ZN4acos6memory7kmallocEm>
  104557:	48 89 45 90          	mov    %rax,-0x70(%rbp)
  10455b:	48 83 7d 90 00       	cmpq   $0x0,-0x70(%rbp)
  104560:	0f 85 16 00 00 00    	jne    10457c <syscall_dispatch+0x48c>
  104566:	48 63 7d ac          	movslq -0x54(%rbp),%rdi
  10456a:	e8 e1 49 00 00       	call   108f50 <_ZN4acos3vfs3VFS5closeEm>
  10456f:	48 c7 45 f8 fd ff ff 	movq   $0xfffffffffffffffd,-0x8(%rbp)
  104576:	ff
  104577:	e9 f5 0f 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  10457c:	48 8b 7d a0          	mov    -0x60(%rbp),%rdi
  104580:	48 8b 75 90          	mov    -0x70(%rbp),%rsi
  104584:	48 8b 55 98          	mov    -0x68(%rbp),%rdx
  104588:	e8 23 4e 00 00       	call   1093b0 <_ZN4acos3vfs4File4readEPvm>
  10458d:	48 63 7d ac          	movslq -0x54(%rbp),%rdi
  104591:	e8 ba 49 00 00       	call   108f50 <_ZN4acos3vfs3VFS5closeEm>
  104596:	48 8b 7d b0          	mov    -0x50(%rbp),%rdi
  10459a:	48 8b 75 90          	mov    -0x70(%rbp),%rsi
  10459e:	48 8b 55 98          	mov    -0x68(%rbp),%rdx
  1045a2:	e8 49 e7 ff ff       	call   102cf0 <_ZN4acos6loader23create_process_from_elfEPKcPKvm>
  1045a7:	48 89 45 88          	mov    %rax,-0x78(%rbp)
  1045ab:	48 8b 7d 90          	mov    -0x70(%rbp),%rdi
  1045af:	e8 6c 42 00 00       	call   108820 <_ZN4acos6memory5kfreeEPv>
  1045b4:	48 83 7d 88 00       	cmpq   $0x0,-0x78(%rbp)
  1045b9:	0f 85 0d 00 00 00    	jne    1045cc <syscall_dispatch+0x4dc>
  1045bf:	48 c7 45 f8 fd ff ff 	movq   $0xfffffffffffffffd,-0x8(%rbp)
  1045c6:	ff
  1045c7:	e9 a5 0f 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  1045cc:	c7 45 84 00 00 00 00 	movl   $0x0,-0x7c(%rbp)
  1045d3:	83 7d 84 03          	cmpl   $0x3,-0x7c(%rbp)
  1045d7:	0f 8d 4a 00 00 00    	jge    104627 <syscall_dispatch+0x537>
  1045dd:	48 8b 45 b8          	mov    -0x48(%rbp),%rax
  1045e1:	48 63 4d 84          	movslq -0x7c(%rbp),%rcx
  1045e5:	48 83 bc c8 10 38 00 	cmpq   $0x0,0x3810(%rax,%rcx,8)
  1045ec:	00 00
  1045ee:	0f 84 20 00 00 00    	je     104614 <syscall_dispatch+0x524>
  1045f4:	48 8b 45 b8          	mov    -0x48(%rbp),%rax
  1045f8:	48 63 4d 84          	movslq -0x7c(%rbp),%rcx
  1045fc:	48 8b 94 c8 10 38 00 	mov    0x3810(%rax,%rcx,8),%rdx
  104603:	00
  104604:	48 8b 45 88          	mov    -0x78(%rbp),%rax
  104608:	48 63 4d 84          	movslq -0x7c(%rbp),%rcx
  10460c:	48 89 94 c8 10 38 00 	mov    %rdx,0x3810(%rax,%rcx,8)
  104613:	00
  104614:	e9 00 00 00 00       	jmp    104619 <syscall_dispatch+0x529>
  104619:	8b 45 84             	mov    -0x7c(%rbp),%eax
  10461c:	83 c0 01             	add    $0x1,%eax
  10461f:	89 45 84             	mov    %eax,-0x7c(%rbp)
  104622:	e9 ac ff ff ff       	jmp    1045d3 <syscall_dispatch+0x4e3>
  104627:	48 8b 7d b8          	mov    -0x48(%rbp),%rdi
  10462b:	48 8b 75 88          	mov    -0x78(%rbp),%rsi
  10462f:	ba 70 00 00 00       	mov    $0x70,%edx
  104634:	e8 b7 18 00 00       	call   105ef0 <_ZN4acos9scheduler7Process16register_processEPS1_m>
  104639:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  10463d:	e9 2f 0f 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  104642:	48 83 7d b8 00       	cmpq   $0x0,-0x48(%rbp)
  104647:	0f 85 0d 00 00 00    	jne    10465a <syscall_dispatch+0x56a>
  10464d:	48 c7 45 f8 ff ff ff 	movq   $0xffffffffffffffff,-0x8(%rbp)
  104654:	ff
  104655:	e9 17 0f 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  10465a:	48 8b 7d b8          	mov    -0x48(%rbp),%rdi
  10465e:	48 8b 75 e8          	mov    -0x18(%rbp),%rsi
  104662:	e8 29 1b 00 00       	call   106190 <_ZN4acos9scheduler7Process11get_processEm>
  104667:	48 89 85 78 ff ff ff 	mov    %rax,-0x88(%rbp)
  10466e:	48 83 bd 78 ff ff ff 	cmpq   $0x0,-0x88(%rbp)
  104675:	00
  104676:	0f 84 15 00 00 00    	je     104691 <syscall_dispatch+0x5a1>
  10467c:	48 8b 85 78 ff ff ff 	mov    -0x88(%rbp),%rax
  104683:	48 83 b8 10 3b 00 00 	cmpq   $0x0,0x3b10(%rax)
  10468a:	00
  10468b:	0f 85 0d 00 00 00    	jne    10469e <syscall_dispatch+0x5ae>
  104691:	48 c7 45 f8 ff ff ff 	movq   $0xffffffffffffffff,-0x8(%rbp)
  104698:	ff
  104699:	e9 d3 0e 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  10469e:	48 8b 85 78 ff ff ff 	mov    -0x88(%rbp),%rax
  1046a5:	48 8b b8 10 3b 00 00 	mov    0x3b10(%rax),%rdi
  1046ac:	e8 5f 22 00 00       	call   106910 <_ZN4acos9scheduler11wake_threadEPNS0_6ThreadE>
  1046b1:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  1046b8:	00
  1046b9:	e9 b3 0e 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  1046be:	48 83 7d b8 00       	cmpq   $0x0,-0x48(%rbp)
  1046c3:	0f 84 1a 00 00 00    	je     1046e3 <syscall_dispatch+0x5f3>
  1046c9:	48 8b 7d b8          	mov    -0x48(%rbp),%rdi
  1046cd:	48 8b 75 e8          	mov    -0x18(%rbp),%rsi
  1046d1:	ba 40 00 00 00       	mov    $0x40,%edx
  1046d6:	e8 a5 0e 00 00       	call   105580 <_ZN4acos3sys12_GLOBAL__N_110has_rightsEPNS_9scheduler7ProcessEmm>
  1046db:	a8 01                	test   $0x1,%al
  1046dd:	0f 85 0d 00 00 00    	jne    1046f0 <syscall_dispatch+0x600>
  1046e3:	48 c7 45 f8 fe ff ff 	movq   $0xfffffffffffffffe,-0x8(%rbp)
  1046ea:	ff
  1046eb:	e9 81 0e 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  1046f0:	48 8b 7d b8          	mov    -0x48(%rbp),%rdi
  1046f4:	48 8b 75 e8          	mov    -0x18(%rbp),%rsi
  1046f8:	e8 93 1a 00 00       	call   106190 <_ZN4acos9scheduler7Process11get_processEm>
  1046fd:	48 89 85 70 ff ff ff 	mov    %rax,-0x90(%rbp)
  104704:	48 83 bd 70 ff ff ff 	cmpq   $0x0,-0x90(%rbp)
  10470b:	00
  10470c:	0f 85 0d 00 00 00    	jne    10471f <syscall_dispatch+0x62f>
  104712:	48 c7 45 f8 ff ff ff 	movq   $0xffffffffffffffff,-0x8(%rbp)
  104719:	ff
  10471a:	e9 52 0e 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  10471f:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  104726:	00
  104727:	e9 45 0e 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  10472c:	48 83 7d b8 00       	cmpq   $0x0,-0x48(%rbp)
  104731:	0f 85 0d 00 00 00    	jne    104744 <syscall_dispatch+0x654>
  104737:	48 c7 45 f8 ff ff ff 	movq   $0xffffffffffffffff,-0x8(%rbp)
  10473e:	ff
  10473f:	e9 2d 0e 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  104744:	48 83 7d e8 00       	cmpq   $0x0,-0x18(%rbp)
  104749:	0f 84 19 00 00 00    	je     104768 <syscall_dispatch+0x678>
  10474f:	48 8b 7d b8          	mov    -0x48(%rbp),%rdi
  104753:	48 8b 75 e8          	mov    -0x18(%rbp),%rsi
  104757:	e8 34 1a 00 00       	call   106190 <_ZN4acos9scheduler7Process11get_processEm>
  10475c:	48 89 85 a0 fd ff ff 	mov    %rax,-0x260(%rbp)
  104763:	e9 0b 00 00 00       	jmp    104773 <syscall_dispatch+0x683>
  104768:	48 8b 45 b8          	mov    -0x48(%rbp),%rax
  10476c:	48 89 85 a0 fd ff ff 	mov    %rax,-0x260(%rbp)
  104773:	48 8b 85 a0 fd ff ff 	mov    -0x260(%rbp),%rax
  10477a:	48 89 85 68 ff ff ff 	mov    %rax,-0x98(%rbp)
  104781:	48 83 bd 68 ff ff ff 	cmpq   $0x0,-0x98(%rbp)
  104788:	00
  104789:	0f 85 0d 00 00 00    	jne    10479c <syscall_dispatch+0x6ac>
  10478f:	48 c7 45 f8 ff ff ff 	movq   $0xffffffffffffffff,-0x8(%rbp)
  104796:	ff
  104797:	e9 d5 0d 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  10479c:	48 8b 7d e0          	mov    -0x20(%rbp),%rdi
  1047a0:	48 8b 75 d8          	mov    -0x28(%rbp),%rsi
  1047a4:	e8 57 22 00 00       	call   106a00 <_ZN4acos9scheduler13create_threadEPFPvS1_ES1_>
  1047a9:	48 89 85 60 ff ff ff 	mov    %rax,-0xa0(%rbp)
  1047b0:	48 83 bd 60 ff ff ff 	cmpq   $0x0,-0xa0(%rbp)
  1047b7:	00
  1047b8:	0f 85 0d 00 00 00    	jne    1047cb <syscall_dispatch+0x6db>
  1047be:	48 c7 45 f8 fd ff ff 	movq   $0xfffffffffffffffd,-0x8(%rbp)
  1047c5:	ff
  1047c6:	e9 a6 0d 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  1047cb:	48 8b 8d 68 ff ff ff 	mov    -0x98(%rbp),%rcx
  1047d2:	48 8b 85 60 ff ff ff 	mov    -0xa0(%rbp),%rax
  1047d9:	48 89 48 20          	mov    %rcx,0x20(%rax)
  1047dd:	48 8b 7d b8          	mov    -0x48(%rbp),%rdi
  1047e1:	48 8b b5 60 ff ff ff 	mov    -0xa0(%rbp),%rsi
  1047e8:	ba 70 00 00 00       	mov    $0x70,%edx
  1047ed:	e8 2e 17 00 00       	call   105f20 <_ZN4acos9scheduler7Process15register_threadEPNS0_6ThreadEm>
  1047f2:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  1047f6:	e9 76 0d 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  1047fb:	48 83 7d b8 00       	cmpq   $0x0,-0x48(%rbp)
  104800:	0f 84 19 00 00 00    	je     10481f <syscall_dispatch+0x72f>
  104806:	48 8b 7d b8          	mov    -0x48(%rbp),%rdi
  10480a:	48 8b 75 e8          	mov    -0x18(%rbp),%rsi
  10480e:	e8 dd 19 00 00       	call   1061f0 <_ZN4acos9scheduler7Process10get_threadEm>
  104813:	48 89 85 98 fd ff ff 	mov    %rax,-0x268(%rbp)
  10481a:	e9 0e 00 00 00       	jmp    10482d <syscall_dispatch+0x73d>
  10481f:	31 c0                	xor    %eax,%eax
  104821:	48 89 85 98 fd ff ff 	mov    %rax,-0x268(%rbp)
  104828:	e9 00 00 00 00       	jmp    10482d <syscall_dispatch+0x73d>
  10482d:	48 8b 85 98 fd ff ff 	mov    -0x268(%rbp),%rax
  104834:	48 89 85 58 ff ff ff 	mov    %rax,-0xa8(%rbp)
  10483b:	48 83 bd 58 ff ff ff 	cmpq   $0x0,-0xa8(%rbp)
  104842:	00
  104843:	0f 85 0d 00 00 00    	jne    104856 <syscall_dispatch+0x766>
  104849:	48 c7 45 f8 ff ff ff 	movq   $0xffffffffffffffff,-0x8(%rbp)
  104850:	ff
  104851:	e9 1b 0d 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  104856:	e9 00 00 00 00       	jmp    10485b <syscall_dispatch+0x76b>
  10485b:	48 8b 85 58 ff ff ff 	mov    -0xa8(%rbp),%rax
  104862:	83 78 18 05          	cmpl   $0x5,0x18(%rax)
  104866:	0f 84 0a 00 00 00    	je     104876 <syscall_dispatch+0x786>
  10486c:	e8 8f 1e 00 00       	call   106700 <_ZN4acos9scheduler8scheduleEv>
  104871:	e9 e5 ff ff ff       	jmp    10485b <syscall_dispatch+0x76b>
  104876:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  10487d:	00
  10487e:	e9 ee 0c 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  104883:	48 83 7d b8 00       	cmpq   $0x0,-0x48(%rbp)
  104888:	0f 84 19 00 00 00    	je     1048a7 <syscall_dispatch+0x7b7>
  10488e:	48 8b 7d b8          	mov    -0x48(%rbp),%rdi
  104892:	48 8b 75 e8          	mov    -0x18(%rbp),%rsi
  104896:	e8 55 19 00 00       	call   1061f0 <_ZN4acos9scheduler7Process10get_threadEm>
  10489b:	48 89 85 90 fd ff ff 	mov    %rax,-0x270(%rbp)
  1048a2:	e9 0e 00 00 00       	jmp    1048b5 <syscall_dispatch+0x7c5>
  1048a7:	31 c0                	xor    %eax,%eax
  1048a9:	48 89 85 90 fd ff ff 	mov    %rax,-0x270(%rbp)
  1048b0:	e9 00 00 00 00       	jmp    1048b5 <syscall_dispatch+0x7c5>
  1048b5:	48 8b 85 90 fd ff ff 	mov    -0x270(%rbp),%rax
  1048bc:	48 89 85 50 ff ff ff 	mov    %rax,-0xb0(%rbp)
  1048c3:	48 83 bd 50 ff ff ff 	cmpq   $0x0,-0xb0(%rbp)
  1048ca:	00
  1048cb:	0f 84 1a 00 00 00    	je     1048eb <syscall_dispatch+0x7fb>
  1048d1:	48 8b 7d b8          	mov    -0x48(%rbp),%rdi
  1048d5:	48 8b 75 e8          	mov    -0x18(%rbp),%rsi
  1048d9:	ba 40 00 00 00       	mov    $0x40,%edx
  1048de:	e8 9d 0c 00 00       	call   105580 <_ZN4acos3sys12_GLOBAL__N_110has_rightsEPNS_9scheduler7ProcessEmm>
  1048e3:	a8 01                	test   $0x1,%al
  1048e5:	0f 85 0d 00 00 00    	jne    1048f8 <syscall_dispatch+0x808>
  1048eb:	48 c7 45 f8 fe ff ff 	movq   $0xfffffffffffffffe,-0x8(%rbp)
  1048f2:	ff
  1048f3:	e9 79 0c 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  1048f8:	48 8b 85 50 ff ff ff 	mov    -0xb0(%rbp),%rax
  1048ff:	c7 40 18 05 00 00 00 	movl   $0x5,0x18(%rax)
  104906:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  10490d:	00
  10490e:	e9 5e 0c 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  104913:	31 c0                	xor    %eax,%eax
  104915:	48 83 7d b8 00       	cmpq   $0x0,-0x48(%rbp)
  10491a:	88 85 8f fd ff ff    	mov    %al,-0x271(%rbp)
  104920:	0f 84 13 00 00 00    	je     104939 <syscall_dispatch+0x849>
  104926:	48 8b 7d b8          	mov    -0x48(%rbp),%rdi
  10492a:	48 8b 75 e8          	mov    -0x18(%rbp),%rsi
  10492e:	e8 2d 12 00 00       	call   105b60 <_ZN4acos9scheduler7Process12close_handleEm>
  104933:	88 85 8f fd ff ff    	mov    %al,-0x271(%rbp)
  104939:	8a 95 8f fd ff ff    	mov    -0x271(%rbp),%dl
  10493f:	48 c7 c0 ff ff ff ff 	mov    $0xffffffffffffffff,%rax
  104946:	31 c9                	xor    %ecx,%ecx
  104948:	f6 c2 01             	test   $0x1,%dl
  10494b:	48 0f 45 c1          	cmovne %rcx,%rax
  10494f:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  104953:	e9 19 0c 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  104958:	48 83 7d b8 00       	cmpq   $0x0,-0x48(%rbp)
  10495d:	0f 84 0b 00 00 00    	je     10496e <syscall_dispatch+0x87e>
  104963:	48 83 7d e0 00       	cmpq   $0x0,-0x20(%rbp)
  104968:	0f 85 0d 00 00 00    	jne    10497b <syscall_dispatch+0x88b>
  10496e:	48 c7 45 f8 ff ff ff 	movq   $0xffffffffffffffff,-0x8(%rbp)
  104975:	ff
  104976:	e9 f6 0b 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  10497b:	48 83 7d e8 00       	cmpq   $0x0,-0x18(%rbp)
  104980:	0f 85 e6 00 00 00    	jne    104a6c <syscall_dispatch+0x97c>
  104986:	e8 85 67 00 00       	call   10b110 <_ZN4acos8graphics15GraphicsManager15primary_displayEv>
  10498b:	48 89 85 48 ff ff ff 	mov    %rax,-0xb8(%rbp)
  104992:	48 83 bd 48 ff ff ff 	cmpq   $0x0,-0xb8(%rbp)
  104999:	00
  10499a:	0f 84 c7 00 00 00    	je     104a67 <syscall_dispatch+0x977>
  1049a0:	48 8b bd 48 ff ff ff 	mov    -0xb8(%rbp),%rdi
  1049a7:	48 8b 07             	mov    (%rdi),%rax
  1049aa:	ff 50 18             	call   *0x18(%rax)
  1049ad:	48 83 f8 00          	cmp    $0x0,%rax
  1049b1:	0f 84 b0 00 00 00    	je     104a67 <syscall_dispatch+0x977>
  1049b7:	48 8b bd 48 ff ff ff 	mov    -0xb8(%rbp),%rdi
  1049be:	48 8b 07             	mov    (%rdi),%rax
  1049c1:	ff 50 18             	call   *0x18(%rax)
  1049c4:	48 89 85 40 ff ff ff 	mov    %rax,-0xc0(%rbp)
  1049cb:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  1049cf:	48 89 85 38 ff ff ff 	mov    %rax,-0xc8(%rbp)
  1049d6:	48 8b 85 38 ff ff ff 	mov    -0xc8(%rbp),%rax
  1049dd:	48 b9 00 00 00 00 c0 	movabs $0xc000000000,%rcx
  1049e4:	00 00 00
  1049e7:	48 89 08             	mov    %rcx,(%rax)
  1049ea:	48 8b bd 40 ff ff ff 	mov    -0xc0(%rbp),%rdi
  1049f1:	e8 4a a1 00 00       	call   10eb40 <_ZNK4acos8graphics11Framebuffer4sizeEv>
  1049f6:	48 89 c1             	mov    %rax,%rcx
  1049f9:	48 8b 85 38 ff ff ff 	mov    -0xc8(%rbp),%rax
  104a00:	48 89 48 08          	mov    %rcx,0x8(%rax)
  104a04:	48 8b bd 40 ff ff ff 	mov    -0xc0(%rbp),%rdi
  104a0b:	e8 50 a1 00 00       	call   10eb60 <_ZNK4acos8graphics11Framebuffer5widthEv>
  104a10:	89 c1                	mov    %eax,%ecx
  104a12:	48 8b 85 38 ff ff ff 	mov    -0xc8(%rbp),%rax
  104a19:	89 48 10             	mov    %ecx,0x10(%rax)
  104a1c:	48 8b bd 40 ff ff ff 	mov    -0xc0(%rbp),%rdi
  104a23:	e8 58 a1 00 00       	call   10eb80 <_ZNK4acos8graphics11Framebuffer6heightEv>
  104a28:	89 c1                	mov    %eax,%ecx
  104a2a:	48 8b 85 38 ff ff ff 	mov    -0xc8(%rbp),%rax
  104a31:	89 48 14             	mov    %ecx,0x14(%rax)
  104a34:	48 8b bd 40 ff ff ff 	mov    -0xc0(%rbp),%rdi
  104a3b:	e8 60 a1 00 00       	call   10eba0 <_ZNK4acos8graphics11Framebuffer5pitchEv>
  104a40:	89 c1                	mov    %eax,%ecx
  104a42:	48 8b 85 38 ff ff ff 	mov    -0xc8(%rbp),%rax
  104a49:	89 48 18             	mov    %ecx,0x18(%rax)
  104a4c:	48 8b 85 38 ff ff ff 	mov    -0xc8(%rbp),%rax
  104a53:	c7 40 1c 20 00 00 00 	movl   $0x20,0x1c(%rax)
  104a5a:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  104a61:	00
  104a62:	e9 0a 0b 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  104a67:	e9 00 00 00 00       	jmp    104a6c <syscall_dispatch+0x97c>
  104a6c:	48 8b 7d b8          	mov    -0x48(%rbp),%rdi
  104a70:	48 8b 75 e8          	mov    -0x18(%rbp),%rsi
  104a74:	e8 a7 12 00 00       	call   105d20 <_ZN4acos9scheduler7Process10get_handleEm>
  104a79:	48 89 85 30 ff ff ff 	mov    %rax,-0xd0(%rbp)
  104a80:	48 83 bd 30 ff ff ff 	cmpq   $0x0,-0xd0(%rbp)
  104a87:	00
  104a88:	0f 85 0d 00 00 00    	jne    104a9b <syscall_dispatch+0x9ab>
  104a8e:	48 c7 45 f8 ff ff ff 	movq   $0xffffffffffffffff,-0x8(%rbp)
  104a95:	ff
  104a96:	e9 d6 0a 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  104a9b:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  104a9f:	48 89 85 28 ff ff ff 	mov    %rax,-0xd8(%rbp)
  104aa6:	48 8b 85 30 ff ff ff 	mov    -0xd0(%rbp),%rax
  104aad:	8b 00                	mov    (%rax),%eax
  104aaf:	89 c1                	mov    %eax,%ecx
  104ab1:	48 8b 85 28 ff ff ff 	mov    -0xd8(%rbp),%rax
  104ab8:	48 89 08             	mov    %rcx,(%rax)
  104abb:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  104abf:	48 8b 85 28 ff ff ff 	mov    -0xd8(%rbp),%rax
  104ac6:	48 89 48 08          	mov    %rcx,0x8(%rax)
  104aca:	48 8b 85 30 ff ff ff 	mov    -0xd0(%rbp),%rax
  104ad1:	48 8b 48 10          	mov    0x10(%rax),%rcx
  104ad5:	48 8b 85 28 ff ff ff 	mov    -0xd8(%rbp),%rax
  104adc:	48 89 48 10          	mov    %rcx,0x10(%rax)
  104ae0:	48 8b 85 30 ff ff ff 	mov    -0xd0(%rbp),%rax
  104ae7:	48 8b 48 18          	mov    0x18(%rax),%rcx
  104aeb:	48 8b 85 28 ff ff ff 	mov    -0xd8(%rbp),%rax
  104af2:	48 89 48 18          	mov    %rcx,0x18(%rax)
  104af6:	48 8b 85 28 ff ff ff 	mov    -0xd8(%rbp),%rax
  104afd:	48 c7 40 20 00 00 00 	movq   $0x0,0x20(%rax)
  104b04:	00
  104b05:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  104b0c:	00
  104b0d:	e9 5f 0a 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  104b12:	48 83 7d b8 00       	cmpq   $0x0,-0x48(%rbp)
  104b17:	0f 84 0b 00 00 00    	je     104b28 <syscall_dispatch+0xa38>
  104b1d:	48 83 7d d8 00       	cmpq   $0x0,-0x28(%rbp)
  104b22:	0f 85 0d 00 00 00    	jne    104b35 <syscall_dispatch+0xa45>
  104b28:	48 c7 45 f8 ff ff ff 	movq   $0xffffffffffffffff,-0x8(%rbp)
  104b2f:	ff
  104b30:	e9 3c 0a 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  104b35:	48 c7 85 20 ff ff ff 	movq   $0x0,-0xe0(%rbp)
  104b3c:	00 00 00 00
  104b40:	48 8b 7d b8          	mov    -0x48(%rbp),%rdi
  104b44:	48 8b 75 e8          	mov    -0x18(%rbp),%rsi
  104b48:	48 8b 55 e0          	mov    -0x20(%rbp),%rdx
  104b4c:	48 8d 8d 20 ff ff ff 	lea    -0xe0(%rbp),%rcx
  104b53:	e8 f8 10 00 00       	call   105c50 <_ZN4acos9scheduler7Process16duplicate_handleEmmPm>
  104b58:	a8 01                	test   $0x1,%al
  104b5a:	0f 85 0d 00 00 00    	jne    104b6d <syscall_dispatch+0xa7d>
  104b60:	48 c7 45 f8 fe ff ff 	movq   $0xfffffffffffffffe,-0x8(%rbp)
  104b67:	ff
  104b68:	e9 04 0a 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  104b6d:	48 8b 8d 20 ff ff ff 	mov    -0xe0(%rbp),%rcx
  104b74:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  104b78:	48 89 08             	mov    %rcx,(%rax)
  104b7b:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  104b82:	00
  104b83:	e9 e9 09 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  104b88:	48 83 7d b8 00       	cmpq   $0x0,-0x48(%rbp)
  104b8d:	0f 84 0b 00 00 00    	je     104b9e <syscall_dispatch+0xaae>
  104b93:	48 83 7d d8 00       	cmpq   $0x0,-0x28(%rbp)
  104b98:	0f 85 0d 00 00 00    	jne    104bab <syscall_dispatch+0xabb>
  104b9e:	48 c7 45 f8 ff ff ff 	movq   $0xffffffffffffffff,-0x8(%rbp)
  104ba5:	ff
  104ba6:	e9 c6 09 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  104bab:	48 8b 7d e0          	mov    -0x20(%rbp),%rdi
  104baf:	e8 8c 20 00 00       	call   106c40 <_ZN4acos9scheduler12find_processEm>
  104bb4:	48 89 85 18 ff ff ff 	mov    %rax,-0xe8(%rbp)
  104bbb:	48 83 bd 18 ff ff ff 	cmpq   $0x0,-0xe8(%rbp)
  104bc2:	00
  104bc3:	0f 85 0d 00 00 00    	jne    104bd6 <syscall_dispatch+0xae6>
  104bc9:	48 c7 45 f8 ff ff ff 	movq   $0xffffffffffffffff,-0x8(%rbp)
  104bd0:	ff
  104bd1:	e9 9b 09 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  104bd6:	48 c7 85 10 ff ff ff 	movq   $0x0,-0xf0(%rbp)
  104bdd:	00 00 00 00
  104be1:	48 8b 7d b8          	mov    -0x48(%rbp),%rdi
  104be5:	48 8b 75 e8          	mov    -0x18(%rbp),%rsi
  104be9:	48 8b 95 18 ff ff ff 	mov    -0xe8(%rbp),%rdx
  104bf0:	48 8d 8d 10 ff ff ff 	lea    -0xf0(%rbp),%rcx
  104bf7:	e8 a4 11 00 00       	call   105da0 <_ZN4acos9scheduler7Process15transfer_handleEmRS1_Pm>
  104bfc:	a8 01                	test   $0x1,%al
  104bfe:	0f 85 0d 00 00 00    	jne    104c11 <syscall_dispatch+0xb21>
  104c04:	48 c7 45 f8 fe ff ff 	movq   $0xfffffffffffffffe,-0x8(%rbp)
  104c0b:	ff
  104c0c:	e9 60 09 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  104c11:	48 8b 8d 10 ff ff ff 	mov    -0xf0(%rbp),%rcx
  104c18:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  104c1c:	48 89 08             	mov    %rcx,(%rax)
  104c1f:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  104c26:	00
  104c27:	e9 45 09 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  104c2c:	48 83 7d b8 00       	cmpq   $0x0,-0x48(%rbp)
  104c31:	0f 85 0d 00 00 00    	jne    104c44 <syscall_dispatch+0xb54>
  104c37:	48 c7 45 f8 ff ff ff 	movq   $0xffffffffffffffff,-0x8(%rbp)
  104c3e:	ff
  104c3f:	e9 2d 09 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  104c44:	bf 70 03 00 00       	mov    $0x370,%edi
  104c49:	e8 02 3b 00 00       	call   108750 <_ZN4acos6memory7kmallocEm>
  104c4e:	48 89 85 08 ff ff ff 	mov    %rax,-0xf8(%rbp)
  104c55:	48 83 bd 08 ff ff ff 	cmpq   $0x0,-0xf8(%rbp)
  104c5c:	00
  104c5d:	0f 85 0d 00 00 00    	jne    104c70 <syscall_dispatch+0xb80>
  104c63:	48 c7 45 f8 fd ff ff 	movq   $0xfffffffffffffffd,-0x8(%rbp)
  104c6a:	ff
  104c6b:	e9 01 09 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  104c70:	48 8b bd 08 ff ff ff 	mov    -0xf8(%rbp),%rdi
  104c77:	48 89 bd 80 fd ff ff 	mov    %rdi,-0x280(%rbp)
  104c7e:	e8 ad 3b 00 00       	call   108830 <_ZN4acos3ipc7ChannelC1Ev>
  104c83:	48 8b 85 80 fd ff ff 	mov    -0x280(%rbp),%rax
  104c8a:	48 89 85 00 ff ff ff 	mov    %rax,-0x100(%rbp)
  104c91:	48 8b 7d b8          	mov    -0x48(%rbp),%rdi
  104c95:	48 8b b5 00 ff ff ff 	mov    -0x100(%rbp),%rsi
  104c9c:	e8 8f 14 00 00       	call   106130 <_ZN4acos9scheduler7Process16register_channelEPNS_3ipc7ChannelE>
  104ca1:	48 89 85 f8 fe ff ff 	mov    %rax,-0x108(%rbp)
  104ca8:	48 83 bd f8 fe ff ff 	cmpq   $0x0,-0x108(%rbp)
  104caf:	00
  104cb0:	0f 84 13 00 00 00    	je     104cc9 <syscall_dispatch+0xbd9>
  104cb6:	48 8b 85 f8 fe ff ff 	mov    -0x108(%rbp),%rax
  104cbd:	48 89 85 78 fd ff ff 	mov    %rax,-0x288(%rbp)
  104cc4:	e9 13 00 00 00       	jmp    104cdc <syscall_dispatch+0xbec>
  104cc9:	48 c7 c0 fd ff ff ff 	mov    $0xfffffffffffffffd,%rax
  104cd0:	48 89 85 78 fd ff ff 	mov    %rax,-0x288(%rbp)
  104cd7:	e9 00 00 00 00       	jmp    104cdc <syscall_dispatch+0xbec>
  104cdc:	48 8b 85 78 fd ff ff 	mov    -0x288(%rbp),%rax
  104ce3:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  104ce7:	e9 85 08 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  104cec:	48 83 7d b8 00       	cmpq   $0x0,-0x48(%rbp)
  104cf1:	0f 85 0d 00 00 00    	jne    104d04 <syscall_dispatch+0xc14>
  104cf7:	48 c7 45 f8 ff ff ff 	movq   $0xffffffffffffffff,-0x8(%rbp)
  104cfe:	ff
  104cff:	e9 6d 08 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  104d04:	bf 98 00 00 00       	mov    $0x98,%edi
  104d09:	e8 42 3a 00 00       	call   108750 <_ZN4acos6memory7kmallocEm>
  104d0e:	48 89 85 f0 fe ff ff 	mov    %rax,-0x110(%rbp)
  104d15:	48 83 bd f0 fe ff ff 	cmpq   $0x0,-0x110(%rbp)
  104d1c:	00
  104d1d:	0f 85 0d 00 00 00    	jne    104d30 <syscall_dispatch+0xc40>
  104d23:	48 c7 45 f8 fd ff ff 	movq   $0xfffffffffffffffd,-0x8(%rbp)
  104d2a:	ff
  104d2b:	e9 41 08 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  104d30:	48 8b bd f0 fe ff ff 	mov    -0x110(%rbp),%rdi
  104d37:	48 89 bd 70 fd ff ff 	mov    %rdi,-0x290(%rbp)
  104d3e:	e8 2d 3e 00 00       	call   108b70 <_ZN4acos3ipc12NotificationC1Ev>
  104d43:	48 8b 85 70 fd ff ff 	mov    -0x290(%rbp),%rax
  104d4a:	48 89 85 e8 fe ff ff 	mov    %rax,-0x118(%rbp)
  104d51:	48 8b 7d b8          	mov    -0x48(%rbp),%rdi
  104d55:	48 8b b5 e8 fe ff ff 	mov    -0x118(%rbp),%rsi
  104d5c:	e8 2f 16 00 00       	call   106390 <_ZN4acos9scheduler7Process21register_notificationEPNS_3ipc12NotificationE>
  104d61:	48 89 85 e0 fe ff ff 	mov    %rax,-0x120(%rbp)
  104d68:	48 83 bd e0 fe ff ff 	cmpq   $0x0,-0x120(%rbp)
  104d6f:	00
  104d70:	0f 84 13 00 00 00    	je     104d89 <syscall_dispatch+0xc99>
  104d76:	48 8b 85 e0 fe ff ff 	mov    -0x120(%rbp),%rax
  104d7d:	48 89 85 68 fd ff ff 	mov    %rax,-0x298(%rbp)
  104d84:	e9 13 00 00 00       	jmp    104d9c <syscall_dispatch+0xcac>
  104d89:	48 c7 c0 fd ff ff ff 	mov    $0xfffffffffffffffd,%rax
  104d90:	48 89 85 68 fd ff ff 	mov    %rax,-0x298(%rbp)
  104d97:	e9 00 00 00 00       	jmp    104d9c <syscall_dispatch+0xcac>
  104d9c:	48 8b 85 68 fd ff ff 	mov    -0x298(%rbp),%rax
  104da3:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  104da7:	e9 c5 07 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  104dac:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  104db0:	48 89 85 d8 fe ff ff 	mov    %rax,-0x128(%rbp)
  104db7:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  104dbb:	48 89 85 d0 fe ff ff 	mov    %rax,-0x130(%rbp)
  104dc2:	48 83 7d b8 00       	cmpq   $0x0,-0x48(%rbp)
  104dc7:	0f 84 0e 00 00 00    	je     104ddb <syscall_dispatch+0xceb>
  104dcd:	48 83 bd d0 fe ff ff 	cmpq   $0x0,-0x130(%rbp)
  104dd4:	00
  104dd5:	0f 85 0d 00 00 00    	jne    104de8 <syscall_dispatch+0xcf8>
  104ddb:	48 c7 45 f8 ff ff ff 	movq   $0xffffffffffffffff,-0x8(%rbp)
  104de2:	ff
  104de3:	e9 89 07 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  104de8:	48 8b 7d b8          	mov    -0x48(%rbp),%rdi
  104dec:	48 8b b5 d8 fe ff ff 	mov    -0x128(%rbp),%rsi
  104df3:	ba 02 00 00 00       	mov    $0x2,%edx
  104df8:	e8 83 07 00 00       	call   105580 <_ZN4acos3sys12_GLOBAL__N_110has_rightsEPNS_9scheduler7ProcessEmm>
  104dfd:	a8 01                	test   $0x1,%al
  104dff:	0f 85 0d 00 00 00    	jne    104e12 <syscall_dispatch+0xd22>
  104e05:	48 c7 45 f8 fe ff ff 	movq   $0xfffffffffffffffe,-0x8(%rbp)
  104e0c:	ff
  104e0d:	e9 5f 07 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  104e12:	48 8b 7d b8          	mov    -0x48(%rbp),%rdi
  104e16:	48 8b b5 d8 fe ff ff 	mov    -0x128(%rbp),%rsi
  104e1d:	e8 2e 14 00 00       	call   106250 <_ZN4acos9scheduler7Process11get_channelEm>
  104e22:	48 89 85 c8 fe ff ff 	mov    %rax,-0x138(%rbp)
  104e29:	48 83 bd c8 fe ff ff 	cmpq   $0x0,-0x138(%rbp)
  104e30:	00
  104e31:	0f 85 0d 00 00 00    	jne    104e44 <syscall_dispatch+0xd54>
  104e37:	48 c7 45 f8 ff ff ff 	movq   $0xffffffffffffffff,-0x8(%rbp)
  104e3e:	ff
  104e3f:	e9 2d 07 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  104e44:	48 8b bd c8 fe ff ff 	mov    -0x138(%rbp),%rdi
  104e4b:	48 8b b5 d0 fe ff ff 	mov    -0x130(%rbp),%rsi
  104e52:	e8 89 3a 00 00       	call   1088e0 <_ZN4acos3ipc7Channel4sendERKNS_3abi7MessageE>
  104e57:	24 01                	and    $0x1,%al
  104e59:	0f b6 c0             	movzbl %al,%eax
  104e5c:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  104e60:	e9 0c 07 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  104e65:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  104e69:	48 89 85 c0 fe ff ff 	mov    %rax,-0x140(%rbp)
  104e70:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  104e74:	48 89 85 b8 fe ff ff 	mov    %rax,-0x148(%rbp)
  104e7b:	48 83 7d b8 00       	cmpq   $0x0,-0x48(%rbp)
  104e80:	0f 84 0e 00 00 00    	je     104e94 <syscall_dispatch+0xda4>
  104e86:	48 83 bd b8 fe ff ff 	cmpq   $0x0,-0x148(%rbp)
  104e8d:	00
  104e8e:	0f 85 0d 00 00 00    	jne    104ea1 <syscall_dispatch+0xdb1>
  104e94:	48 c7 45 f8 ff ff ff 	movq   $0xffffffffffffffff,-0x8(%rbp)
  104e9b:	ff
  104e9c:	e9 d0 06 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  104ea1:	48 8b 7d b8          	mov    -0x48(%rbp),%rdi
  104ea5:	48 8b b5 c0 fe ff ff 	mov    -0x140(%rbp),%rsi
  104eac:	ba 01 00 00 00       	mov    $0x1,%edx
  104eb1:	e8 ca 06 00 00       	call   105580 <_ZN4acos3sys12_GLOBAL__N_110has_rightsEPNS_9scheduler7ProcessEmm>
  104eb6:	a8 01                	test   $0x1,%al
  104eb8:	0f 85 0d 00 00 00    	jne    104ecb <syscall_dispatch+0xddb>
  104ebe:	48 c7 45 f8 fe ff ff 	movq   $0xfffffffffffffffe,-0x8(%rbp)
  104ec5:	ff
  104ec6:	e9 a6 06 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  104ecb:	48 8b 7d b8          	mov    -0x48(%rbp),%rdi
  104ecf:	48 8b b5 c0 fe ff ff 	mov    -0x140(%rbp),%rsi
  104ed6:	e8 75 13 00 00       	call   106250 <_ZN4acos9scheduler7Process11get_channelEm>
  104edb:	48 89 85 b0 fe ff ff 	mov    %rax,-0x150(%rbp)
  104ee2:	48 83 bd b0 fe ff ff 	cmpq   $0x0,-0x150(%rbp)
  104ee9:	00
  104eea:	0f 85 0d 00 00 00    	jne    104efd <syscall_dispatch+0xe0d>
  104ef0:	48 c7 45 f8 ff ff ff 	movq   $0xffffffffffffffff,-0x8(%rbp)
  104ef7:	ff
  104ef8:	e9 74 06 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  104efd:	48 8b bd b0 fe ff ff 	mov    -0x150(%rbp),%rdi
  104f04:	48 8b b5 b8 fe ff ff 	mov    -0x148(%rbp),%rsi
  104f0b:	ba 01 00 00 00       	mov    $0x1,%edx
  104f10:	e8 0b 3b 00 00       	call   108a20 <_ZN4acos3ipc7Channel7receiveERNS_3abi7MessageEb>
  104f15:	24 01                	and    $0x1,%al
  104f17:	0f b6 c0             	movzbl %al,%eax
  104f1a:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  104f1e:	e9 4e 06 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  104f23:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  104f27:	48 89 85 a8 fe ff ff 	mov    %rax,-0x158(%rbp)
  104f2e:	48 83 7d b8 00       	cmpq   $0x0,-0x48(%rbp)
  104f33:	0f 85 0d 00 00 00    	jne    104f46 <syscall_dispatch+0xe56>
  104f39:	48 c7 45 f8 ff ff ff 	movq   $0xffffffffffffffff,-0x8(%rbp)
  104f40:	ff
  104f41:	e9 2b 06 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  104f46:	48 8b 7d b8          	mov    -0x48(%rbp),%rdi
  104f4a:	48 8b b5 a8 fe ff ff 	mov    -0x158(%rbp),%rsi
  104f51:	ba 80 00 00 00       	mov    $0x80,%edx
  104f56:	e8 25 06 00 00       	call   105580 <_ZN4acos3sys12_GLOBAL__N_110has_rightsEPNS_9scheduler7ProcessEmm>
  104f5b:	a8 01                	test   $0x1,%al
  104f5d:	0f 85 0d 00 00 00    	jne    104f70 <syscall_dispatch+0xe80>
  104f63:	48 c7 45 f8 fe ff ff 	movq   $0xfffffffffffffffe,-0x8(%rbp)
  104f6a:	ff
  104f6b:	e9 01 06 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  104f70:	48 8b 7d b8          	mov    -0x48(%rbp),%rdi
  104f74:	48 8b b5 a8 fe ff ff 	mov    -0x158(%rbp),%rsi
  104f7b:	e8 70 14 00 00       	call   1063f0 <_ZN4acos9scheduler7Process16get_notificationEm>
  104f80:	48 89 85 a0 fe ff ff 	mov    %rax,-0x160(%rbp)
  104f87:	48 83 bd a0 fe ff ff 	cmpq   $0x0,-0x160(%rbp)
  104f8e:	00
  104f8f:	0f 85 0d 00 00 00    	jne    104fa2 <syscall_dispatch+0xeb2>
  104f95:	48 c7 45 f8 ff ff ff 	movq   $0xffffffffffffffff,-0x8(%rbp)
  104f9c:	ff
  104f9d:	e9 cf 05 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  104fa2:	48 8b bd a0 fe ff ff 	mov    -0x160(%rbp),%rdi
  104fa9:	e8 52 3c 00 00       	call   108c00 <_ZN4acos3ipc12Notification6signalEv>
  104fae:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  104fb5:	00
  104fb6:	e9 b6 05 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  104fbb:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  104fbf:	48 89 85 98 fe ff ff 	mov    %rax,-0x168(%rbp)
  104fc6:	48 83 7d b8 00       	cmpq   $0x0,-0x48(%rbp)
  104fcb:	0f 85 0d 00 00 00    	jne    104fde <syscall_dispatch+0xeee>
  104fd1:	48 c7 45 f8 ff ff ff 	movq   $0xffffffffffffffff,-0x8(%rbp)
  104fd8:	ff
  104fd9:	e9 93 05 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  104fde:	48 8b 7d b8          	mov    -0x48(%rbp),%rdi
  104fe2:	48 8b b5 98 fe ff ff 	mov    -0x168(%rbp),%rsi
  104fe9:	ba 00 01 00 00       	mov    $0x100,%edx
  104fee:	e8 8d 05 00 00       	call   105580 <_ZN4acos3sys12_GLOBAL__N_110has_rightsEPNS_9scheduler7ProcessEmm>
  104ff3:	a8 01                	test   $0x1,%al
  104ff5:	0f 85 0d 00 00 00    	jne    105008 <syscall_dispatch+0xf18>
  104ffb:	48 c7 45 f8 fe ff ff 	movq   $0xfffffffffffffffe,-0x8(%rbp)
  105002:	ff
  105003:	e9 69 05 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  105008:	48 8b 7d b8          	mov    -0x48(%rbp),%rdi
  10500c:	48 8b b5 98 fe ff ff 	mov    -0x168(%rbp),%rsi
  105013:	e8 d8 13 00 00       	call   1063f0 <_ZN4acos9scheduler7Process16get_notificationEm>
  105018:	48 89 85 90 fe ff ff 	mov    %rax,-0x170(%rbp)
  10501f:	48 83 bd 90 fe ff ff 	cmpq   $0x0,-0x170(%rbp)
  105026:	00
  105027:	0f 85 0d 00 00 00    	jne    10503a <syscall_dispatch+0xf4a>
  10502d:	48 c7 45 f8 ff ff ff 	movq   $0xffffffffffffffff,-0x8(%rbp)
  105034:	ff
  105035:	e9 37 05 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  10503a:	48 8b bd 90 fe ff ff 	mov    -0x170(%rbp),%rdi
  105041:	e8 5a 3c 00 00       	call   108ca0 <_ZN4acos3ipc12Notification4waitEv>
  105046:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  10504d:	00
  10504e:	e9 1e 05 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  105053:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  105057:	48 89 85 88 fe ff ff 	mov    %rax,-0x178(%rbp)
  10505e:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  105062:	48 89 85 80 fe ff ff 	mov    %rax,-0x180(%rbp)
  105069:	48 83 7d b8 00       	cmpq   $0x0,-0x48(%rbp)
  10506e:	0f 85 0d 00 00 00    	jne    105081 <syscall_dispatch+0xf91>
  105074:	48 c7 45 f8 ff ff ff 	movq   $0xffffffffffffffff,-0x8(%rbp)
  10507b:	ff
  10507c:	e9 f0 04 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  105081:	48 8b bd 88 fe ff ff 	mov    -0x178(%rbp),%rdi
  105088:	48 8b b5 80 fe ff ff 	mov    -0x180(%rbp),%rsi
  10508f:	e8 4c 3d 00 00       	call   108de0 <_ZN4acos3vfs3VFS4openEPKcm>
  105094:	48 98                	cltq
  105096:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  10509a:	e9 d2 04 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  10509f:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  1050a3:	48 89 85 78 fe ff ff 	mov    %rax,-0x188(%rbp)
  1050aa:	48 83 7d b8 00       	cmpq   $0x0,-0x48(%rbp)
  1050af:	0f 85 0d 00 00 00    	jne    1050c2 <syscall_dispatch+0xfd2>
  1050b5:	48 c7 45 f8 ff ff ff 	movq   $0xffffffffffffffff,-0x8(%rbp)
  1050bc:	ff
  1050bd:	e9 af 04 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  1050c2:	48 8b bd 78 fe ff ff 	mov    -0x188(%rbp),%rdi
  1050c9:	e8 82 3e 00 00       	call   108f50 <_ZN4acos3vfs3VFS5closeEm>
  1050ce:	48 98                	cltq
  1050d0:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  1050d4:	e9 98 04 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  1050d9:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  1050dd:	48 89 85 70 fe ff ff 	mov    %rax,-0x190(%rbp)
  1050e4:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  1050e8:	48 89 85 68 fe ff ff 	mov    %rax,-0x198(%rbp)
  1050ef:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  1050f3:	48 89 85 60 fe ff ff 	mov    %rax,-0x1a0(%rbp)
  1050fa:	48 83 7d b8 00       	cmpq   $0x0,-0x48(%rbp)
  1050ff:	0f 85 0d 00 00 00    	jne    105112 <syscall_dispatch+0x1022>
  105105:	48 c7 45 f8 ff ff ff 	movq   $0xffffffffffffffff,-0x8(%rbp)
  10510c:	ff
  10510d:	e9 5f 04 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  105112:	48 8b bd 70 fe ff ff 	mov    -0x190(%rbp),%rdi
  105119:	48 8b b5 68 fe ff ff 	mov    -0x198(%rbp),%rsi
  105120:	48 8b 95 60 fe ff ff 	mov    -0x1a0(%rbp),%rdx
  105127:	e8 a4 3e 00 00       	call   108fd0 <_ZN4acos3vfs3VFS4readEmPvm>
  10512c:	48 98                	cltq
  10512e:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  105132:	e9 3a 04 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  105137:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  10513b:	48 89 85 58 fe ff ff 	mov    %rax,-0x1a8(%rbp)
  105142:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  105146:	48 89 85 50 fe ff ff 	mov    %rax,-0x1b0(%rbp)
  10514d:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  105151:	48 89 85 48 fe ff ff 	mov    %rax,-0x1b8(%rbp)
  105158:	48 83 7d b8 00       	cmpq   $0x0,-0x48(%rbp)
  10515d:	0f 85 0d 00 00 00    	jne    105170 <syscall_dispatch+0x1080>
  105163:	48 c7 45 f8 ff ff ff 	movq   $0xffffffffffffffff,-0x8(%rbp)
  10516a:	ff
  10516b:	e9 01 04 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  105170:	48 8b bd 58 fe ff ff 	mov    -0x1a8(%rbp),%rdi
  105177:	48 8b b5 50 fe ff ff 	mov    -0x1b0(%rbp),%rsi
  10517e:	48 8b 95 48 fe ff ff 	mov    -0x1b8(%rbp),%rdx
  105185:	e8 c6 3e 00 00       	call   109050 <_ZN4acos3vfs3VFS5writeEmPKvm>
  10518a:	48 98                	cltq
  10518c:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  105190:	e9 dc 03 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  105195:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  105199:	48 89 85 40 fe ff ff 	mov    %rax,-0x1c0(%rbp)
  1051a0:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  1051a4:	48 89 85 38 fe ff ff 	mov    %rax,-0x1c8(%rbp)
  1051ab:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  1051af:	48 89 85 30 fe ff ff 	mov    %rax,-0x1d0(%rbp)
  1051b6:	48 83 7d b8 00       	cmpq   $0x0,-0x48(%rbp)
  1051bb:	0f 85 0d 00 00 00    	jne    1051ce <syscall_dispatch+0x10de>
  1051c1:	48 c7 45 f8 ff ff ff 	movq   $0xffffffffffffffff,-0x8(%rbp)
  1051c8:	ff
  1051c9:	e9 a3 03 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  1051ce:	48 8b bd 40 fe ff ff 	mov    -0x1c0(%rbp),%rdi
  1051d5:	48 8b b5 38 fe ff ff 	mov    -0x1c8(%rbp),%rsi
  1051dc:	48 8b 95 30 fe ff ff 	mov    -0x1d0(%rbp),%rdx
  1051e3:	e8 18 3f 00 00       	call   109100 <_ZN4acos3vfs3VFS8read_dirEPKcPNS0_14DirectoryEntryEm>
  1051e8:	48 98                	cltq
  1051ea:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  1051ee:	e9 7e 03 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  1051f3:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  1051f7:	48 89 85 28 fe ff ff 	mov    %rax,-0x1d8(%rbp)
  1051fe:	48 83 7d b8 00       	cmpq   $0x0,-0x48(%rbp)
  105203:	0f 84 0e 00 00 00    	je     105217 <syscall_dispatch+0x1127>
  105209:	48 83 bd 28 fe ff ff 	cmpq   $0x0,-0x1d8(%rbp)
  105210:	00
  105211:	0f 85 0d 00 00 00    	jne    105224 <syscall_dispatch+0x1134>
  105217:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  10521e:	00
  10521f:	e9 4d 03 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  105224:	48 8b bd 28 fe ff ff 	mov    -0x1d8(%rbp),%rdi
  10522b:	e8 a0 ea ff ff       	call   103cd0 <_ZN4acos8services14locate_serviceEPKc>
  105230:	48 89 85 20 fe ff ff 	mov    %rax,-0x1e0(%rbp)
  105237:	48 83 bd 20 fe ff ff 	cmpq   $0x0,-0x1e0(%rbp)
  10523e:	00
  10523f:	0f 85 0d 00 00 00    	jne    105252 <syscall_dispatch+0x1162>
  105245:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  10524c:	00
  10524d:	e9 1f 03 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  105252:	48 8b 7d b8          	mov    -0x48(%rbp),%rdi
  105256:	48 8b b5 20 fe ff ff 	mov    -0x1e0(%rbp),%rsi
  10525d:	e8 ce 0e 00 00       	call   106130 <_ZN4acos9scheduler7Process16register_channelEPNS_3ipc7ChannelE>
  105262:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  105266:	e9 06 03 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  10526b:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  10526f:	48 89 85 18 fe ff ff 	mov    %rax,-0x1e8(%rbp)
  105276:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  10527a:	48 89 85 10 fe ff ff 	mov    %rax,-0x1f0(%rbp)
  105281:	48 83 7d b8 00       	cmpq   $0x0,-0x48(%rbp)
  105286:	0f 84 0e 00 00 00    	je     10529a <syscall_dispatch+0x11aa>
  10528c:	48 83 bd 18 fe ff ff 	cmpq   $0x0,-0x1e8(%rbp)
  105293:	00
  105294:	0f 85 0d 00 00 00    	jne    1052a7 <syscall_dispatch+0x11b7>
  10529a:	48 c7 45 f8 ff ff ff 	movq   $0xffffffffffffffff,-0x8(%rbp)
  1052a1:	ff
  1052a2:	e9 ca 02 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  1052a7:	48 8b 7d b8          	mov    -0x48(%rbp),%rdi
  1052ab:	48 8b b5 10 fe ff ff 	mov    -0x1f0(%rbp),%rsi
  1052b2:	e8 99 0f 00 00       	call   106250 <_ZN4acos9scheduler7Process11get_channelEm>
  1052b7:	48 89 85 08 fe ff ff 	mov    %rax,-0x1f8(%rbp)
  1052be:	48 83 bd 08 fe ff ff 	cmpq   $0x0,-0x1f8(%rbp)
  1052c5:	00
  1052c6:	0f 85 0d 00 00 00    	jne    1052d9 <syscall_dispatch+0x11e9>
  1052cc:	48 c7 45 f8 ff ff ff 	movq   $0xffffffffffffffff,-0x8(%rbp)
  1052d3:	ff
  1052d4:	e9 98 02 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  1052d9:	48 8b bd 18 fe ff ff 	mov    -0x1e8(%rbp),%rdi
  1052e0:	48 8b b5 08 fe ff ff 	mov    -0x1f8(%rbp),%rsi
  1052e7:	48 8b 45 b8          	mov    -0x48(%rbp),%rax
  1052eb:	48 8b 10             	mov    (%rax),%rdx
  1052ee:	e8 6d e8 ff ff       	call   103b60 <_ZN4acos8services16register_serviceEPKcPNS_3ipc7ChannelEm>
  1052f3:	a8 01                	test   $0x1,%al
  1052f5:	0f 85 05 00 00 00    	jne    105300 <syscall_dispatch+0x1210>
  1052fb:	e9 0d 00 00 00       	jmp    10530d <syscall_dispatch+0x121d>
  105300:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  105307:	00
  105308:	e9 64 02 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  10530d:	48 c7 45 f8 ff ff ff 	movq   $0xffffffffffffffff,-0x8(%rbp)
  105314:	ff
  105315:	e9 57 02 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  10531a:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  10531e:	89 85 04 fe ff ff    	mov    %eax,-0x1fc(%rbp)
  105324:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  105328:	89 85 00 fe ff ff    	mov    %eax,-0x200(%rbp)
  10532e:	48 83 7d b8 00       	cmpq   $0x0,-0x48(%rbp)
  105333:	0f 85 0d 00 00 00    	jne    105346 <syscall_dispatch+0x1256>
  105339:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  105340:	00
  105341:	e9 2b 02 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  105346:	bf 10 00 00 00       	mov    $0x10,%edi
  10534b:	e8 a0 b0 ff ff       	call   1003f0 <_Znwm>
  105350:	48 89 c7             	mov    %rax,%rdi
  105353:	48 89 bd 60 fd ff ff 	mov    %rdi,-0x2a0(%rbp)
  10535a:	8b b5 04 fe ff ff    	mov    -0x1fc(%rbp),%esi
  105360:	8b 95 00 fe ff ff    	mov    -0x200(%rbp),%edx
  105366:	e8 65 7d 00 00       	call   10d0d0 <_ZN4acos8graphics7SurfaceC1Ejj>
  10536b:	48 8b 85 60 fd ff ff 	mov    -0x2a0(%rbp),%rax
  105372:	48 89 85 f8 fd ff ff 	mov    %rax,-0x208(%rbp)
  105379:	48 8b 7d b8          	mov    -0x48(%rbp),%rdi
  10537d:	48 8b 95 f8 fd ff ff 	mov    -0x208(%rbp),%rdx
  105384:	be 06 00 00 00       	mov    $0x6,%esi
  105389:	b9 13 00 00 00       	mov    $0x13,%ecx
  10538e:	e8 cd 06 00 00       	call   105a60 <_ZN4acos9scheduler7Process17register_resourceENS0_12ResourceKindEPvm>
  105393:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  105397:	e9 d5 01 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  10539c:	48 83 7d b8 00       	cmpq   $0x0,-0x48(%rbp)
  1053a1:	0f 85 0d 00 00 00    	jne    1053b4 <syscall_dispatch+0x12c4>
  1053a7:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  1053ae:	00
  1053af:	e9 bd 01 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  1053b4:	48 8b 7d b8          	mov    -0x48(%rbp),%rdi
  1053b8:	be 07 00 00 00       	mov    $0x7,%esi
  1053bd:	31 c0                	xor    %eax,%eax
  1053bf:	89 c2                	mov    %eax,%edx
  1053c1:	b9 03 00 00 00       	mov    $0x3,%ecx
  1053c6:	e8 95 06 00 00       	call   105a60 <_ZN4acos9scheduler7Process17register_resourceENS0_12ResourceKindEPvm>
  1053cb:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  1053cf:	e9 9d 01 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  1053d4:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  1053d8:	48 89 85 f0 fd ff ff 	mov    %rax,-0x210(%rbp)
  1053df:	48 83 7d b8 00       	cmpq   $0x0,-0x48(%rbp)
  1053e4:	0f 85 0d 00 00 00    	jne    1053f7 <syscall_dispatch+0x1307>
  1053ea:	48 c7 45 f8 ff ff ff 	movq   $0xffffffffffffffff,-0x8(%rbp)
  1053f1:	ff
  1053f2:	e9 7a 01 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  1053f7:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  1053fe:	00
  1053ff:	e9 6d 01 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  105404:	48 83 7d b8 00       	cmpq   $0x0,-0x48(%rbp)
  105409:	0f 85 0d 00 00 00    	jne    10541c <syscall_dispatch+0x132c>
  10540f:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  105416:	00
  105417:	e9 55 01 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  10541c:	e8 ef 5c 00 00       	call   10b110 <_ZN4acos8graphics15GraphicsManager15primary_displayEv>
  105421:	48 89 85 e8 fd ff ff 	mov    %rax,-0x218(%rbp)
  105428:	48 83 bd e8 fd ff ff 	cmpq   $0x0,-0x218(%rbp)
  10542f:	00
  105430:	0f 85 0d 00 00 00    	jne    105443 <syscall_dispatch+0x1353>
  105436:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  10543d:	00
  10543e:	e9 2e 01 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  105443:	48 8b bd e8 fd ff ff 	mov    -0x218(%rbp),%rdi
  10544a:	48 8b 07             	mov    (%rdi),%rax
  10544d:	ff 50 18             	call   *0x18(%rax)
  105450:	48 89 85 e0 fd ff ff 	mov    %rax,-0x220(%rbp)
  105457:	48 83 bd e0 fd ff ff 	cmpq   $0x0,-0x220(%rbp)
  10545e:	00
  10545f:	0f 85 0d 00 00 00    	jne    105472 <syscall_dispatch+0x1382>
  105465:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  10546c:	00
  10546d:	e9 ff 00 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  105472:	48 83 3c 25 b0 67 15 	cmpq   $0x0,0x1567b0
  105479:	00 00
  10547b:	0f 85 14 00 00 00    	jne    105495 <syscall_dispatch+0x13a5>
  105481:	48 8b 45 b8          	mov    -0x48(%rbp),%rax
  105485:	48 8b 00             	mov    (%rax),%rax
  105488:	48 89 04 25 b0 67 15 	mov    %rax,0x1567b0
  10548f:	00
  105490:	e9 27 00 00 00       	jmp    1054bc <syscall_dispatch+0x13cc>
  105495:	48 8b 04 25 b0 67 15 	mov    0x1567b0,%rax
  10549c:	00
  10549d:	48 8b 4d b8          	mov    -0x48(%rbp),%rcx
  1054a1:	48 3b 01             	cmp    (%rcx),%rax
  1054a4:	0f 84 0d 00 00 00    	je     1054b7 <syscall_dispatch+0x13c7>
  1054aa:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  1054b1:	00
  1054b2:	e9 ba 00 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  1054b7:	e9 00 00 00 00       	jmp    1054bc <syscall_dispatch+0x13cc>
  1054bc:	48 b8 00 00 00 00 c0 	movabs $0xc000000000,%rax
  1054c3:	00 00 00
  1054c6:	48 89 85 d8 fd ff ff 	mov    %rax,-0x228(%rbp)
  1054cd:	48 8b bd e0 fd ff ff 	mov    -0x220(%rbp),%rdi
  1054d4:	e8 e7 96 00 00       	call   10ebc0 <_ZNK4acos8graphics11Framebuffer4baseEv>
  1054d9:	48 89 85 d0 fd ff ff 	mov    %rax,-0x230(%rbp)
  1054e0:	48 8b bd e0 fd ff ff 	mov    -0x220(%rbp),%rdi
  1054e7:	e8 54 96 00 00       	call   10eb40 <_ZNK4acos8graphics11Framebuffer4sizeEv>
  1054ec:	48 89 85 c8 fd ff ff 	mov    %rax,-0x238(%rbp)
  1054f3:	48 c7 85 c0 fd ff ff 	movq   $0x0,-0x240(%rbp)
  1054fa:	00 00 00 00
  1054fe:	48 8b 85 c0 fd ff ff 	mov    -0x240(%rbp),%rax
  105505:	48 3b 85 c8 fd ff ff 	cmp    -0x238(%rbp),%rax
  10550c:	0f 83 47 00 00 00    	jae    105559 <syscall_dispatch+0x1469>
  105512:	48 8b 45 b8          	mov    -0x48(%rbp),%rax
  105516:	48 8b 78 08          	mov    0x8(%rax),%rdi
  10551a:	48 8b b5 d8 fd ff ff 	mov    -0x228(%rbp),%rsi
  105521:	48 03 b5 c0 fd ff ff 	add    -0x240(%rbp),%rsi
  105528:	48 8b 95 d0 fd ff ff 	mov    -0x230(%rbp),%rdx
  10552f:	48 03 95 c0 fd ff ff 	add    -0x240(%rbp),%rdx
  105536:	b9 17 00 00 00       	mov    $0x17,%ecx
  10553b:	e8 00 2c 00 00       	call   108140 <_ZN4acos6memory12AddressSpace3mapEmmm>
  105540:	48 8b 85 c0 fd ff ff 	mov    -0x240(%rbp),%rax
  105547:	48 05 00 10 00 00    	add    $0x1000,%rax
  10554d:	48 89 85 c0 fd ff ff 	mov    %rax,-0x240(%rbp)
  105554:	e9 a5 ff ff ff       	jmp    1054fe <syscall_dispatch+0x140e>
  105559:	48 8b 85 d8 fd ff ff 	mov    -0x228(%rbp),%rax
  105560:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  105564:	e9 08 00 00 00       	jmp    105571 <syscall_dispatch+0x1481>
  105569:	48 c7 45 f8 ff ff ff 	movq   $0xffffffffffffffff,-0x8(%rbp)
  105570:	ff
  105571:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  105575:	48 81 c4 a0 02 00 00 	add    $0x2a0,%rsp
  10557c:	5d                   	pop    %rbp
  10557d:	c3                   	ret
  10557e:	66 90                	xchg   %ax,%ax

0000000000105580 <_ZN4acos3sys12_GLOBAL__N_110has_rightsEPNS_9scheduler7ProcessEmm>:
  105580:	55                   	push   %rbp
  105581:	48 89 e5             	mov    %rsp,%rbp
  105584:	48 83 ec 30          	sub    $0x30,%rsp
  105588:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  10558c:	48 89 75 e8          	mov    %rsi,-0x18(%rbp)
  105590:	48 89 55 e0          	mov    %rdx,-0x20(%rbp)
  105594:	48 83 7d f0 00       	cmpq   $0x0,-0x10(%rbp)
  105599:	0f 85 09 00 00 00    	jne    1055a8 <_ZN4acos3sys12_GLOBAL__N_110has_rightsEPNS_9scheduler7ProcessEmm+0x28>
  10559f:	c6 45 ff 00          	movb   $0x0,-0x1(%rbp)
  1055a3:	e9 3f 00 00 00       	jmp    1055e7 <_ZN4acos3sys12_GLOBAL__N_110has_rightsEPNS_9scheduler7ProcessEmm+0x67>
  1055a8:	48 8b 7d f0          	mov    -0x10(%rbp),%rdi
  1055ac:	48 8b 75 e8          	mov    -0x18(%rbp),%rsi
  1055b0:	e8 6b 07 00 00       	call   105d20 <_ZN4acos9scheduler7Process10get_handleEm>
  1055b5:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
  1055b9:	31 c0                	xor    %eax,%eax
  1055bb:	48 83 7d d8 00       	cmpq   $0x0,-0x28(%rbp)
  1055c0:	88 45 d7             	mov    %al,-0x29(%rbp)
  1055c3:	0f 84 16 00 00 00    	je     1055df <_ZN4acos3sys12_GLOBAL__N_110has_rightsEPNS_9scheduler7ProcessEmm+0x5f>
  1055c9:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  1055cd:	48 8b 40 10          	mov    0x10(%rax),%rax
  1055d1:	48 23 45 e0          	and    -0x20(%rbp),%rax
  1055d5:	48 3b 45 e0          	cmp    -0x20(%rbp),%rax
  1055d9:	0f 94 c0             	sete   %al
  1055dc:	88 45 d7             	mov    %al,-0x29(%rbp)
  1055df:	8a 45 d7             	mov    -0x29(%rbp),%al
  1055e2:	24 01                	and    $0x1,%al
  1055e4:	88 45 ff             	mov    %al,-0x1(%rbp)
  1055e7:	8a 45 ff             	mov    -0x1(%rbp),%al
  1055ea:	24 01                	and    $0x1,%al
  1055ec:	0f b6 c0             	movzbl %al,%eax
  1055ef:	48 83 c4 30          	add    $0x30,%rsp
  1055f3:	5d                   	pop    %rbp
  1055f4:	c3                   	ret
  1055f5:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
  1055fc:	00 00 00
  1055ff:	90                   	nop

0000000000105600 <_ZN4acos12capabilities8transferEmmm>:
  105600:	55                   	push   %rbp
  105601:	48 89 e5             	mov    %rsp,%rbp
  105604:	48 83 ec 28          	sub    $0x28,%rsp
  105608:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  10560c:	48 89 75 e8          	mov    %rsi,-0x18(%rbp)
  105610:	48 89 55 e0          	mov    %rdx,-0x20(%rbp)
  105614:	48 c7 45 d8 00 00 00 	movq   $0x0,-0x28(%rbp)
  10561b:	00
  10561c:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  105620:	48 3b 04 25 c0 67 15 	cmp    0x1567c0,%rax
  105627:	00
  105628:	0f 83 81 00 00 00    	jae    1056af <_ZN4acos12capabilities8transferEmmm+0xaf>
  10562e:	48 8b 4d d8          	mov    -0x28(%rbp),%rcx
  105632:	48 b8 d0 67 15 00 00 	movabs $0x1567d0,%rax
  105639:	00 00 00
  10563c:	48 c1 e1 05          	shl    $0x5,%rcx
  105640:	48 01 c8             	add    %rcx,%rax
  105643:	48 8b 00             	mov    (%rax),%rax
  105646:	48 3b 45 f0          	cmp    -0x10(%rbp),%rax
  10564a:	0f 85 49 00 00 00    	jne    105699 <_ZN4acos12capabilities8transferEmmm+0x99>
  105650:	48 8b 4d d8          	mov    -0x28(%rbp),%rcx
  105654:	48 b8 d0 67 15 00 00 	movabs $0x1567d0,%rax
  10565b:	00 00 00
  10565e:	48 c1 e1 05          	shl    $0x5,%rcx
  105662:	48 01 c8             	add    %rcx,%rax
  105665:	48 8b 40 18          	mov    0x18(%rax),%rax
  105669:	48 3b 45 e8          	cmp    -0x18(%rbp),%rax
  10566d:	0f 85 26 00 00 00    	jne    105699 <_ZN4acos12capabilities8transferEmmm+0x99>
  105673:	48 8b 4d e0          	mov    -0x20(%rbp),%rcx
  105677:	48 8b 55 d8          	mov    -0x28(%rbp),%rdx
  10567b:	48 b8 d0 67 15 00 00 	movabs $0x1567d0,%rax
  105682:	00 00 00
  105685:	48 c1 e2 05          	shl    $0x5,%rdx
  105689:	48 01 d0             	add    %rdx,%rax
  10568c:	48 89 48 18          	mov    %rcx,0x18(%rax)
  105690:	c6 45 ff 01          	movb   $0x1,-0x1(%rbp)
  105694:	e9 1a 00 00 00       	jmp    1056b3 <_ZN4acos12capabilities8transferEmmm+0xb3>
  105699:	e9 00 00 00 00       	jmp    10569e <_ZN4acos12capabilities8transferEmmm+0x9e>
  10569e:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  1056a2:	48 83 c0 01          	add    $0x1,%rax
  1056a6:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
  1056aa:	e9 6d ff ff ff       	jmp    10561c <_ZN4acos12capabilities8transferEmmm+0x1c>
  1056af:	c6 45 ff 00          	movb   $0x0,-0x1(%rbp)
  1056b3:	8a 45 ff             	mov    -0x1(%rbp),%al
  1056b6:	24 01                	and    $0x1,%al
  1056b8:	0f b6 c0             	movzbl %al,%eax
  1056bb:	48 83 c4 28          	add    $0x28,%rsp
  1056bf:	5d                   	pop    %rbp
  1056c0:	c3                   	ret
  1056c1:	66 66 66 66 66 66 2e 	data16 data16 data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
  1056c8:	0f 1f 84 00 00 00 00
  1056cf:	00

00000000001056d0 <_ZN4acos12capabilities6revokeEmm>:
  1056d0:	55                   	push   %rbp
  1056d1:	48 89 e5             	mov    %rsp,%rbp
  1056d4:	48 83 ec 20          	sub    $0x20,%rsp
  1056d8:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  1056dc:	48 89 75 e8          	mov    %rsi,-0x18(%rbp)
  1056e0:	48 c7 45 e0 00 00 00 	movq   $0x0,-0x20(%rbp)
  1056e7:	00
  1056e8:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  1056ec:	48 3b 04 25 c0 67 15 	cmp    0x1567c0,%rax
  1056f3:	00
  1056f4:	0f 83 80 00 00 00    	jae    10577a <_ZN4acos12capabilities6revokeEmm+0xaa>
  1056fa:	48 8b 4d e0          	mov    -0x20(%rbp),%rcx
  1056fe:	48 b8 d0 67 15 00 00 	movabs $0x1567d0,%rax
  105705:	00 00 00
  105708:	48 c1 e1 05          	shl    $0x5,%rcx
  10570c:	48 01 c8             	add    %rcx,%rax
  10570f:	48 8b 00             	mov    (%rax),%rax
  105712:	48 3b 45 f0          	cmp    -0x10(%rbp),%rax
  105716:	0f 85 48 00 00 00    	jne    105764 <_ZN4acos12capabilities6revokeEmm+0x94>
  10571c:	48 8b 4d e0          	mov    -0x20(%rbp),%rcx
  105720:	48 b8 d0 67 15 00 00 	movabs $0x1567d0,%rax
  105727:	00 00 00
  10572a:	48 c1 e1 05          	shl    $0x5,%rcx
  10572e:	48 01 c8             	add    %rcx,%rax
  105731:	48 8b 40 18          	mov    0x18(%rax),%rax
  105735:	48 3b 45 e8          	cmp    -0x18(%rbp),%rax
  105739:	0f 85 25 00 00 00    	jne    105764 <_ZN4acos12capabilities6revokeEmm+0x94>
  10573f:	48 8b 4d e0          	mov    -0x20(%rbp),%rcx
  105743:	48 b8 d0 67 15 00 00 	movabs $0x1567d0,%rax
  10574a:	00 00 00
  10574d:	48 c1 e1 05          	shl    $0x5,%rcx
  105751:	48 01 c8             	add    %rcx,%rax
  105754:	48 c7 00 00 00 00 00 	movq   $0x0,(%rax)
  10575b:	c6 45 ff 01          	movb   $0x1,-0x1(%rbp)
  10575f:	e9 1a 00 00 00       	jmp    10577e <_ZN4acos12capabilities6revokeEmm+0xae>
  105764:	e9 00 00 00 00       	jmp    105769 <_ZN4acos12capabilities6revokeEmm+0x99>
  105769:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  10576d:	48 83 c0 01          	add    $0x1,%rax
  105771:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  105775:	e9 6e ff ff ff       	jmp    1056e8 <_ZN4acos12capabilities6revokeEmm+0x18>
  10577a:	c6 45 ff 00          	movb   $0x0,-0x1(%rbp)
  10577e:	8a 45 ff             	mov    -0x1(%rbp),%al
  105781:	24 01                	and    $0x1,%al
  105783:	0f b6 c0             	movzbl %al,%eax
  105786:	48 83 c4 20          	add    $0x20,%rsp
  10578a:	5d                   	pop    %rbp
  10578b:	c3                   	ret
  10578c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000105790 <_ZN4acos8security6Domain6createENS0_10DomainTypeE>:
  105790:	55                   	push   %rbp
  105791:	48 89 e5             	mov    %rsp,%rbp
  105794:	48 83 ec 20          	sub    $0x20,%rsp
  105798:	89 7d f4             	mov    %edi,-0xc(%rbp)
  10579b:	48 83 3c 25 d0 e9 15 	cmpq   $0x20,0x15e9d0
  1057a2:	00 20
  1057a4:	0f 82 0d 00 00 00    	jb     1057b7 <_ZN4acos8security6Domain6createENS0_10DomainTypeE+0x27>
  1057aa:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  1057b1:	00
  1057b2:	e9 93 00 00 00       	jmp    10584a <_ZN4acos8security6Domain6createENS0_10DomainTypeE+0xba>
  1057b7:	48 8b 0c 25 d0 e9 15 	mov    0x15e9d0,%rcx
  1057be:	00
  1057bf:	48 89 c8             	mov    %rcx,%rax
  1057c2:	48 83 c0 01          	add    $0x1,%rax
  1057c6:	48 89 04 25 d0 e9 15 	mov    %rax,0x15e9d0
  1057cd:	00
  1057ce:	48 b8 d0 e7 15 00 00 	movabs $0x15e7d0,%rax
  1057d5:	00 00 00
  1057d8:	48 c1 e1 04          	shl    $0x4,%rcx
  1057dc:	48 01 c8             	add    %rcx,%rax
  1057df:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
  1057e3:	48 8b 0c 25 70 fc 10 	mov    0x10fc70,%rcx
  1057ea:	00
  1057eb:	48 89 c8             	mov    %rcx,%rax
  1057ee:	48 83 c0 01          	add    $0x1,%rax
  1057f2:	48 89 04 25 70 fc 10 	mov    %rax,0x10fc70
  1057f9:	00
  1057fa:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  1057fe:	48 89 08             	mov    %rcx,(%rax)
  105801:	8b 4d f4             	mov    -0xc(%rbp),%ecx
  105804:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  105808:	89 48 08             	mov    %ecx,0x8(%rax)
  10580b:	b0 01                	mov    $0x1,%al
  10580d:	83 7d f4 00          	cmpl   $0x0,-0xc(%rbp)
  105811:	88 45 e7             	mov    %al,-0x19(%rbp)
  105814:	0f 84 0a 00 00 00    	je     105824 <_ZN4acos8security6Domain6createENS0_10DomainTypeE+0x94>
  10581a:	83 7d f4 02          	cmpl   $0x2,-0xc(%rbp)
  10581e:	0f 94 c0             	sete   %al
  105821:	88 45 e7             	mov    %al,-0x19(%rbp)
  105824:	8a 4d e7             	mov    -0x19(%rbp),%cl
  105827:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  10582b:	80 e1 01             	and    $0x1,%cl
  10582e:	88 48 0c             	mov    %cl,0xc(%rax)
  105831:	83 7d f4 00          	cmpl   $0x0,-0xc(%rbp)
  105835:	0f 94 c1             	sete   %cl
  105838:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  10583c:	80 e1 01             	and    $0x1,%cl
  10583f:	88 48 0d             	mov    %cl,0xd(%rax)
  105842:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  105846:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  10584a:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10584e:	48 83 c4 20          	add    $0x20,%rsp
  105852:	5d                   	pop    %rbp
  105853:	c3                   	ret
  105854:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
  10585b:	00 00 00
  10585e:	66 90                	xchg   %ax,%ax

0000000000105860 <_ZN4acos9scheduler7Process6createEv>:
  105860:	55                   	push   %rbp
  105861:	48 89 e5             	mov    %rsp,%rbp
  105864:	48 83 ec 50          	sub    $0x50,%rsp
  105868:	bf 18 3b 00 00       	mov    $0x3b18,%edi
  10586d:	e8 de 2e 00 00       	call   108750 <_ZN4acos6memory7kmallocEm>
  105872:	48 89 45 f0          	mov    %rax,-0x10(%rbp)
  105876:	48 83 7d f0 00       	cmpq   $0x0,-0x10(%rbp)
  10587b:	0f 85 0d 00 00 00    	jne    10588e <_ZN4acos9scheduler7Process6createEv+0x2e>
  105881:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  105888:	00
  105889:	e9 c2 01 00 00       	jmp    105a50 <_ZN4acos9scheduler7Process6createEv+0x1f0>
  10588e:	48 8b 7d f0          	mov    -0x10(%rbp),%rdi
  105892:	31 f6                	xor    %esi,%esi
  105894:	ba 18 3b 00 00       	mov    $0x3b18,%edx
  105899:	e8 d2 a7 ff ff       	call   100070 <memset>
  10589e:	48 8b 0c 25 78 fc 10 	mov    0x10fc78,%rcx
  1058a5:	00
  1058a6:	48 89 c8             	mov    %rcx,%rax
  1058a9:	48 83 c0 01          	add    $0x1,%rax
  1058ad:	48 89 04 25 78 fc 10 	mov    %rax,0x10fc78
  1058b4:	00
  1058b5:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  1058b9:	48 89 08             	mov    %rcx,(%rax)
  1058bc:	bf 10 00 00 00       	mov    $0x10,%edi
  1058c1:	e8 8a 2e 00 00       	call   108750 <_ZN4acos6memory7kmallocEm>
  1058c6:	48 89 c1             	mov    %rax,%rcx
  1058c9:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  1058cd:	48 89 48 08          	mov    %rcx,0x8(%rax)
  1058d1:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  1058d5:	48 8b 78 08          	mov    0x8(%rax),%rdi
  1058d9:	e8 c2 24 00 00       	call   107da0 <_ZN4acos6memory12AddressSpaceC1Ev>
  1058de:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  1058e2:	48 c7 80 10 3b 00 00 	movq   $0x0,0x3b10(%rax)
  1058e9:	00 00 00 00
  1058ed:	48 c7 45 e8 00 00 00 	movq   $0x0,-0x18(%rbp)
  1058f4:	00
  1058f5:	48 81 7d e8 00 01 00 	cmpq   $0x100,-0x18(%rbp)
  1058fc:	00
  1058fd:	0f 83 a0 00 00 00    	jae    1059a3 <_ZN4acos9scheduler7Process6createEv+0x143>
  105903:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  105907:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  10590b:	48 c7 44 c8 10 00 00 	movq   $0x0,0x10(%rax,%rcx,8)
  105912:	00 00
  105914:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  105918:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  10591c:	48 c7 84 c8 10 08 00 	movq   $0x0,0x810(%rax,%rcx,8)
  105923:	00 00 00 00 00
  105928:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10592c:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  105930:	48 c7 84 c8 10 10 00 	movq   $0x0,0x1010(%rax,%rcx,8)
  105937:	00 00 00 00 00
  10593c:	c7 45 c8 00 00 00 00 	movl   $0x0,-0x38(%rbp)
  105943:	48 c7 45 d0 00 00 00 	movq   $0x0,-0x30(%rbp)
  10594a:	00
  10594b:	48 c7 45 d8 00 00 00 	movq   $0x0,-0x28(%rbp)
  105952:	00
  105953:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  105957:	48 8b 00             	mov    (%rax),%rax
  10595a:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  10595e:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  105962:	48 05 10 18 00 00    	add    $0x1810,%rax
  105968:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  10596c:	48 c1 e1 05          	shl    $0x5,%rcx
  105970:	48 01 c8             	add    %rcx,%rax
  105973:	48 8b 4d c8          	mov    -0x38(%rbp),%rcx
  105977:	48 89 08             	mov    %rcx,(%rax)
  10597a:	48 8b 4d d0          	mov    -0x30(%rbp),%rcx
  10597e:	48 89 48 08          	mov    %rcx,0x8(%rax)
  105982:	48 8b 4d d8          	mov    -0x28(%rbp),%rcx
  105986:	48 89 48 10          	mov    %rcx,0x10(%rax)
  10598a:	48 8b 4d e0          	mov    -0x20(%rbp),%rcx
  10598e:	48 89 48 18          	mov    %rcx,0x18(%rax)
  105992:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  105996:	48 83 c0 01          	add    $0x1,%rax
  10599a:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
  10599e:	e9 52 ff ff ff       	jmp    1058f5 <_ZN4acos9scheduler7Process6createEv+0x95>
  1059a3:	48 c7 45 c0 00 00 00 	movq   $0x0,-0x40(%rbp)
  1059aa:	00
  1059ab:	48 83 7d c0 40       	cmpq   $0x40,-0x40(%rbp)
  1059b0:	0f 83 25 00 00 00    	jae    1059db <_ZN4acos9scheduler7Process6createEv+0x17b>
  1059b6:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  1059ba:	48 8b 4d c0          	mov    -0x40(%rbp),%rcx
  1059be:	48 c7 84 c8 10 38 00 	movq   $0x0,0x3810(%rax,%rcx,8)
  1059c5:	00 00 00 00 00
  1059ca:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  1059ce:	48 83 c0 01          	add    $0x1,%rax
  1059d2:	48 89 45 c0          	mov    %rax,-0x40(%rbp)
  1059d6:	e9 d0 ff ff ff       	jmp    1059ab <_ZN4acos9scheduler7Process6createEv+0x14b>
  1059db:	48 c7 45 b8 00 00 00 	movq   $0x0,-0x48(%rbp)
  1059e2:	00
  1059e3:	48 83 7d b8 20       	cmpq   $0x20,-0x48(%rbp)
  1059e8:	0f 83 25 00 00 00    	jae    105a13 <_ZN4acos9scheduler7Process6createEv+0x1b3>
  1059ee:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  1059f2:	48 8b 4d b8          	mov    -0x48(%rbp),%rcx
  1059f6:	48 c7 84 c8 10 3a 00 	movq   $0x0,0x3a10(%rax,%rcx,8)
  1059fd:	00 00 00 00 00
  105a02:	48 8b 45 b8          	mov    -0x48(%rbp),%rax
  105a06:	48 83 c0 01          	add    $0x1,%rax
  105a0a:	48 89 45 b8          	mov    %rax,-0x48(%rbp)
  105a0e:	e9 d0 ff ff ff       	jmp    1059e3 <_ZN4acos9scheduler7Process6createEv+0x183>
  105a13:	48 81 3c 25 e0 e9 15 	cmpq   $0x100,0x15e9e0
  105a1a:	00 00 01 00 00
  105a1f:	0f 83 23 00 00 00    	jae    105a48 <_ZN4acos9scheduler7Process6createEv+0x1e8>
  105a25:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
  105a29:	48 8b 04 25 e0 e9 15 	mov    0x15e9e0,%rax
  105a30:	00
  105a31:	48 89 c2             	mov    %rax,%rdx
  105a34:	48 83 c2 01          	add    $0x1,%rdx
  105a38:	48 89 14 25 e0 e9 15 	mov    %rdx,0x15e9e0
  105a3f:	00
  105a40:	48 89 0c c5 f0 e9 15 	mov    %rcx,0x15e9f0(,%rax,8)
  105a47:	00
  105a48:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  105a4c:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  105a50:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  105a54:	48 83 c4 50          	add    $0x50,%rsp
  105a58:	5d                   	pop    %rbp
  105a59:	c3                   	ret
  105a5a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000105a60 <_ZN4acos9scheduler7Process17register_resourceENS0_12ResourceKindEPvm>:
  105a60:	55                   	push   %rbp
  105a61:	48 89 e5             	mov    %rsp,%rbp
  105a64:	48 83 ec 58          	sub    $0x58,%rsp
  105a68:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  105a6c:	89 75 ec             	mov    %esi,-0x14(%rbp)
  105a6f:	48 89 55 e0          	mov    %rdx,-0x20(%rbp)
  105a73:	48 89 4d d8          	mov    %rcx,-0x28(%rbp)
  105a77:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  105a7b:	48 89 45 a8          	mov    %rax,-0x58(%rbp)
  105a7f:	83 7d ec 00          	cmpl   $0x0,-0x14(%rbp)
  105a83:	0f 84 0b 00 00 00    	je     105a94 <_ZN4acos9scheduler7Process17register_resourceENS0_12ResourceKindEPvm+0x34>
  105a89:	48 83 7d e0 00       	cmpq   $0x0,-0x20(%rbp)
  105a8e:	0f 85 0d 00 00 00    	jne    105aa1 <_ZN4acos9scheduler7Process17register_resourceENS0_12ResourceKindEPvm+0x41>
  105a94:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  105a9b:	00
  105a9c:	e9 b0 00 00 00       	jmp    105b51 <_ZN4acos9scheduler7Process17register_resourceENS0_12ResourceKindEPvm+0xf1>
  105aa1:	48 c7 45 d0 01 00 00 	movq   $0x1,-0x30(%rbp)
  105aa8:	00
  105aa9:	48 81 7d d0 00 01 00 	cmpq   $0x100,-0x30(%rbp)
  105ab0:	00
  105ab1:	0f 83 92 00 00 00    	jae    105b49 <_ZN4acos9scheduler7Process17register_resourceENS0_12ResourceKindEPvm+0xe9>
  105ab7:	48 8b 45 a8          	mov    -0x58(%rbp),%rax
  105abb:	48 05 10 18 00 00    	add    $0x1810,%rax
  105ac1:	48 8b 4d d0          	mov    -0x30(%rbp),%rcx
  105ac5:	48 c1 e1 05          	shl    $0x5,%rcx
  105ac9:	48 01 c8             	add    %rcx,%rax
  105acc:	83 38 00             	cmpl   $0x0,(%rax)
  105acf:	0f 85 5e 00 00 00    	jne    105b33 <_ZN4acos9scheduler7Process17register_resourceENS0_12ResourceKindEPvm+0xd3>
  105ad5:	48 8b 45 a8          	mov    -0x58(%rbp),%rax
  105ad9:	8b 4d ec             	mov    -0x14(%rbp),%ecx
  105adc:	89 4d b0             	mov    %ecx,-0x50(%rbp)
  105adf:	48 8b 4d e0          	mov    -0x20(%rbp),%rcx
  105ae3:	48 89 4d b8          	mov    %rcx,-0x48(%rbp)
  105ae7:	48 8b 4d d8          	mov    -0x28(%rbp),%rcx
  105aeb:	48 89 4d c0          	mov    %rcx,-0x40(%rbp)
  105aef:	48 8b 08             	mov    (%rax),%rcx
  105af2:	48 89 4d c8          	mov    %rcx,-0x38(%rbp)
  105af6:	48 05 10 18 00 00    	add    $0x1810,%rax
  105afc:	48 8b 4d d0          	mov    -0x30(%rbp),%rcx
  105b00:	48 c1 e1 05          	shl    $0x5,%rcx
  105b04:	48 01 c8             	add    %rcx,%rax
  105b07:	48 8b 4d b0          	mov    -0x50(%rbp),%rcx
  105b0b:	48 89 08             	mov    %rcx,(%rax)
  105b0e:	48 8b 4d b8          	mov    -0x48(%rbp),%rcx
  105b12:	48 89 48 08          	mov    %rcx,0x8(%rax)
  105b16:	48 8b 4d c0          	mov    -0x40(%rbp),%rcx
  105b1a:	48 89 48 10          	mov    %rcx,0x10(%rax)
  105b1e:	48 8b 4d c8          	mov    -0x38(%rbp),%rcx
  105b22:	48 89 48 18          	mov    %rcx,0x18(%rax)
  105b26:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  105b2a:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  105b2e:	e9 1e 00 00 00       	jmp    105b51 <_ZN4acos9scheduler7Process17register_resourceENS0_12ResourceKindEPvm+0xf1>
  105b33:	e9 00 00 00 00       	jmp    105b38 <_ZN4acos9scheduler7Process17register_resourceENS0_12ResourceKindEPvm+0xd8>
  105b38:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  105b3c:	48 83 c0 01          	add    $0x1,%rax
  105b40:	48 89 45 d0          	mov    %rax,-0x30(%rbp)
  105b44:	e9 60 ff ff ff       	jmp    105aa9 <_ZN4acos9scheduler7Process17register_resourceENS0_12ResourceKindEPvm+0x49>
  105b49:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  105b50:	00
  105b51:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  105b55:	48 83 c4 58          	add    $0x58,%rsp
  105b59:	5d                   	pop    %rbp
  105b5a:	c3                   	ret
  105b5b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000105b60 <_ZN4acos9scheduler7Process12close_handleEm>:
  105b60:	55                   	push   %rbp
  105b61:	48 89 e5             	mov    %rsp,%rbp
  105b64:	48 83 ec 40          	sub    $0x40,%rsp
  105b68:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  105b6c:	48 89 75 e8          	mov    %rsi,-0x18(%rbp)
  105b70:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  105b74:	48 89 45 c0          	mov    %rax,-0x40(%rbp)
  105b78:	48 83 7d e8 00       	cmpq   $0x0,-0x18(%rbp)
  105b7d:	0f 84 2c 00 00 00    	je     105baf <_ZN4acos9scheduler7Process12close_handleEm+0x4f>
  105b83:	48 81 7d e8 00 01 00 	cmpq   $0x100,-0x18(%rbp)
  105b8a:	00
  105b8b:	0f 83 1e 00 00 00    	jae    105baf <_ZN4acos9scheduler7Process12close_handleEm+0x4f>
  105b91:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  105b95:	48 05 10 18 00 00    	add    $0x1810,%rax
  105b9b:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  105b9f:	48 c1 e1 05          	shl    $0x5,%rcx
  105ba3:	48 01 c8             	add    %rcx,%rax
  105ba6:	83 38 00             	cmpl   $0x0,(%rax)
  105ba9:	0f 85 09 00 00 00    	jne    105bb8 <_ZN4acos9scheduler7Process12close_handleEm+0x58>
  105baf:	c6 45 ff 00          	movb   $0x0,-0x1(%rbp)
  105bb3:	e9 87 00 00 00       	jmp    105c3f <_ZN4acos9scheduler7Process12close_handleEm+0xdf>
  105bb8:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  105bbc:	c7 45 c8 00 00 00 00 	movl   $0x0,-0x38(%rbp)
  105bc3:	48 c7 45 d0 00 00 00 	movq   $0x0,-0x30(%rbp)
  105bca:	00
  105bcb:	48 c7 45 d8 00 00 00 	movq   $0x0,-0x28(%rbp)
  105bd2:	00
  105bd3:	48 8b 08             	mov    (%rax),%rcx
  105bd6:	48 89 4d e0          	mov    %rcx,-0x20(%rbp)
  105bda:	48 89 c1             	mov    %rax,%rcx
  105bdd:	48 81 c1 10 18 00 00 	add    $0x1810,%rcx
  105be4:	48 8b 55 e8          	mov    -0x18(%rbp),%rdx
  105be8:	48 c1 e2 05          	shl    $0x5,%rdx
  105bec:	48 01 d1             	add    %rdx,%rcx
  105bef:	48 8b 55 c8          	mov    -0x38(%rbp),%rdx
  105bf3:	48 89 11             	mov    %rdx,(%rcx)
  105bf6:	48 8b 55 d0          	mov    -0x30(%rbp),%rdx
  105bfa:	48 89 51 08          	mov    %rdx,0x8(%rcx)
  105bfe:	48 8b 55 d8          	mov    -0x28(%rbp),%rdx
  105c02:	48 89 51 10          	mov    %rdx,0x10(%rcx)
  105c06:	48 8b 55 e0          	mov    -0x20(%rbp),%rdx
  105c0a:	48 89 51 18          	mov    %rdx,0x18(%rcx)
  105c0e:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  105c12:	48 c7 44 c8 10 00 00 	movq   $0x0,0x10(%rax,%rcx,8)
  105c19:	00 00
  105c1b:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  105c1f:	48 c7 84 c8 10 08 00 	movq   $0x0,0x810(%rax,%rcx,8)
  105c26:	00 00 00 00 00
  105c2b:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  105c2f:	48 c7 84 c8 10 10 00 	movq   $0x0,0x1010(%rax,%rcx,8)
  105c36:	00 00 00 00 00
  105c3b:	c6 45 ff 01          	movb   $0x1,-0x1(%rbp)
  105c3f:	8a 45 ff             	mov    -0x1(%rbp),%al
  105c42:	24 01                	and    $0x1,%al
  105c44:	0f b6 c0             	movzbl %al,%eax
  105c47:	48 83 c4 40          	add    $0x40,%rsp
  105c4b:	5d                   	pop    %rbp
  105c4c:	c3                   	ret
  105c4d:	0f 1f 00             	nopl   (%rax)

0000000000105c50 <_ZN4acos9scheduler7Process16duplicate_handleEmmPm>:
  105c50:	55                   	push   %rbp
  105c51:	48 89 e5             	mov    %rsp,%rbp
  105c54:	48 83 ec 40          	sub    $0x40,%rsp
  105c58:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  105c5c:	48 89 75 e8          	mov    %rsi,-0x18(%rbp)
  105c60:	48 89 55 e0          	mov    %rdx,-0x20(%rbp)
  105c64:	48 89 4d d8          	mov    %rcx,-0x28(%rbp)
  105c68:	48 8b 7d f0          	mov    -0x10(%rbp),%rdi
  105c6c:	48 89 7d c0          	mov    %rdi,-0x40(%rbp)
  105c70:	48 8b 75 e8          	mov    -0x18(%rbp),%rsi
  105c74:	e8 a7 00 00 00       	call   105d20 <_ZN4acos9scheduler7Process10get_handleEm>
  105c79:	48 89 45 d0          	mov    %rax,-0x30(%rbp)
  105c7d:	48 83 7d d0 00       	cmpq   $0x0,-0x30(%rbp)
  105c82:	0f 84 3e 00 00 00    	je     105cc6 <_ZN4acos9scheduler7Process16duplicate_handleEmmPm+0x76>
  105c88:	48 83 7d d8 00       	cmpq   $0x0,-0x28(%rbp)
  105c8d:	0f 84 33 00 00 00    	je     105cc6 <_ZN4acos9scheduler7Process16duplicate_handleEmmPm+0x76>
  105c93:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  105c97:	48 8b 4d d0          	mov    -0x30(%rbp),%rcx
  105c9b:	48 8b 49 10          	mov    0x10(%rcx),%rcx
  105c9f:	48 83 f1 ff          	xor    $0xffffffffffffffff,%rcx
  105ca3:	48 21 c8             	and    %rcx,%rax
  105ca6:	48 83 f8 00          	cmp    $0x0,%rax
  105caa:	0f 85 16 00 00 00    	jne    105cc6 <_ZN4acos9scheduler7Process16duplicate_handleEmmPm+0x76>
  105cb0:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  105cb4:	48 8b 40 10          	mov    0x10(%rax),%rax
  105cb8:	48 83 e0 20          	and    $0x20,%rax
  105cbc:	48 83 f8 00          	cmp    $0x0,%rax
  105cc0:	0f 85 09 00 00 00    	jne    105ccf <_ZN4acos9scheduler7Process16duplicate_handleEmmPm+0x7f>
  105cc6:	c6 45 ff 00          	movb   $0x0,-0x1(%rbp)
  105cca:	e9 42 00 00 00       	jmp    105d11 <_ZN4acos9scheduler7Process16duplicate_handleEmmPm+0xc1>
  105ccf:	48 8b 7d c0          	mov    -0x40(%rbp),%rdi
  105cd3:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  105cd7:	8b 30                	mov    (%rax),%esi
  105cd9:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  105cdd:	48 8b 50 08          	mov    0x8(%rax),%rdx
  105ce1:	48 8b 4d e0          	mov    -0x20(%rbp),%rcx
  105ce5:	e8 76 fd ff ff       	call   105a60 <_ZN4acos9scheduler7Process17register_resourceENS0_12ResourceKindEPvm>
  105cea:	48 89 45 c8          	mov    %rax,-0x38(%rbp)
  105cee:	48 83 7d c8 00       	cmpq   $0x0,-0x38(%rbp)
  105cf3:	0f 85 09 00 00 00    	jne    105d02 <_ZN4acos9scheduler7Process16duplicate_handleEmmPm+0xb2>
  105cf9:	c6 45 ff 00          	movb   $0x0,-0x1(%rbp)
  105cfd:	e9 0f 00 00 00       	jmp    105d11 <_ZN4acos9scheduler7Process16duplicate_handleEmmPm+0xc1>
  105d02:	48 8b 4d c8          	mov    -0x38(%rbp),%rcx
  105d06:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  105d0a:	48 89 08             	mov    %rcx,(%rax)
  105d0d:	c6 45 ff 01          	movb   $0x1,-0x1(%rbp)
  105d11:	8a 45 ff             	mov    -0x1(%rbp),%al
  105d14:	24 01                	and    $0x1,%al
  105d16:	0f b6 c0             	movzbl %al,%eax
  105d19:	48 83 c4 40          	add    $0x40,%rsp
  105d1d:	5d                   	pop    %rbp
  105d1e:	c3                   	ret
  105d1f:	90                   	nop

0000000000105d20 <_ZN4acos9scheduler7Process10get_handleEm>:
  105d20:	55                   	push   %rbp
  105d21:	48 89 e5             	mov    %rsp,%rbp
  105d24:	48 83 ec 20          	sub    $0x20,%rsp
  105d28:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  105d2c:	48 89 75 e8          	mov    %rsi,-0x18(%rbp)
  105d30:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  105d34:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  105d38:	48 83 7d e8 00       	cmpq   $0x0,-0x18(%rbp)
  105d3d:	0f 84 2c 00 00 00    	je     105d6f <_ZN4acos9scheduler7Process10get_handleEm+0x4f>
  105d43:	48 81 7d e8 00 01 00 	cmpq   $0x100,-0x18(%rbp)
  105d4a:	00
  105d4b:	0f 83 1e 00 00 00    	jae    105d6f <_ZN4acos9scheduler7Process10get_handleEm+0x4f>
  105d51:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  105d55:	48 05 10 18 00 00    	add    $0x1810,%rax
  105d5b:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  105d5f:	48 c1 e1 05          	shl    $0x5,%rcx
  105d63:	48 01 c8             	add    %rcx,%rax
  105d66:	83 38 00             	cmpl   $0x0,(%rax)
  105d69:	0f 85 0d 00 00 00    	jne    105d7c <_ZN4acos9scheduler7Process10get_handleEm+0x5c>
  105d6f:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  105d76:	00
  105d77:	e9 19 00 00 00       	jmp    105d95 <_ZN4acos9scheduler7Process10get_handleEm+0x75>
  105d7c:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  105d80:	48 05 10 18 00 00    	add    $0x1810,%rax
  105d86:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  105d8a:	48 c1 e1 05          	shl    $0x5,%rcx
  105d8e:	48 01 c8             	add    %rcx,%rax
  105d91:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  105d95:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  105d99:	48 83 c4 20          	add    $0x20,%rsp
  105d9d:	5d                   	pop    %rbp
  105d9e:	c3                   	ret
  105d9f:	90                   	nop

0000000000105da0 <_ZN4acos9scheduler7Process15transfer_handleEmRS1_Pm>:
  105da0:	55                   	push   %rbp
  105da1:	48 89 e5             	mov    %rsp,%rbp
  105da4:	48 83 ec 40          	sub    $0x40,%rsp
  105da8:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  105dac:	48 89 75 e8          	mov    %rsi,-0x18(%rbp)
  105db0:	48 89 55 e0          	mov    %rdx,-0x20(%rbp)
  105db4:	48 89 4d d8          	mov    %rcx,-0x28(%rbp)
  105db8:	48 8b 7d f0          	mov    -0x10(%rbp),%rdi
  105dbc:	48 89 7d c0          	mov    %rdi,-0x40(%rbp)
  105dc0:	48 8b 75 e8          	mov    -0x18(%rbp),%rsi
  105dc4:	e8 57 ff ff ff       	call   105d20 <_ZN4acos9scheduler7Process10get_handleEm>
  105dc9:	48 89 45 d0          	mov    %rax,-0x30(%rbp)
  105dcd:	48 83 7d d0 00       	cmpq   $0x0,-0x30(%rbp)
  105dd2:	0f 84 21 00 00 00    	je     105df9 <_ZN4acos9scheduler7Process15transfer_handleEmRS1_Pm+0x59>
  105dd8:	48 83 7d d8 00       	cmpq   $0x0,-0x28(%rbp)
  105ddd:	0f 84 16 00 00 00    	je     105df9 <_ZN4acos9scheduler7Process15transfer_handleEmRS1_Pm+0x59>
  105de3:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  105de7:	48 8b 40 10          	mov    0x10(%rax),%rax
  105deb:	48 83 e0 10          	and    $0x10,%rax
  105def:	48 83 f8 00          	cmp    $0x0,%rax
  105df3:	0f 85 09 00 00 00    	jne    105e02 <_ZN4acos9scheduler7Process15transfer_handleEmRS1_Pm+0x62>
  105df9:	c6 45 ff 00          	movb   $0x0,-0x1(%rbp)
  105dfd:	e9 53 00 00 00       	jmp    105e55 <_ZN4acos9scheduler7Process15transfer_handleEmRS1_Pm+0xb5>
  105e02:	48 8b 7d e0          	mov    -0x20(%rbp),%rdi
  105e06:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  105e0a:	8b 30                	mov    (%rax),%esi
  105e0c:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  105e10:	48 8b 50 08          	mov    0x8(%rax),%rdx
  105e14:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  105e18:	48 8b 48 10          	mov    0x10(%rax),%rcx
  105e1c:	e8 3f fc ff ff       	call   105a60 <_ZN4acos9scheduler7Process17register_resourceENS0_12ResourceKindEPvm>
  105e21:	48 89 45 c8          	mov    %rax,-0x38(%rbp)
  105e25:	48 83 7d c8 00       	cmpq   $0x0,-0x38(%rbp)
  105e2a:	0f 85 09 00 00 00    	jne    105e39 <_ZN4acos9scheduler7Process15transfer_handleEmRS1_Pm+0x99>
  105e30:	c6 45 ff 00          	movb   $0x0,-0x1(%rbp)
  105e34:	e9 1c 00 00 00       	jmp    105e55 <_ZN4acos9scheduler7Process15transfer_handleEmRS1_Pm+0xb5>
  105e39:	48 8b 7d c0          	mov    -0x40(%rbp),%rdi
  105e3d:	48 8b 75 e8          	mov    -0x18(%rbp),%rsi
  105e41:	e8 1a fd ff ff       	call   105b60 <_ZN4acos9scheduler7Process12close_handleEm>
  105e46:	48 8b 4d c8          	mov    -0x38(%rbp),%rcx
  105e4a:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  105e4e:	48 89 08             	mov    %rcx,(%rax)
  105e51:	c6 45 ff 01          	movb   $0x1,-0x1(%rbp)
  105e55:	8a 45 ff             	mov    -0x1(%rbp),%al
  105e58:	24 01                	and    $0x1,%al
  105e5a:	0f b6 c0             	movzbl %al,%eax
  105e5d:	48 83 c4 40          	add    $0x40,%rsp
  105e61:	5d                   	pop    %rbp
  105e62:	c3                   	ret
  105e63:	66 66 66 66 2e 0f 1f 	data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
  105e6a:	84 00 00 00 00 00

0000000000105e70 <_ZNK4acos9scheduler7Process10get_handleEm>:
  105e70:	55                   	push   %rbp
  105e71:	48 89 e5             	mov    %rsp,%rbp
  105e74:	48 83 ec 20          	sub    $0x20,%rsp
  105e78:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  105e7c:	48 89 75 e8          	mov    %rsi,-0x18(%rbp)
  105e80:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  105e84:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  105e88:	48 83 7d e8 00       	cmpq   $0x0,-0x18(%rbp)
  105e8d:	0f 84 2c 00 00 00    	je     105ebf <_ZNK4acos9scheduler7Process10get_handleEm+0x4f>
  105e93:	48 81 7d e8 00 01 00 	cmpq   $0x100,-0x18(%rbp)
  105e9a:	00
  105e9b:	0f 83 1e 00 00 00    	jae    105ebf <_ZNK4acos9scheduler7Process10get_handleEm+0x4f>
  105ea1:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  105ea5:	48 05 10 18 00 00    	add    $0x1810,%rax
  105eab:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  105eaf:	48 c1 e1 05          	shl    $0x5,%rcx
  105eb3:	48 01 c8             	add    %rcx,%rax
  105eb6:	83 38 00             	cmpl   $0x0,(%rax)
  105eb9:	0f 85 0d 00 00 00    	jne    105ecc <_ZNK4acos9scheduler7Process10get_handleEm+0x5c>
  105ebf:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  105ec6:	00
  105ec7:	e9 19 00 00 00       	jmp    105ee5 <_ZNK4acos9scheduler7Process10get_handleEm+0x75>
  105ecc:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  105ed0:	48 05 10 18 00 00    	add    $0x1810,%rax
  105ed6:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  105eda:	48 c1 e1 05          	shl    $0x5,%rcx
  105ede:	48 01 c8             	add    %rcx,%rax
  105ee1:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  105ee5:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  105ee9:	48 83 c4 20          	add    $0x20,%rsp
  105eed:	5d                   	pop    %rbp
  105eee:	c3                   	ret
  105eef:	90                   	nop

0000000000105ef0 <_ZN4acos9scheduler7Process16register_processEPS1_m>:
  105ef0:	55                   	push   %rbp
  105ef1:	48 89 e5             	mov    %rsp,%rbp
  105ef4:	48 83 ec 20          	sub    $0x20,%rsp
  105ef8:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  105efc:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  105f00:	48 89 55 e8          	mov    %rdx,-0x18(%rbp)
  105f04:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  105f08:	48 8b 55 f0          	mov    -0x10(%rbp),%rdx
  105f0c:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  105f10:	be 01 00 00 00       	mov    $0x1,%esi
  105f15:	e8 46 fb ff ff       	call   105a60 <_ZN4acos9scheduler7Process17register_resourceENS0_12ResourceKindEPvm>
  105f1a:	48 83 c4 20          	add    $0x20,%rsp
  105f1e:	5d                   	pop    %rbp
  105f1f:	c3                   	ret

0000000000105f20 <_ZN4acos9scheduler7Process15register_threadEPNS0_6ThreadEm>:
  105f20:	55                   	push   %rbp
  105f21:	48 89 e5             	mov    %rsp,%rbp
  105f24:	48 83 ec 20          	sub    $0x20,%rsp
  105f28:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  105f2c:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  105f30:	48 89 55 e8          	mov    %rdx,-0x18(%rbp)
  105f34:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  105f38:	48 8b 55 f0          	mov    -0x10(%rbp),%rdx
  105f3c:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  105f40:	be 02 00 00 00       	mov    $0x2,%esi
  105f45:	e8 16 fb ff ff       	call   105a60 <_ZN4acos9scheduler7Process17register_resourceENS0_12ResourceKindEPvm>
  105f4a:	48 83 c4 20          	add    $0x20,%rsp
  105f4e:	5d                   	pop    %rbp
  105f4f:	c3                   	ret

0000000000105f50 <_ZN4acos9scheduler7Process13register_fileEPNS_3vfs4FileE>:
  105f50:	55                   	push   %rbp
  105f51:	48 89 e5             	mov    %rsp,%rbp
  105f54:	48 83 ec 28          	sub    $0x28,%rsp
  105f58:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  105f5c:	48 89 75 e8          	mov    %rsi,-0x18(%rbp)
  105f60:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  105f64:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
  105f68:	48 c7 45 e0 00 00 00 	movq   $0x0,-0x20(%rbp)
  105f6f:	00
  105f70:	48 83 7d e0 40       	cmpq   $0x40,-0x20(%rbp)
  105f75:	0f 83 4d 00 00 00    	jae    105fc8 <_ZN4acos9scheduler7Process13register_fileEPNS_3vfs4FileE+0x78>
  105f7b:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  105f7f:	48 8b 4d e0          	mov    -0x20(%rbp),%rcx
  105f83:	48 83 bc c8 10 38 00 	cmpq   $0x0,0x3810(%rax,%rcx,8)
  105f8a:	00 00
  105f8c:	0f 85 20 00 00 00    	jne    105fb2 <_ZN4acos9scheduler7Process13register_fileEPNS_3vfs4FileE+0x62>
  105f92:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  105f96:	48 8b 55 e8          	mov    -0x18(%rbp),%rdx
  105f9a:	48 8b 4d e0          	mov    -0x20(%rbp),%rcx
  105f9e:	48 89 94 c8 10 38 00 	mov    %rdx,0x3810(%rax,%rcx,8)
  105fa5:	00
  105fa6:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  105faa:	89 45 fc             	mov    %eax,-0x4(%rbp)
  105fad:	e9 1d 00 00 00       	jmp    105fcf <_ZN4acos9scheduler7Process13register_fileEPNS_3vfs4FileE+0x7f>
  105fb2:	e9 00 00 00 00       	jmp    105fb7 <_ZN4acos9scheduler7Process13register_fileEPNS_3vfs4FileE+0x67>
  105fb7:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  105fbb:	48 83 c0 01          	add    $0x1,%rax
  105fbf:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  105fc3:	e9 a8 ff ff ff       	jmp    105f70 <_ZN4acos9scheduler7Process13register_fileEPNS_3vfs4FileE+0x20>
  105fc8:	c7 45 fc ff ff ff ff 	movl   $0xffffffff,-0x4(%rbp)
  105fcf:	8b 45 fc             	mov    -0x4(%rbp),%eax
  105fd2:	48 83 c4 28          	add    $0x28,%rsp
  105fd6:	5d                   	pop    %rbp
  105fd7:	c3                   	ret
  105fd8:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  105fdf:	00

0000000000105fe0 <_ZN4acos9scheduler7Process8get_fileEi>:
  105fe0:	55                   	push   %rbp
  105fe1:	48 89 e5             	mov    %rsp,%rbp
  105fe4:	48 83 ec 20          	sub    $0x20,%rsp
  105fe8:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  105fec:	89 75 ec             	mov    %esi,-0x14(%rbp)
  105fef:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  105ff3:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  105ff7:	83 7d ec 00          	cmpl   $0x0,-0x14(%rbp)
  105ffb:	0f 8c 0e 00 00 00    	jl     10600f <_ZN4acos9scheduler7Process8get_fileEi+0x2f>
  106001:	48 63 45 ec          	movslq -0x14(%rbp),%rax
  106005:	48 83 f8 40          	cmp    $0x40,%rax
  106009:	0f 82 0d 00 00 00    	jb     10601c <_ZN4acos9scheduler7Process8get_fileEi+0x3c>
  10600f:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  106016:	00
  106017:	e9 14 00 00 00       	jmp    106030 <_ZN4acos9scheduler7Process8get_fileEi+0x50>
  10601c:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  106020:	48 63 4d ec          	movslq -0x14(%rbp),%rcx
  106024:	48 8b 84 c8 10 38 00 	mov    0x3810(%rax,%rcx,8),%rax
  10602b:	00
  10602c:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  106030:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  106034:	48 83 c4 20          	add    $0x20,%rsp
  106038:	5d                   	pop    %rbp
  106039:	c3                   	ret
  10603a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000106040 <_ZN4acos9scheduler7Process15register_socketEPNS_3net6SocketE>:
  106040:	55                   	push   %rbp
  106041:	48 89 e5             	mov    %rsp,%rbp
  106044:	48 83 ec 28          	sub    $0x28,%rsp
  106048:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  10604c:	48 89 75 e8          	mov    %rsi,-0x18(%rbp)
  106050:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  106054:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
  106058:	48 c7 45 e0 00 00 00 	movq   $0x0,-0x20(%rbp)
  10605f:	00
  106060:	48 83 7d e0 20       	cmpq   $0x20,-0x20(%rbp)
  106065:	0f 83 4d 00 00 00    	jae    1060b8 <_ZN4acos9scheduler7Process15register_socketEPNS_3net6SocketE+0x78>
  10606b:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  10606f:	48 8b 4d e0          	mov    -0x20(%rbp),%rcx
  106073:	48 83 bc c8 10 3a 00 	cmpq   $0x0,0x3a10(%rax,%rcx,8)
  10607a:	00 00
  10607c:	0f 85 20 00 00 00    	jne    1060a2 <_ZN4acos9scheduler7Process15register_socketEPNS_3net6SocketE+0x62>
  106082:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  106086:	48 8b 55 e8          	mov    -0x18(%rbp),%rdx
  10608a:	48 8b 4d e0          	mov    -0x20(%rbp),%rcx
  10608e:	48 89 94 c8 10 3a 00 	mov    %rdx,0x3a10(%rax,%rcx,8)
  106095:	00
  106096:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  10609a:	89 45 fc             	mov    %eax,-0x4(%rbp)
  10609d:	e9 1d 00 00 00       	jmp    1060bf <_ZN4acos9scheduler7Process15register_socketEPNS_3net6SocketE+0x7f>
  1060a2:	e9 00 00 00 00       	jmp    1060a7 <_ZN4acos9scheduler7Process15register_socketEPNS_3net6SocketE+0x67>
  1060a7:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  1060ab:	48 83 c0 01          	add    $0x1,%rax
  1060af:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  1060b3:	e9 a8 ff ff ff       	jmp    106060 <_ZN4acos9scheduler7Process15register_socketEPNS_3net6SocketE+0x20>
  1060b8:	c7 45 fc ff ff ff ff 	movl   $0xffffffff,-0x4(%rbp)
  1060bf:	8b 45 fc             	mov    -0x4(%rbp),%eax
  1060c2:	48 83 c4 28          	add    $0x28,%rsp
  1060c6:	5d                   	pop    %rbp
  1060c7:	c3                   	ret
  1060c8:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  1060cf:	00

00000000001060d0 <_ZN4acos9scheduler7Process10get_socketEi>:
  1060d0:	55                   	push   %rbp
  1060d1:	48 89 e5             	mov    %rsp,%rbp
  1060d4:	48 83 ec 20          	sub    $0x20,%rsp
  1060d8:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  1060dc:	89 75 ec             	mov    %esi,-0x14(%rbp)
  1060df:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  1060e3:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  1060e7:	83 7d ec 00          	cmpl   $0x0,-0x14(%rbp)
  1060eb:	0f 8c 0e 00 00 00    	jl     1060ff <_ZN4acos9scheduler7Process10get_socketEi+0x2f>
  1060f1:	48 63 45 ec          	movslq -0x14(%rbp),%rax
  1060f5:	48 83 f8 20          	cmp    $0x20,%rax
  1060f9:	0f 82 0d 00 00 00    	jb     10610c <_ZN4acos9scheduler7Process10get_socketEi+0x3c>
  1060ff:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  106106:	00
  106107:	e9 14 00 00 00       	jmp    106120 <_ZN4acos9scheduler7Process10get_socketEi+0x50>
  10610c:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  106110:	48 63 4d ec          	movslq -0x14(%rbp),%rcx
  106114:	48 8b 84 c8 10 3a 00 	mov    0x3a10(%rax,%rcx,8),%rax
  10611b:	00
  10611c:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  106120:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  106124:	48 83 c4 20          	add    $0x20,%rsp
  106128:	5d                   	pop    %rbp
  106129:	c3                   	ret
  10612a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000106130 <_ZN4acos9scheduler7Process16register_channelEPNS_3ipc7ChannelE>:
  106130:	55                   	push   %rbp
  106131:	48 89 e5             	mov    %rsp,%rbp
  106134:	48 83 ec 20          	sub    $0x20,%rsp
  106138:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10613c:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  106140:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  106144:	48 89 7d e0          	mov    %rdi,-0x20(%rbp)
  106148:	48 8b 55 f0          	mov    -0x10(%rbp),%rdx
  10614c:	be 03 00 00 00       	mov    $0x3,%esi
  106151:	b9 33 00 00 00       	mov    $0x33,%ecx
  106156:	e8 05 f9 ff ff       	call   105a60 <_ZN4acos9scheduler7Process17register_resourceENS0_12ResourceKindEPvm>
  10615b:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
  10615f:	48 83 7d e8 00       	cmpq   $0x0,-0x18(%rbp)
  106164:	0f 84 11 00 00 00    	je     10617b <_ZN4acos9scheduler7Process16register_channelEPNS_3ipc7ChannelE+0x4b>
  10616a:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  10616e:	48 8b 55 f0          	mov    -0x10(%rbp),%rdx
  106172:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  106176:	48 89 54 c8 10       	mov    %rdx,0x10(%rax,%rcx,8)
  10617b:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  10617f:	48 83 c4 20          	add    $0x20,%rsp
  106183:	5d                   	pop    %rbp
  106184:	c3                   	ret
  106185:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  10618c:	00 00 00 00

0000000000106190 <_ZN4acos9scheduler7Process11get_processEm>:
  106190:	55                   	push   %rbp
  106191:	48 89 e5             	mov    %rsp,%rbp
  106194:	48 83 ec 20          	sub    $0x20,%rsp
  106198:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  10619c:	48 89 75 e8          	mov    %rsi,-0x18(%rbp)
  1061a0:	48 8b 7d f0          	mov    -0x10(%rbp),%rdi
  1061a4:	48 8b 75 e8          	mov    -0x18(%rbp),%rsi
  1061a8:	e8 73 fb ff ff       	call   105d20 <_ZN4acos9scheduler7Process10get_handleEm>
  1061ad:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  1061b1:	48 83 7d e0 00       	cmpq   $0x0,-0x20(%rbp)
  1061b6:	0f 84 0d 00 00 00    	je     1061c9 <_ZN4acos9scheduler7Process11get_processEm+0x39>
  1061bc:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  1061c0:	83 38 01             	cmpl   $0x1,(%rax)
  1061c3:	0f 84 0d 00 00 00    	je     1061d6 <_ZN4acos9scheduler7Process11get_processEm+0x46>
  1061c9:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  1061d0:	00
  1061d1:	e9 0c 00 00 00       	jmp    1061e2 <_ZN4acos9scheduler7Process11get_processEm+0x52>
  1061d6:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  1061da:	48 8b 40 08          	mov    0x8(%rax),%rax
  1061de:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  1061e2:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  1061e6:	48 83 c4 20          	add    $0x20,%rsp
  1061ea:	5d                   	pop    %rbp
  1061eb:	c3                   	ret
  1061ec:	0f 1f 40 00          	nopl   0x0(%rax)

00000000001061f0 <_ZN4acos9scheduler7Process10get_threadEm>:
  1061f0:	55                   	push   %rbp
  1061f1:	48 89 e5             	mov    %rsp,%rbp
  1061f4:	48 83 ec 20          	sub    $0x20,%rsp
  1061f8:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  1061fc:	48 89 75 e8          	mov    %rsi,-0x18(%rbp)
  106200:	48 8b 7d f0          	mov    -0x10(%rbp),%rdi
  106204:	48 8b 75 e8          	mov    -0x18(%rbp),%rsi
  106208:	e8 13 fb ff ff       	call   105d20 <_ZN4acos9scheduler7Process10get_handleEm>
  10620d:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  106211:	48 83 7d e0 00       	cmpq   $0x0,-0x20(%rbp)
  106216:	0f 84 0d 00 00 00    	je     106229 <_ZN4acos9scheduler7Process10get_threadEm+0x39>
  10621c:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  106220:	83 38 02             	cmpl   $0x2,(%rax)
  106223:	0f 84 0d 00 00 00    	je     106236 <_ZN4acos9scheduler7Process10get_threadEm+0x46>
  106229:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  106230:	00
  106231:	e9 0c 00 00 00       	jmp    106242 <_ZN4acos9scheduler7Process10get_threadEm+0x52>
  106236:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  10623a:	48 8b 40 08          	mov    0x8(%rax),%rax
  10623e:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  106242:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  106246:	48 83 c4 20          	add    $0x20,%rsp
  10624a:	5d                   	pop    %rbp
  10624b:	c3                   	ret
  10624c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000106250 <_ZN4acos9scheduler7Process11get_channelEm>:
  106250:	55                   	push   %rbp
  106251:	48 89 e5             	mov    %rsp,%rbp
  106254:	48 83 ec 20          	sub    $0x20,%rsp
  106258:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  10625c:	48 89 75 e8          	mov    %rsi,-0x18(%rbp)
  106260:	48 8b 7d f0          	mov    -0x10(%rbp),%rdi
  106264:	48 8b 75 e8          	mov    -0x18(%rbp),%rsi
  106268:	e8 b3 fa ff ff       	call   105d20 <_ZN4acos9scheduler7Process10get_handleEm>
  10626d:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  106271:	48 83 7d e0 00       	cmpq   $0x0,-0x20(%rbp)
  106276:	0f 84 23 00 00 00    	je     10629f <_ZN4acos9scheduler7Process11get_channelEm+0x4f>
  10627c:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  106280:	83 38 03             	cmpl   $0x3,(%rax)
  106283:	0f 85 16 00 00 00    	jne    10629f <_ZN4acos9scheduler7Process11get_channelEm+0x4f>
  106289:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  10628d:	48 8b 40 10          	mov    0x10(%rax),%rax
  106291:	48 83 e0 01          	and    $0x1,%rax
  106295:	48 83 f8 00          	cmp    $0x0,%rax
  106299:	0f 85 0d 00 00 00    	jne    1062ac <_ZN4acos9scheduler7Process11get_channelEm+0x5c>
  10629f:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  1062a6:	00
  1062a7:	e9 0c 00 00 00       	jmp    1062b8 <_ZN4acos9scheduler7Process11get_channelEm+0x68>
  1062ac:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  1062b0:	48 8b 40 08          	mov    0x8(%rax),%rax
  1062b4:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  1062b8:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  1062bc:	48 83 c4 20          	add    $0x20,%rsp
  1062c0:	5d                   	pop    %rbp
  1062c1:	c3                   	ret
  1062c2:	66 66 66 66 66 2e 0f 	data16 data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
  1062c9:	1f 84 00 00 00 00 00

00000000001062d0 <_ZN4acos9scheduler7Process15register_regionEPNS_3ipc12SharedRegionE>:
  1062d0:	55                   	push   %rbp
  1062d1:	48 89 e5             	mov    %rsp,%rbp
  1062d4:	48 83 ec 20          	sub    $0x20,%rsp
  1062d8:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  1062dc:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  1062e0:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  1062e4:	48 89 7d e0          	mov    %rdi,-0x20(%rbp)
  1062e8:	48 8b 55 f0          	mov    -0x10(%rbp),%rdx
  1062ec:	be 05 00 00 00       	mov    $0x5,%esi
  1062f1:	b9 3b 00 00 00       	mov    $0x3b,%ecx
  1062f6:	e8 65 f7 ff ff       	call   105a60 <_ZN4acos9scheduler7Process17register_resourceENS0_12ResourceKindEPvm>
  1062fb:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
  1062ff:	48 83 7d e8 00       	cmpq   $0x0,-0x18(%rbp)
  106304:	0f 84 14 00 00 00    	je     10631e <_ZN4acos9scheduler7Process15register_regionEPNS_3ipc12SharedRegionE+0x4e>
  10630a:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  10630e:	48 8b 55 f0          	mov    -0x10(%rbp),%rdx
  106312:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  106316:	48 89 94 c8 10 08 00 	mov    %rdx,0x810(%rax,%rcx,8)
  10631d:	00
  10631e:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  106322:	48 83 c4 20          	add    $0x20,%rsp
  106326:	5d                   	pop    %rbp
  106327:	c3                   	ret
  106328:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  10632f:	00

0000000000106330 <_ZN4acos9scheduler7Process10get_regionEm>:
  106330:	55                   	push   %rbp
  106331:	48 89 e5             	mov    %rsp,%rbp
  106334:	48 83 ec 20          	sub    $0x20,%rsp
  106338:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  10633c:	48 89 75 e8          	mov    %rsi,-0x18(%rbp)
  106340:	48 8b 7d f0          	mov    -0x10(%rbp),%rdi
  106344:	48 8b 75 e8          	mov    -0x18(%rbp),%rsi
  106348:	e8 d3 f9 ff ff       	call   105d20 <_ZN4acos9scheduler7Process10get_handleEm>
  10634d:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  106351:	48 83 7d e0 00       	cmpq   $0x0,-0x20(%rbp)
  106356:	0f 84 0d 00 00 00    	je     106369 <_ZN4acos9scheduler7Process10get_regionEm+0x39>
  10635c:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  106360:	83 38 05             	cmpl   $0x5,(%rax)
  106363:	0f 84 0d 00 00 00    	je     106376 <_ZN4acos9scheduler7Process10get_regionEm+0x46>
  106369:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  106370:	00
  106371:	e9 0c 00 00 00       	jmp    106382 <_ZN4acos9scheduler7Process10get_regionEm+0x52>
  106376:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  10637a:	48 8b 40 08          	mov    0x8(%rax),%rax
  10637e:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  106382:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  106386:	48 83 c4 20          	add    $0x20,%rsp
  10638a:	5d                   	pop    %rbp
  10638b:	c3                   	ret
  10638c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000106390 <_ZN4acos9scheduler7Process21register_notificationEPNS_3ipc12NotificationE>:
  106390:	55                   	push   %rbp
  106391:	48 89 e5             	mov    %rsp,%rbp
  106394:	48 83 ec 20          	sub    $0x20,%rsp
  106398:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10639c:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  1063a0:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  1063a4:	48 89 7d e0          	mov    %rdi,-0x20(%rbp)
  1063a8:	48 8b 55 f0          	mov    -0x10(%rbp),%rdx
  1063ac:	be 04 00 00 00       	mov    $0x4,%esi
  1063b1:	b9 b0 01 00 00       	mov    $0x1b0,%ecx
  1063b6:	e8 a5 f6 ff ff       	call   105a60 <_ZN4acos9scheduler7Process17register_resourceENS0_12ResourceKindEPvm>
  1063bb:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
  1063bf:	48 83 7d e8 00       	cmpq   $0x0,-0x18(%rbp)
  1063c4:	0f 84 14 00 00 00    	je     1063de <_ZN4acos9scheduler7Process21register_notificationEPNS_3ipc12NotificationE+0x4e>
  1063ca:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  1063ce:	48 8b 55 f0          	mov    -0x10(%rbp),%rdx
  1063d2:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  1063d6:	48 89 94 c8 10 10 00 	mov    %rdx,0x1010(%rax,%rcx,8)
  1063dd:	00
  1063de:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  1063e2:	48 83 c4 20          	add    $0x20,%rsp
  1063e6:	5d                   	pop    %rbp
  1063e7:	c3                   	ret
  1063e8:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  1063ef:	00

00000000001063f0 <_ZN4acos9scheduler7Process16get_notificationEm>:
  1063f0:	55                   	push   %rbp
  1063f1:	48 89 e5             	mov    %rsp,%rbp
  1063f4:	48 83 ec 20          	sub    $0x20,%rsp
  1063f8:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  1063fc:	48 89 75 e8          	mov    %rsi,-0x18(%rbp)
  106400:	48 8b 7d f0          	mov    -0x10(%rbp),%rdi
  106404:	48 8b 75 e8          	mov    -0x18(%rbp),%rsi
  106408:	e8 13 f9 ff ff       	call   105d20 <_ZN4acos9scheduler7Process10get_handleEm>
  10640d:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  106411:	48 83 7d e0 00       	cmpq   $0x0,-0x20(%rbp)
  106416:	0f 84 0d 00 00 00    	je     106429 <_ZN4acos9scheduler7Process16get_notificationEm+0x39>
  10641c:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  106420:	83 38 04             	cmpl   $0x4,(%rax)
  106423:	0f 84 0d 00 00 00    	je     106436 <_ZN4acos9scheduler7Process16get_notificationEm+0x46>
  106429:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  106430:	00
  106431:	e9 0c 00 00 00       	jmp    106442 <_ZN4acos9scheduler7Process16get_notificationEm+0x52>
  106436:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  10643a:	48 8b 40 08          	mov    0x8(%rax),%rax
  10643e:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  106442:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  106446:	48 83 c4 20          	add    $0x20,%rsp
  10644a:	5d                   	pop    %rbp
  10644b:	c3                   	ret
  10644c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000106450 <_ZN4acos9scheduler18process_table_findEm>:
  106450:	55                   	push   %rbp
  106451:	48 89 e5             	mov    %rsp,%rbp
  106454:	48 83 ec 18          	sub    $0x18,%rsp
  106458:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  10645c:	48 c7 45 e8 00 00 00 	movq   $0x0,-0x18(%rbp)
  106463:	00
  106464:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  106468:	48 3b 04 25 e0 e9 15 	cmp    0x15e9e0,%rax
  10646f:	00
  106470:	0f 83 57 00 00 00    	jae    1064cd <_ZN4acos9scheduler18process_table_findEm+0x7d>
  106476:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  10647a:	48 83 3c c5 f0 e9 15 	cmpq   $0x0,0x15e9f0(,%rax,8)
  106481:	00 00
  106483:	0f 84 2e 00 00 00    	je     1064b7 <_ZN4acos9scheduler18process_table_findEm+0x67>
  106489:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  10648d:	48 8b 04 c5 f0 e9 15 	mov    0x15e9f0(,%rax,8),%rax
  106494:	00
  106495:	48 8b 00             	mov    (%rax),%rax
  106498:	48 3b 45 f0          	cmp    -0x10(%rbp),%rax
  10649c:	0f 85 15 00 00 00    	jne    1064b7 <_ZN4acos9scheduler18process_table_findEm+0x67>
  1064a2:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  1064a6:	48 8b 04 c5 f0 e9 15 	mov    0x15e9f0(,%rax,8),%rax
  1064ad:	00
  1064ae:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  1064b2:	e9 1e 00 00 00       	jmp    1064d5 <_ZN4acos9scheduler18process_table_findEm+0x85>
  1064b7:	e9 00 00 00 00       	jmp    1064bc <_ZN4acos9scheduler18process_table_findEm+0x6c>
  1064bc:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  1064c0:	48 83 c0 01          	add    $0x1,%rax
  1064c4:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
  1064c8:	e9 97 ff ff ff       	jmp    106464 <_ZN4acos9scheduler18process_table_findEm+0x14>
  1064cd:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  1064d4:	00
  1064d5:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  1064d9:	48 83 c4 18          	add    $0x18,%rsp
  1064dd:	5d                   	pop    %rbp
  1064de:	c3                   	ret
  1064df:	90                   	nop

00000000001064e0 <_ZN4acos9scheduler19set_console_blockedEPNS0_6ThreadE>:
  1064e0:	55                   	push   %rbp
  1064e1:	48 89 e5             	mov    %rsp,%rbp
  1064e4:	50                   	push   %rax
  1064e5:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  1064e9:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  1064ed:	48 89 04 25 f0 f1 15 	mov    %rax,0x15f1f0
  1064f4:	00
  1064f5:	48 83 c4 08          	add    $0x8,%rsp
  1064f9:	5d                   	pop    %rbp
  1064fa:	c3                   	ret
  1064fb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000106500 <_ZN4acos9scheduler21clear_console_blockedEPNS0_6ThreadE>:
  106500:	55                   	push   %rbp
  106501:	48 89 e5             	mov    %rsp,%rbp
  106504:	50                   	push   %rax
  106505:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  106509:	48 8b 04 25 f0 f1 15 	mov    0x15f1f0,%rax
  106510:	00
  106511:	48 3b 45 f8          	cmp    -0x8(%rbp),%rax
  106515:	0f 85 0c 00 00 00    	jne    106527 <_ZN4acos9scheduler21clear_console_blockedEPNS0_6ThreadE+0x27>
  10651b:	48 c7 04 25 f0 f1 15 	movq   $0x0,0x15f1f0
  106522:	00 00 00 00 00
  106527:	48 83 c4 08          	add    $0x8,%rsp
  10652b:	5d                   	pop    %rbp
  10652c:	c3                   	ret
  10652d:	0f 1f 00             	nopl   (%rax)

0000000000106530 <_ZN4acos9scheduler19get_console_blockedEv>:
  106530:	55                   	push   %rbp
  106531:	48 89 e5             	mov    %rsp,%rbp
  106534:	48 8b 04 25 f0 f1 15 	mov    0x15f1f0,%rax
  10653b:	00
  10653c:	5d                   	pop    %rbp
  10653d:	c3                   	ret
  10653e:	66 90                	xchg   %ax,%ax

0000000000106540 <_ZN4acos9scheduler14get_run_queuesEv>:
  106540:	55                   	push   %rbp
  106541:	48 89 e5             	mov    %rsp,%rbp
  106544:	48 b8 00 f2 15 00 00 	movabs $0x15f200,%rax
  10654b:	00 00 00
  10654e:	5d                   	pop    %rbp
  10654f:	c3                   	ret

0000000000106550 <_ZN4acos9scheduler14scheduler_initEv>:
  106550:	55                   	push   %rbp
  106551:	48 89 e5             	mov    %rsp,%rbp
  106554:	48 83 ec 04          	sub    $0x4,%rsp
  106558:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%rbp)
  10655f:	83 7d fc 40          	cmpl   $0x40,-0x4(%rbp)
  106563:	0f 8d 63 00 00 00    	jge    1065cc <_ZN4acos9scheduler14scheduler_initEv+0x7c>
  106569:	48 63 4d fc          	movslq -0x4(%rbp),%rcx
  10656d:	48 b8 00 f2 15 00 00 	movabs $0x15f200,%rax
  106574:	00 00 00
  106577:	48 6b c9 18          	imul   $0x18,%rcx,%rcx
  10657b:	48 01 c8             	add    %rcx,%rax
  10657e:	48 c7 00 00 00 00 00 	movq   $0x0,(%rax)
  106585:	48 63 4d fc          	movslq -0x4(%rbp),%rcx
  106589:	48 b8 00 f2 15 00 00 	movabs $0x15f200,%rax
  106590:	00 00 00
  106593:	48 6b c9 18          	imul   $0x18,%rcx,%rcx
  106597:	48 01 c8             	add    %rcx,%rax
  10659a:	48 c7 40 08 00 00 00 	movq   $0x0,0x8(%rax)
  1065a1:	00
  1065a2:	48 63 4d fc          	movslq -0x4(%rbp),%rcx
  1065a6:	48 b8 00 f2 15 00 00 	movabs $0x15f200,%rax
  1065ad:	00 00 00
  1065b0:	48 6b c9 18          	imul   $0x18,%rcx,%rcx
  1065b4:	48 01 c8             	add    %rcx,%rax
  1065b7:	c7 40 10 00 00 00 00 	movl   $0x0,0x10(%rax)
  1065be:	8b 45 fc             	mov    -0x4(%rbp),%eax
  1065c1:	83 c0 01             	add    $0x1,%eax
  1065c4:	89 45 fc             	mov    %eax,-0x4(%rbp)
  1065c7:	e9 93 ff ff ff       	jmp    10655f <_ZN4acos9scheduler14scheduler_initEv+0xf>
  1065cc:	48 83 c4 04          	add    $0x4,%rsp
  1065d0:	5d                   	pop    %rbp
  1065d1:	c3                   	ret
  1065d2:	66 66 66 66 66 2e 0f 	data16 data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
  1065d9:	1f 84 00 00 00 00 00

00000000001065e0 <_ZN4acos9scheduler14enqueue_threadEjPNS0_6ThreadE>:
  1065e0:	55                   	push   %rbp
  1065e1:	48 89 e5             	mov    %rsp,%rbp
  1065e4:	48 83 ec 20          	sub    $0x20,%rsp
  1065e8:	89 7d fc             	mov    %edi,-0x4(%rbp)
  1065eb:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  1065ef:	8b 45 fc             	mov    -0x4(%rbp),%eax
  1065f2:	48 be 00 f8 15 00 00 	movabs $0x15f800,%rsi
  1065f9:	00 00 00
  1065fc:	48 01 c6             	add    %rax,%rsi
  1065ff:	48 8d 7d e8          	lea    -0x18(%rbp),%rdi
  106603:	e8 88 84 00 00       	call   10ea90 <_ZN4acos3hal10ScopedLockC2ERNS0_8SpinLockE>
  106608:	8b 7d fc             	mov    -0x4(%rbp),%edi
  10660b:	48 8b 75 f0          	mov    -0x10(%rbp),%rsi
  10660f:	e8 1c 00 00 00       	call   106630 <_ZN4acos9schedulerL23enqueue_thread_internalEjPNS0_6ThreadE>
  106614:	48 8d 7d e8          	lea    -0x18(%rbp),%rdi
  106618:	e8 a3 84 00 00       	call   10eac0 <_ZN4acos3hal10ScopedLockD2Ev>
  10661d:	48 83 c4 20          	add    $0x20,%rsp
  106621:	5d                   	pop    %rbp
  106622:	c3                   	ret
  106623:	66 66 66 66 2e 0f 1f 	data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
  10662a:	84 00 00 00 00 00

0000000000106630 <_ZN4acos9schedulerL23enqueue_thread_internalEjPNS0_6ThreadE>:
  106630:	55                   	push   %rbp
  106631:	48 89 e5             	mov    %rsp,%rbp
  106634:	48 83 ec 10          	sub    $0x10,%rsp
  106638:	89 7d fc             	mov    %edi,-0x4(%rbp)
  10663b:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  10663f:	8b 45 fc             	mov    -0x4(%rbp),%eax
  106642:	89 c1                	mov    %eax,%ecx
  106644:	48 b8 00 f2 15 00 00 	movabs $0x15f200,%rax
  10664b:	00 00 00
  10664e:	48 6b c9 18          	imul   $0x18,%rcx,%rcx
  106652:	48 01 c8             	add    %rcx,%rax
  106655:	48 83 38 00          	cmpq   $0x0,(%rax)
  106659:	0f 85 22 00 00 00    	jne    106681 <_ZN4acos9schedulerL23enqueue_thread_internalEjPNS0_6ThreadE+0x51>
  10665f:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
  106663:	8b 45 fc             	mov    -0x4(%rbp),%eax
  106666:	89 c2                	mov    %eax,%edx
  106668:	48 b8 00 f2 15 00 00 	movabs $0x15f200,%rax
  10666f:	00 00 00
  106672:	48 6b d2 18          	imul   $0x18,%rdx,%rdx
  106676:	48 01 d0             	add    %rdx,%rax
  106679:	48 89 08             	mov    %rcx,(%rax)
  10667c:	e9 22 00 00 00       	jmp    1066a3 <_ZN4acos9schedulerL23enqueue_thread_internalEjPNS0_6ThreadE+0x73>
  106681:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
  106685:	8b 45 fc             	mov    -0x4(%rbp),%eax
  106688:	89 c2                	mov    %eax,%edx
  10668a:	48 b8 00 f2 15 00 00 	movabs $0x15f200,%rax
  106691:	00 00 00
  106694:	48 6b d2 18          	imul   $0x18,%rdx,%rdx
  106698:	48 01 d0             	add    %rdx,%rax
  10669b:	48 8b 40 08          	mov    0x8(%rax),%rax
  10669f:	48 89 48 38          	mov    %rcx,0x38(%rax)
  1066a3:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
  1066a7:	8b 45 fc             	mov    -0x4(%rbp),%eax
  1066aa:	89 c2                	mov    %eax,%edx
  1066ac:	48 b8 00 f2 15 00 00 	movabs $0x15f200,%rax
  1066b3:	00 00 00
  1066b6:	48 6b d2 18          	imul   $0x18,%rdx,%rdx
  1066ba:	48 01 d0             	add    %rdx,%rax
  1066bd:	48 89 48 08          	mov    %rcx,0x8(%rax)
  1066c1:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  1066c5:	48 c7 40 38 00 00 00 	movq   $0x0,0x38(%rax)
  1066cc:	00
  1066cd:	8b 45 fc             	mov    -0x4(%rbp),%eax
  1066d0:	89 c1                	mov    %eax,%ecx
  1066d2:	48 b8 00 f2 15 00 00 	movabs $0x15f200,%rax
  1066d9:	00 00 00
  1066dc:	48 6b c9 18          	imul   $0x18,%rcx,%rcx
  1066e0:	48 01 c8             	add    %rcx,%rax
  1066e3:	8b 48 10             	mov    0x10(%rax),%ecx
  1066e6:	83 c1 01             	add    $0x1,%ecx
  1066e9:	89 48 10             	mov    %ecx,0x10(%rax)
  1066ec:	48 83 c4 10          	add    $0x10,%rsp
  1066f0:	5d                   	pop    %rbp
  1066f1:	c3                   	ret
  1066f2:	66 66 66 66 66 2e 0f 	data16 data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
  1066f9:	1f 84 00 00 00 00 00

0000000000106700 <_ZN4acos9scheduler8scheduleEv>:
  106700:	55                   	push   %rbp
  106701:	48 89 e5             	mov    %rsp,%rbp
  106704:	48 83 ec 20          	sub    $0x20,%rsp
  106708:	e8 d3 84 00 00       	call   10ebe0 <_ZN4acos3smp3Cpu2idEv>
  10670d:	89 45 fc             	mov    %eax,-0x4(%rbp)
  106710:	8b 45 fc             	mov    -0x4(%rbp),%eax
  106713:	48 bf 00 f8 15 00 00 	movabs $0x15f800,%rdi
  10671a:	00 00 00
  10671d:	48 01 c7             	add    %rax,%rdi
  106720:	e8 bb 83 00 00       	call   10eae0 <_ZN4acos3hal8SpinLock4lockEv>
  106725:	e8 76 78 00 00       	call   10dfa0 <_ZN4acos3smp3Cpu7currentEv>
  10672a:	48 89 45 f0          	mov    %rax,-0x10(%rbp)
  10672e:	48 83 7d f0 00       	cmpq   $0x0,-0x10(%rbp)
  106733:	0f 85 1a 00 00 00    	jne    106753 <_ZN4acos9scheduler8scheduleEv+0x53>
  106739:	8b 45 fc             	mov    -0x4(%rbp),%eax
  10673c:	48 bf 00 f8 15 00 00 	movabs $0x15f800,%rdi
  106743:	00 00 00
  106746:	48 01 c7             	add    %rax,%rdi
  106749:	e8 d2 83 00 00       	call   10eb20 <_ZN4acos3hal8SpinLock6unlockEv>
  10674e:	e9 9d 01 00 00       	jmp    1068f0 <_ZN4acos9scheduler8scheduleEv+0x1f0>
  106753:	8b 45 fc             	mov    -0x4(%rbp),%eax
  106756:	89 c1                	mov    %eax,%ecx
  106758:	48 b8 00 f2 15 00 00 	movabs $0x15f200,%rax
  10675f:	00 00 00
  106762:	48 6b c9 18          	imul   $0x18,%rcx,%rcx
  106766:	48 01 c8             	add    %rcx,%rax
  106769:	48 8b 00             	mov    (%rax),%rax
  10676c:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
  106770:	48 83 7d e8 00       	cmpq   $0x0,-0x18(%rbp)
  106775:	0f 85 1a 00 00 00    	jne    106795 <_ZN4acos9scheduler8scheduleEv+0x95>
  10677b:	8b 45 fc             	mov    -0x4(%rbp),%eax
  10677e:	48 bf 00 f8 15 00 00 	movabs $0x15f800,%rdi
  106785:	00 00 00
  106788:	48 01 c7             	add    %rax,%rdi
  10678b:	e8 90 83 00 00       	call   10eb20 <_ZN4acos3hal8SpinLock6unlockEv>
  106790:	e9 5b 01 00 00       	jmp    1068f0 <_ZN4acos9scheduler8scheduleEv+0x1f0>
  106795:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  106799:	48 8b 48 38          	mov    0x38(%rax),%rcx
  10679d:	8b 45 fc             	mov    -0x4(%rbp),%eax
  1067a0:	89 c2                	mov    %eax,%edx
  1067a2:	48 b8 00 f2 15 00 00 	movabs $0x15f200,%rax
  1067a9:	00 00 00
  1067ac:	48 6b d2 18          	imul   $0x18,%rdx,%rdx
  1067b0:	48 01 d0             	add    %rdx,%rax
  1067b3:	48 89 08             	mov    %rcx,(%rax)
  1067b6:	8b 45 fc             	mov    -0x4(%rbp),%eax
  1067b9:	89 c1                	mov    %eax,%ecx
  1067bb:	48 b8 00 f2 15 00 00 	movabs $0x15f200,%rax
  1067c2:	00 00 00
  1067c5:	48 6b c9 18          	imul   $0x18,%rcx,%rcx
  1067c9:	48 01 c8             	add    %rcx,%rax
  1067cc:	48 83 38 00          	cmpq   $0x0,(%rax)
  1067d0:	0f 85 1e 00 00 00    	jne    1067f4 <_ZN4acos9scheduler8scheduleEv+0xf4>
  1067d6:	8b 45 fc             	mov    -0x4(%rbp),%eax
  1067d9:	89 c1                	mov    %eax,%ecx
  1067db:	48 b8 00 f2 15 00 00 	movabs $0x15f200,%rax
  1067e2:	00 00 00
  1067e5:	48 6b c9 18          	imul   $0x18,%rcx,%rcx
  1067e9:	48 01 c8             	add    %rcx,%rax
  1067ec:	48 c7 40 08 00 00 00 	movq   $0x0,0x8(%rax)
  1067f3:	00
  1067f4:	8b 45 fc             	mov    -0x4(%rbp),%eax
  1067f7:	89 c1                	mov    %eax,%ecx
  1067f9:	48 b8 00 f2 15 00 00 	movabs $0x15f200,%rax
  106800:	00 00 00
  106803:	48 6b c9 18          	imul   $0x18,%rcx,%rcx
  106807:	48 01 c8             	add    %rcx,%rax
  10680a:	8b 48 10             	mov    0x10(%rax),%ecx
  10680d:	83 c1 ff             	add    $0xffffffff,%ecx
  106810:	89 48 10             	mov    %ecx,0x10(%rax)
  106813:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  106817:	48 8b 40 18          	mov    0x18(%rax),%rax
  10681b:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  10681f:	48 83 7d e0 00       	cmpq   $0x0,-0x20(%rbp)
  106824:	0f 84 25 00 00 00    	je     10684f <_ZN4acos9scheduler8scheduleEv+0x14f>
  10682a:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  10682e:	83 78 18 02          	cmpl   $0x2,0x18(%rax)
  106832:	0f 85 17 00 00 00    	jne    10684f <_ZN4acos9scheduler8scheduleEv+0x14f>
  106838:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  10683c:	c7 40 18 01 00 00 00 	movl   $0x1,0x18(%rax)
  106843:	8b 7d fc             	mov    -0x4(%rbp),%edi
  106846:	48 8b 75 e0          	mov    -0x20(%rbp),%rsi
  10684a:	e8 e1 fd ff ff       	call   106630 <_ZN4acos9schedulerL23enqueue_thread_internalEjPNS0_6ThreadE>
  10684f:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  106853:	48 3b 45 e0          	cmp    -0x20(%rbp),%rax
  106857:	0f 84 7e 00 00 00    	je     1068db <_ZN4acos9scheduler8scheduleEv+0x1db>
  10685d:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  106861:	c7 40 18 02 00 00 00 	movl   $0x2,0x18(%rax)
  106868:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  10686c:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  106870:	48 89 48 18          	mov    %rcx,0x18(%rax)
  106874:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  106878:	48 8b 78 08          	mov    0x8(%rax),%rdi
  10687c:	e8 df 03 00 00       	call   106c60 <_ZN4acos3hal12tss_set_rsp0Em>
  106881:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  106885:	48 8b 48 08          	mov    0x8(%rax),%rcx
  106889:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10688d:	48 89 48 08          	mov    %rcx,0x8(%rax)
  106891:	8b 45 fc             	mov    -0x4(%rbp),%eax
  106894:	48 bf 00 f8 15 00 00 	movabs $0x15f800,%rdi
  10689b:	00 00 00
  10689e:	48 01 c7             	add    %rax,%rdi
  1068a1:	e8 7a 82 00 00       	call   10eb20 <_ZN4acos3hal8SpinLock6unlockEv>
  1068a6:	48 83 7d e0 00       	cmpq   $0x0,-0x20(%rbp)
  1068ab:	0f 84 1a 00 00 00    	je     1068cb <_ZN4acos9scheduler8scheduleEv+0x1cb>
  1068b1:	48 8b 7d e0          	mov    -0x20(%rbp),%rdi
  1068b5:	48 83 c7 10          	add    $0x10,%rdi
  1068b9:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  1068bd:	48 8b 70 10          	mov    0x10(%rax),%rsi
  1068c1:	e8 ee 7c 00 00       	call   10e5b4 <context_switch>
  1068c6:	e9 0b 00 00 00       	jmp    1068d6 <_ZN4acos9scheduler8scheduleEv+0x1d6>
  1068cb:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  1068cf:	48 8b 40 10          	mov    0x10(%rax),%rax
  1068d3:	48 89 c4             	mov    %rax,%rsp
  1068d6:	e9 15 00 00 00       	jmp    1068f0 <_ZN4acos9scheduler8scheduleEv+0x1f0>
  1068db:	8b 45 fc             	mov    -0x4(%rbp),%eax
  1068de:	48 bf 00 f8 15 00 00 	movabs $0x15f800,%rdi
  1068e5:	00 00 00
  1068e8:	48 01 c7             	add    %rax,%rdi
  1068eb:	e8 30 82 00 00       	call   10eb20 <_ZN4acos3hal8SpinLock6unlockEv>
  1068f0:	48 83 c4 20          	add    $0x20,%rsp
  1068f4:	5d                   	pop    %rbp
  1068f5:	c3                   	ret
  1068f6:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
  1068fd:	00 00 00

0000000000106900 <_ZN4acos9scheduler14current_threadEv>:
  106900:	55                   	push   %rbp
  106901:	48 89 e5             	mov    %rsp,%rbp
  106904:	e8 97 76 00 00       	call   10dfa0 <_ZN4acos3smp3Cpu7currentEv>
  106909:	48 8b 40 18          	mov    0x18(%rax),%rax
  10690d:	5d                   	pop    %rbp
  10690e:	c3                   	ret
  10690f:	90                   	nop

0000000000106910 <_ZN4acos9scheduler11wake_threadEPNS0_6ThreadE>:
  106910:	55                   	push   %rbp
  106911:	48 89 e5             	mov    %rsp,%rbp
  106914:	48 83 ec 10          	sub    $0x10,%rsp
  106918:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10691c:	48 83 7d f8 00       	cmpq   $0x0,-0x8(%rbp)
  106921:	0f 85 05 00 00 00    	jne    10692c <_ZN4acos9scheduler11wake_threadEPNS0_6ThreadE+0x1c>
  106927:	e9 16 00 00 00       	jmp    106942 <_ZN4acos9scheduler11wake_threadEPNS0_6ThreadE+0x32>
  10692c:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  106930:	c7 40 18 01 00 00 00 	movl   $0x1,0x18(%rax)
  106937:	48 8b 75 f8          	mov    -0x8(%rbp),%rsi
  10693b:	31 ff                	xor    %edi,%edi
  10693d:	e8 9e fc ff ff       	call   1065e0 <_ZN4acos9scheduler14enqueue_threadEjPNS0_6ThreadE>
  106942:	48 83 c4 10          	add    $0x10,%rsp
  106946:	5d                   	pop    %rbp
  106947:	c3                   	ret
  106948:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  10694f:	00

0000000000106950 <_ZN4acos9scheduler12block_threadEPNS0_6ThreadE>:
  106950:	55                   	push   %rbp
  106951:	48 89 e5             	mov    %rsp,%rbp
  106954:	48 83 ec 10          	sub    $0x10,%rsp
  106958:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10695c:	48 83 7d f8 00       	cmpq   $0x0,-0x8(%rbp)
  106961:	0f 85 05 00 00 00    	jne    10696c <_ZN4acos9scheduler12block_threadEPNS0_6ThreadE+0x1c>
  106967:	e9 10 00 00 00       	jmp    10697c <_ZN4acos9scheduler12block_threadEPNS0_6ThreadE+0x2c>
  10696c:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  106970:	c7 40 18 03 00 00 00 	movl   $0x3,0x18(%rax)
  106977:	e8 84 fd ff ff       	call   106700 <_ZN4acos9scheduler8scheduleEv>
  10697c:	48 83 c4 10          	add    $0x10,%rsp
  106980:	5d                   	pop    %rbp
  106981:	c3                   	ret
  106982:	66 66 66 66 66 2e 0f 	data16 data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
  106989:	1f 84 00 00 00 00 00

0000000000106990 <_ZN4acos9scheduler16get_thread_countEv>:
  106990:	55                   	push   %rbp
  106991:	48 89 e5             	mov    %rsp,%rbp
  106994:	48 83 ec 20          	sub    $0x20,%rsp
  106998:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  10699f:	00
  1069a0:	e8 9b fb ff ff       	call   106540 <_ZN4acos9scheduler14get_run_queuesEv>
  1069a5:	48 89 45 f0          	mov    %rax,-0x10(%rbp)
  1069a9:	c7 45 ec 00 00 00 00 	movl   $0x0,-0x14(%rbp)
  1069b0:	83 7d ec 40          	cmpl   $0x40,-0x14(%rbp)
  1069b4:	0f 8d 28 00 00 00    	jge    1069e2 <_ZN4acos9scheduler16get_thread_countEv+0x52>
  1069ba:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  1069be:	48 63 4d ec          	movslq -0x14(%rbp),%rcx
  1069c2:	48 6b c9 18          	imul   $0x18,%rcx,%rcx
  1069c6:	48 01 c8             	add    %rcx,%rax
  1069c9:	8b 40 10             	mov    0x10(%rax),%eax
  1069cc:	48 03 45 f8          	add    -0x8(%rbp),%rax
  1069d0:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  1069d4:	8b 45 ec             	mov    -0x14(%rbp),%eax
  1069d7:	83 c0 01             	add    $0x1,%eax
  1069da:	89 45 ec             	mov    %eax,-0x14(%rbp)
  1069dd:	e9 ce ff ff ff       	jmp    1069b0 <_ZN4acos9scheduler16get_thread_countEv+0x20>
  1069e2:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  1069e6:	48 83 c4 20          	add    $0x20,%rsp
  1069ea:	5d                   	pop    %rbp
  1069eb:	c3                   	ret
  1069ec:	0f 1f 40 00          	nopl   0x0(%rax)

00000000001069f0 <_ZN4acos9scheduler24get_running_thread_countEv>:
  1069f0:	55                   	push   %rbp
  1069f1:	48 89 e5             	mov    %rsp,%rbp
  1069f4:	e8 97 ff ff ff       	call   106990 <_ZN4acos9scheduler16get_thread_countEv>
  1069f9:	5d                   	pop    %rbp
  1069fa:	c3                   	ret
  1069fb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000106a00 <_ZN4acos9scheduler13create_threadEPFPvS1_ES1_>:
  106a00:	55                   	push   %rbp
  106a01:	48 89 e5             	mov    %rsp,%rbp
  106a04:	48 83 ec 40          	sub    $0x40,%rsp
  106a08:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  106a0c:	48 89 75 e8          	mov    %rsi,-0x18(%rbp)
  106a10:	bf 50 00 00 00       	mov    $0x50,%edi
  106a15:	e8 36 1d 00 00       	call   108750 <_ZN4acos6memory7kmallocEm>
  106a1a:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  106a1e:	48 83 7d e0 00       	cmpq   $0x0,-0x20(%rbp)
  106a23:	0f 85 0d 00 00 00    	jne    106a36 <_ZN4acos9scheduler13create_threadEPFPvS1_ES1_+0x36>
  106a29:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  106a30:	00
  106a31:	e9 5b 01 00 00       	jmp    106b91 <_ZN4acos9scheduler13create_threadEPFPvS1_ES1_+0x191>
  106a36:	48 8b 0c 25 80 fc 10 	mov    0x10fc80,%rcx
  106a3d:	00
  106a3e:	48 89 c8             	mov    %rcx,%rax
  106a41:	48 83 c0 01          	add    $0x1,%rax
  106a45:	48 89 04 25 80 fc 10 	mov    %rax,0x10fc80
  106a4c:	00
  106a4d:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  106a51:	48 89 08             	mov    %rcx,(%rax)
  106a54:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  106a58:	c7 40 18 00 00 00 00 	movl   $0x0,0x18(%rax)
  106a5f:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  106a63:	48 c7 40 20 00 00 00 	movq   $0x0,0x20(%rax)
  106a6a:	00
  106a6b:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  106a6f:	c6 40 28 00          	movb   $0x0,0x28(%rax)
  106a73:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  106a77:	48 c7 40 30 00 00 00 	movq   $0x0,0x30(%rax)
  106a7e:	00
  106a7f:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  106a83:	48 c7 40 38 00 00 00 	movq   $0x0,0x38(%rax)
  106a8a:	00
  106a8b:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
  106a8f:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  106a93:	48 89 48 40          	mov    %rcx,0x40(%rax)
  106a97:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  106a9b:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  106a9f:	48 89 48 48          	mov    %rcx,0x48(%rax)
  106aa3:	48 c7 45 d8 00 40 00 	movq   $0x4000,-0x28(%rbp)
  106aaa:	00
  106aab:	bf 00 40 00 00       	mov    $0x4000,%edi
  106ab0:	e8 9b 1c 00 00       	call   108750 <_ZN4acos6memory7kmallocEm>
  106ab5:	48 89 45 d0          	mov    %rax,-0x30(%rbp)
  106ab9:	48 83 7d d0 00       	cmpq   $0x0,-0x30(%rbp)
  106abe:	0f 85 16 00 00 00    	jne    106ada <_ZN4acos9scheduler13create_threadEPFPvS1_ES1_+0xda>
  106ac4:	48 8b 7d e0          	mov    -0x20(%rbp),%rdi
  106ac8:	e8 53 1d 00 00       	call   108820 <_ZN4acos6memory5kfreeEPv>
  106acd:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  106ad4:	00
  106ad5:	e9 b7 00 00 00       	jmp    106b91 <_ZN4acos9scheduler13create_threadEPFPvS1_ES1_+0x191>
  106ada:	48 8b 4d d0          	mov    -0x30(%rbp),%rcx
  106ade:	48 81 c1 00 40 00 00 	add    $0x4000,%rcx
  106ae5:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  106ae9:	48 89 48 08          	mov    %rcx,0x8(%rax)
  106aed:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  106af1:	48 8b 48 08          	mov    0x8(%rax),%rcx
  106af5:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  106af9:	48 89 48 10          	mov    %rcx,0x10(%rax)
  106afd:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  106b01:	48 8b 48 10          	mov    0x10(%rax),%rcx
  106b05:	48 83 e1 f0          	and    $0xfffffffffffffff0,%rcx
  106b09:	48 89 48 10          	mov    %rcx,0x10(%rax)
  106b0d:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  106b11:	48 8b 48 10          	mov    0x10(%rax),%rcx
  106b15:	48 83 e9 08          	sub    $0x8,%rcx
  106b19:	48 89 48 10          	mov    %rcx,0x10(%rax)
  106b1d:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  106b21:	48 8b 40 10          	mov    0x10(%rax),%rax
  106b25:	48 c7 00 00 00 00 00 	movq   $0x0,(%rax)
  106b2c:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  106b30:	48 8b 48 10          	mov    0x10(%rax),%rcx
  106b34:	48 83 e9 08          	sub    $0x8,%rcx
  106b38:	48 89 48 10          	mov    %rcx,0x10(%rax)
  106b3c:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
  106b40:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  106b44:	48 8b 40 10          	mov    0x10(%rax),%rax
  106b48:	48 89 08             	mov    %rcx,(%rax)
  106b4b:	c7 45 cc 00 00 00 00 	movl   $0x0,-0x34(%rbp)
  106b52:	83 7d cc 06          	cmpl   $0x6,-0x34(%rbp)
  106b56:	0f 8d 2d 00 00 00    	jge    106b89 <_ZN4acos9scheduler13create_threadEPFPvS1_ES1_+0x189>
  106b5c:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  106b60:	48 8b 48 10          	mov    0x10(%rax),%rcx
  106b64:	48 83 e9 08          	sub    $0x8,%rcx
  106b68:	48 89 48 10          	mov    %rcx,0x10(%rax)
  106b6c:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  106b70:	48 8b 40 10          	mov    0x10(%rax),%rax
  106b74:	48 c7 00 00 00 00 00 	movq   $0x0,(%rax)
  106b7b:	8b 45 cc             	mov    -0x34(%rbp),%eax
  106b7e:	83 c0 01             	add    $0x1,%eax
  106b81:	89 45 cc             	mov    %eax,-0x34(%rbp)
  106b84:	e9 c9 ff ff ff       	jmp    106b52 <_ZN4acos9scheduler13create_threadEPFPvS1_ES1_+0x152>
  106b89:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  106b8d:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  106b91:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  106b95:	48 83 c4 40          	add    $0x40,%rsp
  106b99:	5d                   	pop    %rbp
  106b9a:	c3                   	ret
  106b9b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000106ba0 <_ZN4acos9scheduler11find_threadEm>:
  106ba0:	55                   	push   %rbp
  106ba1:	48 89 e5             	mov    %rsp,%rbp
  106ba4:	48 83 ec 30          	sub    $0x30,%rsp
  106ba8:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  106bac:	e8 8f f9 ff ff       	call   106540 <_ZN4acos9scheduler14get_run_queuesEv>
  106bb1:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
  106bb5:	c7 45 e4 00 00 00 00 	movl   $0x0,-0x1c(%rbp)
  106bbc:	83 7d e4 40          	cmpl   $0x40,-0x1c(%rbp)
  106bc0:	0f 8d 63 00 00 00    	jge    106c29 <_ZN4acos9scheduler11find_threadEm+0x89>
  106bc6:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  106bca:	48 63 4d e4          	movslq -0x1c(%rbp),%rcx
  106bce:	48 6b c9 18          	imul   $0x18,%rcx,%rcx
  106bd2:	48 01 c8             	add    %rcx,%rax
  106bd5:	48 8b 00             	mov    (%rax),%rax
  106bd8:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
  106bdc:	48 83 7d d8 00       	cmpq   $0x0,-0x28(%rbp)
  106be1:	0f 84 2f 00 00 00    	je     106c16 <_ZN4acos9scheduler11find_threadEm+0x76>
  106be7:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  106beb:	48 8b 00             	mov    (%rax),%rax
  106bee:	48 3b 45 f0          	cmp    -0x10(%rbp),%rax
  106bf2:	0f 85 0d 00 00 00    	jne    106c05 <_ZN4acos9scheduler11find_threadEm+0x65>
  106bf8:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  106bfc:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  106c00:	e9 2c 00 00 00       	jmp    106c31 <_ZN4acos9scheduler11find_threadEm+0x91>
  106c05:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  106c09:	48 8b 40 38          	mov    0x38(%rax),%rax
  106c0d:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
  106c11:	e9 c6 ff ff ff       	jmp    106bdc <_ZN4acos9scheduler11find_threadEm+0x3c>
  106c16:	e9 00 00 00 00       	jmp    106c1b <_ZN4acos9scheduler11find_threadEm+0x7b>
  106c1b:	8b 45 e4             	mov    -0x1c(%rbp),%eax
  106c1e:	83 c0 01             	add    $0x1,%eax
  106c21:	89 45 e4             	mov    %eax,-0x1c(%rbp)
  106c24:	e9 93 ff ff ff       	jmp    106bbc <_ZN4acos9scheduler11find_threadEm+0x1c>
  106c29:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  106c30:	00
  106c31:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  106c35:	48 83 c4 30          	add    $0x30,%rsp
  106c39:	5d                   	pop    %rbp
  106c3a:	c3                   	ret
  106c3b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000106c40 <_ZN4acos9scheduler12find_processEm>:
  106c40:	55                   	push   %rbp
  106c41:	48 89 e5             	mov    %rsp,%rbp
  106c44:	48 83 ec 10          	sub    $0x10,%rsp
  106c48:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  106c4c:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  106c50:	e8 fb f7 ff ff       	call   106450 <_ZN4acos9scheduler18process_table_findEm>
  106c55:	48 83 c4 10          	add    $0x10,%rsp
  106c59:	5d                   	pop    %rbp
  106c5a:	c3                   	ret
  106c5b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000106c60 <_ZN4acos3hal12tss_set_rsp0Em>:
  106c60:	55                   	push   %rbp
  106c61:	48 89 e5             	mov    %rsp,%rbp
  106c64:	50                   	push   %rax
  106c65:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  106c69:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  106c6d:	48 89 04 25 44 f8 15 	mov    %rax,0x15f844
  106c74:	00
  106c75:	48 83 c4 08          	add    $0x8,%rsp
  106c79:	5d                   	pop    %rbp
  106c7a:	c3                   	ret
  106c7b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000106c80 <_ZN4acos3hal8gdt_initEv>:
  106c80:	55                   	push   %rbp
  106c81:	48 89 e5             	mov    %rsp,%rbp
  106c84:	48 83 ec 48          	sub    $0x48,%rsp
  106c88:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%rbp)
  106c8f:	83 7d fc 07          	cmpl   $0x7,-0x4(%rbp)
  106c93:	0f 8d 1e 00 00 00    	jge    106cb7 <_ZN4acos3hal8gdt_initEv+0x37>
  106c99:	48 63 45 fc          	movslq -0x4(%rbp),%rax
  106c9d:	48 c7 04 c5 b0 f8 15 	movq   $0x0,0x15f8b0(,%rax,8)
  106ca4:	00 00 00 00 00
  106ca9:	8b 45 fc             	mov    -0x4(%rbp),%eax
  106cac:	83 c0 01             	add    $0x1,%eax
  106caf:	89 45 fc             	mov    %eax,-0x4(%rbp)
  106cb2:	e9 d8 ff ff ff       	jmp    106c8f <_ZN4acos3hal8gdt_initEv+0xf>
  106cb7:	66 c7 45 f4 00 00    	movw   $0x0,-0xc(%rbp)
  106cbd:	66 c7 45 f6 00 00    	movw   $0x0,-0xa(%rbp)
  106cc3:	c6 45 f8 00          	movb   $0x0,-0x8(%rbp)
  106cc7:	c6 45 f9 00          	movb   $0x0,-0x7(%rbp)
  106ccb:	c6 45 fa 00          	movb   $0x0,-0x6(%rbp)
  106ccf:	c6 45 fb 00          	movb   $0x0,-0x5(%rbp)
  106cd3:	48 8b 45 f4          	mov    -0xc(%rbp),%rax
  106cd7:	48 89 04 25 b0 f8 15 	mov    %rax,0x15f8b0
  106cde:	00
  106cdf:	66 c7 45 ec 00 00    	movw   $0x0,-0x14(%rbp)
  106ce5:	66 c7 45 ee 00 00    	movw   $0x0,-0x12(%rbp)
  106ceb:	c6 45 f0 00          	movb   $0x0,-0x10(%rbp)
  106cef:	c6 45 f1 9a          	movb   $0x9a,-0xf(%rbp)
  106cf3:	c6 45 f2 20          	movb   $0x20,-0xe(%rbp)
  106cf7:	c6 45 f3 00          	movb   $0x0,-0xd(%rbp)
  106cfb:	48 8b 45 ec          	mov    -0x14(%rbp),%rax
  106cff:	48 89 04 25 b8 f8 15 	mov    %rax,0x15f8b8
  106d06:	00
  106d07:	66 c7 45 e4 00 00    	movw   $0x0,-0x1c(%rbp)
  106d0d:	66 c7 45 e6 00 00    	movw   $0x0,-0x1a(%rbp)
  106d13:	c6 45 e8 00          	movb   $0x0,-0x18(%rbp)
  106d17:	c6 45 e9 92          	movb   $0x92,-0x17(%rbp)
  106d1b:	c6 45 ea 00          	movb   $0x0,-0x16(%rbp)
  106d1f:	c6 45 eb 00          	movb   $0x0,-0x15(%rbp)
  106d23:	48 8b 45 e4          	mov    -0x1c(%rbp),%rax
  106d27:	48 89 04 25 c0 f8 15 	mov    %rax,0x15f8c0
  106d2e:	00
  106d2f:	66 c7 45 dc 00 00    	movw   $0x0,-0x24(%rbp)
  106d35:	66 c7 45 de 00 00    	movw   $0x0,-0x22(%rbp)
  106d3b:	c6 45 e0 00          	movb   $0x0,-0x20(%rbp)
  106d3f:	c6 45 e1 f2          	movb   $0xf2,-0x1f(%rbp)
  106d43:	c6 45 e2 00          	movb   $0x0,-0x1e(%rbp)
  106d47:	c6 45 e3 00          	movb   $0x0,-0x1d(%rbp)
  106d4b:	48 8b 45 dc          	mov    -0x24(%rbp),%rax
  106d4f:	48 89 04 25 c8 f8 15 	mov    %rax,0x15f8c8
  106d56:	00
  106d57:	66 c7 45 d4 00 00    	movw   $0x0,-0x2c(%rbp)
  106d5d:	66 c7 45 d6 00 00    	movw   $0x0,-0x2a(%rbp)
  106d63:	c6 45 d8 00          	movb   $0x0,-0x28(%rbp)
  106d67:	c6 45 d9 fa          	movb   $0xfa,-0x27(%rbp)
  106d6b:	c6 45 da 20          	movb   $0x20,-0x26(%rbp)
  106d6f:	c6 45 db 00          	movb   $0x0,-0x25(%rbp)
  106d73:	48 8b 45 d4          	mov    -0x2c(%rbp),%rax
  106d77:	48 89 04 25 d0 f8 15 	mov    %rax,0x15f8d0
  106d7e:	00
  106d7f:	48 c7 45 c8 00 00 00 	movq   $0x0,-0x38(%rbp)
  106d86:	00
  106d87:	48 83 7d c8 68       	cmpq   $0x68,-0x38(%rbp)
  106d8c:	0f 83 1d 00 00 00    	jae    106daf <_ZN4acos3hal8gdt_initEv+0x12f>
  106d92:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  106d96:	c6 04 05 40 f8 15 00 	movb   $0x0,0x15f840(,%rax,1)
  106d9d:	00
  106d9e:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  106da2:	48 83 c0 01          	add    $0x1,%rax
  106da6:	48 89 45 c8          	mov    %rax,-0x38(%rbp)
  106daa:	e9 d8 ff ff ff       	jmp    106d87 <_ZN4acos3hal8gdt_initEv+0x107>
  106daf:	48 b8 f0 f8 15 00 00 	movabs $0x15f8f0,%rax
  106db6:	00 00 00
  106db9:	48 05 00 40 00 00    	add    $0x4000,%rax
  106dbf:	48 89 04 25 44 f8 15 	mov    %rax,0x15f844
  106dc6:	00
  106dc7:	48 b8 f0 38 16 00 00 	movabs $0x1638f0,%rax
  106dce:	00 00 00
  106dd1:	48 05 00 40 00 00    	add    $0x4000,%rax
  106dd7:	48 89 04 25 64 f8 15 	mov    %rax,0x15f864
  106dde:	00
  106ddf:	66 c7 04 25 a6 f8 15 	movw   $0x68,0x15f8a6
  106de6:	00 68 00
  106de9:	48 b8 40 f8 15 00 00 	movabs $0x15f840,%rax
  106df0:	00 00 00
  106df3:	48 89 45 c0          	mov    %rax,-0x40(%rbp)
  106df7:	c7 45 bc 67 00 00 00 	movl   $0x67,-0x44(%rbp)
  106dfe:	8b 45 bc             	mov    -0x44(%rbp),%eax
  106e01:	25 ff ff 00 00       	and    $0xffff,%eax
  106e06:	66 89 04 25 d8 f8 15 	mov    %ax,0x15f8d8
  106e0d:	00
  106e0e:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  106e12:	48 25 ff ff 00 00    	and    $0xffff,%rax
  106e18:	66 89 04 25 da f8 15 	mov    %ax,0x15f8da
  106e1f:	00
  106e20:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  106e24:	48 c1 e8 10          	shr    $0x10,%rax
  106e28:	48 25 ff 00 00 00    	and    $0xff,%rax
  106e2e:	88 04 25 dc f8 15 00 	mov    %al,0x15f8dc
  106e35:	c6 04 25 dd f8 15 00 	movb   $0x89,0x15f8dd
  106e3c:	89
  106e3d:	8b 45 bc             	mov    -0x44(%rbp),%eax
  106e40:	c1 e8 10             	shr    $0x10,%eax
  106e43:	83 e0 0f             	and    $0xf,%eax
  106e46:	88 04 25 de f8 15 00 	mov    %al,0x15f8de
  106e4d:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  106e51:	48 c1 e8 18          	shr    $0x18,%rax
  106e55:	48 25 ff 00 00 00    	and    $0xff,%rax
  106e5b:	88 04 25 df f8 15 00 	mov    %al,0x15f8df
  106e62:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  106e66:	48 c1 e8 20          	shr    $0x20,%rax
  106e6a:	48 89 04 25 e0 f8 15 	mov    %rax,0x15f8e0
  106e71:	00
  106e72:	66 c7 04 25 f0 78 16 	movw   $0x37,0x1678f0
  106e79:	00 37 00
  106e7c:	48 b8 b0 f8 15 00 00 	movabs $0x15f8b0,%rax
  106e83:	00 00 00
  106e86:	48 89 04 25 f2 78 16 	mov    %rax,0x1678f2
  106e8d:	00
  106e8e:	0f 01 15 5b 0a 06 00 	lgdt   0x60a5b(%rip)        # 1678f0 <_ZN4acos3halL9g_gdt_ptrE>
  106e95:	66 b8 28 00          	mov    $0x28,%ax
  106e99:	0f 00 d8             	ltr    %eax
  106e9c:	48 83 c4 48          	add    $0x48,%rsp
  106ea0:	5d                   	pop    %rbp
  106ea1:	c3                   	ret
  106ea2:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
  106ea9:	00 00 00
  106eac:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000106eb0 <_ZN4acos3hal12idt_set_gateEhmth>:
  106eb0:	55                   	push   %rbp
  106eb1:	48 89 e5             	mov    %rsp,%rbp
  106eb4:	48 83 ec 18          	sub    $0x18,%rsp
  106eb8:	88 c8                	mov    %cl,%al
  106eba:	66 89 d1             	mov    %dx,%cx
  106ebd:	40 88 fa             	mov    %dil,%dl
  106ec0:	88 55 ff             	mov    %dl,-0x1(%rbp)
  106ec3:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  106ec7:	66 89 4d ee          	mov    %cx,-0x12(%rbp)
  106ecb:	88 45 ed             	mov    %al,-0x13(%rbp)
  106ece:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  106ed2:	48 25 ff ff 00 00    	and    $0xffff,%rax
  106ed8:	66 89 c1             	mov    %ax,%cx
  106edb:	0f b6 45 ff          	movzbl -0x1(%rbp),%eax
  106edf:	89 c2                	mov    %eax,%edx
  106ee1:	48 b8 00 79 16 00 00 	movabs $0x167900,%rax
  106ee8:	00 00 00
  106eeb:	48 c1 e2 04          	shl    $0x4,%rdx
  106eef:	48 01 d0             	add    %rdx,%rax
  106ef2:	66 89 08             	mov    %cx,(%rax)
  106ef5:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  106ef9:	48 c1 e8 10          	shr    $0x10,%rax
  106efd:	48 25 ff ff 00 00    	and    $0xffff,%rax
  106f03:	66 89 c1             	mov    %ax,%cx
  106f06:	0f b6 45 ff          	movzbl -0x1(%rbp),%eax
  106f0a:	89 c2                	mov    %eax,%edx
  106f0c:	48 b8 00 79 16 00 00 	movabs $0x167900,%rax
  106f13:	00 00 00
  106f16:	48 c1 e2 04          	shl    $0x4,%rdx
  106f1a:	48 01 d0             	add    %rdx,%rax
  106f1d:	66 89 48 06          	mov    %cx,0x6(%rax)
  106f21:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  106f25:	48 c1 e8 20          	shr    $0x20,%rax
  106f29:	48 b9 ff ff ff ff 00 	movabs $0xffffffff,%rcx
  106f30:	00 00 00
  106f33:	48 21 c8             	and    %rcx,%rax
  106f36:	89 c1                	mov    %eax,%ecx
  106f38:	0f b6 45 ff          	movzbl -0x1(%rbp),%eax
  106f3c:	89 c2                	mov    %eax,%edx
  106f3e:	48 b8 00 79 16 00 00 	movabs $0x167900,%rax
  106f45:	00 00 00
  106f48:	48 c1 e2 04          	shl    $0x4,%rdx
  106f4c:	48 01 d0             	add    %rdx,%rax
  106f4f:	89 48 08             	mov    %ecx,0x8(%rax)
  106f52:	66 8b 4d ee          	mov    -0x12(%rbp),%cx
  106f56:	0f b6 45 ff          	movzbl -0x1(%rbp),%eax
  106f5a:	89 c2                	mov    %eax,%edx
  106f5c:	48 b8 00 79 16 00 00 	movabs $0x167900,%rax
  106f63:	00 00 00
  106f66:	48 c1 e2 04          	shl    $0x4,%rdx
  106f6a:	48 01 d0             	add    %rdx,%rax
  106f6d:	66 89 48 02          	mov    %cx,0x2(%rax)
  106f71:	0f b6 45 ff          	movzbl -0x1(%rbp),%eax
  106f75:	89 c1                	mov    %eax,%ecx
  106f77:	48 b8 00 79 16 00 00 	movabs $0x167900,%rax
  106f7e:	00 00 00
  106f81:	48 c1 e1 04          	shl    $0x4,%rcx
  106f85:	48 01 c8             	add    %rcx,%rax
  106f88:	c6 40 04 00          	movb   $0x0,0x4(%rax)
  106f8c:	8a 4d ed             	mov    -0x13(%rbp),%cl
  106f8f:	0f b6 45 ff          	movzbl -0x1(%rbp),%eax
  106f93:	89 c2                	mov    %eax,%edx
  106f95:	48 b8 00 79 16 00 00 	movabs $0x167900,%rax
  106f9c:	00 00 00
  106f9f:	48 c1 e2 04          	shl    $0x4,%rdx
  106fa3:	48 01 d0             	add    %rdx,%rax
  106fa6:	88 48 05             	mov    %cl,0x5(%rax)
  106fa9:	0f b6 45 ff          	movzbl -0x1(%rbp),%eax
  106fad:	89 c1                	mov    %eax,%ecx
  106faf:	48 b8 00 79 16 00 00 	movabs $0x167900,%rax
  106fb6:	00 00 00
  106fb9:	48 c1 e1 04          	shl    $0x4,%rcx
  106fbd:	48 01 c8             	add    %rcx,%rax
  106fc0:	c7 40 0c 00 00 00 00 	movl   $0x0,0xc(%rax)
  106fc7:	48 83 c4 18          	add    $0x18,%rsp
  106fcb:	5d                   	pop    %rbp
  106fcc:	c3                   	ret
  106fcd:	0f 1f 00             	nopl   (%rax)

0000000000106fd0 <_ZN4acos3hal8idt_initEv>:
  106fd0:	55                   	push   %rbp
  106fd1:	48 89 e5             	mov    %rsp,%rbp
  106fd4:	48 83 ec 20          	sub    $0x20,%rsp
  106fd8:	66 c7 04 25 00 89 16 	movw   $0xfff,0x168900
  106fdf:	00 ff 0f
  106fe2:	48 b8 00 79 16 00 00 	movabs $0x167900,%rax
  106fe9:	00 00 00
  106fec:	48 89 04 25 02 89 16 	mov    %rax,0x168902
  106ff3:	00
  106ff4:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%rbp)
  106ffb:	81 7d fc 00 01 00 00 	cmpl   $0x100,-0x4(%rbp)
  107002:	0f 8d 27 00 00 00    	jge    10702f <_ZN4acos3hal8idt_initEv+0x5f>
  107008:	8b 45 fc             	mov    -0x4(%rbp),%eax
  10700b:	31 c9                	xor    %ecx,%ecx
  10700d:	89 ce                	mov    %ecx,%esi
  10700f:	ba 08 00 00 00       	mov    $0x8,%edx
  107014:	b9 8e 00 00 00       	mov    $0x8e,%ecx
  107019:	0f b6 f8             	movzbl %al,%edi
  10701c:	e8 8f fe ff ff       	call   106eb0 <_ZN4acos3hal12idt_set_gateEhmth>
  107021:	8b 45 fc             	mov    -0x4(%rbp),%eax
  107024:	83 c0 01             	add    $0x1,%eax
  107027:	89 45 fc             	mov    %eax,-0x4(%rbp)
  10702a:	e9 cc ff ff ff       	jmp    106ffb <_ZN4acos3hal8idt_initEv+0x2b>
  10702f:	0f 01 1d ca 18 06 00 	lidt   0x618ca(%rip)        # 168900 <_ZN4acos3halL9g_idt_ptrE>
  107036:	b9 80 00 00 c0       	mov    $0xc0000080,%ecx
  10703b:	0f 32                	rdmsr
  10703d:	89 45 f8             	mov    %eax,-0x8(%rbp)
  107040:	89 55 f4             	mov    %edx,-0xc(%rbp)
  107043:	8b 45 f8             	mov    -0x8(%rbp),%eax
  107046:	83 c8 01             	or     $0x1,%eax
  107049:	89 45 f8             	mov    %eax,-0x8(%rbp)
  10704c:	8b 45 f8             	mov    -0x8(%rbp),%eax
  10704f:	8b 55 f4             	mov    -0xc(%rbp),%edx
  107052:	b9 80 00 00 c0       	mov    $0xc0000080,%ecx
  107057:	0f 30                	wrmsr
  107059:	c7 45 f8 00 00 00 00 	movl   $0x0,-0x8(%rbp)
  107060:	c7 45 f4 08 00 13 00 	movl   $0x130008,-0xc(%rbp)
  107067:	8b 45 f8             	mov    -0x8(%rbp),%eax
  10706a:	8b 55 f4             	mov    -0xc(%rbp),%edx
  10706d:	b9 81 00 00 c0       	mov    $0xc0000081,%ecx
  107072:	0f 30                	wrmsr
  107074:	48 b8 10 e6 10 00 00 	movabs $0x10e610,%rax
  10707b:	00 00 00
  10707e:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
  107082:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  107086:	89 45 f8             	mov    %eax,-0x8(%rbp)
  107089:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  10708d:	48 c1 e8 20          	shr    $0x20,%rax
  107091:	89 45 f4             	mov    %eax,-0xc(%rbp)
  107094:	8b 45 f8             	mov    -0x8(%rbp),%eax
  107097:	8b 55 f4             	mov    -0xc(%rbp),%edx
  10709a:	b9 82 00 00 c0       	mov    $0xc0000082,%ecx
  10709f:	0f 30                	wrmsr
  1070a1:	c7 45 f8 00 02 00 00 	movl   $0x200,-0x8(%rbp)
  1070a8:	c7 45 f4 00 00 00 00 	movl   $0x0,-0xc(%rbp)
  1070af:	8b 45 f8             	mov    -0x8(%rbp),%eax
  1070b2:	8b 55 f4             	mov    -0xc(%rbp),%edx
  1070b5:	b9 84 00 00 c0       	mov    $0xc0000084,%ecx
  1070ba:	0f 30                	wrmsr
  1070bc:	48 83 c4 20          	add    $0x20,%rsp
  1070c0:	5d                   	pop    %rbp
  1070c1:	c3                   	ret
  1070c2:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
  1070c9:	00 00 00
  1070cc:	0f 1f 40 00          	nopl   0x0(%rax)

00000000001070d0 <_ZN4acos6memory15get_total_pagesEv>:
  1070d0:	55                   	push   %rbp
  1070d1:	48 89 e5             	mov    %rsp,%rbp
  1070d4:	48 8b 04 25 10 89 16 	mov    0x168910,%rax
  1070db:	00
  1070dc:	5d                   	pop    %rbp
  1070dd:	c3                   	ret
  1070de:	66 90                	xchg   %ax,%ax

00000000001070e0 <_ZN4acos6memory14get_used_pagesEv>:
  1070e0:	55                   	push   %rbp
  1070e1:	48 89 e5             	mov    %rsp,%rbp
  1070e4:	48 8b 04 25 18 89 16 	mov    0x168918,%rax
  1070eb:	00
  1070ec:	5d                   	pop    %rbp
  1070ed:	c3                   	ret
  1070ee:	66 90                	xchg   %ax,%ax

00000000001070f0 <_ZN4acos6memory8pmm_initEPNS_8BootInfoE>:
  1070f0:	55                   	push   %rbp
  1070f1:	48 89 e5             	mov    %rsp,%rbp
  1070f4:	48 81 ec c0 00 00 00 	sub    $0xc0,%rsp
  1070fb:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  1070ff:	48 83 7d f8 00       	cmpq   $0x0,-0x8(%rbp)
  107104:	0f 84 0e 00 00 00    	je     107118 <_ZN4acos6memory8pmm_initEPNS_8BootInfoE+0x28>
  10710a:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10710e:	48 83 38 00          	cmpq   $0x0,(%rax)
  107112:	0f 85 14 00 00 00    	jne    10712c <_ZN4acos6memory8pmm_initEPNS_8BootInfoE+0x3c>
  107118:	48 bf 06 f9 10 00 00 	movabs $0x10f906,%rdi
  10711f:	00 00 00
  107122:	e8 69 33 00 00       	call   10a490 <_ZN4acos3hal12serial_printEPKc>
  107127:	e9 a2 03 00 00       	jmp    1074ce <_ZN4acos6memory8pmm_initEPNS_8BootInfoE+0x3de>
  10712c:	48 c7 45 f0 00 00 00 	movq   $0x0,-0x10(%rbp)
  107133:	00
  107134:	48 c7 45 e8 00 00 00 	movq   $0x0,-0x18(%rbp)
  10713b:	00
  10713c:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  107140:	48 8b 4d f8          	mov    -0x8(%rbp),%rcx
  107144:	48 8b 09             	mov    (%rcx),%rcx
  107147:	48 3b 41 08          	cmp    0x8(%rcx),%rax
  10714b:	0f 83 68 00 00 00    	jae    1071b9 <_ZN4acos6memory8pmm_initEPNS_8BootInfoE+0xc9>
  107151:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  107155:	48 8b 00             	mov    (%rax),%rax
  107158:	48 8b 00             	mov    (%rax),%rax
  10715b:	48 6b 4d e8 18       	imul   $0x18,-0x18(%rbp),%rcx
  107160:	48 01 c8             	add    %rcx,%rax
  107163:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  107167:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  10716b:	83 78 10 01          	cmpl   $0x1,0x10(%rax)
  10716f:	0f 84 05 00 00 00    	je     10717a <_ZN4acos6memory8pmm_initEPNS_8BootInfoE+0x8a>
  107175:	e9 2e 00 00 00       	jmp    1071a8 <_ZN4acos6memory8pmm_initEPNS_8BootInfoE+0xb8>
  10717a:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  10717e:	48 8b 00             	mov    (%rax),%rax
  107181:	48 8b 4d e0          	mov    -0x20(%rbp),%rcx
  107185:	48 03 41 08          	add    0x8(%rcx),%rax
  107189:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
  10718d:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  107191:	48 3b 45 f0          	cmp    -0x10(%rbp),%rax
  107195:	0f 86 08 00 00 00    	jbe    1071a3 <_ZN4acos6memory8pmm_initEPNS_8BootInfoE+0xb3>
  10719b:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  10719f:	48 89 45 f0          	mov    %rax,-0x10(%rbp)
  1071a3:	e9 00 00 00 00       	jmp    1071a8 <_ZN4acos6memory8pmm_initEPNS_8BootInfoE+0xb8>
  1071a8:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  1071ac:	48 83 c0 01          	add    $0x1,%rax
  1071b0:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
  1071b4:	e9 83 ff ff ff       	jmp    10713c <_ZN4acos6memory8pmm_initEPNS_8BootInfoE+0x4c>
  1071b9:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  1071bd:	48 c1 e8 0c          	shr    $0xc,%rax
  1071c1:	48 89 04 25 10 89 16 	mov    %rax,0x168910
  1071c8:	00
  1071c9:	48 8b 04 25 10 89 16 	mov    0x168910,%rax
  1071d0:	00
  1071d1:	48 c1 e8 06          	shr    $0x6,%rax
  1071d5:	48 83 c0 01          	add    $0x1,%rax
  1071d9:	48 89 04 25 20 89 16 	mov    %rax,0x168920
  1071e0:	00
  1071e1:	48 8b 04 25 20 89 16 	mov    0x168920,%rax
  1071e8:	00
  1071e9:	48 c1 e0 03          	shl    $0x3,%rax
  1071ed:	48 89 45 d0          	mov    %rax,-0x30(%rbp)
  1071f1:	48 bf 00 40 17 00 00 	movabs $0x174000,%rdi
  1071f8:	00 00 00
  1071fb:	be 00 10 00 00       	mov    $0x1000,%esi
  107200:	e8 db 02 00 00       	call   1074e0 <_ZN4acos6memoryL8align_upEmm>
  107205:	48 89 45 c8          	mov    %rax,-0x38(%rbp)
  107209:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  10720d:	48 89 45 c0          	mov    %rax,-0x40(%rbp)
  107211:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  107215:	48 03 45 d0          	add    -0x30(%rbp),%rax
  107219:	48 89 45 b8          	mov    %rax,-0x48(%rbp)
  10721d:	48 8b 7d b8          	mov    -0x48(%rbp),%rdi
  107221:	be 00 10 00 00       	mov    $0x1000,%esi
  107226:	e8 b5 02 00 00       	call   1074e0 <_ZN4acos6memoryL8align_upEmm>
  10722b:	48 89 45 b8          	mov    %rax,-0x48(%rbp)
  10722f:	c6 45 b7 00          	movb   $0x0,-0x49(%rbp)
  107233:	48 c7 45 a8 00 00 00 	movq   $0x0,-0x58(%rbp)
  10723a:	00
  10723b:	48 8b 45 a8          	mov    -0x58(%rbp),%rax
  10723f:	48 8b 4d f8          	mov    -0x8(%rbp),%rcx
  107243:	48 8b 09             	mov    (%rcx),%rcx
  107246:	48 3b 41 08          	cmp    0x8(%rcx),%rax
  10724a:	0f 83 7a 00 00 00    	jae    1072ca <_ZN4acos6memory8pmm_initEPNS_8BootInfoE+0x1da>
  107250:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  107254:	48 8b 00             	mov    (%rax),%rax
  107257:	48 8b 00             	mov    (%rax),%rax
  10725a:	48 6b 4d a8 18       	imul   $0x18,-0x58(%rbp),%rcx
  10725f:	48 01 c8             	add    %rcx,%rax
  107262:	48 89 45 a0          	mov    %rax,-0x60(%rbp)
  107266:	48 8b 45 a0          	mov    -0x60(%rbp),%rax
  10726a:	83 78 10 01          	cmpl   $0x1,0x10(%rax)
  10726e:	0f 84 05 00 00 00    	je     107279 <_ZN4acos6memory8pmm_initEPNS_8BootInfoE+0x189>
  107274:	e9 40 00 00 00       	jmp    1072b9 <_ZN4acos6memory8pmm_initEPNS_8BootInfoE+0x1c9>
  107279:	48 8b 45 a0          	mov    -0x60(%rbp),%rax
  10727d:	48 8b 00             	mov    (%rax),%rax
  107280:	48 8b 4d a0          	mov    -0x60(%rbp),%rcx
  107284:	48 03 41 08          	add    0x8(%rcx),%rax
  107288:	48 89 45 98          	mov    %rax,-0x68(%rbp)
  10728c:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  107290:	48 8b 4d a0          	mov    -0x60(%rbp),%rcx
  107294:	48 3b 01             	cmp    (%rcx),%rax
  107297:	0f 82 17 00 00 00    	jb     1072b4 <_ZN4acos6memory8pmm_initEPNS_8BootInfoE+0x1c4>
  10729d:	48 8b 45 b8          	mov    -0x48(%rbp),%rax
  1072a1:	48 3b 45 98          	cmp    -0x68(%rbp),%rax
  1072a5:	0f 87 09 00 00 00    	ja     1072b4 <_ZN4acos6memory8pmm_initEPNS_8BootInfoE+0x1c4>
  1072ab:	c6 45 b7 01          	movb   $0x1,-0x49(%rbp)
  1072af:	e9 16 00 00 00       	jmp    1072ca <_ZN4acos6memory8pmm_initEPNS_8BootInfoE+0x1da>
  1072b4:	e9 00 00 00 00       	jmp    1072b9 <_ZN4acos6memory8pmm_initEPNS_8BootInfoE+0x1c9>
  1072b9:	48 8b 45 a8          	mov    -0x58(%rbp),%rax
  1072bd:	48 83 c0 01          	add    $0x1,%rax
  1072c1:	48 89 45 a8          	mov    %rax,-0x58(%rbp)
  1072c5:	e9 71 ff ff ff       	jmp    10723b <_ZN4acos6memory8pmm_initEPNS_8BootInfoE+0x14b>
  1072ca:	f6 45 b7 01          	testb  $0x1,-0x49(%rbp)
  1072ce:	0f 85 14 00 00 00    	jne    1072e8 <_ZN4acos6memory8pmm_initEPNS_8BootInfoE+0x1f8>
  1072d4:	48 bf 2d f9 10 00 00 	movabs $0x10f92d,%rdi
  1072db:	00 00 00
  1072de:	e8 ad 31 00 00       	call   10a490 <_ZN4acos3hal12serial_printEPKc>
  1072e3:	e9 e6 01 00 00       	jmp    1074ce <_ZN4acos6memory8pmm_initEPNS_8BootInfoE+0x3de>
  1072e8:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  1072ec:	48 89 04 25 28 89 16 	mov    %rax,0x168928
  1072f3:	00
  1072f4:	48 c7 45 90 00 00 00 	movq   $0x0,-0x70(%rbp)
  1072fb:	00
  1072fc:	48 8b 45 90          	mov    -0x70(%rbp),%rax
  107300:	48 3b 04 25 20 89 16 	cmp    0x168920,%rax
  107307:	00
  107308:	0f 83 25 00 00 00    	jae    107333 <_ZN4acos6memory8pmm_initEPNS_8BootInfoE+0x243>
  10730e:	48 8b 04 25 28 89 16 	mov    0x168928,%rax
  107315:	00
  107316:	48 8b 4d 90          	mov    -0x70(%rbp),%rcx
  10731a:	48 c7 04 c8 ff ff ff 	movq   $0xffffffffffffffff,(%rax,%rcx,8)
  107321:	ff
  107322:	48 8b 45 90          	mov    -0x70(%rbp),%rax
  107326:	48 83 c0 01          	add    $0x1,%rax
  10732a:	48 89 45 90          	mov    %rax,-0x70(%rbp)
  10732e:	e9 c9 ff ff ff       	jmp    1072fc <_ZN4acos6memory8pmm_initEPNS_8BootInfoE+0x20c>
  107333:	48 c7 45 88 00 00 00 	movq   $0x0,-0x78(%rbp)
  10733a:	00
  10733b:	48 8b 45 88          	mov    -0x78(%rbp),%rax
  10733f:	48 8b 4d f8          	mov    -0x8(%rbp),%rcx
  107343:	48 8b 09             	mov    (%rcx),%rcx
  107346:	48 3b 41 08          	cmp    0x8(%rcx),%rax
  10734a:	0f 83 b0 00 00 00    	jae    107400 <_ZN4acos6memory8pmm_initEPNS_8BootInfoE+0x310>
  107350:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  107354:	48 8b 00             	mov    (%rax),%rax
  107357:	48 8b 00             	mov    (%rax),%rax
  10735a:	48 6b 4d 88 18       	imul   $0x18,-0x78(%rbp),%rcx
  10735f:	48 01 c8             	add    %rcx,%rax
  107362:	48 89 45 80          	mov    %rax,-0x80(%rbp)
  107366:	48 8b 45 80          	mov    -0x80(%rbp),%rax
  10736a:	83 78 10 01          	cmpl   $0x1,0x10(%rax)
  10736e:	0f 85 76 00 00 00    	jne    1073ea <_ZN4acos6memory8pmm_initEPNS_8BootInfoE+0x2fa>
  107374:	48 8b 45 80          	mov    -0x80(%rbp),%rax
  107378:	48 8b 00             	mov    (%rax),%rax
  10737b:	48 c1 e8 0c          	shr    $0xc,%rax
  10737f:	48 89 85 78 ff ff ff 	mov    %rax,-0x88(%rbp)
  107386:	48 8b 45 80          	mov    -0x80(%rbp),%rax
  10738a:	48 8b 00             	mov    (%rax),%rax
  10738d:	48 8b 4d 80          	mov    -0x80(%rbp),%rcx
  107391:	48 03 41 08          	add    0x8(%rcx),%rax
  107395:	48 c1 e8 0c          	shr    $0xc,%rax
  107399:	48 89 85 70 ff ff ff 	mov    %rax,-0x90(%rbp)
  1073a0:	48 8b 85 78 ff ff ff 	mov    -0x88(%rbp),%rax
  1073a7:	48 89 85 68 ff ff ff 	mov    %rax,-0x98(%rbp)
  1073ae:	48 8b 85 68 ff ff ff 	mov    -0x98(%rbp),%rax
  1073b5:	48 3b 85 70 ff ff ff 	cmp    -0x90(%rbp),%rax
  1073bc:	0f 83 23 00 00 00    	jae    1073e5 <_ZN4acos6memory8pmm_initEPNS_8BootInfoE+0x2f5>
  1073c2:	48 8b bd 68 ff ff ff 	mov    -0x98(%rbp),%rdi
  1073c9:	e8 52 01 00 00       	call   107520 <_ZN4acos6memoryL12bitmap_clearEm>
  1073ce:	48 8b 85 68 ff ff ff 	mov    -0x98(%rbp),%rax
  1073d5:	48 83 c0 01          	add    $0x1,%rax
  1073d9:	48 89 85 68 ff ff ff 	mov    %rax,-0x98(%rbp)
  1073e0:	e9 c9 ff ff ff       	jmp    1073ae <_ZN4acos6memory8pmm_initEPNS_8BootInfoE+0x2be>
  1073e5:	e9 00 00 00 00       	jmp    1073ea <_ZN4acos6memory8pmm_initEPNS_8BootInfoE+0x2fa>
  1073ea:	e9 00 00 00 00       	jmp    1073ef <_ZN4acos6memory8pmm_initEPNS_8BootInfoE+0x2ff>
  1073ef:	48 8b 45 88          	mov    -0x78(%rbp),%rax
  1073f3:	48 83 c0 01          	add    $0x1,%rax
  1073f7:	48 89 45 88          	mov    %rax,-0x78(%rbp)
  1073fb:	e9 3b ff ff ff       	jmp    10733b <_ZN4acos6memory8pmm_initEPNS_8BootInfoE+0x24b>
  107400:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  107404:	48 c1 e8 0c          	shr    $0xc,%rax
  107408:	48 89 85 60 ff ff ff 	mov    %rax,-0xa0(%rbp)
  10740f:	48 8b 45 b8          	mov    -0x48(%rbp),%rax
  107413:	48 c1 e8 0c          	shr    $0xc,%rax
  107417:	48 89 85 58 ff ff ff 	mov    %rax,-0xa8(%rbp)
  10741e:	48 8b 85 60 ff ff ff 	mov    -0xa0(%rbp),%rax
  107425:	48 89 85 50 ff ff ff 	mov    %rax,-0xb0(%rbp)
  10742c:	48 8b 85 50 ff ff ff 	mov    -0xb0(%rbp),%rax
  107433:	48 3b 85 58 ff ff ff 	cmp    -0xa8(%rbp),%rax
  10743a:	0f 83 23 00 00 00    	jae    107463 <_ZN4acos6memory8pmm_initEPNS_8BootInfoE+0x373>
  107440:	48 8b bd 50 ff ff ff 	mov    -0xb0(%rbp),%rdi
  107447:	e8 14 01 00 00       	call   107560 <_ZN4acos6memoryL10bitmap_setEm>
  10744c:	48 8b 85 50 ff ff ff 	mov    -0xb0(%rbp),%rax
  107453:	48 83 c0 01          	add    $0x1,%rax
  107457:	48 89 85 50 ff ff ff 	mov    %rax,-0xb0(%rbp)
  10745e:	e9 c9 ff ff ff       	jmp    10742c <_ZN4acos6memory8pmm_initEPNS_8BootInfoE+0x33c>
  107463:	31 c0                	xor    %eax,%eax
  107465:	89 c7                	mov    %eax,%edi
  107467:	e8 f4 00 00 00       	call   107560 <_ZN4acos6memoryL10bitmap_setEm>
  10746c:	48 c7 85 48 ff ff ff 	movq   $0x100000,-0xb8(%rbp)
  107473:	00 00 10 00
  107477:	48 8b 85 48 ff ff ff 	mov    -0xb8(%rbp),%rax
  10747e:	48 89 85 40 ff ff ff 	mov    %rax,-0xc0(%rbp)
  107485:	48 8b 85 40 ff ff ff 	mov    -0xc0(%rbp),%rax
  10748c:	48 3b 45 c8          	cmp    -0x38(%rbp),%rax
  107490:	0f 83 29 00 00 00    	jae    1074bf <_ZN4acos6memory8pmm_initEPNS_8BootInfoE+0x3cf>
  107496:	48 8b bd 40 ff ff ff 	mov    -0xc0(%rbp),%rdi
  10749d:	48 c1 ef 0c          	shr    $0xc,%rdi
  1074a1:	e8 ba 00 00 00       	call   107560 <_ZN4acos6memoryL10bitmap_setEm>
  1074a6:	48 8b 85 40 ff ff ff 	mov    -0xc0(%rbp),%rax
  1074ad:	48 05 00 10 00 00    	add    $0x1000,%rax
  1074b3:	48 89 85 40 ff ff ff 	mov    %rax,-0xc0(%rbp)
  1074ba:	e9 c6 ff ff ff       	jmp    107485 <_ZN4acos6memory8pmm_initEPNS_8BootInfoE+0x395>
  1074bf:	48 bf 67 f9 10 00 00 	movabs $0x10f967,%rdi
  1074c6:	00 00 00
  1074c9:	e8 c2 2f 00 00       	call   10a490 <_ZN4acos3hal12serial_printEPKc>
  1074ce:	48 81 c4 c0 00 00 00 	add    $0xc0,%rsp
  1074d5:	5d                   	pop    %rbp
  1074d6:	c3                   	ret
  1074d7:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
  1074de:	00 00

00000000001074e0 <_ZN4acos6memoryL8align_upEmm>:
  1074e0:	55                   	push   %rbp
  1074e1:	48 89 e5             	mov    %rsp,%rbp
  1074e4:	48 83 ec 10          	sub    $0x10,%rsp
  1074e8:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  1074ec:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  1074f0:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  1074f4:	48 03 45 f0          	add    -0x10(%rbp),%rax
  1074f8:	48 83 e8 01          	sub    $0x1,%rax
  1074fc:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
  107500:	48 83 e9 01          	sub    $0x1,%rcx
  107504:	48 83 f1 ff          	xor    $0xffffffffffffffff,%rcx
  107508:	48 21 c8             	and    %rcx,%rax
  10750b:	48 83 c4 10          	add    $0x10,%rsp
  10750f:	5d                   	pop    %rbp
  107510:	c3                   	ret
  107511:	66 66 66 66 66 66 2e 	data16 data16 data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
  107518:	0f 1f 84 00 00 00 00
  10751f:	00

0000000000107520 <_ZN4acos6memoryL12bitmap_clearEm>:
  107520:	55                   	push   %rbp
  107521:	48 89 e5             	mov    %rsp,%rbp
  107524:	50                   	push   %rax
  107525:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  107529:	48 8b 4d f8          	mov    -0x8(%rbp),%rcx
  10752d:	48 83 e1 3f          	and    $0x3f,%rcx
  107531:	ba 01 00 00 00       	mov    $0x1,%edx
  107536:	48 d3 e2             	shl    %cl,%rdx
  107539:	48 83 f2 ff          	xor    $0xffffffffffffffff,%rdx
  10753d:	48 8b 04 25 28 89 16 	mov    0x168928,%rax
  107544:	00
  107545:	48 8b 4d f8          	mov    -0x8(%rbp),%rcx
  107549:	48 c1 e9 06          	shr    $0x6,%rcx
  10754d:	48 23 14 c8          	and    (%rax,%rcx,8),%rdx
  107551:	48 89 14 c8          	mov    %rdx,(%rax,%rcx,8)
  107555:	48 83 c4 08          	add    $0x8,%rsp
  107559:	5d                   	pop    %rbp
  10755a:	c3                   	ret
  10755b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000107560 <_ZN4acos6memoryL10bitmap_setEm>:
  107560:	55                   	push   %rbp
  107561:	48 89 e5             	mov    %rsp,%rbp
  107564:	50                   	push   %rax
  107565:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  107569:	48 8b 4d f8          	mov    -0x8(%rbp),%rcx
  10756d:	48 83 e1 3f          	and    $0x3f,%rcx
  107571:	ba 01 00 00 00       	mov    $0x1,%edx
  107576:	48 d3 e2             	shl    %cl,%rdx
  107579:	48 8b 04 25 28 89 16 	mov    0x168928,%rax
  107580:	00
  107581:	48 8b 4d f8          	mov    -0x8(%rbp),%rcx
  107585:	48 c1 e9 06          	shr    $0x6,%rcx
  107589:	48 0b 14 c8          	or     (%rax,%rcx,8),%rdx
  10758d:	48 89 14 c8          	mov    %rdx,(%rax,%rcx,8)
  107591:	48 83 c4 08          	add    $0x8,%rsp
  107595:	5d                   	pop    %rbp
  107596:	c3                   	ret
  107597:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
  10759e:	00 00

00000000001075a0 <_ZN4acos6memory9pmm_allocEv>:
  1075a0:	55                   	push   %rbp
  1075a1:	48 89 e5             	mov    %rsp,%rbp
  1075a4:	48 83 ec 10          	sub    $0x10,%rsp
  1075a8:	48 83 3c 25 28 89 16 	cmpq   $0x0,0x168928
  1075af:	00 00
  1075b1:	0f 85 0d 00 00 00    	jne    1075c4 <_ZN4acos6memory9pmm_allocEv+0x24>
  1075b7:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  1075be:	00
  1075bf:	e9 77 00 00 00       	jmp    10763b <_ZN4acos6memory9pmm_allocEv+0x9b>
  1075c4:	48 c7 45 f0 01 00 00 	movq   $0x1,-0x10(%rbp)
  1075cb:	00
  1075cc:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  1075d0:	48 3b 04 25 10 89 16 	cmp    0x168910,%rax
  1075d7:	00
  1075d8:	0f 83 55 00 00 00    	jae    107633 <_ZN4acos6memory9pmm_allocEv+0x93>
  1075de:	48 8b 7d f0          	mov    -0x10(%rbp),%rdi
  1075e2:	e8 69 00 00 00       	call   107650 <_ZN4acos6memoryL11bitmap_testEm>
  1075e7:	a8 01                	test   $0x1,%al
  1075e9:	0f 85 2e 00 00 00    	jne    10761d <_ZN4acos6memory9pmm_allocEv+0x7d>
  1075ef:	48 8b 7d f0          	mov    -0x10(%rbp),%rdi
  1075f3:	e8 68 ff ff ff       	call   107560 <_ZN4acos6memoryL10bitmap_setEm>
  1075f8:	48 8b 04 25 18 89 16 	mov    0x168918,%rax
  1075ff:	00
  107600:	48 83 c0 01          	add    $0x1,%rax
  107604:	48 89 04 25 18 89 16 	mov    %rax,0x168918
  10760b:	00
  10760c:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  107610:	48 c1 e0 0c          	shl    $0xc,%rax
  107614:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  107618:	e9 1e 00 00 00       	jmp    10763b <_ZN4acos6memory9pmm_allocEv+0x9b>
  10761d:	e9 00 00 00 00       	jmp    107622 <_ZN4acos6memory9pmm_allocEv+0x82>
  107622:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  107626:	48 83 c0 01          	add    $0x1,%rax
  10762a:	48 89 45 f0          	mov    %rax,-0x10(%rbp)
  10762e:	e9 99 ff ff ff       	jmp    1075cc <_ZN4acos6memory9pmm_allocEv+0x2c>
  107633:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  10763a:	00
  10763b:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10763f:	48 83 c4 10          	add    $0x10,%rsp
  107643:	5d                   	pop    %rbp
  107644:	c3                   	ret
  107645:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  10764c:	00 00 00 00

0000000000107650 <_ZN4acos6memoryL11bitmap_testEm>:
  107650:	55                   	push   %rbp
  107651:	48 89 e5             	mov    %rsp,%rbp
  107654:	50                   	push   %rax
  107655:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  107659:	48 8b 04 25 28 89 16 	mov    0x168928,%rax
  107660:	00
  107661:	48 8b 4d f8          	mov    -0x8(%rbp),%rcx
  107665:	48 c1 e9 06          	shr    $0x6,%rcx
  107669:	48 8b 04 c8          	mov    (%rax,%rcx,8),%rax
  10766d:	48 8b 4d f8          	mov    -0x8(%rbp),%rcx
  107671:	48 83 e1 3f          	and    $0x3f,%rcx
  107675:	ba 01 00 00 00       	mov    $0x1,%edx
  10767a:	48 d3 e2             	shl    %cl,%rdx
  10767d:	48 89 d1             	mov    %rdx,%rcx
  107680:	48 21 c8             	and    %rcx,%rax
  107683:	48 83 f8 00          	cmp    $0x0,%rax
  107687:	0f 95 c0             	setne  %al
  10768a:	24 01                	and    $0x1,%al
  10768c:	0f b6 c0             	movzbl %al,%eax
  10768f:	48 83 c4 08          	add    $0x8,%rsp
  107693:	5d                   	pop    %rbp
  107694:	c3                   	ret
  107695:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  10769c:	00 00 00 00

00000000001076a0 <_ZN4acos6memory20pmm_alloc_contiguousEm>:
  1076a0:	55                   	push   %rbp
  1076a1:	48 89 e5             	mov    %rsp,%rbp
  1076a4:	48 83 ec 40          	sub    $0x40,%rsp
  1076a8:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  1076ac:	48 83 3c 25 28 89 16 	cmpq   $0x0,0x168928
  1076b3:	00 00
  1076b5:	0f 84 0b 00 00 00    	je     1076c6 <_ZN4acos6memory20pmm_alloc_contiguousEm+0x26>
  1076bb:	48 83 7d f0 00       	cmpq   $0x0,-0x10(%rbp)
  1076c0:	0f 85 0d 00 00 00    	jne    1076d3 <_ZN4acos6memory20pmm_alloc_contiguousEm+0x33>
  1076c6:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  1076cd:	00
  1076ce:	e9 06 01 00 00       	jmp    1077d9 <_ZN4acos6memory20pmm_alloc_contiguousEm+0x139>
  1076d3:	48 8b 04 25 10 89 16 	mov    0x168910,%rax
  1076da:	00
  1076db:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
  1076df:	48 c7 45 e0 01 00 00 	movq   $0x1,-0x20(%rbp)
  1076e6:	00
  1076e7:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  1076eb:	48 03 45 f0          	add    -0x10(%rbp),%rax
  1076ef:	48 3b 45 e8          	cmp    -0x18(%rbp),%rax
  1076f3:	0f 87 d8 00 00 00    	ja     1077d1 <_ZN4acos6memory20pmm_alloc_contiguousEm+0x131>
  1076f9:	c6 45 df 01          	movb   $0x1,-0x21(%rbp)
  1076fd:	48 c7 45 d0 00 00 00 	movq   $0x0,-0x30(%rbp)
  107704:	00
  107705:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  107709:	48 3b 45 f0          	cmp    -0x10(%rbp),%rax
  10770d:	0f 83 45 00 00 00    	jae    107758 <_ZN4acos6memory20pmm_alloc_contiguousEm+0xb8>
  107713:	48 8b 7d e0          	mov    -0x20(%rbp),%rdi
  107717:	48 03 7d d0          	add    -0x30(%rbp),%rdi
  10771b:	e8 30 ff ff ff       	call   107650 <_ZN4acos6memoryL11bitmap_testEm>
  107720:	a8 01                	test   $0x1,%al
  107722:	0f 85 05 00 00 00    	jne    10772d <_ZN4acos6memory20pmm_alloc_contiguousEm+0x8d>
  107728:	e9 15 00 00 00       	jmp    107742 <_ZN4acos6memory20pmm_alloc_contiguousEm+0xa2>
  10772d:	c6 45 df 00          	movb   $0x0,-0x21(%rbp)
  107731:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  107735:	48 03 45 e0          	add    -0x20(%rbp),%rax
  107739:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  10773d:	e9 16 00 00 00       	jmp    107758 <_ZN4acos6memory20pmm_alloc_contiguousEm+0xb8>
  107742:	e9 00 00 00 00       	jmp    107747 <_ZN4acos6memory20pmm_alloc_contiguousEm+0xa7>
  107747:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  10774b:	48 83 c0 01          	add    $0x1,%rax
  10774f:	48 89 45 d0          	mov    %rax,-0x30(%rbp)
  107753:	e9 ad ff ff ff       	jmp    107705 <_ZN4acos6memory20pmm_alloc_contiguousEm+0x65>
  107758:	f6 45 df 01          	testb  $0x1,-0x21(%rbp)
  10775c:	0f 85 05 00 00 00    	jne    107767 <_ZN4acos6memory20pmm_alloc_contiguousEm+0xc7>
  107762:	e9 59 00 00 00       	jmp    1077c0 <_ZN4acos6memory20pmm_alloc_contiguousEm+0x120>
  107767:	48 c7 45 c8 00 00 00 	movq   $0x0,-0x38(%rbp)
  10776e:	00
  10776f:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  107773:	48 3b 45 f0          	cmp    -0x10(%rbp),%rax
  107777:	0f 83 1e 00 00 00    	jae    10779b <_ZN4acos6memory20pmm_alloc_contiguousEm+0xfb>
  10777d:	48 8b 7d e0          	mov    -0x20(%rbp),%rdi
  107781:	48 03 7d c8          	add    -0x38(%rbp),%rdi
  107785:	e8 d6 fd ff ff       	call   107560 <_ZN4acos6memoryL10bitmap_setEm>
  10778a:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  10778e:	48 83 c0 01          	add    $0x1,%rax
  107792:	48 89 45 c8          	mov    %rax,-0x38(%rbp)
  107796:	e9 d4 ff ff ff       	jmp    10776f <_ZN4acos6memory20pmm_alloc_contiguousEm+0xcf>
  10779b:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10779f:	48 03 04 25 18 89 16 	add    0x168918,%rax
  1077a6:	00
  1077a7:	48 89 04 25 18 89 16 	mov    %rax,0x168918
  1077ae:	00
  1077af:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  1077b3:	48 c1 e0 0c          	shl    $0xc,%rax
  1077b7:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  1077bb:	e9 19 00 00 00       	jmp    1077d9 <_ZN4acos6memory20pmm_alloc_contiguousEm+0x139>
  1077c0:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  1077c4:	48 83 c0 01          	add    $0x1,%rax
  1077c8:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  1077cc:	e9 16 ff ff ff       	jmp    1076e7 <_ZN4acos6memory20pmm_alloc_contiguousEm+0x47>
  1077d1:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  1077d8:	00
  1077d9:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  1077dd:	48 83 c4 40          	add    $0x40,%rsp
  1077e1:	5d                   	pop    %rbp
  1077e2:	c3                   	ret
  1077e3:	66 66 66 66 2e 0f 1f 	data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
  1077ea:	84 00 00 00 00 00

00000000001077f0 <_ZN4acos6memory8pmm_freeEm>:
  1077f0:	55                   	push   %rbp
  1077f1:	48 89 e5             	mov    %rsp,%rbp
  1077f4:	48 83 ec 10          	sub    $0x10,%rsp
  1077f8:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  1077fc:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  107800:	48 c1 e8 0c          	shr    $0xc,%rax
  107804:	48 89 45 f0          	mov    %rax,-0x10(%rbp)
  107808:	48 8b 7d f0          	mov    -0x10(%rbp),%rdi
  10780c:	e8 3f fe ff ff       	call   107650 <_ZN4acos6memoryL11bitmap_testEm>
  107811:	a8 01                	test   $0x1,%al
  107813:	0f 85 05 00 00 00    	jne    10781e <_ZN4acos6memory8pmm_freeEm+0x2e>
  107819:	e9 1d 00 00 00       	jmp    10783b <_ZN4acos6memory8pmm_freeEm+0x4b>
  10781e:	48 8b 7d f0          	mov    -0x10(%rbp),%rdi
  107822:	e8 f9 fc ff ff       	call   107520 <_ZN4acos6memoryL12bitmap_clearEm>
  107827:	48 8b 04 25 18 89 16 	mov    0x168918,%rax
  10782e:	00
  10782f:	48 83 c0 ff          	add    $0xffffffffffffffff,%rax
  107833:	48 89 04 25 18 89 16 	mov    %rax,0x168918
  10783a:	00
  10783b:	48 83 c4 10          	add    $0x10,%rsp
  10783f:	5d                   	pop    %rbp
  107840:	c3                   	ret
  107841:	66 66 66 66 66 66 2e 	data16 data16 data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
  107848:	0f 1f 84 00 00 00 00
  10784f:	00

0000000000107850 <_ZN4acos6memory20pmm_get_total_memoryEv>:
  107850:	55                   	push   %rbp
  107851:	48 89 e5             	mov    %rsp,%rbp
  107854:	e8 77 f8 ff ff       	call   1070d0 <_ZN4acos6memory15get_total_pagesEv>
  107859:	48 c1 e0 0c          	shl    $0xc,%rax
  10785d:	5d                   	pop    %rbp
  10785e:	c3                   	ret
  10785f:	90                   	nop

0000000000107860 <_ZN4acos6memory19pmm_get_used_memoryEv>:
  107860:	55                   	push   %rbp
  107861:	48 89 e5             	mov    %rsp,%rbp
  107864:	e8 77 f8 ff ff       	call   1070e0 <_ZN4acos6memory14get_used_pagesEv>
  107869:	48 c1 e0 0c          	shl    $0xc,%rax
  10786d:	5d                   	pop    %rbp
  10786e:	c3                   	ret
  10786f:	90                   	nop

0000000000107870 <_ZN4acos6memory16clear_page_tableEPNS0_9PageTableE>:
  107870:	55                   	push   %rbp
  107871:	48 89 e5             	mov    %rsp,%rbp
  107874:	48 83 ec 10          	sub    $0x10,%rsp
  107878:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10787c:	48 83 7d f8 00       	cmpq   $0x0,-0x8(%rbp)
  107881:	0f 85 05 00 00 00    	jne    10788c <_ZN4acos6memory16clear_page_tableEPNS0_9PageTableE+0x1c>
  107887:	e9 32 00 00 00       	jmp    1078be <_ZN4acos6memory16clear_page_tableEPNS0_9PageTableE+0x4e>
  10788c:	c7 45 f4 00 00 00 00 	movl   $0x0,-0xc(%rbp)
  107893:	81 7d f4 00 02 00 00 	cmpl   $0x200,-0xc(%rbp)
  10789a:	0f 8d 1e 00 00 00    	jge    1078be <_ZN4acos6memory16clear_page_tableEPNS0_9PageTableE+0x4e>
  1078a0:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  1078a4:	48 63 4d f4          	movslq -0xc(%rbp),%rcx
  1078a8:	48 c7 04 c8 00 00 00 	movq   $0x0,(%rax,%rcx,8)
  1078af:	00
  1078b0:	8b 45 f4             	mov    -0xc(%rbp),%eax
  1078b3:	83 c0 01             	add    $0x1,%eax
  1078b6:	89 45 f4             	mov    %eax,-0xc(%rbp)
  1078b9:	e9 d5 ff ff ff       	jmp    107893 <_ZN4acos6memory16clear_page_tableEPNS0_9PageTableE+0x23>
  1078be:	48 83 c4 10          	add    $0x10,%rsp
  1078c2:	5d                   	pop    %rbp
  1078c3:	c3                   	ret
  1078c4:	66 66 66 2e 0f 1f 84 	data16 data16 cs nopw 0x0(%rax,%rax,1)
  1078cb:	00 00 00 00 00

00000000001078d0 <_ZN4acos6memory7vmm_mapEPNS0_9PageTableEmmm>:
  1078d0:	55                   	push   %rbp
  1078d1:	48 89 e5             	mov    %rsp,%rbp
  1078d4:	48 83 ec 70          	sub    $0x70,%rsp
  1078d8:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  1078dc:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  1078e0:	48 89 55 e8          	mov    %rdx,-0x18(%rbp)
  1078e4:	48 89 4d e0          	mov    %rcx,-0x20(%rbp)
  1078e8:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  1078ec:	48 c1 e8 27          	shr    $0x27,%rax
  1078f0:	48 25 ff 01 00 00    	and    $0x1ff,%rax
  1078f6:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
  1078fa:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  1078fe:	48 c1 e8 1e          	shr    $0x1e,%rax
  107902:	48 25 ff 01 00 00    	and    $0x1ff,%rax
  107908:	48 89 45 d0          	mov    %rax,-0x30(%rbp)
  10790c:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  107910:	48 c1 e8 15          	shr    $0x15,%rax
  107914:	48 25 ff 01 00 00    	and    $0x1ff,%rax
  10791a:	48 89 45 c8          	mov    %rax,-0x38(%rbp)
  10791e:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  107922:	48 c1 e8 0c          	shr    $0xc,%rax
  107926:	48 25 ff 01 00 00    	and    $0x1ff,%rax
  10792c:	48 89 45 c0          	mov    %rax,-0x40(%rbp)
  107930:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  107934:	48 8b 4d d8          	mov    -0x28(%rbp),%rcx
  107938:	48 8b 04 c8          	mov    (%rax,%rcx,8),%rax
  10793c:	48 83 e0 01          	and    $0x1,%rax
  107940:	48 83 f8 00          	cmp    $0x0,%rax
  107944:	0f 85 2d 00 00 00    	jne    107977 <_ZN4acos6memory7vmm_mapEPNS0_9PageTableEmmm+0xa7>
  10794a:	e8 21 01 00 00       	call   107a70 <_ZN4acos6memoryL11alloc_tableEv>
  10794f:	48 89 45 b8          	mov    %rax,-0x48(%rbp)
  107953:	48 83 7d b8 00       	cmpq   $0x0,-0x48(%rbp)
  107958:	0f 85 05 00 00 00    	jne    107963 <_ZN4acos6memory7vmm_mapEPNS0_9PageTableEmmm+0x93>
  10795e:	e9 fc 00 00 00       	jmp    107a5f <_ZN4acos6memory7vmm_mapEPNS0_9PageTableEmmm+0x18f>
  107963:	48 8b 55 b8          	mov    -0x48(%rbp),%rdx
  107967:	48 83 ca 03          	or     $0x3,%rdx
  10796b:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10796f:	48 8b 4d d8          	mov    -0x28(%rbp),%rcx
  107973:	48 89 14 c8          	mov    %rdx,(%rax,%rcx,8)
  107977:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10797b:	48 8b 4d d8          	mov    -0x28(%rbp),%rcx
  10797f:	48 8b 04 c8          	mov    (%rax,%rcx,8),%rax
  107983:	48 25 00 f0 ff ff    	and    $0xfffffffffffff000,%rax
  107989:	48 89 45 b0          	mov    %rax,-0x50(%rbp)
  10798d:	48 8b 45 b0          	mov    -0x50(%rbp),%rax
  107991:	48 8b 4d d0          	mov    -0x30(%rbp),%rcx
  107995:	48 8b 04 c8          	mov    (%rax,%rcx,8),%rax
  107999:	48 83 e0 01          	and    $0x1,%rax
  10799d:	48 83 f8 00          	cmp    $0x0,%rax
  1079a1:	0f 85 2d 00 00 00    	jne    1079d4 <_ZN4acos6memory7vmm_mapEPNS0_9PageTableEmmm+0x104>
  1079a7:	e8 c4 00 00 00       	call   107a70 <_ZN4acos6memoryL11alloc_tableEv>
  1079ac:	48 89 45 a8          	mov    %rax,-0x58(%rbp)
  1079b0:	48 83 7d a8 00       	cmpq   $0x0,-0x58(%rbp)
  1079b5:	0f 85 05 00 00 00    	jne    1079c0 <_ZN4acos6memory7vmm_mapEPNS0_9PageTableEmmm+0xf0>
  1079bb:	e9 9f 00 00 00       	jmp    107a5f <_ZN4acos6memory7vmm_mapEPNS0_9PageTableEmmm+0x18f>
  1079c0:	48 8b 55 a8          	mov    -0x58(%rbp),%rdx
  1079c4:	48 83 ca 03          	or     $0x3,%rdx
  1079c8:	48 8b 45 b0          	mov    -0x50(%rbp),%rax
  1079cc:	48 8b 4d d0          	mov    -0x30(%rbp),%rcx
  1079d0:	48 89 14 c8          	mov    %rdx,(%rax,%rcx,8)
  1079d4:	48 8b 45 b0          	mov    -0x50(%rbp),%rax
  1079d8:	48 8b 4d d0          	mov    -0x30(%rbp),%rcx
  1079dc:	48 8b 04 c8          	mov    (%rax,%rcx,8),%rax
  1079e0:	48 25 00 f0 ff ff    	and    $0xfffffffffffff000,%rax
  1079e6:	48 89 45 a0          	mov    %rax,-0x60(%rbp)
  1079ea:	48 8b 45 a0          	mov    -0x60(%rbp),%rax
  1079ee:	48 8b 4d c8          	mov    -0x38(%rbp),%rcx
  1079f2:	48 8b 04 c8          	mov    (%rax,%rcx,8),%rax
  1079f6:	48 83 e0 01          	and    $0x1,%rax
  1079fa:	48 83 f8 00          	cmp    $0x0,%rax
  1079fe:	0f 85 2d 00 00 00    	jne    107a31 <_ZN4acos6memory7vmm_mapEPNS0_9PageTableEmmm+0x161>
  107a04:	e8 67 00 00 00       	call   107a70 <_ZN4acos6memoryL11alloc_tableEv>
  107a09:	48 89 45 98          	mov    %rax,-0x68(%rbp)
  107a0d:	48 83 7d 98 00       	cmpq   $0x0,-0x68(%rbp)
  107a12:	0f 85 05 00 00 00    	jne    107a1d <_ZN4acos6memory7vmm_mapEPNS0_9PageTableEmmm+0x14d>
  107a18:	e9 42 00 00 00       	jmp    107a5f <_ZN4acos6memory7vmm_mapEPNS0_9PageTableEmmm+0x18f>
  107a1d:	48 8b 55 98          	mov    -0x68(%rbp),%rdx
  107a21:	48 83 ca 03          	or     $0x3,%rdx
  107a25:	48 8b 45 a0          	mov    -0x60(%rbp),%rax
  107a29:	48 8b 4d c8          	mov    -0x38(%rbp),%rcx
  107a2d:	48 89 14 c8          	mov    %rdx,(%rax,%rcx,8)
  107a31:	48 8b 45 a0          	mov    -0x60(%rbp),%rax
  107a35:	48 8b 4d c8          	mov    -0x38(%rbp),%rcx
  107a39:	48 8b 04 c8          	mov    (%rax,%rcx,8),%rax
  107a3d:	48 25 00 f0 ff ff    	and    $0xfffffffffffff000,%rax
  107a43:	48 89 45 90          	mov    %rax,-0x70(%rbp)
  107a47:	48 8b 55 e8          	mov    -0x18(%rbp),%rdx
  107a4b:	48 0b 55 e0          	or     -0x20(%rbp),%rdx
  107a4f:	48 83 ca 01          	or     $0x1,%rdx
  107a53:	48 8b 45 90          	mov    -0x70(%rbp),%rax
  107a57:	48 8b 4d c0          	mov    -0x40(%rbp),%rcx
  107a5b:	48 89 14 c8          	mov    %rdx,(%rax,%rcx,8)
  107a5f:	48 83 c4 70          	add    $0x70,%rsp
  107a63:	5d                   	pop    %rbp
  107a64:	c3                   	ret
  107a65:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  107a6c:	00 00 00 00

0000000000107a70 <_ZN4acos6memoryL11alloc_tableEv>:
  107a70:	55                   	push   %rbp
  107a71:	48 89 e5             	mov    %rsp,%rbp
  107a74:	48 83 ec 20          	sub    $0x20,%rsp
  107a78:	e8 23 fb ff ff       	call   1075a0 <_ZN4acos6memory9pmm_allocEv>
  107a7d:	48 89 45 f0          	mov    %rax,-0x10(%rbp)
  107a81:	48 83 7d f0 00       	cmpq   $0x0,-0x10(%rbp)
  107a86:	0f 85 0d 00 00 00    	jne    107a99 <_ZN4acos6memoryL11alloc_tableEv+0x29>
  107a8c:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  107a93:	00
  107a94:	e9 19 00 00 00       	jmp    107ab2 <_ZN4acos6memoryL11alloc_tableEv+0x42>
  107a99:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  107a9d:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
  107aa1:	48 8b 7d e8          	mov    -0x18(%rbp),%rdi
  107aa5:	e8 c6 fd ff ff       	call   107870 <_ZN4acos6memory16clear_page_tableEPNS0_9PageTableE>
  107aaa:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  107aae:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  107ab2:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  107ab6:	48 83 c4 20          	add    $0x20,%rsp
  107aba:	5d                   	pop    %rbp
  107abb:	c3                   	ret
  107abc:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000107ac0 <_ZN4acos6memory8vmm_initEPNS_8BootInfoE>:
  107ac0:	55                   	push   %rbp
  107ac1:	48 89 e5             	mov    %rsp,%rbp
  107ac4:	48 83 ec 40          	sub    $0x40,%rsp
  107ac8:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  107acc:	e8 cf fa ff ff       	call   1075a0 <_ZN4acos6memory9pmm_allocEv>
  107ad1:	48 89 04 25 30 89 16 	mov    %rax,0x168930
  107ad8:	00
  107ad9:	48 83 3c 25 30 89 16 	cmpq   $0x0,0x168930
  107ae0:	00 00
  107ae2:	0f 85 14 00 00 00    	jne    107afc <_ZN4acos6memory8vmm_initEPNS_8BootInfoE+0x3c>
  107ae8:	48 bf 93 f9 10 00 00 	movabs $0x10f993,%rdi
  107aef:	00 00 00
  107af2:	e8 99 29 00 00       	call   10a490 <_ZN4acos3hal12serial_printEPKc>
  107af7:	e9 6c 01 00 00       	jmp    107c68 <_ZN4acos6memory8vmm_initEPNS_8BootInfoE+0x1a8>
  107afc:	48 8b 3c 25 30 89 16 	mov    0x168930,%rdi
  107b03:	00
  107b04:	e8 67 fd ff ff       	call   107870 <_ZN4acos6memory16clear_page_tableEPNS0_9PageTableE>
  107b09:	e8 42 fd ff ff       	call   107850 <_ZN4acos6memory20pmm_get_total_memoryEv>
  107b0e:	48 89 45 f0          	mov    %rax,-0x10(%rbp)
  107b12:	48 b8 00 00 00 00 01 	movabs $0x100000000,%rax
  107b19:	00 00 00
  107b1c:	48 39 45 f0          	cmp    %rax,-0x10(%rbp)
  107b20:	0f 83 0e 00 00 00    	jae    107b34 <_ZN4acos6memory8vmm_initEPNS_8BootInfoE+0x74>
  107b26:	48 b8 00 00 00 00 01 	movabs $0x100000000,%rax
  107b2d:	00 00 00
  107b30:	48 89 45 f0          	mov    %rax,-0x10(%rbp)
  107b34:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  107b38:	48 05 ff ff 1f 00    	add    $0x1fffff,%rax
  107b3e:	48 25 00 00 e0 ff    	and    $0xffffffffffe00000,%rax
  107b44:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
  107b48:	48 c7 45 e0 00 00 00 	movq   $0x0,-0x20(%rbp)
  107b4f:	00
  107b50:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  107b54:	48 3b 45 e8          	cmp    -0x18(%rbp),%rax
  107b58:	0f 83 2d 00 00 00    	jae    107b8b <_ZN4acos6memory8vmm_initEPNS_8BootInfoE+0xcb>
  107b5e:	48 8b 3c 25 30 89 16 	mov    0x168930,%rdi
  107b65:	00
  107b66:	48 8b 75 e0          	mov    -0x20(%rbp),%rsi
  107b6a:	48 8b 55 e0          	mov    -0x20(%rbp),%rdx
  107b6e:	b9 03 00 00 00       	mov    $0x3,%ecx
  107b73:	e8 f8 00 00 00       	call   107c70 <_ZN4acos6memoryL10vmm_map_2mEPNS0_9PageTableEmmm>
  107b78:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  107b7c:	48 05 00 00 20 00    	add    $0x200000,%rax
  107b82:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  107b86:	e9 c5 ff ff ff       	jmp    107b50 <_ZN4acos6memory8vmm_initEPNS_8BootInfoE+0x90>
  107b8b:	48 83 7d f8 00       	cmpq   $0x0,-0x8(%rbp)
  107b90:	0f 84 b8 00 00 00    	je     107c4e <_ZN4acos6memory8vmm_initEPNS_8BootInfoE+0x18e>
  107b96:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  107b9a:	48 83 78 10 00       	cmpq   $0x0,0x10(%rax)
  107b9f:	0f 84 a9 00 00 00    	je     107c4e <_ZN4acos6memory8vmm_initEPNS_8BootInfoE+0x18e>
  107ba5:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  107ba9:	48 8b 40 10          	mov    0x10(%rax),%rax
  107bad:	48 83 38 00          	cmpq   $0x0,(%rax)
  107bb1:	0f 84 97 00 00 00    	je     107c4e <_ZN4acos6memory8vmm_initEPNS_8BootInfoE+0x18e>
  107bb7:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  107bbb:	48 8b 40 10          	mov    0x10(%rax),%rax
  107bbf:	48 83 78 08 00       	cmpq   $0x0,0x8(%rax)
  107bc4:	0f 84 84 00 00 00    	je     107c4e <_ZN4acos6memory8vmm_initEPNS_8BootInfoE+0x18e>
  107bca:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  107bce:	48 8b 40 10          	mov    0x10(%rax),%rax
  107bd2:	48 8b 00             	mov    (%rax),%rax
  107bd5:	48 25 00 00 e0 ff    	and    $0xffffffffffe00000,%rax
  107bdb:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
  107bdf:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  107be3:	48 8b 40 10          	mov    0x10(%rax),%rax
  107be7:	48 8b 00             	mov    (%rax),%rax
  107bea:	48 8b 4d f8          	mov    -0x8(%rbp),%rcx
  107bee:	48 8b 49 10          	mov    0x10(%rcx),%rcx
  107bf2:	48 03 41 08          	add    0x8(%rcx),%rax
  107bf6:	48 05 ff ff 1f 00    	add    $0x1fffff,%rax
  107bfc:	48 25 00 00 e0 ff    	and    $0xffffffffffe00000,%rax
  107c02:	48 89 45 d0          	mov    %rax,-0x30(%rbp)
  107c06:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  107c0a:	48 89 45 c8          	mov    %rax,-0x38(%rbp)
  107c0e:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  107c12:	48 3b 45 d0          	cmp    -0x30(%rbp),%rax
  107c16:	0f 83 2d 00 00 00    	jae    107c49 <_ZN4acos6memory8vmm_initEPNS_8BootInfoE+0x189>
  107c1c:	48 8b 3c 25 30 89 16 	mov    0x168930,%rdi
  107c23:	00
  107c24:	48 8b 75 c8          	mov    -0x38(%rbp),%rsi
  107c28:	48 8b 55 c8          	mov    -0x38(%rbp),%rdx
  107c2c:	b9 03 00 00 00       	mov    $0x3,%ecx
  107c31:	e8 3a 00 00 00       	call   107c70 <_ZN4acos6memoryL10vmm_map_2mEPNS0_9PageTableEmmm>
  107c36:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  107c3a:	48 05 00 00 20 00    	add    $0x200000,%rax
  107c40:	48 89 45 c8          	mov    %rax,-0x38(%rbp)
  107c44:	e9 c5 ff ff ff       	jmp    107c0e <_ZN4acos6memory8vmm_initEPNS_8BootInfoE+0x14e>
  107c49:	e9 00 00 00 00       	jmp    107c4e <_ZN4acos6memory8vmm_initEPNS_8BootInfoE+0x18e>
  107c4e:	48 bf bb f9 10 00 00 	movabs $0x10f9bb,%rdi
  107c55:	00 00 00
  107c58:	e8 33 28 00 00       	call   10a490 <_ZN4acos3hal12serial_printEPKc>
  107c5d:	48 8b 04 25 30 89 16 	mov    0x168930,%rax
  107c64:	00
  107c65:	0f 22 d8             	mov    %rax,%cr3
  107c68:	48 83 c4 40          	add    $0x40,%rsp
  107c6c:	5d                   	pop    %rbp
  107c6d:	c3                   	ret
  107c6e:	66 90                	xchg   %ax,%ax

0000000000107c70 <_ZN4acos6memoryL10vmm_map_2mEPNS0_9PageTableEmmm>:
  107c70:	55                   	push   %rbp
  107c71:	48 89 e5             	mov    %rsp,%rbp
  107c74:	48 83 ec 60          	sub    $0x60,%rsp
  107c78:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  107c7c:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  107c80:	48 89 55 e8          	mov    %rdx,-0x18(%rbp)
  107c84:	48 89 4d e0          	mov    %rcx,-0x20(%rbp)
  107c88:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  107c8c:	48 c1 e8 27          	shr    $0x27,%rax
  107c90:	48 25 ff 01 00 00    	and    $0x1ff,%rax
  107c96:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
  107c9a:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  107c9e:	48 c1 e8 1e          	shr    $0x1e,%rax
  107ca2:	48 25 ff 01 00 00    	and    $0x1ff,%rax
  107ca8:	48 89 45 d0          	mov    %rax,-0x30(%rbp)
  107cac:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  107cb0:	48 c1 e8 15          	shr    $0x15,%rax
  107cb4:	48 25 ff 01 00 00    	and    $0x1ff,%rax
  107cba:	48 89 45 c8          	mov    %rax,-0x38(%rbp)
  107cbe:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  107cc2:	48 8b 4d d8          	mov    -0x28(%rbp),%rcx
  107cc6:	48 8b 04 c8          	mov    (%rax,%rcx,8),%rax
  107cca:	48 83 e0 01          	and    $0x1,%rax
  107cce:	48 83 f8 00          	cmp    $0x0,%rax
  107cd2:	0f 85 2d 00 00 00    	jne    107d05 <_ZN4acos6memoryL10vmm_map_2mEPNS0_9PageTableEmmm+0x95>
  107cd8:	e8 93 fd ff ff       	call   107a70 <_ZN4acos6memoryL11alloc_tableEv>
  107cdd:	48 89 45 c0          	mov    %rax,-0x40(%rbp)
  107ce1:	48 83 7d c0 00       	cmpq   $0x0,-0x40(%rbp)
  107ce6:	0f 85 05 00 00 00    	jne    107cf1 <_ZN4acos6memoryL10vmm_map_2mEPNS0_9PageTableEmmm+0x81>
  107cec:	e9 a6 00 00 00       	jmp    107d97 <_ZN4acos6memoryL10vmm_map_2mEPNS0_9PageTableEmmm+0x127>
  107cf1:	48 8b 55 c0          	mov    -0x40(%rbp),%rdx
  107cf5:	48 83 ca 03          	or     $0x3,%rdx
  107cf9:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  107cfd:	48 8b 4d d8          	mov    -0x28(%rbp),%rcx
  107d01:	48 89 14 c8          	mov    %rdx,(%rax,%rcx,8)
  107d05:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  107d09:	48 8b 4d d8          	mov    -0x28(%rbp),%rcx
  107d0d:	48 8b 04 c8          	mov    (%rax,%rcx,8),%rax
  107d11:	48 25 00 f0 ff ff    	and    $0xfffffffffffff000,%rax
  107d17:	48 89 45 b8          	mov    %rax,-0x48(%rbp)
  107d1b:	48 8b 45 b8          	mov    -0x48(%rbp),%rax
  107d1f:	48 8b 4d d0          	mov    -0x30(%rbp),%rcx
  107d23:	48 8b 04 c8          	mov    (%rax,%rcx,8),%rax
  107d27:	48 83 e0 01          	and    $0x1,%rax
  107d2b:	48 83 f8 00          	cmp    $0x0,%rax
  107d2f:	0f 85 2d 00 00 00    	jne    107d62 <_ZN4acos6memoryL10vmm_map_2mEPNS0_9PageTableEmmm+0xf2>
  107d35:	e8 36 fd ff ff       	call   107a70 <_ZN4acos6memoryL11alloc_tableEv>
  107d3a:	48 89 45 b0          	mov    %rax,-0x50(%rbp)
  107d3e:	48 83 7d b0 00       	cmpq   $0x0,-0x50(%rbp)
  107d43:	0f 85 05 00 00 00    	jne    107d4e <_ZN4acos6memoryL10vmm_map_2mEPNS0_9PageTableEmmm+0xde>
  107d49:	e9 49 00 00 00       	jmp    107d97 <_ZN4acos6memoryL10vmm_map_2mEPNS0_9PageTableEmmm+0x127>
  107d4e:	48 8b 55 b0          	mov    -0x50(%rbp),%rdx
  107d52:	48 83 ca 03          	or     $0x3,%rdx
  107d56:	48 8b 45 b8          	mov    -0x48(%rbp),%rax
  107d5a:	48 8b 4d d0          	mov    -0x30(%rbp),%rcx
  107d5e:	48 89 14 c8          	mov    %rdx,(%rax,%rcx,8)
  107d62:	48 8b 45 b8          	mov    -0x48(%rbp),%rax
  107d66:	48 8b 4d d0          	mov    -0x30(%rbp),%rcx
  107d6a:	48 8b 04 c8          	mov    (%rax,%rcx,8),%rax
  107d6e:	48 25 00 f0 ff ff    	and    $0xfffffffffffff000,%rax
  107d74:	48 89 45 a8          	mov    %rax,-0x58(%rbp)
  107d78:	48 8b 55 e8          	mov    -0x18(%rbp),%rdx
  107d7c:	48 0b 55 e0          	or     -0x20(%rbp),%rdx
  107d80:	48 83 ca 01          	or     $0x1,%rdx
  107d84:	48 81 ca 80 00 00 00 	or     $0x80,%rdx
  107d8b:	48 8b 45 a8          	mov    -0x58(%rbp),%rax
  107d8f:	48 8b 4d c8          	mov    -0x38(%rbp),%rcx
  107d93:	48 89 14 c8          	mov    %rdx,(%rax,%rcx,8)
  107d97:	48 83 c4 60          	add    $0x60,%rsp
  107d9b:	5d                   	pop    %rbp
  107d9c:	c3                   	ret
  107d9d:	0f 1f 00             	nopl   (%rax)

0000000000107da0 <_ZN4acos6memory12AddressSpaceC1Ev>:
  107da0:	55                   	push   %rbp
  107da1:	48 89 e5             	mov    %rsp,%rbp
  107da4:	48 83 ec 50          	sub    $0x50,%rsp
  107da8:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  107dac:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  107db0:	48 89 45 b0          	mov    %rax,-0x50(%rbp)
  107db4:	e8 e7 f7 ff ff       	call   1075a0 <_ZN4acos6memory9pmm_allocEv>
  107db9:	48 89 c1             	mov    %rax,%rcx
  107dbc:	48 8b 45 b0          	mov    -0x50(%rbp),%rax
  107dc0:	48 89 08             	mov    %rcx,(%rax)
  107dc3:	48 83 38 00          	cmpq   $0x0,(%rax)
  107dc7:	0f 85 0b 00 00 00    	jne    107dd8 <_ZN4acos6memory12AddressSpaceC1Ev+0x38>
  107dcd:	e9 00 00 00 00       	jmp    107dd2 <_ZN4acos6memory12AddressSpaceC1Ev+0x32>
  107dd2:	f4                   	hlt
  107dd3:	e9 fa ff ff ff       	jmp    107dd2 <_ZN4acos6memory12AddressSpaceC1Ev+0x32>
  107dd8:	48 8b 45 b0          	mov    -0x50(%rbp),%rax
  107ddc:	48 8b 08             	mov    (%rax),%rcx
  107ddf:	48 89 48 08          	mov    %rcx,0x8(%rax)
  107de3:	c7 45 f4 00 00 00 00 	movl   $0x0,-0xc(%rbp)
  107dea:	81 7d f4 00 02 00 00 	cmpl   $0x200,-0xc(%rbp)
  107df1:	0f 8d 22 00 00 00    	jge    107e19 <_ZN4acos6memory12AddressSpaceC1Ev+0x79>
  107df7:	48 8b 45 b0          	mov    -0x50(%rbp),%rax
  107dfb:	48 8b 40 08          	mov    0x8(%rax),%rax
  107dff:	48 63 4d f4          	movslq -0xc(%rbp),%rcx
  107e03:	48 c7 04 c8 00 00 00 	movq   $0x0,(%rax,%rcx,8)
  107e0a:	00
  107e0b:	8b 45 f4             	mov    -0xc(%rbp),%eax
  107e0e:	83 c0 01             	add    $0x1,%eax
  107e11:	89 45 f4             	mov    %eax,-0xc(%rbp)
  107e14:	e9 d1 ff ff ff       	jmp    107dea <_ZN4acos6memory12AddressSpaceC1Ev+0x4a>
  107e19:	48 c7 45 e8 00 00 00 	movq   $0x0,-0x18(%rbp)
  107e20:	00
  107e21:	48 b8 00 00 00 00 01 	movabs $0x100000000,%rax
  107e28:	00 00 00
  107e2b:	48 39 45 e8          	cmp    %rax,-0x18(%rbp)
  107e2f:	0f 83 a9 00 00 00    	jae    107ede <_ZN4acos6memory12AddressSpaceC1Ev+0x13e>
  107e35:	48 8b 45 b0          	mov    -0x50(%rbp),%rax
  107e39:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  107e3d:	48 c1 e9 27          	shr    $0x27,%rcx
  107e41:	48 81 e1 ff 01 00 00 	and    $0x1ff,%rcx
  107e48:	48 89 4d e0          	mov    %rcx,-0x20(%rbp)
  107e4c:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  107e50:	48 c1 e9 1e          	shr    $0x1e,%rcx
  107e54:	48 81 e1 ff 01 00 00 	and    $0x1ff,%rcx
  107e5b:	48 89 4d d8          	mov    %rcx,-0x28(%rbp)
  107e5f:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  107e63:	48 c1 e9 15          	shr    $0x15,%rcx
  107e67:	48 81 e1 ff 01 00 00 	and    $0x1ff,%rcx
  107e6e:	48 89 4d d0          	mov    %rcx,-0x30(%rbp)
  107e72:	8a 0c 25 70 f4 10 00 	mov    0x10f470,%cl
  107e79:	88 4d cf             	mov    %cl,-0x31(%rbp)
  107e7c:	48 8b 70 08          	mov    0x8(%rax),%rsi
  107e80:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  107e84:	48 c1 e0 03          	shl    $0x3,%rax
  107e88:	48 01 c6             	add    %rax,%rsi
  107e8b:	48 8d 7d cf          	lea    -0x31(%rbp),%rdi
  107e8f:	e8 5c 00 00 00       	call   107ef0 <_ZZN4acos6memory12AddressSpaceC1EvENK3$_0clEPm>
  107e94:	48 89 45 c0          	mov    %rax,-0x40(%rbp)
  107e98:	48 8b 75 c0          	mov    -0x40(%rbp),%rsi
  107e9c:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  107ea0:	48 c1 e0 03          	shl    $0x3,%rax
  107ea4:	48 01 c6             	add    %rax,%rsi
  107ea7:	48 8d 7d cf          	lea    -0x31(%rbp),%rdi
  107eab:	e8 40 00 00 00       	call   107ef0 <_ZZN4acos6memory12AddressSpaceC1EvENK3$_0clEPm>
  107eb0:	48 89 45 b8          	mov    %rax,-0x48(%rbp)
  107eb4:	48 8b 55 e8          	mov    -0x18(%rbp),%rdx
  107eb8:	48 81 ca 83 00 00 00 	or     $0x83,%rdx
  107ebf:	48 8b 45 b8          	mov    -0x48(%rbp),%rax
  107ec3:	48 8b 4d d0          	mov    -0x30(%rbp),%rcx
  107ec7:	48 89 14 c8          	mov    %rdx,(%rax,%rcx,8)
  107ecb:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  107ecf:	48 05 00 00 20 00    	add    $0x200000,%rax
  107ed5:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
  107ed9:	e9 43 ff ff ff       	jmp    107e21 <_ZN4acos6memory12AddressSpaceC1Ev+0x81>
  107ede:	48 83 c4 50          	add    $0x50,%rsp
  107ee2:	5d                   	pop    %rbp
  107ee3:	c3                   	ret
  107ee4:	66 66 66 2e 0f 1f 84 	data16 data16 cs nopw 0x0(%rax,%rax,1)
  107eeb:	00 00 00 00 00

0000000000107ef0 <_ZZN4acos6memory12AddressSpaceC1EvENK3$_0clEPm>:
  107ef0:	55                   	push   %rbp
  107ef1:	48 89 e5             	mov    %rsp,%rbp
  107ef4:	48 83 ec 30          	sub    $0x30,%rsp
  107ef8:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  107efc:	48 89 75 e8          	mov    %rsi,-0x18(%rbp)
  107f00:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  107f04:	48 8b 00             	mov    (%rax),%rax
  107f07:	48 83 e0 01          	and    $0x1,%rax
  107f0b:	48 83 f8 00          	cmp    $0x0,%rax
  107f0f:	0f 85 77 00 00 00    	jne    107f8c <_ZZN4acos6memory12AddressSpaceC1EvENK3$_0clEPm+0x9c>
  107f15:	e8 86 f6 ff ff       	call   1075a0 <_ZN4acos6memory9pmm_allocEv>
  107f1a:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  107f1e:	48 83 7d e0 00       	cmpq   $0x0,-0x20(%rbp)
  107f23:	0f 85 0d 00 00 00    	jne    107f36 <_ZZN4acos6memory12AddressSpaceC1EvENK3$_0clEPm+0x46>
  107f29:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  107f30:	00
  107f31:	e9 67 00 00 00       	jmp    107f9d <_ZZN4acos6memory12AddressSpaceC1EvENK3$_0clEPm+0xad>
  107f36:	48 8b 4d e0          	mov    -0x20(%rbp),%rcx
  107f3a:	48 83 c9 03          	or     $0x3,%rcx
  107f3e:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  107f42:	48 89 08             	mov    %rcx,(%rax)
  107f45:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  107f49:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
  107f4d:	c7 45 d4 00 00 00 00 	movl   $0x0,-0x2c(%rbp)
  107f54:	81 7d d4 00 02 00 00 	cmpl   $0x200,-0x2c(%rbp)
  107f5b:	0f 8d 1e 00 00 00    	jge    107f7f <_ZZN4acos6memory12AddressSpaceC1EvENK3$_0clEPm+0x8f>
  107f61:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  107f65:	48 63 4d d4          	movslq -0x2c(%rbp),%rcx
  107f69:	48 c7 04 c8 00 00 00 	movq   $0x0,(%rax,%rcx,8)
  107f70:	00
  107f71:	8b 45 d4             	mov    -0x2c(%rbp),%eax
  107f74:	83 c0 01             	add    $0x1,%eax
  107f77:	89 45 d4             	mov    %eax,-0x2c(%rbp)
  107f7a:	e9 d5 ff ff ff       	jmp    107f54 <_ZZN4acos6memory12AddressSpaceC1EvENK3$_0clEPm+0x64>
  107f7f:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  107f83:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  107f87:	e9 11 00 00 00       	jmp    107f9d <_ZZN4acos6memory12AddressSpaceC1EvENK3$_0clEPm+0xad>
  107f8c:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  107f90:	48 8b 00             	mov    (%rax),%rax
  107f93:	48 25 00 f0 ff ff    	and    $0xfffffffffffff000,%rax
  107f99:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  107f9d:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  107fa1:	48 83 c4 30          	add    $0x30,%rsp
  107fa5:	5d                   	pop    %rbp
  107fa6:	c3                   	ret
  107fa7:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
  107fae:	00 00

0000000000107fb0 <_ZN4acos6memory12AddressSpaceD1Ev>:
  107fb0:	55                   	push   %rbp
  107fb1:	48 89 e5             	mov    %rsp,%rbp
  107fb4:	48 83 ec 50          	sub    $0x50,%rsp
  107fb8:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  107fbc:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  107fc0:	48 89 45 b0          	mov    %rax,-0x50(%rbp)
  107fc4:	48 83 78 08 00       	cmpq   $0x0,0x8(%rax)
  107fc9:	0f 84 60 01 00 00    	je     10812f <_ZN4acos6memory12AddressSpaceD1Ev+0x17f>
  107fcf:	c7 45 f4 00 00 00 00 	movl   $0x0,-0xc(%rbp)
  107fd6:	81 7d f4 00 02 00 00 	cmpl   $0x200,-0xc(%rbp)
  107fdd:	0f 8d 40 01 00 00    	jge    108123 <_ZN4acos6memory12AddressSpaceD1Ev+0x173>
  107fe3:	48 8b 45 b0          	mov    -0x50(%rbp),%rax
  107fe7:	48 8b 40 08          	mov    0x8(%rax),%rax
  107feb:	48 63 4d f4          	movslq -0xc(%rbp),%rcx
  107fef:	48 8b 04 c8          	mov    (%rax,%rcx,8),%rax
  107ff3:	48 83 e0 01          	and    $0x1,%rax
  107ff7:	48 83 f8 00          	cmp    $0x0,%rax
  107ffb:	0f 84 0f 01 00 00    	je     108110 <_ZN4acos6memory12AddressSpaceD1Ev+0x160>
  108001:	48 8b 45 b0          	mov    -0x50(%rbp),%rax
  108005:	48 8b 40 08          	mov    0x8(%rax),%rax
  108009:	48 63 4d f4          	movslq -0xc(%rbp),%rcx
  10800d:	48 8b 04 c8          	mov    (%rax,%rcx,8),%rax
  108011:	48 25 00 f0 ff ff    	and    $0xfffffffffffff000,%rax
  108017:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
  10801b:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  10801f:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  108023:	c7 45 dc 00 00 00 00 	movl   $0x0,-0x24(%rbp)
  10802a:	81 7d dc 00 02 00 00 	cmpl   $0x200,-0x24(%rbp)
  108031:	0f 8d d0 00 00 00    	jge    108107 <_ZN4acos6memory12AddressSpaceD1Ev+0x157>
  108037:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  10803b:	48 63 4d dc          	movslq -0x24(%rbp),%rcx
  10803f:	48 8b 04 c8          	mov    (%rax,%rcx,8),%rax
  108043:	48 83 e0 01          	and    $0x1,%rax
  108047:	48 83 f8 00          	cmp    $0x0,%rax
  10804b:	0f 84 a3 00 00 00    	je     1080f4 <_ZN4acos6memory12AddressSpaceD1Ev+0x144>
  108051:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  108055:	48 63 4d dc          	movslq -0x24(%rbp),%rcx
  108059:	48 8b 04 c8          	mov    (%rax,%rcx,8),%rax
  10805d:	48 25 00 f0 ff ff    	and    $0xfffffffffffff000,%rax
  108063:	48 89 45 d0          	mov    %rax,-0x30(%rbp)
  108067:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  10806b:	48 89 45 c8          	mov    %rax,-0x38(%rbp)
  10806f:	c7 45 c4 00 00 00 00 	movl   $0x0,-0x3c(%rbp)
  108076:	81 7d c4 00 02 00 00 	cmpl   $0x200,-0x3c(%rbp)
  10807d:	0f 8d 68 00 00 00    	jge    1080eb <_ZN4acos6memory12AddressSpaceD1Ev+0x13b>
  108083:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  108087:	48 63 4d c4          	movslq -0x3c(%rbp),%rcx
  10808b:	48 8b 04 c8          	mov    (%rax,%rcx,8),%rax
  10808f:	48 83 e0 01          	and    $0x1,%rax
  108093:	48 83 f8 00          	cmp    $0x0,%rax
  108097:	0f 84 3b 00 00 00    	je     1080d8 <_ZN4acos6memory12AddressSpaceD1Ev+0x128>
  10809d:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  1080a1:	48 63 4d c4          	movslq -0x3c(%rbp),%rcx
  1080a5:	48 8b 04 c8          	mov    (%rax,%rcx,8),%rax
  1080a9:	48 25 80 00 00 00    	and    $0x80,%rax
  1080af:	48 83 f8 00          	cmp    $0x0,%rax
  1080b3:	0f 85 1f 00 00 00    	jne    1080d8 <_ZN4acos6memory12AddressSpaceD1Ev+0x128>
  1080b9:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  1080bd:	48 63 4d c4          	movslq -0x3c(%rbp),%rcx
  1080c1:	48 8b 04 c8          	mov    (%rax,%rcx,8),%rax
  1080c5:	48 25 00 f0 ff ff    	and    $0xfffffffffffff000,%rax
  1080cb:	48 89 45 b8          	mov    %rax,-0x48(%rbp)
  1080cf:	48 8b 7d b8          	mov    -0x48(%rbp),%rdi
  1080d3:	e8 18 f7 ff ff       	call   1077f0 <_ZN4acos6memory8pmm_freeEm>
  1080d8:	e9 00 00 00 00       	jmp    1080dd <_ZN4acos6memory12AddressSpaceD1Ev+0x12d>
  1080dd:	8b 45 c4             	mov    -0x3c(%rbp),%eax
  1080e0:	83 c0 01             	add    $0x1,%eax
  1080e3:	89 45 c4             	mov    %eax,-0x3c(%rbp)
  1080e6:	e9 8b ff ff ff       	jmp    108076 <_ZN4acos6memory12AddressSpaceD1Ev+0xc6>
  1080eb:	48 8b 7d d0          	mov    -0x30(%rbp),%rdi
  1080ef:	e8 fc f6 ff ff       	call   1077f0 <_ZN4acos6memory8pmm_freeEm>
  1080f4:	e9 00 00 00 00       	jmp    1080f9 <_ZN4acos6memory12AddressSpaceD1Ev+0x149>
  1080f9:	8b 45 dc             	mov    -0x24(%rbp),%eax
  1080fc:	83 c0 01             	add    $0x1,%eax
  1080ff:	89 45 dc             	mov    %eax,-0x24(%rbp)
  108102:	e9 23 ff ff ff       	jmp    10802a <_ZN4acos6memory12AddressSpaceD1Ev+0x7a>
  108107:	48 8b 7d e8          	mov    -0x18(%rbp),%rdi
  10810b:	e8 e0 f6 ff ff       	call   1077f0 <_ZN4acos6memory8pmm_freeEm>
  108110:	e9 00 00 00 00       	jmp    108115 <_ZN4acos6memory12AddressSpaceD1Ev+0x165>
  108115:	8b 45 f4             	mov    -0xc(%rbp),%eax
  108118:	83 c0 01             	add    $0x1,%eax
  10811b:	89 45 f4             	mov    %eax,-0xc(%rbp)
  10811e:	e9 b3 fe ff ff       	jmp    107fd6 <_ZN4acos6memory12AddressSpaceD1Ev+0x26>
  108123:	48 8b 45 b0          	mov    -0x50(%rbp),%rax
  108127:	48 8b 38             	mov    (%rax),%rdi
  10812a:	e8 c1 f6 ff ff       	call   1077f0 <_ZN4acos6memory8pmm_freeEm>
  10812f:	48 83 c4 50          	add    $0x50,%rsp
  108133:	5d                   	pop    %rbp
  108134:	c3                   	ret
  108135:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  10813c:	00 00 00 00

0000000000108140 <_ZN4acos6memory12AddressSpace3mapEmmm>:
  108140:	55                   	push   %rbp
  108141:	48 89 e5             	mov    %rsp,%rbp
  108144:	48 83 ec 70          	sub    $0x70,%rsp
  108148:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  10814c:	48 89 75 e8          	mov    %rsi,-0x18(%rbp)
  108150:	48 89 55 e0          	mov    %rdx,-0x20(%rbp)
  108154:	48 89 4d d8          	mov    %rcx,-0x28(%rbp)
  108158:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10815c:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  108160:	48 c1 e9 27          	shr    $0x27,%rcx
  108164:	48 81 e1 ff 01 00 00 	and    $0x1ff,%rcx
  10816b:	48 89 4d d0          	mov    %rcx,-0x30(%rbp)
  10816f:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  108173:	48 c1 e9 1e          	shr    $0x1e,%rcx
  108177:	48 81 e1 ff 01 00 00 	and    $0x1ff,%rcx
  10817e:	48 89 4d c8          	mov    %rcx,-0x38(%rbp)
  108182:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  108186:	48 c1 e9 15          	shr    $0x15,%rcx
  10818a:	48 81 e1 ff 01 00 00 	and    $0x1ff,%rcx
  108191:	48 89 4d c0          	mov    %rcx,-0x40(%rbp)
  108195:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  108199:	48 c1 e9 0c          	shr    $0xc,%rcx
  10819d:	48 81 e1 ff 01 00 00 	and    $0x1ff,%rcx
  1081a4:	48 89 4d b8          	mov    %rcx,-0x48(%rbp)
  1081a8:	8a 0c 25 71 f4 10 00 	mov    0x10f471,%cl
  1081af:	88 4d b7             	mov    %cl,-0x49(%rbp)
  1081b2:	48 8b 4d d8          	mov    -0x28(%rbp),%rcx
  1081b6:	48 83 e1 04          	and    $0x4,%rcx
  1081ba:	48 83 f9 00          	cmp    $0x0,%rcx
  1081be:	0f 95 c1             	setne  %cl
  1081c1:	80 e1 01             	and    $0x1,%cl
  1081c4:	88 4d b6             	mov    %cl,-0x4a(%rbp)
  1081c7:	48 8b 70 08          	mov    0x8(%rax),%rsi
  1081cb:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  1081cf:	48 c1 e0 03          	shl    $0x3,%rax
  1081d3:	48 01 c6             	add    %rax,%rsi
  1081d6:	8a 45 b6             	mov    -0x4a(%rbp),%al
  1081d9:	48 8d 7d b7          	lea    -0x49(%rbp),%rdi
  1081dd:	24 01                	and    $0x1,%al
  1081df:	0f b6 d0             	movzbl %al,%edx
  1081e2:	e8 b9 00 00 00       	call   1082a0 <_ZZN4acos6memory12AddressSpace3mapEmmmENK3$_0clEPmb>
  1081e7:	48 89 45 a8          	mov    %rax,-0x58(%rbp)
  1081eb:	48 83 7d a8 00       	cmpq   $0x0,-0x58(%rbp)
  1081f0:	0f 85 09 00 00 00    	jne    1081ff <_ZN4acos6memory12AddressSpace3mapEmmm+0xbf>
  1081f6:	c6 45 ff 00          	movb   $0x0,-0x1(%rbp)
  1081fa:	e9 8c 00 00 00       	jmp    10828b <_ZN4acos6memory12AddressSpace3mapEmmm+0x14b>
  1081ff:	48 8b 75 a8          	mov    -0x58(%rbp),%rsi
  108203:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  108207:	48 c1 e0 03          	shl    $0x3,%rax
  10820b:	48 01 c6             	add    %rax,%rsi
  10820e:	8a 45 b6             	mov    -0x4a(%rbp),%al
  108211:	48 8d 7d b7          	lea    -0x49(%rbp),%rdi
  108215:	24 01                	and    $0x1,%al
  108217:	0f b6 d0             	movzbl %al,%edx
  10821a:	e8 81 00 00 00       	call   1082a0 <_ZZN4acos6memory12AddressSpace3mapEmmmENK3$_0clEPmb>
  10821f:	48 89 45 a0          	mov    %rax,-0x60(%rbp)
  108223:	48 83 7d a0 00       	cmpq   $0x0,-0x60(%rbp)
  108228:	0f 85 09 00 00 00    	jne    108237 <_ZN4acos6memory12AddressSpace3mapEmmm+0xf7>
  10822e:	c6 45 ff 00          	movb   $0x0,-0x1(%rbp)
  108232:	e9 54 00 00 00       	jmp    10828b <_ZN4acos6memory12AddressSpace3mapEmmm+0x14b>
  108237:	48 8b 75 a0          	mov    -0x60(%rbp),%rsi
  10823b:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  10823f:	48 c1 e0 03          	shl    $0x3,%rax
  108243:	48 01 c6             	add    %rax,%rsi
  108246:	8a 45 b6             	mov    -0x4a(%rbp),%al
  108249:	48 8d 7d b7          	lea    -0x49(%rbp),%rdi
  10824d:	24 01                	and    $0x1,%al
  10824f:	0f b6 d0             	movzbl %al,%edx
  108252:	e8 49 00 00 00       	call   1082a0 <_ZZN4acos6memory12AddressSpace3mapEmmmENK3$_0clEPmb>
  108257:	48 89 45 98          	mov    %rax,-0x68(%rbp)
  10825b:	48 83 7d 98 00       	cmpq   $0x0,-0x68(%rbp)
  108260:	0f 85 09 00 00 00    	jne    10826f <_ZN4acos6memory12AddressSpace3mapEmmm+0x12f>
  108266:	c6 45 ff 00          	movb   $0x0,-0x1(%rbp)
  10826a:	e9 1c 00 00 00       	jmp    10828b <_ZN4acos6memory12AddressSpace3mapEmmm+0x14b>
  10826f:	48 8b 55 e0          	mov    -0x20(%rbp),%rdx
  108273:	48 0b 55 d8          	or     -0x28(%rbp),%rdx
  108277:	48 83 ca 01          	or     $0x1,%rdx
  10827b:	48 8b 45 98          	mov    -0x68(%rbp),%rax
  10827f:	48 8b 4d b8          	mov    -0x48(%rbp),%rcx
  108283:	48 89 14 c8          	mov    %rdx,(%rax,%rcx,8)
  108287:	c6 45 ff 01          	movb   $0x1,-0x1(%rbp)
  10828b:	8a 45 ff             	mov    -0x1(%rbp),%al
  10828e:	24 01                	and    $0x1,%al
  108290:	0f b6 c0             	movzbl %al,%eax
  108293:	48 83 c4 70          	add    $0x70,%rsp
  108297:	5d                   	pop    %rbp
  108298:	c3                   	ret
  108299:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

00000000001082a0 <_ZZN4acos6memory12AddressSpace3mapEmmmENK3$_0clEPmb>:
  1082a0:	55                   	push   %rbp
  1082a1:	48 89 e5             	mov    %rsp,%rbp
  1082a4:	48 83 ec 60          	sub    $0x60,%rsp
  1082a8:	88 d0                	mov    %dl,%al
  1082aa:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  1082ae:	48 89 75 e8          	mov    %rsi,-0x18(%rbp)
  1082b2:	24 01                	and    $0x1,%al
  1082b4:	88 45 e7             	mov    %al,-0x19(%rbp)
  1082b7:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  1082bb:	48 8b 00             	mov    (%rax),%rax
  1082be:	48 83 e0 01          	and    $0x1,%rax
  1082c2:	48 83 f8 00          	cmp    $0x0,%rax
  1082c6:	0f 85 8e 00 00 00    	jne    10835a <_ZZN4acos6memory12AddressSpace3mapEmmmENK3$_0clEPmb+0xba>
  1082cc:	e8 cf f2 ff ff       	call   1075a0 <_ZN4acos6memory9pmm_allocEv>
  1082d1:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
  1082d5:	48 83 7d d8 00       	cmpq   $0x0,-0x28(%rbp)
  1082da:	0f 85 0d 00 00 00    	jne    1082ed <_ZZN4acos6memory12AddressSpace3mapEmmmENK3$_0clEPmb+0x4d>
  1082e0:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  1082e7:	00
  1082e8:	e9 72 01 00 00       	jmp    10845f <_ZZN4acos6memory12AddressSpace3mapEmmmENK3$_0clEPmb+0x1bf>
  1082ed:	48 8b 4d d8          	mov    -0x28(%rbp),%rcx
  1082f1:	48 83 c9 03          	or     $0x3,%rcx
  1082f5:	40 8a 75 e7          	mov    -0x19(%rbp),%sil
  1082f9:	31 c0                	xor    %eax,%eax
  1082fb:	ba 04 00 00 00       	mov    $0x4,%edx
  108300:	40 f6 c6 01          	test   $0x1,%sil
  108304:	0f 45 c2             	cmovne %edx,%eax
  108307:	48 98                	cltq
  108309:	48 09 c1             	or     %rax,%rcx
  10830c:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  108310:	48 89 08             	mov    %rcx,(%rax)
  108313:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  108317:	48 89 45 d0          	mov    %rax,-0x30(%rbp)
  10831b:	c7 45 cc 00 00 00 00 	movl   $0x0,-0x34(%rbp)
  108322:	81 7d cc 00 02 00 00 	cmpl   $0x200,-0x34(%rbp)
  108329:	0f 8d 1e 00 00 00    	jge    10834d <_ZZN4acos6memory12AddressSpace3mapEmmmENK3$_0clEPmb+0xad>
  10832f:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  108333:	48 63 4d cc          	movslq -0x34(%rbp),%rcx
  108337:	48 c7 04 c8 00 00 00 	movq   $0x0,(%rax,%rcx,8)
  10833e:	00
  10833f:	8b 45 cc             	mov    -0x34(%rbp),%eax
  108342:	83 c0 01             	add    $0x1,%eax
  108345:	89 45 cc             	mov    %eax,-0x34(%rbp)
  108348:	e9 d5 ff ff ff       	jmp    108322 <_ZZN4acos6memory12AddressSpace3mapEmmmENK3$_0clEPmb+0x82>
  10834d:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  108351:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  108355:	e9 05 01 00 00       	jmp    10845f <_ZZN4acos6memory12AddressSpace3mapEmmmENK3$_0clEPmb+0x1bf>
  10835a:	f6 45 e7 01          	testb  $0x1,-0x19(%rbp)
  10835e:	0f 84 0e 00 00 00    	je     108372 <_ZZN4acos6memory12AddressSpace3mapEmmmENK3$_0clEPmb+0xd2>
  108364:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  108368:	48 8b 08             	mov    (%rax),%rcx
  10836b:	48 83 c9 04          	or     $0x4,%rcx
  10836f:	48 89 08             	mov    %rcx,(%rax)
  108372:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  108376:	48 8b 00             	mov    (%rax),%rax
  108379:	48 25 80 00 00 00    	and    $0x80,%rax
  10837f:	48 83 f8 00          	cmp    $0x0,%rax
  108383:	0f 84 c5 00 00 00    	je     10844e <_ZZN4acos6memory12AddressSpace3mapEmmmENK3$_0clEPmb+0x1ae>
  108389:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  10838d:	48 8b 00             	mov    (%rax),%rax
  108390:	48 25 00 00 e0 ff    	and    $0xffffffffffe00000,%rax
  108396:	48 89 45 c0          	mov    %rax,-0x40(%rbp)
  10839a:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  10839e:	48 8b 00             	mov    (%rax),%rax
  1083a1:	48 25 ff ff 1f 00    	and    $0x1fffff,%rax
  1083a7:	48 25 7f ff ff ff    	and    $0xffffffffffffff7f,%rax
  1083ad:	48 89 45 b8          	mov    %rax,-0x48(%rbp)
  1083b1:	e8 ea f1 ff ff       	call   1075a0 <_ZN4acos6memory9pmm_allocEv>
  1083b6:	48 89 45 b0          	mov    %rax,-0x50(%rbp)
  1083ba:	48 83 7d b0 00       	cmpq   $0x0,-0x50(%rbp)
  1083bf:	0f 85 0d 00 00 00    	jne    1083d2 <_ZZN4acos6memory12AddressSpace3mapEmmmENK3$_0clEPmb+0x132>
  1083c5:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  1083cc:	00
  1083cd:	e9 8d 00 00 00       	jmp    10845f <_ZZN4acos6memory12AddressSpace3mapEmmmENK3$_0clEPmb+0x1bf>
  1083d2:	48 8b 45 b0          	mov    -0x50(%rbp),%rax
  1083d6:	48 89 45 a8          	mov    %rax,-0x58(%rbp)
  1083da:	c7 45 a4 00 00 00 00 	movl   $0x0,-0x5c(%rbp)
  1083e1:	81 7d a4 00 02 00 00 	cmpl   $0x200,-0x5c(%rbp)
  1083e8:	0f 8d 2d 00 00 00    	jge    10841b <_ZZN4acos6memory12AddressSpace3mapEmmmENK3$_0clEPmb+0x17b>
  1083ee:	48 8b 55 c0          	mov    -0x40(%rbp),%rdx
  1083f2:	8b 45 a4             	mov    -0x5c(%rbp),%eax
  1083f5:	c1 e0 0c             	shl    $0xc,%eax
  1083f8:	48 98                	cltq
  1083fa:	48 01 c2             	add    %rax,%rdx
  1083fd:	48 0b 55 b8          	or     -0x48(%rbp),%rdx
  108401:	48 8b 45 a8          	mov    -0x58(%rbp),%rax
  108405:	48 63 4d a4          	movslq -0x5c(%rbp),%rcx
  108409:	48 89 14 c8          	mov    %rdx,(%rax,%rcx,8)
  10840d:	8b 45 a4             	mov    -0x5c(%rbp),%eax
  108410:	83 c0 01             	add    $0x1,%eax
  108413:	89 45 a4             	mov    %eax,-0x5c(%rbp)
  108416:	e9 c6 ff ff ff       	jmp    1083e1 <_ZZN4acos6memory12AddressSpace3mapEmmmENK3$_0clEPmb+0x141>
  10841b:	48 8b 4d b0          	mov    -0x50(%rbp),%rcx
  10841f:	48 83 c9 03          	or     $0x3,%rcx
  108423:	40 8a 75 e7          	mov    -0x19(%rbp),%sil
  108427:	31 c0                	xor    %eax,%eax
  108429:	ba 04 00 00 00       	mov    $0x4,%edx
  10842e:	40 f6 c6 01          	test   $0x1,%sil
  108432:	0f 45 c2             	cmovne %edx,%eax
  108435:	48 98                	cltq
  108437:	48 09 c1             	or     %rax,%rcx
  10843a:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  10843e:	48 89 08             	mov    %rcx,(%rax)
  108441:	48 8b 45 a8          	mov    -0x58(%rbp),%rax
  108445:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  108449:	e9 11 00 00 00       	jmp    10845f <_ZZN4acos6memory12AddressSpace3mapEmmmENK3$_0clEPmb+0x1bf>
  10844e:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  108452:	48 8b 00             	mov    (%rax),%rax
  108455:	48 25 00 f0 ff ff    	and    $0xfffffffffffff000,%rax
  10845b:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  10845f:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  108463:	48 83 c4 60          	add    $0x60,%rsp
  108467:	5d                   	pop    %rbp
  108468:	c3                   	ret
  108469:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000108470 <_ZN4acos6memory12AddressSpace5unmapEm>:
  108470:	55                   	push   %rbp
  108471:	48 89 e5             	mov    %rsp,%rbp
  108474:	48 83 ec 58          	sub    $0x58,%rsp
  108478:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  10847c:	48 89 75 e8          	mov    %rsi,-0x18(%rbp)
  108480:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  108484:	48 89 45 a8          	mov    %rax,-0x58(%rbp)
  108488:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  10848c:	48 c1 e9 27          	shr    $0x27,%rcx
  108490:	48 81 e1 ff 01 00 00 	and    $0x1ff,%rcx
  108497:	48 89 4d e0          	mov    %rcx,-0x20(%rbp)
  10849b:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  10849f:	48 c1 e9 1e          	shr    $0x1e,%rcx
  1084a3:	48 81 e1 ff 01 00 00 	and    $0x1ff,%rcx
  1084aa:	48 89 4d d8          	mov    %rcx,-0x28(%rbp)
  1084ae:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  1084b2:	48 c1 e9 15          	shr    $0x15,%rcx
  1084b6:	48 81 e1 ff 01 00 00 	and    $0x1ff,%rcx
  1084bd:	48 89 4d d0          	mov    %rcx,-0x30(%rbp)
  1084c1:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  1084c5:	48 c1 e9 0c          	shr    $0xc,%rcx
  1084c9:	48 81 e1 ff 01 00 00 	and    $0x1ff,%rcx
  1084d0:	48 89 4d c8          	mov    %rcx,-0x38(%rbp)
  1084d4:	48 8b 40 08          	mov    0x8(%rax),%rax
  1084d8:	48 8b 4d e0          	mov    -0x20(%rbp),%rcx
  1084dc:	48 8b 04 c8          	mov    (%rax,%rcx,8),%rax
  1084e0:	48 83 e0 01          	and    $0x1,%rax
  1084e4:	48 83 f8 00          	cmp    $0x0,%rax
  1084e8:	0f 85 09 00 00 00    	jne    1084f7 <_ZN4acos6memory12AddressSpace5unmapEm+0x87>
  1084ee:	c6 45 ff 00          	movb   $0x0,-0x1(%rbp)
  1084f2:	e9 a7 00 00 00       	jmp    10859e <_ZN4acos6memory12AddressSpace5unmapEm+0x12e>
  1084f7:	48 8b 45 a8          	mov    -0x58(%rbp),%rax
  1084fb:	48 8b 40 08          	mov    0x8(%rax),%rax
  1084ff:	48 8b 4d e0          	mov    -0x20(%rbp),%rcx
  108503:	48 8b 04 c8          	mov    (%rax,%rcx,8),%rax
  108507:	48 25 00 f0 ff ff    	and    $0xfffffffffffff000,%rax
  10850d:	48 89 45 c0          	mov    %rax,-0x40(%rbp)
  108511:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  108515:	48 8b 4d d8          	mov    -0x28(%rbp),%rcx
  108519:	48 8b 04 c8          	mov    (%rax,%rcx,8),%rax
  10851d:	48 83 e0 01          	and    $0x1,%rax
  108521:	48 83 f8 00          	cmp    $0x0,%rax
  108525:	0f 85 09 00 00 00    	jne    108534 <_ZN4acos6memory12AddressSpace5unmapEm+0xc4>
  10852b:	c6 45 ff 00          	movb   $0x0,-0x1(%rbp)
  10852f:	e9 6a 00 00 00       	jmp    10859e <_ZN4acos6memory12AddressSpace5unmapEm+0x12e>
  108534:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  108538:	48 8b 4d d8          	mov    -0x28(%rbp),%rcx
  10853c:	48 8b 04 c8          	mov    (%rax,%rcx,8),%rax
  108540:	48 25 00 f0 ff ff    	and    $0xfffffffffffff000,%rax
  108546:	48 89 45 b8          	mov    %rax,-0x48(%rbp)
  10854a:	48 8b 45 b8          	mov    -0x48(%rbp),%rax
  10854e:	48 8b 4d d0          	mov    -0x30(%rbp),%rcx
  108552:	48 8b 04 c8          	mov    (%rax,%rcx,8),%rax
  108556:	48 83 e0 01          	and    $0x1,%rax
  10855a:	48 83 f8 00          	cmp    $0x0,%rax
  10855e:	0f 85 09 00 00 00    	jne    10856d <_ZN4acos6memory12AddressSpace5unmapEm+0xfd>
  108564:	c6 45 ff 00          	movb   $0x0,-0x1(%rbp)
  108568:	e9 31 00 00 00       	jmp    10859e <_ZN4acos6memory12AddressSpace5unmapEm+0x12e>
  10856d:	48 8b 45 b8          	mov    -0x48(%rbp),%rax
  108571:	48 8b 4d d0          	mov    -0x30(%rbp),%rcx
  108575:	48 8b 04 c8          	mov    (%rax,%rcx,8),%rax
  108579:	48 25 00 f0 ff ff    	and    $0xfffffffffffff000,%rax
  10857f:	48 89 45 b0          	mov    %rax,-0x50(%rbp)
  108583:	48 8b 45 b0          	mov    -0x50(%rbp),%rax
  108587:	48 8b 4d c8          	mov    -0x38(%rbp),%rcx
  10858b:	48 c7 04 c8 00 00 00 	movq   $0x0,(%rax,%rcx,8)
  108592:	00
  108593:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  108597:	0f 01 38             	invlpg (%rax)
  10859a:	c6 45 ff 01          	movb   $0x1,-0x1(%rbp)
  10859e:	8a 45 ff             	mov    -0x1(%rbp),%al
  1085a1:	24 01                	and    $0x1,%al
  1085a3:	0f b6 c0             	movzbl %al,%eax
  1085a6:	48 83 c4 58          	add    $0x58,%rsp
  1085aa:	5d                   	pop    %rbp
  1085ab:	c3                   	ret
  1085ac:	0f 1f 40 00          	nopl   0x0(%rax)

00000000001085b0 <_ZN4acos6memory12AddressSpace9translateEm>:
  1085b0:	55                   	push   %rbp
  1085b1:	48 89 e5             	mov    %rsp,%rbp
  1085b4:	48 83 ec 58          	sub    $0x58,%rsp
  1085b8:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  1085bc:	48 89 75 e8          	mov    %rsi,-0x18(%rbp)
  1085c0:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  1085c4:	48 89 45 a8          	mov    %rax,-0x58(%rbp)
  1085c8:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  1085cc:	48 c1 e9 27          	shr    $0x27,%rcx
  1085d0:	48 81 e1 ff 01 00 00 	and    $0x1ff,%rcx
  1085d7:	48 89 4d e0          	mov    %rcx,-0x20(%rbp)
  1085db:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  1085df:	48 c1 e9 1e          	shr    $0x1e,%rcx
  1085e3:	48 81 e1 ff 01 00 00 	and    $0x1ff,%rcx
  1085ea:	48 89 4d d8          	mov    %rcx,-0x28(%rbp)
  1085ee:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  1085f2:	48 c1 e9 15          	shr    $0x15,%rcx
  1085f6:	48 81 e1 ff 01 00 00 	and    $0x1ff,%rcx
  1085fd:	48 89 4d d0          	mov    %rcx,-0x30(%rbp)
  108601:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  108605:	48 c1 e9 0c          	shr    $0xc,%rcx
  108609:	48 81 e1 ff 01 00 00 	and    $0x1ff,%rcx
  108610:	48 89 4d c8          	mov    %rcx,-0x38(%rbp)
  108614:	48 8b 40 08          	mov    0x8(%rax),%rax
  108618:	48 8b 4d e0          	mov    -0x20(%rbp),%rcx
  10861c:	48 8b 04 c8          	mov    (%rax,%rcx,8),%rax
  108620:	48 83 e0 01          	and    $0x1,%rax
  108624:	48 83 f8 00          	cmp    $0x0,%rax
  108628:	0f 85 0d 00 00 00    	jne    10863b <_ZN4acos6memory12AddressSpace9translateEm+0x8b>
  10862e:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  108635:	00
  108636:	e9 fd 00 00 00       	jmp    108738 <_ZN4acos6memory12AddressSpace9translateEm+0x188>
  10863b:	48 8b 45 a8          	mov    -0x58(%rbp),%rax
  10863f:	48 8b 40 08          	mov    0x8(%rax),%rax
  108643:	48 8b 4d e0          	mov    -0x20(%rbp),%rcx
  108647:	48 8b 04 c8          	mov    (%rax,%rcx,8),%rax
  10864b:	48 25 00 f0 ff ff    	and    $0xfffffffffffff000,%rax
  108651:	48 89 45 c0          	mov    %rax,-0x40(%rbp)
  108655:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  108659:	48 8b 4d d8          	mov    -0x28(%rbp),%rcx
  10865d:	48 8b 04 c8          	mov    (%rax,%rcx,8),%rax
  108661:	48 83 e0 01          	and    $0x1,%rax
  108665:	48 83 f8 00          	cmp    $0x0,%rax
  108669:	0f 85 0d 00 00 00    	jne    10867c <_ZN4acos6memory12AddressSpace9translateEm+0xcc>
  10866f:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  108676:	00
  108677:	e9 bc 00 00 00       	jmp    108738 <_ZN4acos6memory12AddressSpace9translateEm+0x188>
  10867c:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  108680:	48 8b 4d d8          	mov    -0x28(%rbp),%rcx
  108684:	48 8b 04 c8          	mov    (%rax,%rcx,8),%rax
  108688:	48 25 00 f0 ff ff    	and    $0xfffffffffffff000,%rax
  10868e:	48 89 45 b8          	mov    %rax,-0x48(%rbp)
  108692:	48 8b 45 b8          	mov    -0x48(%rbp),%rax
  108696:	48 8b 4d d0          	mov    -0x30(%rbp),%rcx
  10869a:	48 8b 04 c8          	mov    (%rax,%rcx,8),%rax
  10869e:	48 83 e0 01          	and    $0x1,%rax
  1086a2:	48 83 f8 00          	cmp    $0x0,%rax
  1086a6:	0f 85 0d 00 00 00    	jne    1086b9 <_ZN4acos6memory12AddressSpace9translateEm+0x109>
  1086ac:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  1086b3:	00
  1086b4:	e9 7f 00 00 00       	jmp    108738 <_ZN4acos6memory12AddressSpace9translateEm+0x188>
  1086b9:	48 8b 45 b8          	mov    -0x48(%rbp),%rax
  1086bd:	48 8b 4d d0          	mov    -0x30(%rbp),%rcx
  1086c1:	48 8b 04 c8          	mov    (%rax,%rcx,8),%rax
  1086c5:	48 25 80 00 00 00    	and    $0x80,%rax
  1086cb:	48 83 f8 00          	cmp    $0x0,%rax
  1086cf:	0f 84 29 00 00 00    	je     1086fe <_ZN4acos6memory12AddressSpace9translateEm+0x14e>
  1086d5:	48 8b 45 b8          	mov    -0x48(%rbp),%rax
  1086d9:	48 8b 4d d0          	mov    -0x30(%rbp),%rcx
  1086dd:	48 8b 04 c8          	mov    (%rax,%rcx,8),%rax
  1086e1:	48 25 00 00 e0 ff    	and    $0xffffffffffe00000,%rax
  1086e7:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  1086eb:	48 81 e1 ff ff 1f 00 	and    $0x1fffff,%rcx
  1086f2:	48 09 c8             	or     %rcx,%rax
  1086f5:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  1086f9:	e9 3a 00 00 00       	jmp    108738 <_ZN4acos6memory12AddressSpace9translateEm+0x188>
  1086fe:	48 8b 45 b8          	mov    -0x48(%rbp),%rax
  108702:	48 8b 4d d0          	mov    -0x30(%rbp),%rcx
  108706:	48 8b 04 c8          	mov    (%rax,%rcx,8),%rax
  10870a:	48 25 00 f0 ff ff    	and    $0xfffffffffffff000,%rax
  108710:	48 89 45 b0          	mov    %rax,-0x50(%rbp)
  108714:	48 8b 45 b0          	mov    -0x50(%rbp),%rax
  108718:	48 8b 4d c8          	mov    -0x38(%rbp),%rcx
  10871c:	48 8b 04 c8          	mov    (%rax,%rcx,8),%rax
  108720:	48 25 00 f0 ff ff    	and    $0xfffffffffffff000,%rax
  108726:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  10872a:	48 81 e1 ff 0f 00 00 	and    $0xfff,%rcx
  108731:	48 09 c8             	or     %rcx,%rax
  108734:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  108738:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10873c:	48 83 c4 58          	add    $0x58,%rsp
  108740:	5d                   	pop    %rbp
  108741:	c3                   	ret
  108742:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
  108749:	00 00 00
  10874c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000108750 <_ZN4acos6memory7kmallocEm>:
  108750:	55                   	push   %rbp
  108751:	48 89 e5             	mov    %rsp,%rbp
  108754:	48 83 ec 30          	sub    $0x30,%rsp
  108758:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  10875c:	48 83 7d f0 00       	cmpq   $0x0,-0x10(%rbp)
  108761:	0f 85 0d 00 00 00    	jne    108774 <_ZN4acos6memory7kmallocEm+0x24>
  108767:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  10876e:	00
  10876f:	e9 60 00 00 00       	jmp    1087d4 <_ZN4acos6memory7kmallocEm+0x84>
  108774:	48 8b 7d f0          	mov    -0x10(%rbp),%rdi
  108778:	be 10 00 00 00       	mov    $0x10,%esi
  10877d:	e8 5e 00 00 00       	call   1087e0 <_ZN4acos6memory12_GLOBAL__N_18align_upEmm>
  108782:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
  108786:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  10878a:	48 05 00 10 00 00    	add    $0x1000,%rax
  108790:	48 83 e8 01          	sub    $0x1,%rax
  108794:	48 c1 e8 0c          	shr    $0xc,%rax
  108798:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  10879c:	48 8b 7d e0          	mov    -0x20(%rbp),%rdi
  1087a0:	e8 fb ee ff ff       	call   1076a0 <_ZN4acos6memory20pmm_alloc_contiguousEm>
  1087a5:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
  1087a9:	48 83 7d d8 00       	cmpq   $0x0,-0x28(%rbp)
  1087ae:	0f 84 0d 00 00 00    	je     1087c1 <_ZN4acos6memory7kmallocEm+0x71>
  1087b4:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  1087b8:	48 89 45 d0          	mov    %rax,-0x30(%rbp)
  1087bc:	e9 0b 00 00 00       	jmp    1087cc <_ZN4acos6memory7kmallocEm+0x7c>
  1087c1:	31 c0                	xor    %eax,%eax
  1087c3:	48 89 45 d0          	mov    %rax,-0x30(%rbp)
  1087c7:	e9 00 00 00 00       	jmp    1087cc <_ZN4acos6memory7kmallocEm+0x7c>
  1087cc:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  1087d0:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  1087d4:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  1087d8:	48 83 c4 30          	add    $0x30,%rsp
  1087dc:	5d                   	pop    %rbp
  1087dd:	c3                   	ret
  1087de:	66 90                	xchg   %ax,%ax

00000000001087e0 <_ZN4acos6memory12_GLOBAL__N_18align_upEmm>:
  1087e0:	55                   	push   %rbp
  1087e1:	48 89 e5             	mov    %rsp,%rbp
  1087e4:	48 83 ec 10          	sub    $0x10,%rsp
  1087e8:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  1087ec:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  1087f0:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  1087f4:	48 03 45 f0          	add    -0x10(%rbp),%rax
  1087f8:	48 83 e8 01          	sub    $0x1,%rax
  1087fc:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
  108800:	48 83 e9 01          	sub    $0x1,%rcx
  108804:	48 83 f1 ff          	xor    $0xffffffffffffffff,%rcx
  108808:	48 21 c8             	and    %rcx,%rax
  10880b:	48 83 c4 10          	add    $0x10,%rsp
  10880f:	5d                   	pop    %rbp
  108810:	c3                   	ret
  108811:	66 66 66 66 66 66 2e 	data16 data16 data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
  108818:	0f 1f 84 00 00 00 00
  10881f:	00

0000000000108820 <_ZN4acos6memory5kfreeEPv>:
  108820:	55                   	push   %rbp
  108821:	48 89 e5             	mov    %rsp,%rbp
  108824:	50                   	push   %rax
  108825:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  108829:	48 83 c4 08          	add    $0x8,%rsp
  10882d:	5d                   	pop    %rbp
  10882e:	c3                   	ret
  10882f:	90                   	nop

0000000000108830 <_ZN4acos3ipc7ChannelC1Ev>:
  108830:	55                   	push   %rbp
  108831:	48 89 e5             	mov    %rsp,%rbp
  108834:	48 83 ec 20          	sub    $0x20,%rsp
  108838:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10883c:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  108840:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
  108844:	48 83 c7 08          	add    $0x8,%rdi
  108848:	e8 a3 63 00 00       	call   10ebf0 <_ZN4acos3hal8SpinLockC2Ev>
  10884d:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  108851:	48 c7 80 10 03 00 00 	movq   $0x0,0x310(%rax)
  108858:	00 00 00 00
  10885c:	48 c7 80 18 03 00 00 	movq   $0x0,0x318(%rax)
  108863:	00 00 00 00
  108867:	48 c7 80 20 03 00 00 	movq   $0x0,0x320(%rax)
  10886e:	00 00 00 00
  108872:	48 c7 80 68 03 00 00 	movq   $0x0,0x368(%rax)
  108879:	00 00 00 00
  10887d:	48 8b 0c 25 88 fc 10 	mov    0x10fc88,%rcx
  108884:	00
  108885:	48 89 ca             	mov    %rcx,%rdx
  108888:	48 83 c2 01          	add    $0x1,%rdx
  10888c:	48 89 14 25 88 fc 10 	mov    %rdx,0x10fc88
  108893:	00
  108894:	48 89 08             	mov    %rcx,(%rax)
  108897:	48 c7 45 f0 00 00 00 	movq   $0x0,-0x10(%rbp)
  10889e:	00
  10889f:	48 83 7d f0 08       	cmpq   $0x8,-0x10(%rbp)
  1088a4:	0f 83 25 00 00 00    	jae    1088cf <_ZN4acos3ipc7ChannelC1Ev+0x9f>
  1088aa:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  1088ae:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
  1088b2:	48 c7 84 c8 28 03 00 	movq   $0x0,0x328(%rax,%rcx,8)
  1088b9:	00 00 00 00 00
  1088be:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  1088c2:	48 83 c0 01          	add    $0x1,%rax
  1088c6:	48 89 45 f0          	mov    %rax,-0x10(%rbp)
  1088ca:	e9 d0 ff ff ff       	jmp    10889f <_ZN4acos3ipc7ChannelC1Ev+0x6f>
  1088cf:	48 83 c4 20          	add    $0x20,%rsp
  1088d3:	5d                   	pop    %rbp
  1088d4:	c3                   	ret
  1088d5:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  1088dc:	00 00 00 00

00000000001088e0 <_ZN4acos3ipc7Channel4sendERKNS_3abi7MessageE>:
  1088e0:	55                   	push   %rbp
  1088e1:	48 89 e5             	mov    %rsp,%rbp
  1088e4:	48 83 ec 40          	sub    $0x40,%rsp
  1088e8:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  1088ec:	48 89 75 e8          	mov    %rsi,-0x18(%rbp)
  1088f0:	48 8b 75 f0          	mov    -0x10(%rbp),%rsi
  1088f4:	48 89 75 c8          	mov    %rsi,-0x38(%rbp)
  1088f8:	48 83 c6 08          	add    $0x8,%rsi
  1088fc:	48 8d 7d e0          	lea    -0x20(%rbp),%rdi
  108900:	e8 8b 61 00 00       	call   10ea90 <_ZN4acos3hal10ScopedLockC2ERNS0_8SpinLockE>
  108905:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  108909:	48 83 b8 20 03 00 00 	cmpq   $0x10,0x320(%rax)
  108910:	10
  108911:	0f 82 10 00 00 00    	jb     108927 <_ZN4acos3ipc7Channel4sendERKNS_3abi7MessageE+0x47>
  108917:	c6 45 ff 00          	movb   $0x0,-0x1(%rbp)
  10891b:	c7 45 dc 01 00 00 00 	movl   $0x1,-0x24(%rbp)
  108922:	e9 e0 00 00 00       	jmp    108a07 <_ZN4acos3ipc7Channel4sendERKNS_3abi7MessageE+0x127>
  108927:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  10892b:	48 8b 75 e8          	mov    -0x18(%rbp),%rsi
  10892f:	48 89 c7             	mov    %rax,%rdi
  108932:	48 83 c7 10          	add    $0x10,%rdi
  108936:	48 6b 80 18 03 00 00 	imul   $0x30,0x318(%rax),%rax
  10893d:	30
  10893e:	48 01 c7             	add    %rax,%rdi
  108941:	ba 30 00 00 00       	mov    $0x30,%edx
  108946:	e8 b5 76 ff ff       	call   100000 <memcpy>
  10894b:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  10894f:	48 8b 88 18 03 00 00 	mov    0x318(%rax),%rcx
  108956:	48 83 c1 01          	add    $0x1,%rcx
  10895a:	48 83 e1 0f          	and    $0xf,%rcx
  10895e:	48 89 88 18 03 00 00 	mov    %rcx,0x318(%rax)
  108965:	48 8b 88 20 03 00 00 	mov    0x320(%rax),%rcx
  10896c:	48 83 c1 01          	add    $0x1,%rcx
  108970:	48 89 88 20 03 00 00 	mov    %rcx,0x320(%rax)
  108977:	48 83 b8 68 03 00 00 	cmpq   $0x0,0x368(%rax)
  10897e:	00
  10897f:	0f 86 77 00 00 00    	jbe    1089fc <_ZN4acos3ipc7Channel4sendERKNS_3abi7MessageE+0x11c>
  108985:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  108989:	48 8b b8 28 03 00 00 	mov    0x328(%rax),%rdi
  108990:	e8 7b df ff ff       	call   106910 <_ZN4acos9scheduler11wake_threadEPNS0_6ThreadE>
  108995:	48 c7 45 d0 00 00 00 	movq   $0x0,-0x30(%rbp)
  10899c:	00
  10899d:	48 8b 4d c8          	mov    -0x38(%rbp),%rcx
  1089a1:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  1089a5:	48 8b 89 68 03 00 00 	mov    0x368(%rcx),%rcx
  1089ac:	48 83 e9 01          	sub    $0x1,%rcx
  1089b0:	48 39 c8             	cmp    %rcx,%rax
  1089b3:	0f 83 2d 00 00 00    	jae    1089e6 <_ZN4acos3ipc7Channel4sendERKNS_3abi7MessageE+0x106>
  1089b9:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  1089bd:	48 8b 4d d0          	mov    -0x30(%rbp),%rcx
  1089c1:	48 8b 94 c8 30 03 00 	mov    0x330(%rax,%rcx,8),%rdx
  1089c8:	00
  1089c9:	48 8b 4d d0          	mov    -0x30(%rbp),%rcx
  1089cd:	48 89 94 c8 28 03 00 	mov    %rdx,0x328(%rax,%rcx,8)
  1089d4:	00
  1089d5:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  1089d9:	48 83 c0 01          	add    $0x1,%rax
  1089dd:	48 89 45 d0          	mov    %rax,-0x30(%rbp)
  1089e1:	e9 b7 ff ff ff       	jmp    10899d <_ZN4acos3ipc7Channel4sendERKNS_3abi7MessageE+0xbd>
  1089e6:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  1089ea:	48 8b 88 68 03 00 00 	mov    0x368(%rax),%rcx
  1089f1:	48 83 c1 ff          	add    $0xffffffffffffffff,%rcx
  1089f5:	48 89 88 68 03 00 00 	mov    %rcx,0x368(%rax)
  1089fc:	c6 45 ff 01          	movb   $0x1,-0x1(%rbp)
  108a00:	c7 45 dc 01 00 00 00 	movl   $0x1,-0x24(%rbp)
  108a07:	48 8d 7d e0          	lea    -0x20(%rbp),%rdi
  108a0b:	e8 b0 60 00 00       	call   10eac0 <_ZN4acos3hal10ScopedLockD2Ev>
  108a10:	8a 45 ff             	mov    -0x1(%rbp),%al
  108a13:	24 01                	and    $0x1,%al
  108a15:	0f b6 c0             	movzbl %al,%eax
  108a18:	48 83 c4 40          	add    $0x40,%rsp
  108a1c:	5d                   	pop    %rbp
  108a1d:	c3                   	ret
  108a1e:	66 90                	xchg   %ax,%ax

0000000000108a20 <_ZN4acos3ipc7Channel7receiveERNS_3abi7MessageEb>:
  108a20:	55                   	push   %rbp
  108a21:	48 89 e5             	mov    %rsp,%rbp
  108a24:	48 83 ec 30          	sub    $0x30,%rsp
  108a28:	88 d0                	mov    %dl,%al
  108a2a:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  108a2e:	48 89 75 e8          	mov    %rsi,-0x18(%rbp)
  108a32:	24 01                	and    $0x1,%al
  108a34:	88 45 e7             	mov    %al,-0x19(%rbp)
  108a37:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  108a3b:	48 89 45 d0          	mov    %rax,-0x30(%rbp)
  108a3f:	48 8b 7d d0          	mov    -0x30(%rbp),%rdi
  108a43:	48 83 c7 08          	add    $0x8,%rdi
  108a47:	e8 94 60 00 00       	call   10eae0 <_ZN4acos3hal8SpinLock4lockEv>
  108a4c:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  108a50:	48 83 b8 20 03 00 00 	cmpq   $0x0,0x320(%rax)
  108a57:	00
  108a58:	0f 86 62 00 00 00    	jbe    108ac0 <_ZN4acos3ipc7Channel7receiveERNS_3abi7MessageEb+0xa0>
  108a5e:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  108a62:	48 89 c6             	mov    %rax,%rsi
  108a65:	48 83 c6 10          	add    $0x10,%rsi
  108a69:	48 6b 80 10 03 00 00 	imul   $0x30,0x310(%rax),%rax
  108a70:	30
  108a71:	48 01 c6             	add    %rax,%rsi
  108a74:	48 8b 7d e8          	mov    -0x18(%rbp),%rdi
  108a78:	ba 30 00 00 00       	mov    $0x30,%edx
  108a7d:	e8 7e 75 ff ff       	call   100000 <memcpy>
  108a82:	48 8b 7d d0          	mov    -0x30(%rbp),%rdi
  108a86:	48 8b 87 10 03 00 00 	mov    0x310(%rdi),%rax
  108a8d:	48 83 c0 01          	add    $0x1,%rax
  108a91:	48 83 e0 0f          	and    $0xf,%rax
  108a95:	48 89 87 10 03 00 00 	mov    %rax,0x310(%rdi)
  108a9c:	48 8b 87 20 03 00 00 	mov    0x320(%rdi),%rax
  108aa3:	48 83 c0 ff          	add    $0xffffffffffffffff,%rax
  108aa7:	48 89 87 20 03 00 00 	mov    %rax,0x320(%rdi)
  108aae:	48 83 c7 08          	add    $0x8,%rdi
  108ab2:	e8 69 60 00 00       	call   10eb20 <_ZN4acos3hal8SpinLock6unlockEv>
  108ab7:	c6 45 ff 01          	movb   $0x1,-0x1(%rbp)
  108abb:	e9 95 00 00 00       	jmp    108b55 <_ZN4acos3ipc7Channel7receiveERNS_3abi7MessageEb+0x135>
  108ac0:	f6 45 e7 01          	testb  $0x1,-0x19(%rbp)
  108ac4:	0f 85 16 00 00 00    	jne    108ae0 <_ZN4acos3ipc7Channel7receiveERNS_3abi7MessageEb+0xc0>
  108aca:	48 8b 7d d0          	mov    -0x30(%rbp),%rdi
  108ace:	48 83 c7 08          	add    $0x8,%rdi
  108ad2:	e8 49 60 00 00       	call   10eb20 <_ZN4acos3hal8SpinLock6unlockEv>
  108ad7:	c6 45 ff 00          	movb   $0x0,-0x1(%rbp)
  108adb:	e9 75 00 00 00       	jmp    108b55 <_ZN4acos3ipc7Channel7receiveERNS_3abi7MessageEb+0x135>
  108ae0:	e8 1b de ff ff       	call   106900 <_ZN4acos9scheduler14current_threadEv>
  108ae5:	48 89 c1             	mov    %rax,%rcx
  108ae8:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  108aec:	48 89 4d d8          	mov    %rcx,-0x28(%rbp)
  108af0:	48 83 b8 68 03 00 00 	cmpq   $0x8,0x368(%rax)
  108af7:	08
  108af8:	0f 83 3c 00 00 00    	jae    108b3a <_ZN4acos3ipc7Channel7receiveERNS_3abi7MessageEb+0x11a>
  108afe:	48 8b 7d d0          	mov    -0x30(%rbp),%rdi
  108b02:	48 8b 4d d8          	mov    -0x28(%rbp),%rcx
  108b06:	48 8b 87 68 03 00 00 	mov    0x368(%rdi),%rax
  108b0d:	48 89 c2             	mov    %rax,%rdx
  108b10:	48 83 c2 01          	add    $0x1,%rdx
  108b14:	48 89 97 68 03 00 00 	mov    %rdx,0x368(%rdi)
  108b1b:	48 89 8c c7 28 03 00 	mov    %rcx,0x328(%rdi,%rax,8)
  108b22:	00
  108b23:	48 83 c7 08          	add    $0x8,%rdi
  108b27:	e8 f4 5f 00 00       	call   10eb20 <_ZN4acos3hal8SpinLock6unlockEv>
  108b2c:	48 8b 7d d8          	mov    -0x28(%rbp),%rdi
  108b30:	e8 1b de ff ff       	call   106950 <_ZN4acos9scheduler12block_threadEPNS0_6ThreadE>
  108b35:	e9 16 00 00 00       	jmp    108b50 <_ZN4acos3ipc7Channel7receiveERNS_3abi7MessageEb+0x130>
  108b3a:	48 8b 7d d0          	mov    -0x30(%rbp),%rdi
  108b3e:	48 83 c7 08          	add    $0x8,%rdi
  108b42:	e8 d9 5f 00 00       	call   10eb20 <_ZN4acos3hal8SpinLock6unlockEv>
  108b47:	c6 45 ff 00          	movb   $0x0,-0x1(%rbp)
  108b4b:	e9 05 00 00 00       	jmp    108b55 <_ZN4acos3ipc7Channel7receiveERNS_3abi7MessageEb+0x135>
  108b50:	e9 ea fe ff ff       	jmp    108a3f <_ZN4acos3ipc7Channel7receiveERNS_3abi7MessageEb+0x1f>
  108b55:	8a 45 ff             	mov    -0x1(%rbp),%al
  108b58:	24 01                	and    $0x1,%al
  108b5a:	0f b6 c0             	movzbl %al,%eax
  108b5d:	48 83 c4 30          	add    $0x30,%rsp
  108b61:	5d                   	pop    %rbp
  108b62:	c3                   	ret
  108b63:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
  108b6a:	00 00 00
  108b6d:	0f 1f 00             	nopl   (%rax)

0000000000108b70 <_ZN4acos3ipc12NotificationC1Ev>:
  108b70:	55                   	push   %rbp
  108b71:	48 89 e5             	mov    %rsp,%rbp
  108b74:	48 83 ec 20          	sub    $0x20,%rsp
  108b78:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  108b7c:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  108b80:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
  108b84:	48 83 c7 08          	add    $0x8,%rdi
  108b88:	e8 63 60 00 00       	call   10ebf0 <_ZN4acos3hal8SpinLockC2Ev>
  108b8d:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  108b91:	c6 40 09 00          	movb   $0x0,0x9(%rax)
  108b95:	48 c7 80 90 00 00 00 	movq   $0x0,0x90(%rax)
  108b9c:	00 00 00 00
  108ba0:	48 8b 0c 25 90 fc 10 	mov    0x10fc90,%rcx
  108ba7:	00
  108ba8:	48 89 ca             	mov    %rcx,%rdx
  108bab:	48 83 c2 01          	add    $0x1,%rdx
  108baf:	48 89 14 25 90 fc 10 	mov    %rdx,0x10fc90
  108bb6:	00
  108bb7:	48 89 08             	mov    %rcx,(%rax)
  108bba:	48 c7 45 f0 00 00 00 	movq   $0x0,-0x10(%rbp)
  108bc1:	00
  108bc2:	48 83 7d f0 10       	cmpq   $0x10,-0x10(%rbp)
  108bc7:	0f 83 22 00 00 00    	jae    108bef <_ZN4acos3ipc12NotificationC1Ev+0x7f>
  108bcd:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  108bd1:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
  108bd5:	48 c7 44 c8 10 00 00 	movq   $0x0,0x10(%rax,%rcx,8)
  108bdc:	00 00
  108bde:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  108be2:	48 83 c0 01          	add    $0x1,%rax
  108be6:	48 89 45 f0          	mov    %rax,-0x10(%rbp)
  108bea:	e9 d3 ff ff ff       	jmp    108bc2 <_ZN4acos3ipc12NotificationC1Ev+0x52>
  108bef:	48 83 c4 20          	add    $0x20,%rsp
  108bf3:	5d                   	pop    %rbp
  108bf4:	c3                   	ret
  108bf5:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  108bfc:	00 00 00 00

0000000000108c00 <_ZN4acos3ipc12Notification6signalEv>:
  108c00:	55                   	push   %rbp
  108c01:	48 89 e5             	mov    %rsp,%rbp
  108c04:	48 83 ec 20          	sub    $0x20,%rsp
  108c08:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  108c0c:	48 8b 75 f8          	mov    -0x8(%rbp),%rsi
  108c10:	48 89 75 e0          	mov    %rsi,-0x20(%rbp)
  108c14:	48 83 c6 08          	add    $0x8,%rsi
  108c18:	48 8d 7d f0          	lea    -0x10(%rbp),%rdi
  108c1c:	e8 6f 5e 00 00       	call   10ea90 <_ZN4acos3hal10ScopedLockC2ERNS0_8SpinLockE>
  108c21:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  108c25:	c6 40 09 01          	movb   $0x1,0x9(%rax)
  108c29:	48 c7 45 e8 00 00 00 	movq   $0x0,-0x18(%rbp)
  108c30:	00
  108c31:	48 8b 4d e0          	mov    -0x20(%rbp),%rcx
  108c35:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  108c39:	48 3b 81 90 00 00 00 	cmp    0x90(%rcx),%rax
  108c40:	0f 83 34 00 00 00    	jae    108c7a <_ZN4acos3ipc12Notification6signalEv+0x7a>
  108c46:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  108c4a:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  108c4e:	48 8b 7c c8 10       	mov    0x10(%rax,%rcx,8),%rdi
  108c53:	e8 b8 dc ff ff       	call   106910 <_ZN4acos9scheduler11wake_threadEPNS0_6ThreadE>
  108c58:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  108c5c:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  108c60:	48 c7 44 c8 10 00 00 	movq   $0x0,0x10(%rax,%rcx,8)
  108c67:	00 00
  108c69:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  108c6d:	48 83 c0 01          	add    $0x1,%rax
  108c71:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
  108c75:	e9 b7 ff ff ff       	jmp    108c31 <_ZN4acos3ipc12Notification6signalEv+0x31>
  108c7a:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  108c7e:	48 c7 80 90 00 00 00 	movq   $0x0,0x90(%rax)
  108c85:	00 00 00 00
  108c89:	48 8d 7d f0          	lea    -0x10(%rbp),%rdi
  108c8d:	e8 2e 5e 00 00       	call   10eac0 <_ZN4acos3hal10ScopedLockD2Ev>
  108c92:	48 83 c4 20          	add    $0x20,%rsp
  108c96:	5d                   	pop    %rbp
  108c97:	c3                   	ret
  108c98:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  108c9f:	00

0000000000108ca0 <_ZN4acos3ipc12Notification4waitEv>:
  108ca0:	55                   	push   %rbp
  108ca1:	48 89 e5             	mov    %rsp,%rbp
  108ca4:	48 83 ec 20          	sub    $0x20,%rsp
  108ca8:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  108cac:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  108cb0:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
  108cb4:	48 83 c7 08          	add    $0x8,%rdi
  108cb8:	e8 23 5e 00 00       	call   10eae0 <_ZN4acos3hal8SpinLock4lockEv>
  108cbd:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  108cc1:	f6 40 09 01          	testb  $0x1,0x9(%rax)
  108cc5:	0f 84 12 00 00 00    	je     108cdd <_ZN4acos3ipc12Notification4waitEv+0x3d>
  108ccb:	48 8b 7d e8          	mov    -0x18(%rbp),%rdi
  108ccf:	48 83 c7 08          	add    $0x8,%rdi
  108cd3:	e8 48 5e 00 00       	call   10eb20 <_ZN4acos3hal8SpinLock6unlockEv>
  108cd8:	e9 64 00 00 00       	jmp    108d41 <_ZN4acos3ipc12Notification4waitEv+0xa1>
  108cdd:	e8 1e dc ff ff       	call   106900 <_ZN4acos9scheduler14current_threadEv>
  108ce2:	48 89 c1             	mov    %rax,%rcx
  108ce5:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  108ce9:	48 89 4d f0          	mov    %rcx,-0x10(%rbp)
  108ced:	48 83 b8 90 00 00 00 	cmpq   $0x10,0x90(%rax)
  108cf4:	10
  108cf5:	0f 83 39 00 00 00    	jae    108d34 <_ZN4acos3ipc12Notification4waitEv+0x94>
  108cfb:	48 8b 7d e8          	mov    -0x18(%rbp),%rdi
  108cff:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
  108d03:	48 8b 87 90 00 00 00 	mov    0x90(%rdi),%rax
  108d0a:	48 89 c2             	mov    %rax,%rdx
  108d0d:	48 83 c2 01          	add    $0x1,%rdx
  108d11:	48 89 97 90 00 00 00 	mov    %rdx,0x90(%rdi)
  108d18:	48 89 4c c7 10       	mov    %rcx,0x10(%rdi,%rax,8)
  108d1d:	48 83 c7 08          	add    $0x8,%rdi
  108d21:	e8 fa 5d 00 00       	call   10eb20 <_ZN4acos3hal8SpinLock6unlockEv>
  108d26:	48 8b 7d f0          	mov    -0x10(%rbp),%rdi
  108d2a:	e8 21 dc ff ff       	call   106950 <_ZN4acos9scheduler12block_threadEPNS0_6ThreadE>
  108d2f:	e9 0d 00 00 00       	jmp    108d41 <_ZN4acos3ipc12Notification4waitEv+0xa1>
  108d34:	48 8b 7d e8          	mov    -0x18(%rbp),%rdi
  108d38:	48 83 c7 08          	add    $0x8,%rdi
  108d3c:	e8 df 5d 00 00       	call   10eb20 <_ZN4acos3hal8SpinLock6unlockEv>
  108d41:	48 83 c4 20          	add    $0x20,%rsp
  108d45:	5d                   	pop    %rbp
  108d46:	c3                   	ret
  108d47:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
  108d4e:	00 00

0000000000108d50 <_ZN4acos3ipc12Notification5resetEv>:
  108d50:	55                   	push   %rbp
  108d51:	48 89 e5             	mov    %rsp,%rbp
  108d54:	48 83 ec 20          	sub    $0x20,%rsp
  108d58:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  108d5c:	48 8b 75 f8          	mov    -0x8(%rbp),%rsi
  108d60:	48 89 75 e8          	mov    %rsi,-0x18(%rbp)
  108d64:	48 83 c6 08          	add    $0x8,%rsi
  108d68:	48 8d 7d f0          	lea    -0x10(%rbp),%rdi
  108d6c:	e8 1f 5d 00 00       	call   10ea90 <_ZN4acos3hal10ScopedLockC2ERNS0_8SpinLockE>
  108d71:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  108d75:	c6 40 09 00          	movb   $0x0,0x9(%rax)
  108d79:	48 8d 7d f0          	lea    -0x10(%rbp),%rdi
  108d7d:	e8 3e 5d 00 00       	call   10eac0 <_ZN4acos3hal10ScopedLockD2Ev>
  108d82:	48 83 c4 20          	add    $0x20,%rsp
  108d86:	5d                   	pop    %rbp
  108d87:	c3                   	ret
  108d88:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  108d8f:	00

0000000000108d90 <_ZN4acos3ipc12SharedRegionC1Emm>:
  108d90:	55                   	push   %rbp
  108d91:	48 89 e5             	mov    %rsp,%rbp
  108d94:	48 83 ec 18          	sub    $0x18,%rsp
  108d98:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  108d9c:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  108da0:	48 89 55 e8          	mov    %rdx,-0x18(%rbp)
  108da4:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  108da8:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
  108dac:	48 89 48 08          	mov    %rcx,0x8(%rax)
  108db0:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  108db4:	48 89 48 10          	mov    %rcx,0x10(%rax)
  108db8:	48 8b 0c 25 98 fc 10 	mov    0x10fc98,%rcx
  108dbf:	00
  108dc0:	48 89 ca             	mov    %rcx,%rdx
  108dc3:	48 83 c2 01          	add    $0x1,%rdx
  108dc7:	48 89 14 25 98 fc 10 	mov    %rdx,0x10fc98
  108dce:	00
  108dcf:	48 89 08             	mov    %rcx,(%rax)
  108dd2:	48 83 c4 18          	add    $0x18,%rsp
  108dd6:	5d                   	pop    %rbp
  108dd7:	c3                   	ret
  108dd8:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  108ddf:	00

0000000000108de0 <_ZN4acos3vfs3VFS4openEPKcm>:
  108de0:	55                   	push   %rbp
  108de1:	48 89 e5             	mov    %rsp,%rbp
  108de4:	48 83 ec 50          	sub    $0x50,%rsp
  108de8:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  108dec:	48 89 75 e8          	mov    %rsi,-0x18(%rbp)
  108df0:	48 83 7d f0 00       	cmpq   $0x0,-0x10(%rbp)
  108df5:	0f 84 10 00 00 00    	je     108e0b <_ZN4acos3vfs3VFS4openEPKcm+0x2b>
  108dfb:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  108dff:	0f be 00             	movsbl (%rax),%eax
  108e02:	83 f8 00             	cmp    $0x0,%eax
  108e05:	0f 85 0c 00 00 00    	jne    108e17 <_ZN4acos3vfs3VFS4openEPKcm+0x37>
  108e0b:	c7 45 fc ff ff ff ff 	movl   $0xffffffff,-0x4(%rbp)
  108e12:	e9 22 01 00 00       	jmp    108f39 <_ZN4acos3vfs3VFS4openEPKcm+0x159>
  108e17:	48 8b 7d f0          	mov    -0x10(%rbp),%rdi
  108e1b:	e8 60 08 00 00       	call   109680 <_ZN4acos3vfs13MountRegistry10find_mountEPKc>
  108e20:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  108e24:	48 83 7d e0 00       	cmpq   $0x0,-0x20(%rbp)
  108e29:	0f 84 12 00 00 00    	je     108e41 <_ZN4acos3vfs3VFS4openEPKcm+0x61>
  108e2f:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  108e33:	48 83 b8 00 01 00 00 	cmpq   $0x0,0x100(%rax)
  108e3a:	00
  108e3b:	0f 85 0c 00 00 00    	jne    108e4d <_ZN4acos3vfs3VFS4openEPKcm+0x6d>
  108e41:	c7 45 fc ff ff ff ff 	movl   $0xffffffff,-0x4(%rbp)
  108e48:	e9 ec 00 00 00       	jmp    108f39 <_ZN4acos3vfs3VFS4openEPKcm+0x159>
  108e4d:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  108e51:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
  108e55:	48 8b 7d e0          	mov    -0x20(%rbp),%rdi
  108e59:	e8 32 75 ff ff       	call   100390 <strlen>
  108e5e:	48 89 45 d0          	mov    %rax,-0x30(%rbp)
  108e62:	48 83 7d d0 01       	cmpq   $0x1,-0x30(%rbp)
  108e67:	0f 86 2d 00 00 00    	jbe    108e9a <_ZN4acos3vfs3VFS4openEPKcm+0xba>
  108e6d:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  108e71:	48 03 45 d8          	add    -0x28(%rbp),%rax
  108e75:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
  108e79:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  108e7d:	0f be 00             	movsbl (%rax),%eax
  108e80:	83 f8 2f             	cmp    $0x2f,%eax
  108e83:	0f 85 0c 00 00 00    	jne    108e95 <_ZN4acos3vfs3VFS4openEPKcm+0xb5>
  108e89:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  108e8d:	48 83 c0 01          	add    $0x1,%rax
  108e91:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
  108e95:	e9 00 00 00 00       	jmp    108e9a <_ZN4acos3vfs3VFS4openEPKcm+0xba>
  108e9a:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  108e9e:	48 8b b8 00 01 00 00 	mov    0x100(%rax),%rdi
  108ea5:	48 8b 75 d8          	mov    -0x28(%rbp),%rsi
  108ea9:	48 8b 07             	mov    (%rdi),%rax
  108eac:	ff 50 10             	call   *0x10(%rax)
  108eaf:	48 89 45 c8          	mov    %rax,-0x38(%rbp)
  108eb3:	48 83 7d c8 00       	cmpq   $0x0,-0x38(%rbp)
  108eb8:	0f 85 0c 00 00 00    	jne    108eca <_ZN4acos3vfs3VFS4openEPKcm+0xea>
  108ebe:	c7 45 fc ff ff ff ff 	movl   $0xffffffff,-0x4(%rbp)
  108ec5:	e9 6f 00 00 00       	jmp    108f39 <_ZN4acos3vfs3VFS4openEPKcm+0x159>
  108eca:	bf 10 00 00 00       	mov    $0x10,%edi
  108ecf:	e8 7c f8 ff ff       	call   108750 <_ZN4acos6memory7kmallocEm>
  108ed4:	48 89 45 c0          	mov    %rax,-0x40(%rbp)
  108ed8:	48 83 7d c0 00       	cmpq   $0x0,-0x40(%rbp)
  108edd:	0f 85 0c 00 00 00    	jne    108eef <_ZN4acos3vfs3VFS4openEPKcm+0x10f>
  108ee3:	c7 45 fc ff ff ff ff 	movl   $0xffffffff,-0x4(%rbp)
  108eea:	e9 4a 00 00 00       	jmp    108f39 <_ZN4acos3vfs3VFS4openEPKcm+0x159>
  108eef:	48 8b 7d c0          	mov    -0x40(%rbp),%rdi
  108ef3:	48 8b 75 c8          	mov    -0x38(%rbp),%rsi
  108ef7:	e8 84 04 00 00       	call   109380 <_ZN4acos3vfs4FileC1EPNS0_4NodeE>
  108efc:	e8 ff d9 ff ff       	call   106900 <_ZN4acos9scheduler14current_threadEv>
  108f01:	48 8b 40 20          	mov    0x20(%rax),%rax
  108f05:	48 89 45 b8          	mov    %rax,-0x48(%rbp)
  108f09:	48 83 7d b8 00       	cmpq   $0x0,-0x48(%rbp)
  108f0e:	0f 85 15 00 00 00    	jne    108f29 <_ZN4acos3vfs3VFS4openEPKcm+0x149>
  108f14:	48 8b 7d c0          	mov    -0x40(%rbp),%rdi
  108f18:	e8 03 f9 ff ff       	call   108820 <_ZN4acos6memory5kfreeEPv>
  108f1d:	c7 45 fc ff ff ff ff 	movl   $0xffffffff,-0x4(%rbp)
  108f24:	e9 10 00 00 00       	jmp    108f39 <_ZN4acos3vfs3VFS4openEPKcm+0x159>
  108f29:	48 8b 7d b8          	mov    -0x48(%rbp),%rdi
  108f2d:	48 8b 75 c0          	mov    -0x40(%rbp),%rsi
  108f31:	e8 1a d0 ff ff       	call   105f50 <_ZN4acos9scheduler7Process13register_fileEPNS_3vfs4FileE>
  108f36:	89 45 fc             	mov    %eax,-0x4(%rbp)
  108f39:	8b 45 fc             	mov    -0x4(%rbp),%eax
  108f3c:	48 83 c4 50          	add    $0x50,%rsp
  108f40:	5d                   	pop    %rbp
  108f41:	c3                   	ret
  108f42:	66 66 66 66 66 2e 0f 	data16 data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
  108f49:	1f 84 00 00 00 00 00

0000000000108f50 <_ZN4acos3vfs3VFS5closeEm>:
  108f50:	55                   	push   %rbp
  108f51:	48 89 e5             	mov    %rsp,%rbp
  108f54:	48 83 ec 20          	sub    $0x20,%rsp
  108f58:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  108f5c:	e8 9f d9 ff ff       	call   106900 <_ZN4acos9scheduler14current_threadEv>
  108f61:	48 8b 40 20          	mov    0x20(%rax),%rax
  108f65:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
  108f69:	48 83 7d e8 00       	cmpq   $0x0,-0x18(%rbp)
  108f6e:	0f 85 0c 00 00 00    	jne    108f80 <_ZN4acos3vfs3VFS5closeEm+0x30>
  108f74:	c7 45 fc ff ff ff ff 	movl   $0xffffffff,-0x4(%rbp)
  108f7b:	e9 45 00 00 00       	jmp    108fc5 <_ZN4acos3vfs3VFS5closeEm+0x75>
  108f80:	48 8b 7d e8          	mov    -0x18(%rbp),%rdi
  108f84:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  108f88:	89 c6                	mov    %eax,%esi
  108f8a:	e8 51 d0 ff ff       	call   105fe0 <_ZN4acos9scheduler7Process8get_fileEi>
  108f8f:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  108f93:	48 83 7d e0 00       	cmpq   $0x0,-0x20(%rbp)
  108f98:	0f 85 0c 00 00 00    	jne    108faa <_ZN4acos3vfs3VFS5closeEm+0x5a>
  108f9e:	c7 45 fc ff ff ff ff 	movl   $0xffffffff,-0x4(%rbp)
  108fa5:	e9 1b 00 00 00       	jmp    108fc5 <_ZN4acos3vfs3VFS5closeEm+0x75>
  108faa:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  108fae:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
  108fb2:	48 c7 84 c8 10 38 00 	movq   $0x0,0x3810(%rax,%rcx,8)
  108fb9:	00 00 00 00 00
  108fbe:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%rbp)
  108fc5:	8b 45 fc             	mov    -0x4(%rbp),%eax
  108fc8:	48 83 c4 20          	add    $0x20,%rsp
  108fcc:	5d                   	pop    %rbp
  108fcd:	c3                   	ret
  108fce:	66 90                	xchg   %ax,%ax

0000000000108fd0 <_ZN4acos3vfs3VFS4readEmPvm>:
  108fd0:	55                   	push   %rbp
  108fd1:	48 89 e5             	mov    %rsp,%rbp
  108fd4:	48 83 ec 30          	sub    $0x30,%rsp
  108fd8:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  108fdc:	48 89 75 e8          	mov    %rsi,-0x18(%rbp)
  108fe0:	48 89 55 e0          	mov    %rdx,-0x20(%rbp)
  108fe4:	e8 17 d9 ff ff       	call   106900 <_ZN4acos9scheduler14current_threadEv>
  108fe9:	48 8b 40 20          	mov    0x20(%rax),%rax
  108fed:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
  108ff1:	48 83 7d d8 00       	cmpq   $0x0,-0x28(%rbp)
  108ff6:	0f 85 0c 00 00 00    	jne    109008 <_ZN4acos3vfs3VFS4readEmPvm+0x38>
  108ffc:	c7 45 fc ff ff ff ff 	movl   $0xffffffff,-0x4(%rbp)
  109003:	e9 3e 00 00 00       	jmp    109046 <_ZN4acos3vfs3VFS4readEmPvm+0x76>
  109008:	48 8b 7d d8          	mov    -0x28(%rbp),%rdi
  10900c:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  109010:	89 c6                	mov    %eax,%esi
  109012:	e8 c9 cf ff ff       	call   105fe0 <_ZN4acos9scheduler7Process8get_fileEi>
  109017:	48 89 45 d0          	mov    %rax,-0x30(%rbp)
  10901b:	48 83 7d d0 00       	cmpq   $0x0,-0x30(%rbp)
  109020:	0f 85 0c 00 00 00    	jne    109032 <_ZN4acos3vfs3VFS4readEmPvm+0x62>
  109026:	c7 45 fc ff ff ff ff 	movl   $0xffffffff,-0x4(%rbp)
  10902d:	e9 14 00 00 00       	jmp    109046 <_ZN4acos3vfs3VFS4readEmPvm+0x76>
  109032:	48 8b 7d d0          	mov    -0x30(%rbp),%rdi
  109036:	48 8b 75 e8          	mov    -0x18(%rbp),%rsi
  10903a:	48 8b 55 e0          	mov    -0x20(%rbp),%rdx
  10903e:	e8 6d 03 00 00       	call   1093b0 <_ZN4acos3vfs4File4readEPvm>
  109043:	89 45 fc             	mov    %eax,-0x4(%rbp)
  109046:	8b 45 fc             	mov    -0x4(%rbp),%eax
  109049:	48 83 c4 30          	add    $0x30,%rsp
  10904d:	5d                   	pop    %rbp
  10904e:	c3                   	ret
  10904f:	90                   	nop

0000000000109050 <_ZN4acos3vfs3VFS5writeEmPKvm>:
  109050:	55                   	push   %rbp
  109051:	48 89 e5             	mov    %rsp,%rbp
  109054:	48 83 ec 30          	sub    $0x30,%rsp
  109058:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  10905c:	48 89 75 e8          	mov    %rsi,-0x18(%rbp)
  109060:	48 89 55 e0          	mov    %rdx,-0x20(%rbp)
  109064:	e8 97 d8 ff ff       	call   106900 <_ZN4acos9scheduler14current_threadEv>
  109069:	48 8b 40 20          	mov    0x20(%rax),%rax
  10906d:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
  109071:	48 83 7d d8 00       	cmpq   $0x0,-0x28(%rbp)
  109076:	0f 85 0c 00 00 00    	jne    109088 <_ZN4acos3vfs3VFS5writeEmPKvm+0x38>
  10907c:	c7 45 fc ff ff ff ff 	movl   $0xffffffff,-0x4(%rbp)
  109083:	e9 3e 00 00 00       	jmp    1090c6 <_ZN4acos3vfs3VFS5writeEmPKvm+0x76>
  109088:	48 8b 7d d8          	mov    -0x28(%rbp),%rdi
  10908c:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  109090:	89 c6                	mov    %eax,%esi
  109092:	e8 49 cf ff ff       	call   105fe0 <_ZN4acos9scheduler7Process8get_fileEi>
  109097:	48 89 45 d0          	mov    %rax,-0x30(%rbp)
  10909b:	48 83 7d d0 00       	cmpq   $0x0,-0x30(%rbp)
  1090a0:	0f 85 0c 00 00 00    	jne    1090b2 <_ZN4acos3vfs3VFS5writeEmPKvm+0x62>
  1090a6:	c7 45 fc ff ff ff ff 	movl   $0xffffffff,-0x4(%rbp)
  1090ad:	e9 14 00 00 00       	jmp    1090c6 <_ZN4acos3vfs3VFS5writeEmPKvm+0x76>
  1090b2:	48 8b 7d d0          	mov    -0x30(%rbp),%rdi
  1090b6:	48 8b 75 e8          	mov    -0x18(%rbp),%rsi
  1090ba:	48 8b 55 e0          	mov    -0x20(%rbp),%rdx
  1090be:	e8 6d 03 00 00       	call   109430 <_ZN4acos3vfs4File5writeEPKvm>
  1090c3:	89 45 fc             	mov    %eax,-0x4(%rbp)
  1090c6:	8b 45 fc             	mov    -0x4(%rbp),%eax
  1090c9:	48 83 c4 30          	add    $0x30,%rsp
  1090cd:	5d                   	pop    %rbp
  1090ce:	c3                   	ret
  1090cf:	90                   	nop

00000000001090d0 <_ZN4acos3vfs3VFS5mountEPKcPNS0_10FileSystemE>:
  1090d0:	55                   	push   %rbp
  1090d1:	48 89 e5             	mov    %rsp,%rbp
  1090d4:	48 83 ec 10          	sub    $0x10,%rsp
  1090d8:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  1090dc:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  1090e0:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  1090e4:	48 8b 75 f0          	mov    -0x10(%rbp),%rsi
  1090e8:	e8 43 04 00 00       	call   109530 <_ZN4acos3vfs13MountRegistry5mountEPKcPNS0_10FileSystemE>
  1090ed:	24 01                	and    $0x1,%al
  1090ef:	0f b6 c0             	movzbl %al,%eax
  1090f2:	48 83 c4 10          	add    $0x10,%rsp
  1090f6:	5d                   	pop    %rbp
  1090f7:	c3                   	ret
  1090f8:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  1090ff:	00

0000000000109100 <_ZN4acos3vfs3VFS8read_dirEPKcPNS0_14DirectoryEntryEm>:
  109100:	55                   	push   %rbp
  109101:	48 89 e5             	mov    %rsp,%rbp
  109104:	48 83 ec 40          	sub    $0x40,%rsp
  109108:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  10910c:	48 89 75 e8          	mov    %rsi,-0x18(%rbp)
  109110:	48 89 55 e0          	mov    %rdx,-0x20(%rbp)
  109114:	48 8b 7d f0          	mov    -0x10(%rbp),%rdi
  109118:	e8 63 05 00 00       	call   109680 <_ZN4acos3vfs13MountRegistry10find_mountEPKc>
  10911d:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
  109121:	48 83 7d d8 00       	cmpq   $0x0,-0x28(%rbp)
  109126:	0f 84 12 00 00 00    	je     10913e <_ZN4acos3vfs3VFS8read_dirEPKcPNS0_14DirectoryEntryEm+0x3e>
  10912c:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  109130:	48 83 b8 00 01 00 00 	cmpq   $0x0,0x100(%rax)
  109137:	00
  109138:	0f 85 0c 00 00 00    	jne    10914a <_ZN4acos3vfs3VFS8read_dirEPKcPNS0_14DirectoryEntryEm+0x4a>
  10913e:	c7 45 fc ff ff ff ff 	movl   $0xffffffff,-0x4(%rbp)
  109145:	e9 94 00 00 00       	jmp    1091de <_ZN4acos3vfs3VFS8read_dirEPKcPNS0_14DirectoryEntryEm+0xde>
  10914a:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10914e:	48 89 45 d0          	mov    %rax,-0x30(%rbp)
  109152:	48 8b 7d d8          	mov    -0x28(%rbp),%rdi
  109156:	e8 35 72 ff ff       	call   100390 <strlen>
  10915b:	48 89 45 c8          	mov    %rax,-0x38(%rbp)
  10915f:	48 83 7d c8 01       	cmpq   $0x1,-0x38(%rbp)
  109164:	0f 86 2d 00 00 00    	jbe    109197 <_ZN4acos3vfs3VFS8read_dirEPKcPNS0_14DirectoryEntryEm+0x97>
  10916a:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  10916e:	48 03 45 d0          	add    -0x30(%rbp),%rax
  109172:	48 89 45 d0          	mov    %rax,-0x30(%rbp)
  109176:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  10917a:	0f be 00             	movsbl (%rax),%eax
  10917d:	83 f8 2f             	cmp    $0x2f,%eax
  109180:	0f 85 0c 00 00 00    	jne    109192 <_ZN4acos3vfs3VFS8read_dirEPKcPNS0_14DirectoryEntryEm+0x92>
  109186:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  10918a:	48 83 c0 01          	add    $0x1,%rax
  10918e:	48 89 45 d0          	mov    %rax,-0x30(%rbp)
  109192:	e9 00 00 00 00       	jmp    109197 <_ZN4acos3vfs3VFS8read_dirEPKcPNS0_14DirectoryEntryEm+0x97>
  109197:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  10919b:	48 8b b8 00 01 00 00 	mov    0x100(%rax),%rdi
  1091a2:	48 8b 75 d0          	mov    -0x30(%rbp),%rsi
  1091a6:	48 8b 07             	mov    (%rdi),%rax
  1091a9:	ff 50 10             	call   *0x10(%rax)
  1091ac:	48 89 45 c0          	mov    %rax,-0x40(%rbp)
  1091b0:	48 83 7d c0 00       	cmpq   $0x0,-0x40(%rbp)
  1091b5:	0f 85 0c 00 00 00    	jne    1091c7 <_ZN4acos3vfs3VFS8read_dirEPKcPNS0_14DirectoryEntryEm+0xc7>
  1091bb:	c7 45 fc ff ff ff ff 	movl   $0xffffffff,-0x4(%rbp)
  1091c2:	e9 17 00 00 00       	jmp    1091de <_ZN4acos3vfs3VFS8read_dirEPKcPNS0_14DirectoryEntryEm+0xde>
  1091c7:	48 8b 7d c0          	mov    -0x40(%rbp),%rdi
  1091cb:	48 8b 55 e8          	mov    -0x18(%rbp),%rdx
  1091cf:	48 8b 4d e0          	mov    -0x20(%rbp),%rcx
  1091d3:	48 8b 07             	mov    (%rdi),%rax
  1091d6:	31 f6                	xor    %esi,%esi
  1091d8:	ff 50 30             	call   *0x30(%rax)
  1091db:	89 45 fc             	mov    %eax,-0x4(%rbp)
  1091de:	8b 45 fc             	mov    -0x4(%rbp),%eax
  1091e1:	48 83 c4 40          	add    $0x40,%rsp
  1091e5:	5d                   	pop    %rbp
  1091e6:	c3                   	ret
  1091e7:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
  1091ee:	00 00

00000000001091f0 <_ZN4acos3vfs3VFS13get_node_typeEPKc>:
  1091f0:	55                   	push   %rbp
  1091f1:	48 89 e5             	mov    %rsp,%rbp
  1091f4:	48 83 ec 30          	sub    $0x30,%rsp
  1091f8:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  1091fc:	48 8b 7d f0          	mov    -0x10(%rbp),%rdi
  109200:	e8 7b 04 00 00       	call   109680 <_ZN4acos3vfs13MountRegistry10find_mountEPKc>
  109205:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
  109209:	48 83 7d e8 00       	cmpq   $0x0,-0x18(%rbp)
  10920e:	0f 84 12 00 00 00    	je     109226 <_ZN4acos3vfs3VFS13get_node_typeEPKc+0x36>
  109214:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  109218:	48 83 b8 00 01 00 00 	cmpq   $0x0,0x100(%rax)
  10921f:	00
  109220:	0f 85 0c 00 00 00    	jne    109232 <_ZN4acos3vfs3VFS13get_node_typeEPKc+0x42>
  109226:	c7 45 fc 01 00 00 00 	movl   $0x1,-0x4(%rbp)
  10922d:	e9 8a 00 00 00       	jmp    1092bc <_ZN4acos3vfs3VFS13get_node_typeEPKc+0xcc>
  109232:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  109236:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  10923a:	48 8b 7d e8          	mov    -0x18(%rbp),%rdi
  10923e:	e8 4d 71 ff ff       	call   100390 <strlen>
  109243:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
  109247:	48 83 7d d8 01       	cmpq   $0x1,-0x28(%rbp)
  10924c:	0f 86 2d 00 00 00    	jbe    10927f <_ZN4acos3vfs3VFS13get_node_typeEPKc+0x8f>
  109252:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  109256:	48 03 45 e0          	add    -0x20(%rbp),%rax
  10925a:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  10925e:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  109262:	0f be 00             	movsbl (%rax),%eax
  109265:	83 f8 2f             	cmp    $0x2f,%eax
  109268:	0f 85 0c 00 00 00    	jne    10927a <_ZN4acos3vfs3VFS13get_node_typeEPKc+0x8a>
  10926e:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  109272:	48 83 c0 01          	add    $0x1,%rax
  109276:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  10927a:	e9 00 00 00 00       	jmp    10927f <_ZN4acos3vfs3VFS13get_node_typeEPKc+0x8f>
  10927f:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  109283:	48 8b b8 00 01 00 00 	mov    0x100(%rax),%rdi
  10928a:	48 8b 75 e0          	mov    -0x20(%rbp),%rsi
  10928e:	48 8b 07             	mov    (%rdi),%rax
  109291:	ff 50 10             	call   *0x10(%rax)
  109294:	48 89 45 d0          	mov    %rax,-0x30(%rbp)
  109298:	48 83 7d d0 00       	cmpq   $0x0,-0x30(%rbp)
  10929d:	0f 85 0c 00 00 00    	jne    1092af <_ZN4acos3vfs3VFS13get_node_typeEPKc+0xbf>
  1092a3:	c7 45 fc 01 00 00 00 	movl   $0x1,-0x4(%rbp)
  1092aa:	e9 0d 00 00 00       	jmp    1092bc <_ZN4acos3vfs3VFS13get_node_typeEPKc+0xcc>
  1092af:	48 8b 7d d0          	mov    -0x30(%rbp),%rdi
  1092b3:	48 8b 07             	mov    (%rdi),%rax
  1092b6:	ff 50 28             	call   *0x28(%rax)
  1092b9:	89 45 fc             	mov    %eax,-0x4(%rbp)
  1092bc:	8b 45 fc             	mov    -0x4(%rbp),%eax
  1092bf:	48 83 c4 30          	add    $0x30,%rsp
  1092c3:	5d                   	pop    %rbp
  1092c4:	c3                   	ret
  1092c5:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
  1092cc:	00 00 00
  1092cf:	90                   	nop

00000000001092d0 <_ZN4acos3vfs6DentryC1EPKcPNS0_5InodeEPS1_>:
  1092d0:	55                   	push   %rbp
  1092d1:	48 89 e5             	mov    %rsp,%rbp
  1092d4:	48 83 ec 38          	sub    $0x38,%rsp
  1092d8:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  1092dc:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  1092e0:	48 89 55 e8          	mov    %rdx,-0x18(%rbp)
  1092e4:	48 89 4d e0          	mov    %rcx,-0x20(%rbp)
  1092e8:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  1092ec:	48 89 45 d0          	mov    %rax,-0x30(%rbp)
  1092f0:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  1092f4:	48 89 88 00 01 00 00 	mov    %rcx,0x100(%rax)
  1092fb:	48 8b 4d e0          	mov    -0x20(%rbp),%rcx
  1092ff:	48 89 88 08 01 00 00 	mov    %rcx,0x108(%rax)
  109306:	48 c7 45 d8 00 00 00 	movq   $0x0,-0x28(%rbp)
  10930d:	00
  10930e:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
  109312:	48 8b 55 d8          	mov    -0x28(%rbp),%rdx
  109316:	31 c0                	xor    %eax,%eax
  109318:	80 3c 11 00          	cmpb   $0x0,(%rcx,%rdx,1)
  10931c:	88 45 cf             	mov    %al,-0x31(%rbp)
  10931f:	0f 84 0e 00 00 00    	je     109333 <_ZN4acos3vfs6DentryC1EPKcPNS0_5InodeEPS1_+0x63>
  109325:	48 81 7d d8 ff 00 00 	cmpq   $0xff,-0x28(%rbp)
  10932c:	00
  10932d:	0f 92 c0             	setb   %al
  109330:	88 45 cf             	mov    %al,-0x31(%rbp)
  109333:	8a 45 cf             	mov    -0x31(%rbp),%al
  109336:	a8 01                	test   $0x1,%al
  109338:	0f 85 05 00 00 00    	jne    109343 <_ZN4acos3vfs6DentryC1EPKcPNS0_5InodeEPS1_+0x73>
  10933e:	e9 27 00 00 00       	jmp    10936a <_ZN4acos3vfs6DentryC1EPKcPNS0_5InodeEPS1_+0x9a>
  109343:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  109347:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
  10934b:	48 8b 55 d8          	mov    -0x28(%rbp),%rdx
  10934f:	8a 14 11             	mov    (%rcx,%rdx,1),%dl
  109352:	48 8b 4d d8          	mov    -0x28(%rbp),%rcx
  109356:	88 14 08             	mov    %dl,(%rax,%rcx,1)
  109359:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  10935d:	48 83 c0 01          	add    $0x1,%rax
  109361:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
  109365:	e9 a4 ff ff ff       	jmp    10930e <_ZN4acos3vfs6DentryC1EPKcPNS0_5InodeEPS1_+0x3e>
  10936a:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  10936e:	48 8b 4d d8          	mov    -0x28(%rbp),%rcx
  109372:	c6 04 08 00          	movb   $0x0,(%rax,%rcx,1)
  109376:	48 83 c4 38          	add    $0x38,%rsp
  10937a:	5d                   	pop    %rbp
  10937b:	c3                   	ret
  10937c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000109380 <_ZN4acos3vfs4FileC1EPNS0_4NodeE>:
  109380:	55                   	push   %rbp
  109381:	48 89 e5             	mov    %rsp,%rbp
  109384:	48 83 ec 10          	sub    $0x10,%rsp
  109388:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10938c:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  109390:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  109394:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
  109398:	48 89 08             	mov    %rcx,(%rax)
  10939b:	48 c7 40 08 00 00 00 	movq   $0x0,0x8(%rax)
  1093a2:	00
  1093a3:	48 83 c4 10          	add    $0x10,%rsp
  1093a7:	5d                   	pop    %rbp
  1093a8:	c3                   	ret
  1093a9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

00000000001093b0 <_ZN4acos3vfs4File4readEPvm>:
  1093b0:	55                   	push   %rbp
  1093b1:	48 89 e5             	mov    %rsp,%rbp
  1093b4:	48 83 ec 30          	sub    $0x30,%rsp
  1093b8:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  1093bc:	48 89 75 e8          	mov    %rsi,-0x18(%rbp)
  1093c0:	48 89 55 e0          	mov    %rdx,-0x20(%rbp)
  1093c4:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  1093c8:	48 89 45 d0          	mov    %rax,-0x30(%rbp)
  1093cc:	48 83 38 00          	cmpq   $0x0,(%rax)
  1093d0:	0f 85 0c 00 00 00    	jne    1093e2 <_ZN4acos3vfs4File4readEPvm+0x32>
  1093d6:	c7 45 fc ff ff ff ff 	movl   $0xffffffff,-0x4(%rbp)
  1093dd:	e9 3c 00 00 00       	jmp    10941e <_ZN4acos3vfs4File4readEPvm+0x6e>
  1093e2:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  1093e6:	48 8b 38             	mov    (%rax),%rdi
  1093e9:	48 8b 70 08          	mov    0x8(%rax),%rsi
  1093ed:	48 8b 55 e0          	mov    -0x20(%rbp),%rdx
  1093f1:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  1093f5:	48 8b 07             	mov    (%rdi),%rax
  1093f8:	ff 50 10             	call   *0x10(%rax)
  1093fb:	89 45 dc             	mov    %eax,-0x24(%rbp)
  1093fe:	83 7d dc 00          	cmpl   $0x0,-0x24(%rbp)
  109402:	0f 8e 10 00 00 00    	jle    109418 <_ZN4acos3vfs4File4readEPvm+0x68>
  109408:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  10940c:	48 63 4d dc          	movslq -0x24(%rbp),%rcx
  109410:	48 03 48 08          	add    0x8(%rax),%rcx
  109414:	48 89 48 08          	mov    %rcx,0x8(%rax)
  109418:	8b 45 dc             	mov    -0x24(%rbp),%eax
  10941b:	89 45 fc             	mov    %eax,-0x4(%rbp)
  10941e:	8b 45 fc             	mov    -0x4(%rbp),%eax
  109421:	48 83 c4 30          	add    $0x30,%rsp
  109425:	5d                   	pop    %rbp
  109426:	c3                   	ret
  109427:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
  10942e:	00 00

0000000000109430 <_ZN4acos3vfs4File5writeEPKvm>:
  109430:	55                   	push   %rbp
  109431:	48 89 e5             	mov    %rsp,%rbp
  109434:	48 83 ec 30          	sub    $0x30,%rsp
  109438:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  10943c:	48 89 75 e8          	mov    %rsi,-0x18(%rbp)
  109440:	48 89 55 e0          	mov    %rdx,-0x20(%rbp)
  109444:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  109448:	48 89 45 d0          	mov    %rax,-0x30(%rbp)
  10944c:	48 83 38 00          	cmpq   $0x0,(%rax)
  109450:	0f 85 0c 00 00 00    	jne    109462 <_ZN4acos3vfs4File5writeEPKvm+0x32>
  109456:	c7 45 fc ff ff ff ff 	movl   $0xffffffff,-0x4(%rbp)
  10945d:	e9 3c 00 00 00       	jmp    10949e <_ZN4acos3vfs4File5writeEPKvm+0x6e>
  109462:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  109466:	48 8b 38             	mov    (%rax),%rdi
  109469:	48 8b 70 08          	mov    0x8(%rax),%rsi
  10946d:	48 8b 55 e0          	mov    -0x20(%rbp),%rdx
  109471:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  109475:	48 8b 07             	mov    (%rdi),%rax
  109478:	ff 50 18             	call   *0x18(%rax)
  10947b:	89 45 dc             	mov    %eax,-0x24(%rbp)
  10947e:	83 7d dc 00          	cmpl   $0x0,-0x24(%rbp)
  109482:	0f 8e 10 00 00 00    	jle    109498 <_ZN4acos3vfs4File5writeEPKvm+0x68>
  109488:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  10948c:	48 63 4d dc          	movslq -0x24(%rbp),%rcx
  109490:	48 03 48 08          	add    0x8(%rax),%rcx
  109494:	48 89 48 08          	mov    %rcx,0x8(%rax)
  109498:	8b 45 dc             	mov    -0x24(%rbp),%eax
  10949b:	89 45 fc             	mov    %eax,-0x4(%rbp)
  10949e:	8b 45 fc             	mov    -0x4(%rbp),%eax
  1094a1:	48 83 c4 30          	add    $0x30,%rsp
  1094a5:	5d                   	pop    %rbp
  1094a6:	c3                   	ret
  1094a7:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
  1094ae:	00 00

00000000001094b0 <_ZN4acos3vfs4File4seekEm>:
  1094b0:	55                   	push   %rbp
  1094b1:	48 89 e5             	mov    %rsp,%rbp
  1094b4:	48 83 ec 10          	sub    $0x10,%rsp
  1094b8:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  1094bc:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  1094c0:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  1094c4:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
  1094c8:	48 89 48 08          	mov    %rcx,0x8(%rax)
  1094cc:	48 8b 40 08          	mov    0x8(%rax),%rax
  1094d0:	48 83 c4 10          	add    $0x10,%rsp
  1094d4:	5d                   	pop    %rbp
  1094d5:	c3                   	ret
  1094d6:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
  1094dd:	00 00 00

00000000001094e0 <_ZNK4acos3vfs4File4sizeEv>:
  1094e0:	55                   	push   %rbp
  1094e1:	48 89 e5             	mov    %rsp,%rbp
  1094e4:	48 83 ec 20          	sub    $0x20,%rsp
  1094e8:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  1094ec:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  1094f0:	48 89 45 f0          	mov    %rax,-0x10(%rbp)
  1094f4:	48 83 38 00          	cmpq   $0x0,(%rax)
  1094f8:	0f 84 16 00 00 00    	je     109514 <_ZNK4acos3vfs4File4sizeEv+0x34>
  1094fe:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  109502:	48 8b 38             	mov    (%rax),%rdi
  109505:	48 8b 07             	mov    (%rdi),%rax
  109508:	ff 50 20             	call   *0x20(%rax)
  10950b:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
  10950f:	e9 0b 00 00 00       	jmp    10951f <_ZNK4acos3vfs4File4sizeEv+0x3f>
  109514:	31 c0                	xor    %eax,%eax
  109516:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
  10951a:	e9 00 00 00 00       	jmp    10951f <_ZNK4acos3vfs4File4sizeEv+0x3f>
  10951f:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  109523:	48 83 c4 20          	add    $0x20,%rsp
  109527:	5d                   	pop    %rbp
  109528:	c3                   	ret
  109529:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000109530 <_ZN4acos3vfs13MountRegistry5mountEPKcPNS0_10FileSystemE>:
  109530:	55                   	push   %rbp
  109531:	48 89 e5             	mov    %rsp,%rbp
  109534:	48 83 ec 40          	sub    $0x40,%rsp
  109538:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  10953c:	48 89 75 e8          	mov    %rsi,-0x18(%rbp)
  109540:	48 83 3c 25 40 9a 16 	cmpq   $0x10,0x169a40
  109547:	00 10
  109549:	0f 82 09 00 00 00    	jb     109558 <_ZN4acos3vfs13MountRegistry5mountEPKcPNS0_10FileSystemE+0x28>
  10954f:	c6 45 ff 00          	movb   $0x0,-0x1(%rbp)
  109553:	e9 12 01 00 00       	jmp    10966a <_ZN4acos3vfs13MountRegistry5mountEPKcPNS0_10FileSystemE+0x13a>
  109558:	48 c7 45 e0 00 00 00 	movq   $0x0,-0x20(%rbp)
  10955f:	00
  109560:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  109564:	48 3b 04 25 40 9a 16 	cmp    0x169a40,%rax
  10956b:	00
  10956c:	0f 83 46 00 00 00    	jae    1095b8 <_ZN4acos3vfs13MountRegistry5mountEPKcPNS0_10FileSystemE+0x88>
  109572:	48 bf 40 89 16 00 00 	movabs $0x168940,%rdi
  109579:	00 00 00
  10957c:	48 69 45 e0 10 01 00 	imul   $0x110,-0x20(%rbp),%rax
  109583:	00
  109584:	48 01 c7             	add    %rax,%rdi
  109587:	48 8b 75 f0          	mov    -0x10(%rbp),%rsi
  10958b:	e8 d0 6c ff ff       	call   100260 <strcmp>
  109590:	83 f8 00             	cmp    $0x0,%eax
  109593:	0f 85 09 00 00 00    	jne    1095a2 <_ZN4acos3vfs13MountRegistry5mountEPKcPNS0_10FileSystemE+0x72>
  109599:	c6 45 ff 00          	movb   $0x0,-0x1(%rbp)
  10959d:	e9 c8 00 00 00       	jmp    10966a <_ZN4acos3vfs13MountRegistry5mountEPKcPNS0_10FileSystemE+0x13a>
  1095a2:	e9 00 00 00 00       	jmp    1095a7 <_ZN4acos3vfs13MountRegistry5mountEPKcPNS0_10FileSystemE+0x77>
  1095a7:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  1095ab:	48 83 c0 01          	add    $0x1,%rax
  1095af:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  1095b3:	e9 a8 ff ff ff       	jmp    109560 <_ZN4acos3vfs13MountRegistry5mountEPKcPNS0_10FileSystemE+0x30>
  1095b8:	48 8b 0c 25 40 9a 16 	mov    0x169a40,%rcx
  1095bf:	00
  1095c0:	48 89 c8             	mov    %rcx,%rax
  1095c3:	48 83 c0 01          	add    $0x1,%rax
  1095c7:	48 89 04 25 40 9a 16 	mov    %rax,0x169a40
  1095ce:	00
  1095cf:	48 b8 40 89 16 00 00 	movabs $0x168940,%rax
  1095d6:	00 00 00
  1095d9:	48 69 c9 10 01 00 00 	imul   $0x110,%rcx,%rcx
  1095e0:	48 01 c8             	add    %rcx,%rax
  1095e3:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
  1095e7:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  1095eb:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  1095ef:	48 89 88 00 01 00 00 	mov    %rcx,0x100(%rax)
  1095f6:	48 c7 45 d0 00 00 00 	movq   $0x0,-0x30(%rbp)
  1095fd:	00
  1095fe:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
  109602:	48 8b 55 d0          	mov    -0x30(%rbp),%rdx
  109606:	31 c0                	xor    %eax,%eax
  109608:	80 3c 11 00          	cmpb   $0x0,(%rcx,%rdx,1)
  10960c:	88 45 cf             	mov    %al,-0x31(%rbp)
  10960f:	0f 84 0e 00 00 00    	je     109623 <_ZN4acos3vfs13MountRegistry5mountEPKcPNS0_10FileSystemE+0xf3>
  109615:	48 81 7d d0 ff 00 00 	cmpq   $0xff,-0x30(%rbp)
  10961c:	00
  10961d:	0f 92 c0             	setb   %al
  109620:	88 45 cf             	mov    %al,-0x31(%rbp)
  109623:	8a 45 cf             	mov    -0x31(%rbp),%al
  109626:	a8 01                	test   $0x1,%al
  109628:	0f 85 05 00 00 00    	jne    109633 <_ZN4acos3vfs13MountRegistry5mountEPKcPNS0_10FileSystemE+0x103>
  10962e:	e9 27 00 00 00       	jmp    10965a <_ZN4acos3vfs13MountRegistry5mountEPKcPNS0_10FileSystemE+0x12a>
  109633:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  109637:	48 8b 4d d0          	mov    -0x30(%rbp),%rcx
  10963b:	8a 14 08             	mov    (%rax,%rcx,1),%dl
  10963e:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  109642:	48 8b 4d d0          	mov    -0x30(%rbp),%rcx
  109646:	88 14 08             	mov    %dl,(%rax,%rcx,1)
  109649:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  10964d:	48 83 c0 01          	add    $0x1,%rax
  109651:	48 89 45 d0          	mov    %rax,-0x30(%rbp)
  109655:	e9 a4 ff ff ff       	jmp    1095fe <_ZN4acos3vfs13MountRegistry5mountEPKcPNS0_10FileSystemE+0xce>
  10965a:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  10965e:	48 8b 4d d0          	mov    -0x30(%rbp),%rcx
  109662:	c6 04 08 00          	movb   $0x0,(%rax,%rcx,1)
  109666:	c6 45 ff 01          	movb   $0x1,-0x1(%rbp)
  10966a:	8a 45 ff             	mov    -0x1(%rbp),%al
  10966d:	24 01                	and    $0x1,%al
  10966f:	0f b6 c0             	movzbl %al,%eax
  109672:	48 83 c4 40          	add    $0x40,%rsp
  109676:	5d                   	pop    %rbp
  109677:	c3                   	ret
  109678:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  10967f:	00

0000000000109680 <_ZN4acos3vfs13MountRegistry10find_mountEPKc>:
  109680:	55                   	push   %rbp
  109681:	48 89 e5             	mov    %rsp,%rbp
  109684:	48 83 ec 50          	sub    $0x50,%rsp
  109688:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  10968c:	48 83 7d f0 00       	cmpq   $0x0,-0x10(%rbp)
  109691:	0f 85 0d 00 00 00    	jne    1096a4 <_ZN4acos3vfs13MountRegistry10find_mountEPKc+0x24>
  109697:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  10969e:	00
  10969f:	e9 a5 01 00 00       	jmp    109849 <_ZN4acos3vfs13MountRegistry10find_mountEPKc+0x1c9>
  1096a4:	48 c7 45 e8 00 00 00 	movq   $0x0,-0x18(%rbp)
  1096ab:	00
  1096ac:	48 c7 45 e0 00 00 00 	movq   $0x0,-0x20(%rbp)
  1096b3:	00
  1096b4:	c7 45 dc ff ff ff ff 	movl   $0xffffffff,-0x24(%rbp)
  1096bb:	48 c7 45 d0 00 00 00 	movq   $0x0,-0x30(%rbp)
  1096c2:	00
  1096c3:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  1096c7:	48 3b 04 25 40 9a 16 	cmp    0x169a40,%rax
  1096ce:	00
  1096cf:	0f 83 29 01 00 00    	jae    1097fe <_ZN4acos3vfs13MountRegistry10find_mountEPKc+0x17e>
  1096d5:	48 b8 40 89 16 00 00 	movabs $0x168940,%rax
  1096dc:	00 00 00
  1096df:	48 69 4d d0 10 01 00 	imul   $0x110,-0x30(%rbp),%rcx
  1096e6:	00
  1096e7:	48 01 c8             	add    %rcx,%rax
  1096ea:	48 89 45 c8          	mov    %rax,-0x38(%rbp)
  1096ee:	48 8b 7d c8          	mov    -0x38(%rbp),%rdi
  1096f2:	e8 69 01 00 00       	call   109860 <_ZN4acos3vfsL11strlen_implEPKc>
  1096f7:	48 89 45 c0          	mov    %rax,-0x40(%rbp)
  1096fb:	48 83 7d c0 01       	cmpq   $0x1,-0x40(%rbp)
  109700:	0f 85 1c 00 00 00    	jne    109722 <_ZN4acos3vfs13MountRegistry10find_mountEPKc+0xa2>
  109706:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  10970a:	0f be 00             	movsbl (%rax),%eax
  10970d:	83 f8 2f             	cmp    $0x2f,%eax
  109710:	0f 85 0c 00 00 00    	jne    109722 <_ZN4acos3vfs13MountRegistry10find_mountEPKc+0xa2>
  109716:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  10971a:	89 45 dc             	mov    %eax,-0x24(%rbp)
  10971d:	e9 cb 00 00 00       	jmp    1097ed <_ZN4acos3vfs13MountRegistry10find_mountEPKc+0x16d>
  109722:	c6 45 bf 01          	movb   $0x1,-0x41(%rbp)
  109726:	48 c7 45 b0 00 00 00 	movq   $0x0,-0x50(%rbp)
  10972d:	00
  10972e:	48 8b 45 b0          	mov    -0x50(%rbp),%rax
  109732:	48 3b 45 c0          	cmp    -0x40(%rbp),%rax
  109736:	0f 83 3f 00 00 00    	jae    10977b <_ZN4acos3vfs13MountRegistry10find_mountEPKc+0xfb>
  10973c:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  109740:	48 8b 4d b0          	mov    -0x50(%rbp),%rcx
  109744:	0f be 04 08          	movsbl (%rax,%rcx,1),%eax
  109748:	48 8b 4d c8          	mov    -0x38(%rbp),%rcx
  10974c:	48 8b 55 b0          	mov    -0x50(%rbp),%rdx
  109750:	0f be 0c 11          	movsbl (%rcx,%rdx,1),%ecx
  109754:	39 c8                	cmp    %ecx,%eax
  109756:	0f 84 09 00 00 00    	je     109765 <_ZN4acos3vfs13MountRegistry10find_mountEPKc+0xe5>
  10975c:	c6 45 bf 00          	movb   $0x0,-0x41(%rbp)
  109760:	e9 16 00 00 00       	jmp    10977b <_ZN4acos3vfs13MountRegistry10find_mountEPKc+0xfb>
  109765:	e9 00 00 00 00       	jmp    10976a <_ZN4acos3vfs13MountRegistry10find_mountEPKc+0xea>
  10976a:	48 8b 45 b0          	mov    -0x50(%rbp),%rax
  10976e:	48 83 c0 01          	add    $0x1,%rax
  109772:	48 89 45 b0          	mov    %rax,-0x50(%rbp)
  109776:	e9 b3 ff ff ff       	jmp    10972e <_ZN4acos3vfs13MountRegistry10find_mountEPKc+0xae>
  10977b:	f6 45 bf 01          	testb  $0x1,-0x41(%rbp)
  10977f:	0f 85 05 00 00 00    	jne    10978a <_ZN4acos3vfs13MountRegistry10find_mountEPKc+0x10a>
  109785:	e9 63 00 00 00       	jmp    1097ed <_ZN4acos3vfs13MountRegistry10find_mountEPKc+0x16d>
  10978a:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10978e:	48 8b 4d c0          	mov    -0x40(%rbp),%rcx
  109792:	0f be 04 08          	movsbl (%rax,%rcx,1),%eax
  109796:	83 f8 00             	cmp    $0x0,%eax
  109799:	0f 84 1a 00 00 00    	je     1097b9 <_ZN4acos3vfs13MountRegistry10find_mountEPKc+0x139>
  10979f:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  1097a3:	48 8b 4d c0          	mov    -0x40(%rbp),%rcx
  1097a7:	0f be 04 08          	movsbl (%rax,%rcx,1),%eax
  1097ab:	83 f8 2f             	cmp    $0x2f,%eax
  1097ae:	0f 84 05 00 00 00    	je     1097b9 <_ZN4acos3vfs13MountRegistry10find_mountEPKc+0x139>
  1097b4:	e9 34 00 00 00       	jmp    1097ed <_ZN4acos3vfs13MountRegistry10find_mountEPKc+0x16d>
  1097b9:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  1097bd:	48 3b 45 e0          	cmp    -0x20(%rbp),%rax
  1097c1:	0f 86 21 00 00 00    	jbe    1097e8 <_ZN4acos3vfs13MountRegistry10find_mountEPKc+0x168>
  1097c7:	48 b8 40 89 16 00 00 	movabs $0x168940,%rax
  1097ce:	00 00 00
  1097d1:	48 69 4d d0 10 01 00 	imul   $0x110,-0x30(%rbp),%rcx
  1097d8:	00
  1097d9:	48 01 c8             	add    %rcx,%rax
  1097dc:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
  1097e0:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  1097e4:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  1097e8:	e9 00 00 00 00       	jmp    1097ed <_ZN4acos3vfs13MountRegistry10find_mountEPKc+0x16d>
  1097ed:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  1097f1:	48 83 c0 01          	add    $0x1,%rax
  1097f5:	48 89 45 d0          	mov    %rax,-0x30(%rbp)
  1097f9:	e9 c5 fe ff ff       	jmp    1096c3 <_ZN4acos3vfs13MountRegistry10find_mountEPKc+0x43>
  1097fe:	48 83 7d e8 00       	cmpq   $0x0,-0x18(%rbp)
  109803:	0f 84 0d 00 00 00    	je     109816 <_ZN4acos3vfs13MountRegistry10find_mountEPKc+0x196>
  109809:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  10980d:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  109811:	e9 33 00 00 00       	jmp    109849 <_ZN4acos3vfs13MountRegistry10find_mountEPKc+0x1c9>
  109816:	83 7d dc ff          	cmpl   $0xffffffff,-0x24(%rbp)
  10981a:	0f 84 21 00 00 00    	je     109841 <_ZN4acos3vfs13MountRegistry10find_mountEPKc+0x1c1>
  109820:	48 63 4d dc          	movslq -0x24(%rbp),%rcx
  109824:	48 b8 40 89 16 00 00 	movabs $0x168940,%rax
  10982b:	00 00 00
  10982e:	48 69 c9 10 01 00 00 	imul   $0x110,%rcx,%rcx
  109835:	48 01 c8             	add    %rcx,%rax
  109838:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  10983c:	e9 08 00 00 00       	jmp    109849 <_ZN4acos3vfs13MountRegistry10find_mountEPKc+0x1c9>
  109841:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  109848:	00
  109849:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10984d:	48 83 c4 50          	add    $0x50,%rsp
  109851:	5d                   	pop    %rbp
  109852:	c3                   	ret
  109853:	66 66 66 66 2e 0f 1f 	data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
  10985a:	84 00 00 00 00 00

0000000000109860 <_ZN4acos3vfsL11strlen_implEPKc>:
  109860:	55                   	push   %rbp
  109861:	48 89 e5             	mov    %rsp,%rbp
  109864:	48 83 ec 10          	sub    $0x10,%rsp
  109868:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10986c:	48 c7 45 f0 00 00 00 	movq   $0x0,-0x10(%rbp)
  109873:	00
  109874:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  109878:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
  10987c:	80 3c 08 00          	cmpb   $0x0,(%rax,%rcx,1)
  109880:	0f 84 11 00 00 00    	je     109897 <_ZN4acos3vfsL11strlen_implEPKc+0x37>
  109886:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10988a:	48 83 c0 01          	add    $0x1,%rax
  10988e:	48 89 45 f0          	mov    %rax,-0x10(%rbp)
  109892:	e9 dd ff ff ff       	jmp    109874 <_ZN4acos3vfsL11strlen_implEPKc+0x14>
  109897:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10989b:	48 83 c4 10          	add    $0x10,%rsp
  10989f:	5d                   	pop    %rbp
  1098a0:	c3                   	ret
  1098a1:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
  1098a8:	00 00 00
  1098ab:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000001098b0 <_ZN4acos3vfs4Path9normalizeEPc>:
  1098b0:	55                   	push   %rbp
  1098b1:	48 89 e5             	mov    %rsp,%rbp
  1098b4:	48 83 ec 18          	sub    $0x18,%rsp
  1098b8:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  1098bc:	48 83 7d f8 00       	cmpq   $0x0,-0x8(%rbp)
  1098c1:	0f 85 05 00 00 00    	jne    1098cc <_ZN4acos3vfs4Path9normalizeEPc+0x1c>
  1098c7:	e9 9b 00 00 00       	jmp    109967 <_ZN4acos3vfs4Path9normalizeEPc+0xb7>
  1098cc:	48 c7 45 f0 00 00 00 	movq   $0x0,-0x10(%rbp)
  1098d3:	00
  1098d4:	48 c7 45 e8 00 00 00 	movq   $0x0,-0x18(%rbp)
  1098db:	00
  1098dc:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  1098e0:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
  1098e4:	80 3c 08 00          	cmpb   $0x0,(%rax,%rcx,1)
  1098e8:	0f 84 6d 00 00 00    	je     10995b <_ZN4acos3vfs4Path9normalizeEPc+0xab>
  1098ee:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  1098f2:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
  1098f6:	0f be 04 08          	movsbl (%rax,%rcx,1),%eax
  1098fa:	83 f8 2f             	cmp    $0x2f,%eax
  1098fd:	0f 85 27 00 00 00    	jne    10992a <_ZN4acos3vfs4Path9normalizeEPc+0x7a>
  109903:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  109907:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
  10990b:	0f be 44 08 01       	movsbl 0x1(%rax,%rcx,1),%eax
  109910:	83 f8 2f             	cmp    $0x2f,%eax
  109913:	0f 85 11 00 00 00    	jne    10992a <_ZN4acos3vfs4Path9normalizeEPc+0x7a>
  109919:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10991d:	48 83 c0 01          	add    $0x1,%rax
  109921:	48 89 45 f0          	mov    %rax,-0x10(%rbp)
  109925:	e9 b2 ff ff ff       	jmp    1098dc <_ZN4acos3vfs4Path9normalizeEPc+0x2c>
  10992a:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10992e:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
  109932:	48 89 ca             	mov    %rcx,%rdx
  109935:	48 83 c2 01          	add    $0x1,%rdx
  109939:	48 89 55 f0          	mov    %rdx,-0x10(%rbp)
  10993d:	8a 14 08             	mov    (%rax,%rcx,1),%dl
  109940:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  109944:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  109948:	48 89 ce             	mov    %rcx,%rsi
  10994b:	48 83 c6 01          	add    $0x1,%rsi
  10994f:	48 89 75 e8          	mov    %rsi,-0x18(%rbp)
  109953:	88 14 08             	mov    %dl,(%rax,%rcx,1)
  109956:	e9 81 ff ff ff       	jmp    1098dc <_ZN4acos3vfs4Path9normalizeEPc+0x2c>
  10995b:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10995f:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  109963:	c6 04 08 00          	movb   $0x0,(%rax,%rcx,1)
  109967:	48 83 c4 18          	add    $0x18,%rsp
  10996b:	5d                   	pop    %rbp
  10996c:	c3                   	ret
  10996d:	0f 1f 00             	nopl   (%rax)

0000000000109970 <_ZN4acos3vfs4Path11is_absoluteEPKc>:
  109970:	55                   	push   %rbp
  109971:	48 89 e5             	mov    %rsp,%rbp
  109974:	48 83 ec 10          	sub    $0x10,%rsp
  109978:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10997c:	31 c0                	xor    %eax,%eax
  10997e:	48 83 7d f8 00       	cmpq   $0x0,-0x8(%rbp)
  109983:	88 45 f7             	mov    %al,-0x9(%rbp)
  109986:	0f 84 10 00 00 00    	je     10999c <_ZN4acos3vfs4Path11is_absoluteEPKc+0x2c>
  10998c:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  109990:	0f be 00             	movsbl (%rax),%eax
  109993:	83 f8 2f             	cmp    $0x2f,%eax
  109996:	0f 94 c0             	sete   %al
  109999:	88 45 f7             	mov    %al,-0x9(%rbp)
  10999c:	8a 45 f7             	mov    -0x9(%rbp),%al
  10999f:	24 01                	and    $0x1,%al
  1099a1:	0f b6 c0             	movzbl %al,%eax
  1099a4:	48 83 c4 10          	add    $0x10,%rsp
  1099a8:	5d                   	pop    %rbp
  1099a9:	c3                   	ret
  1099aa:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

00000000001099b0 <_ZN4acos3vfs11ConsoleNode4readEmmPv>:
  1099b0:	55                   	push   %rbp
  1099b1:	48 89 e5             	mov    %rsp,%rbp
  1099b4:	48 83 ec 40          	sub    $0x40,%rsp
  1099b8:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  1099bc:	48 89 75 e8          	mov    %rsi,-0x18(%rbp)
  1099c0:	48 89 55 e0          	mov    %rdx,-0x20(%rbp)
  1099c4:	48 89 4d d8          	mov    %rcx,-0x28(%rbp)
  1099c8:	48 83 7d d8 00       	cmpq   $0x0,-0x28(%rbp)
  1099cd:	0f 84 0b 00 00 00    	je     1099de <_ZN4acos3vfs11ConsoleNode4readEmmPv+0x2e>
  1099d3:	48 83 7d e0 00       	cmpq   $0x0,-0x20(%rbp)
  1099d8:	0f 85 0c 00 00 00    	jne    1099ea <_ZN4acos3vfs11ConsoleNode4readEmmPv+0x3a>
  1099de:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%rbp)
  1099e5:	e9 6f 00 00 00       	jmp    109a59 <_ZN4acos3vfs11ConsoleNode4readEmmPv+0xa9>
  1099ea:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  1099ee:	48 89 45 d0          	mov    %rax,-0x30(%rbp)
  1099f2:	48 c7 45 c8 00 00 00 	movq   $0x0,-0x38(%rbp)
  1099f9:	00
  1099fa:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  1099fe:	48 3b 45 e0          	cmp    -0x20(%rbp),%rax
  109a02:	0f 83 4a 00 00 00    	jae    109a52 <_ZN4acos3vfs11ConsoleNode4readEmmPv+0xa2>
  109a08:	e8 73 09 00 00       	call   10a380 <_ZN4acos3hal15serial_receivedEv>
  109a0d:	a8 01                	test   $0x1,%al
  109a0f:	0f 85 05 00 00 00    	jne    109a1a <_ZN4acos3vfs11ConsoleNode4readEmmPv+0x6a>
  109a15:	e9 22 00 00 00       	jmp    109a3c <_ZN4acos3vfs11ConsoleNode4readEmmPv+0x8c>
  109a1a:	e8 c1 09 00 00       	call   10a3e0 <_ZN4acos3hal11serial_readEv>
  109a1f:	88 c2                	mov    %al,%dl
  109a21:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  109a25:	48 8b 4d c8          	mov    -0x38(%rbp),%rcx
  109a29:	48 89 ce             	mov    %rcx,%rsi
  109a2c:	48 83 c6 01          	add    $0x1,%rsi
  109a30:	48 89 75 c8          	mov    %rsi,-0x38(%rbp)
  109a34:	88 14 08             	mov    %dl,(%rax,%rcx,1)
  109a37:	e9 11 00 00 00       	jmp    109a4d <_ZN4acos3vfs11ConsoleNode4readEmmPv+0x9d>
  109a3c:	48 83 7d c8 00       	cmpq   $0x0,-0x38(%rbp)
  109a41:	0f 86 05 00 00 00    	jbe    109a4c <_ZN4acos3vfs11ConsoleNode4readEmmPv+0x9c>
  109a47:	e9 06 00 00 00       	jmp    109a52 <_ZN4acos3vfs11ConsoleNode4readEmmPv+0xa2>
  109a4c:	f4                   	hlt
  109a4d:	e9 a8 ff ff ff       	jmp    1099fa <_ZN4acos3vfs11ConsoleNode4readEmmPv+0x4a>
  109a52:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  109a56:	89 45 fc             	mov    %eax,-0x4(%rbp)
  109a59:	8b 45 fc             	mov    -0x4(%rbp),%eax
  109a5c:	48 83 c4 40          	add    $0x40,%rsp
  109a60:	5d                   	pop    %rbp
  109a61:	c3                   	ret
  109a62:	66 66 66 66 66 2e 0f 	data16 data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
  109a69:	1f 84 00 00 00 00 00

0000000000109a70 <_ZN4acos3vfs11ConsoleNode5writeEmmPKv>:
  109a70:	55                   	push   %rbp
  109a71:	48 89 e5             	mov    %rsp,%rbp
  109a74:	48 81 ec 50 04 00 00 	sub    $0x450,%rsp
  109a7b:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  109a7f:	48 89 75 e8          	mov    %rsi,-0x18(%rbp)
  109a83:	48 89 55 e0          	mov    %rdx,-0x20(%rbp)
  109a87:	48 89 4d d8          	mov    %rcx,-0x28(%rbp)
  109a8b:	48 83 7d d8 00       	cmpq   $0x0,-0x28(%rbp)
  109a90:	0f 84 0b 00 00 00    	je     109aa1 <_ZN4acos3vfs11ConsoleNode5writeEmmPKv+0x31>
  109a96:	48 83 7d e0 00       	cmpq   $0x0,-0x20(%rbp)
  109a9b:	0f 85 0c 00 00 00    	jne    109aad <_ZN4acos3vfs11ConsoleNode5writeEmmPKv+0x3d>
  109aa1:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%rbp)
  109aa8:	e9 45 01 00 00       	jmp    109bf2 <_ZN4acos3vfs11ConsoleNode5writeEmmPKv+0x182>
  109aad:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  109ab1:	48 89 45 d0          	mov    %rax,-0x30(%rbp)
  109ab5:	48 81 7d e0 00 04 00 	cmpq   $0x400,-0x20(%rbp)
  109abc:	00
  109abd:	0f 83 71 00 00 00    	jae    109b34 <_ZN4acos3vfs11ConsoleNode5writeEmmPKv+0xc4>
  109ac3:	48 c7 85 c8 fb ff ff 	movq   $0x0,-0x438(%rbp)
  109aca:	00 00 00 00
  109ace:	48 8b 85 c8 fb ff ff 	mov    -0x438(%rbp),%rax
  109ad5:	48 3b 45 e0          	cmp    -0x20(%rbp),%rax
  109ad9:	0f 83 33 00 00 00    	jae    109b12 <_ZN4acos3vfs11ConsoleNode5writeEmmPKv+0xa2>
  109adf:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  109ae3:	48 8b 8d c8 fb ff ff 	mov    -0x438(%rbp),%rcx
  109aea:	8a 0c 08             	mov    (%rax,%rcx,1),%cl
  109aed:	48 8b 85 c8 fb ff ff 	mov    -0x438(%rbp),%rax
  109af4:	88 8c 05 d0 fb ff ff 	mov    %cl,-0x430(%rbp,%rax,1)
  109afb:	48 8b 85 c8 fb ff ff 	mov    -0x438(%rbp),%rax
  109b02:	48 83 c0 01          	add    $0x1,%rax
  109b06:	48 89 85 c8 fb ff ff 	mov    %rax,-0x438(%rbp)
  109b0d:	e9 bc ff ff ff       	jmp    109ace <_ZN4acos3vfs11ConsoleNode5writeEmmPKv+0x5e>
  109b12:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  109b16:	c6 84 05 d0 fb ff ff 	movb   $0x0,-0x430(%rbp,%rax,1)
  109b1d:	00
  109b1e:	48 8d bd d0 fb ff ff 	lea    -0x430(%rbp),%rdi
  109b25:	be ff ff ff ff       	mov    $0xffffffff,%esi
  109b2a:	e8 61 0c 00 00       	call   10a790 <_ZN4acos3hal13console_printEPKcj>
  109b2f:	e9 70 00 00 00       	jmp    109ba4 <_ZN4acos3vfs11ConsoleNode5writeEmmPKv+0x134>
  109b34:	48 8d bd c6 fb ff ff 	lea    -0x43a(%rbp),%rdi
  109b3b:	31 f6                	xor    %esi,%esi
  109b3d:	ba 02 00 00 00       	mov    $0x2,%edx
  109b42:	e8 29 65 ff ff       	call   100070 <memset>
  109b47:	48 c7 85 b8 fb ff ff 	movq   $0x0,-0x448(%rbp)
  109b4e:	00 00 00 00
  109b52:	48 8b 85 b8 fb ff ff 	mov    -0x448(%rbp),%rax
  109b59:	48 3b 45 e0          	cmp    -0x20(%rbp),%rax
  109b5d:	0f 83 3c 00 00 00    	jae    109b9f <_ZN4acos3vfs11ConsoleNode5writeEmmPKv+0x12f>
  109b63:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  109b67:	48 8b 8d b8 fb ff ff 	mov    -0x448(%rbp),%rcx
  109b6e:	8a 04 08             	mov    (%rax,%rcx,1),%al
  109b71:	88 85 c6 fb ff ff    	mov    %al,-0x43a(%rbp)
  109b77:	48 8d bd c6 fb ff ff 	lea    -0x43a(%rbp),%rdi
  109b7e:	be ff ff ff ff       	mov    $0xffffffff,%esi
  109b83:	e8 08 0c 00 00       	call   10a790 <_ZN4acos3hal13console_printEPKcj>
  109b88:	48 8b 85 b8 fb ff ff 	mov    -0x448(%rbp),%rax
  109b8f:	48 83 c0 01          	add    $0x1,%rax
  109b93:	48 89 85 b8 fb ff ff 	mov    %rax,-0x448(%rbp)
  109b9a:	e9 b3 ff ff ff       	jmp    109b52 <_ZN4acos3vfs11ConsoleNode5writeEmmPKv+0xe2>
  109b9f:	e9 00 00 00 00       	jmp    109ba4 <_ZN4acos3vfs11ConsoleNode5writeEmmPKv+0x134>
  109ba4:	48 c7 85 b0 fb ff ff 	movq   $0x0,-0x450(%rbp)
  109bab:	00 00 00 00
  109baf:	48 8b 85 b0 fb ff ff 	mov    -0x450(%rbp),%rax
  109bb6:	48 3b 45 e0          	cmp    -0x20(%rbp),%rax
  109bba:	0f 83 2b 00 00 00    	jae    109beb <_ZN4acos3vfs11ConsoleNode5writeEmmPKv+0x17b>
  109bc0:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  109bc4:	48 8b 8d b0 fb ff ff 	mov    -0x450(%rbp),%rcx
  109bcb:	0f be 3c 08          	movsbl (%rax,%rcx,1),%edi
  109bcf:	e8 7c 08 00 00       	call   10a450 <_ZN4acos3hal12serial_writeEc>
  109bd4:	48 8b 85 b0 fb ff ff 	mov    -0x450(%rbp),%rax
  109bdb:	48 83 c0 01          	add    $0x1,%rax
  109bdf:	48 89 85 b0 fb ff ff 	mov    %rax,-0x450(%rbp)
  109be6:	e9 c4 ff ff ff       	jmp    109baf <_ZN4acos3vfs11ConsoleNode5writeEmmPKv+0x13f>
  109beb:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  109bef:	89 45 fc             	mov    %eax,-0x4(%rbp)
  109bf2:	8b 45 fc             	mov    -0x4(%rbp),%eax
  109bf5:	48 81 c4 50 04 00 00 	add    $0x450,%rsp
  109bfc:	5d                   	pop    %rbp
  109bfd:	c3                   	ret
  109bfe:	66 90                	xchg   %ax,%ax

0000000000109c00 <kernelMain>:
  109c00:	55                   	push   %rbp
  109c01:	48 89 e5             	mov    %rsp,%rbp
  109c04:	48 81 ec 00 12 00 00 	sub    $0x1200,%rsp
  109c0b:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  109c0f:	e8 cc 06 00 00       	call   10a2e0 <_ZN4acos3hal11serial_initEv>
  109c14:	31 c0                	xor    %eax,%eax
  109c16:	89 c7                	mov    %eax,%edi
  109c18:	e8 83 09 00 00       	call   10a5a0 <_ZN4acos3hal12console_initEPNS_15FramebufferInfoE>
  109c1d:	48 bf cd f9 10 00 00 	movabs $0x10f9cd,%rdi
  109c24:	00 00 00
  109c27:	e8 64 08 00 00       	call   10a490 <_ZN4acos3hal12serial_printEPKc>
  109c2c:	31 c0                	xor    %eax,%eax
  109c2e:	48 83 7d f8 00       	cmpq   $0x0,-0x8(%rbp)
  109c33:	88 85 16 ee ff ff    	mov    %al,-0x11ea(%rbp)
  109c39:	0f 84 12 00 00 00    	je     109c51 <kernelMain+0x51>
  109c3f:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  109c43:	48 83 78 10 00       	cmpq   $0x0,0x10(%rax)
  109c48:	0f 95 c0             	setne  %al
  109c4b:	88 85 16 ee ff ff    	mov    %al,-0x11ea(%rbp)
  109c51:	8a 85 16 ee ff ff    	mov    -0x11ea(%rbp),%al
  109c57:	24 01                	and    $0x1,%al
  109c59:	88 45 f7             	mov    %al,-0x9(%rbp)
  109c5c:	f6 45 f7 01          	testb  $0x1,-0x9(%rbp)
  109c60:	0f 84 17 00 00 00    	je     109c7d <kernelMain+0x7d>
  109c66:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  109c6a:	48 8b 78 10          	mov    0x10(%rax),%rdi
  109c6e:	e8 2d 09 00 00       	call   10a5a0 <_ZN4acos3hal12console_initEPNS_15FramebufferInfoE>
  109c73:	bf 5f 3a 1e 00       	mov    $0x1e3a5f,%edi
  109c78:	e8 63 0a 00 00       	call   10a6e0 <_ZN4acos3hal13console_clearEj>
  109c7d:	e8 fe cf ff ff       	call   106c80 <_ZN4acos3hal8gdt_initEv>
  109c82:	e8 79 41 00 00       	call   10de00 <_ZN4acos3smp10SmpManager4initEv>
  109c87:	e8 44 d3 ff ff       	call   106fd0 <_ZN4acos3hal8idt_initEv>
  109c8c:	48 c7 04 25 48 9a 16 	movq   $0x0,0x169a48
  109c93:	00 00 00 00 00
  109c98:	c7 04 25 60 9a 16 00 	movl   $0x2,0x169a60
  109c9f:	02 00 00 00
  109ca3:	c6 04 25 70 9a 16 00 	movb   $0x0,0x169a70
  109caa:	00
  109cab:	48 b8 98 9a 16 00 00 	movabs $0x169a98,%rax
  109cb2:	00 00 00
  109cb5:	48 89 04 25 68 9a 16 	mov    %rax,0x169a68
  109cbc:	00
  109cbd:	48 c7 04 25 98 9a 16 	movq   $0x0,0x169a98
  109cc4:	00 00 00 00 00
  109cc9:	e8 d2 42 00 00       	call   10dfa0 <_ZN4acos3smp3Cpu7currentEv>
  109cce:	48 b9 48 9a 16 00 00 	movabs $0x169a48,%rcx
  109cd5:	00 00 00
  109cd8:	48 89 48 18          	mov    %rcx,0x18(%rax)
  109cdc:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  109ce0:	e8 0b d4 ff ff       	call   1070f0 <_ZN4acos6memory8pmm_initEPNS_8BootInfoE>
  109ce5:	48 bf eb f9 10 00 00 	movabs $0x10f9eb,%rdi
  109cec:	00 00 00
  109cef:	48 be a0 fc 10 00 00 	movabs $0x10fca0,%rsi
  109cf6:	00 00 00
  109cf9:	e8 d2 f3 ff ff       	call   1090d0 <_ZN4acos3vfs3VFS5mountEPKcPNS0_10FileSystemE>
  109cfe:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  109d02:	e8 b9 dd ff ff       	call   107ac0 <_ZN4acos6memory8vmm_initEPNS_8BootInfoE>
  109d07:	e8 44 c8 ff ff       	call   106550 <_ZN4acos9scheduler14scheduler_initEv>
  109d0c:	e8 af 9d ff ff       	call   103ac0 <_ZN4acos8services4initEv>
  109d11:	e8 ca 8f ff ff       	call   102ce0 <_ZN4acos7storage14StorageManager4initEv>
  109d16:	80 3c 25 e0 d5 16 00 	cmpb   $0x0,0x16d5e0
  109d1d:	00
  109d1e:	0f 85 3a 00 00 00    	jne    109d5e <kernelMain+0x15e>
  109d24:	48 bf e0 d5 16 00 00 	movabs $0x16d5e0,%rdi
  109d2b:	00 00 00
  109d2e:	e8 dd 03 00 00       	call   10a110 <__cxa_guard_acquire>
  109d33:	83 f8 00             	cmp    $0x0,%eax
  109d36:	0f 84 22 00 00 00    	je     109d5e <kernelMain+0x15e>
  109d3c:	48 bf b0 d5 16 00 00 	movabs $0x16d5b0,%rdi
  109d43:	00 00 00
  109d46:	31 c0                	xor    %eax,%eax
  109d48:	89 c6                	mov    %eax,%esi
  109d4a:	e8 31 74 ff ff       	call   101180 <_ZN4acos7storage15FAT32FileSystemC1EPNS0_11BlockDeviceE>
  109d4f:	48 bf e0 d5 16 00 00 	movabs $0x16d5e0,%rdi
  109d56:	00 00 00
  109d59:	e8 d2 03 00 00       	call   10a130 <__cxa_guard_release>
  109d5e:	bf f0 f9 10 00       	mov    $0x10f9f0,%edi
  109d63:	be b0 d5 16 00       	mov    $0x16d5b0,%esi
  109d68:	e8 73 70 ff ff       	call   100de0 <_ZN4acos7storage17FileSystemManager19register_filesystemEPKcPNS_3vfs10FileSystemE>
  109d6d:	bf 01 00 00 00       	mov    $0x1,%edi
  109d72:	be 06 00 00 00       	mov    $0x6,%esi
  109d77:	e8 04 0c 00 00       	call   10a980 <_ZN4acos3hal3PCI11find_deviceEhh>
  109d7c:	89 55 e0             	mov    %edx,-0x20(%rbp)
  109d7f:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
  109d83:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  109d87:	48 89 45 ea          	mov    %rax,-0x16(%rbp)
  109d8b:	8b 45 e0             	mov    -0x20(%rbp),%eax
  109d8e:	89 45 f2             	mov    %eax,-0xe(%rbp)
  109d91:	0f b7 45 ee          	movzwl -0x12(%rbp),%eax
  109d95:	3d ff ff 00 00       	cmp    $0xffff,%eax
  109d9a:	0f 85 2f 00 00 00    	jne    109dcf <kernelMain+0x1cf>
  109da0:	be 01 00 00 00       	mov    $0x1,%esi
  109da5:	89 f7                	mov    %esi,%edi
  109da7:	e8 d4 0b 00 00       	call   10a980 <_ZN4acos3hal3PCI11find_deviceEhh>
  109dac:	89 55 c0             	mov    %edx,-0x40(%rbp)
  109daf:	48 89 45 b8          	mov    %rax,-0x48(%rbp)
  109db3:	48 8b 45 b8          	mov    -0x48(%rbp),%rax
  109db7:	48 89 45 cc          	mov    %rax,-0x34(%rbp)
  109dbb:	8b 45 c0             	mov    -0x40(%rbp),%eax
  109dbe:	89 45 d4             	mov    %eax,-0x2c(%rbp)
  109dc1:	48 8b 45 cc          	mov    -0x34(%rbp),%rax
  109dc5:	48 89 45 ea          	mov    %rax,-0x16(%rbp)
  109dc9:	8b 45 d4             	mov    -0x2c(%rbp),%eax
  109dcc:	89 45 f2             	mov    %eax,-0xe(%rbp)
  109dcf:	0f b7 45 ee          	movzwl -0x12(%rbp),%eax
  109dd3:	3d ff ff 00 00       	cmp    $0xffff,%eax
  109dd8:	0f 84 25 01 00 00    	je     109f03 <kernelMain+0x303>
  109dde:	48 8d 7d ea          	lea    -0x16(%rbp),%rdi
  109de2:	e8 69 0e 00 00       	call   10ac50 <_ZN4acos3hal3PCI20enable_bus_masteringERKNS0_9PCIDeviceE>
  109de7:	48 8d 7d ea          	lea    -0x16(%rbp),%rdi
  109deb:	be 05 00 00 00       	mov    $0x5,%esi
  109df0:	e8 7b 0d 00 00       	call   10ab70 <_ZN4acos3hal3PCI7get_barERKNS0_9PCIDeviceEh>
  109df5:	48 89 45 b0          	mov    %rax,-0x50(%rbp)
  109df9:	48 83 7d b0 00       	cmpq   $0x0,-0x50(%rbp)
  109dfe:	0f 85 0f 00 00 00    	jne    109e13 <kernelMain+0x213>
  109e04:	48 8d 7d ea          	lea    -0x16(%rbp),%rdi
  109e08:	31 f6                	xor    %esi,%esi
  109e0a:	e8 61 0d 00 00       	call   10ab70 <_ZN4acos3hal3PCI7get_barERKNS0_9PCIDeviceEh>
  109e0f:	48 89 45 b0          	mov    %rax,-0x50(%rbp)
  109e13:	80 3c 25 f8 d6 16 00 	cmpb   $0x0,0x16d6f8
  109e1a:	00
  109e1b:	0f 85 3a 00 00 00    	jne    109e5b <kernelMain+0x25b>
  109e21:	48 bf f8 d6 16 00 00 	movabs $0x16d6f8,%rdi
  109e28:	00 00 00
  109e2b:	e8 e0 02 00 00       	call   10a110 <__cxa_guard_acquire>
  109e30:	83 f8 00             	cmp    $0x0,%eax
  109e33:	0f 84 22 00 00 00    	je     109e5b <kernelMain+0x25b>
  109e39:	48 8b 75 b0          	mov    -0x50(%rbp),%rsi
  109e3d:	48 bf e8 d5 16 00 00 	movabs $0x16d5e8,%rdi
  109e44:	00 00 00
  109e47:	e8 84 66 ff ff       	call   1004d0 <_ZN4acos7storage14AHCIControllerC1Em>
  109e4c:	48 bf f8 d6 16 00 00 	movabs $0x16d6f8,%rdi
  109e53:	00 00 00
  109e56:	e8 d5 02 00 00       	call   10a130 <__cxa_guard_release>
  109e5b:	48 bf e8 d5 16 00 00 	movabs $0x16d5e8,%rdi
  109e62:	00 00 00
  109e65:	e8 96 66 ff ff       	call   100500 <_ZN4acos7storage14AHCIController10initializeEv>
  109e6a:	a8 01                	test   $0x1,%al
  109e6c:	0f 85 05 00 00 00    	jne    109e77 <kernelMain+0x277>
  109e72:	e9 87 00 00 00       	jmp    109efe <kernelMain+0x2fe>
  109e77:	c7 45 ac 00 00 00 00 	movl   $0x0,-0x54(%rbp)
  109e7e:	8b 45 ac             	mov    -0x54(%rbp),%eax
  109e81:	89 85 10 ee ff ff    	mov    %eax,-0x11f0(%rbp)
  109e87:	48 bf e8 d5 16 00 00 	movabs $0x16d5e8,%rdi
  109e8e:	00 00 00
  109e91:	e8 0a 4e 00 00       	call   10eca0 <_ZNK4acos7storage14AHCIController10port_countEv>
  109e96:	89 c1                	mov    %eax,%ecx
  109e98:	8b 85 10 ee ff ff    	mov    -0x11f0(%rbp),%eax
  109e9e:	39 c8                	cmp    %ecx,%eax
  109ea0:	0f 83 53 00 00 00    	jae    109ef9 <kernelMain+0x2f9>
  109ea6:	8b 45 ac             	mov    -0x54(%rbp),%eax
  109ea9:	48 89 85 08 ee ff ff 	mov    %rax,-0x11f8(%rbp)
  109eb0:	8b 75 ac             	mov    -0x54(%rbp),%esi
  109eb3:	48 bf e8 d5 16 00 00 	movabs $0x16d5e8,%rdi
  109eba:	00 00 00
  109ebd:	e8 fe 4d 00 00       	call   10ecc0 <_ZNK4acos7storage14AHCIController8get_portEj>
  109ec2:	48 8b bd 08 ee ff ff 	mov    -0x11f8(%rbp),%rdi
  109ec9:	48 89 c6             	mov    %rax,%rsi
  109ecc:	e8 ef 8c ff ff       	call   102bc0 <_ZN4acos7storage14StorageManager15register_deviceEmPNS0_11BlockDeviceE>
  109ed1:	8b 75 ac             	mov    -0x54(%rbp),%esi
  109ed4:	48 bf e8 d5 16 00 00 	movabs $0x16d5e8,%rdi
  109edb:	00 00 00
  109ede:	e8 dd 4d 00 00       	call   10ecc0 <_ZNK4acos7storage14AHCIController8get_portEj>
  109ee3:	48 89 c7             	mov    %rax,%rdi
  109ee6:	e8 45 6d ff ff       	call   100c30 <_ZN4acos7storage16PartitionManager9enumerateEPNS0_11BlockDeviceE>
  109eeb:	8b 45 ac             	mov    -0x54(%rbp),%eax
  109eee:	83 c0 01             	add    $0x1,%eax
  109ef1:	89 45 ac             	mov    %eax,-0x54(%rbp)
  109ef4:	e9 85 ff ff ff       	jmp    109e7e <kernelMain+0x27e>
  109ef9:	e9 00 00 00 00       	jmp    109efe <kernelMain+0x2fe>
  109efe:	e9 00 00 00 00       	jmp    109f03 <kernelMain+0x303>
  109f03:	be 01 00 00 00       	mov    $0x1,%esi
  109f08:	48 89 f7             	mov    %rsi,%rdi
  109f0b:	e8 e0 96 ff ff       	call   1035f0 <_ZN4acos8services14ServiceManager16register_serviceENS0_9ServiceIdEm>
  109f10:	bf 03 00 00 00       	mov    $0x3,%edi
  109f15:	be 02 00 00 00       	mov    $0x2,%esi
  109f1a:	e8 d1 96 ff ff       	call   1035f0 <_ZN4acos8services14ServiceManager16register_serviceENS0_9ServiceIdEm>
  109f1f:	bf 04 00 00 00       	mov    $0x4,%edi
  109f24:	be 03 00 00 00       	mov    $0x3,%esi
  109f29:	e8 c2 96 ff ff       	call   1035f0 <_ZN4acos8services14ServiceManager16register_serviceENS0_9ServiceIdEm>
  109f2e:	f6 45 f7 01          	testb  $0x1,-0x9(%rbp)
  109f32:	0f 84 0d 00 00 00    	je     109f45 <kernelMain+0x345>
  109f38:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  109f3c:	48 8b 78 10          	mov    0x10(%rax),%rdi
  109f40:	e8 1b 12 00 00       	call   10b160 <_ZN4acos8graphics15GraphicsManager4initEPNS_15FramebufferInfoE>
  109f45:	e8 26 3c 00 00       	call   10db70 <_ZN4acos5audio12AudioManager4initEv>
  109f4a:	48 bf f6 f9 10 00 00 	movabs $0x10f9f6,%rdi
  109f51:	00 00 00
  109f54:	e8 37 05 00 00       	call   10a490 <_ZN4acos3hal12serial_printEPKc>
  109f59:	48 8d b5 20 ee ff ff 	lea    -0x11e0(%rbp),%rsi
  109f60:	48 bf b0 f8 10 00 00 	movabs $0x10f8b0,%rdi
  109f67:	00 00 00
  109f6a:	ba 10 00 00 00       	mov    $0x10,%edx
  109f6f:	e8 8c f1 ff ff       	call   109100 <_ZN4acos3vfs3VFS8read_dirEPKcPNS0_14DirectoryEntryEm>
  109f74:	89 85 1c ee ff ff    	mov    %eax,-0x11e4(%rbp)
  109f7a:	83 bd 1c ee ff ff 00 	cmpl   $0x0,-0x11e4(%rbp)
  109f81:	0f 8c 7f 00 00 00    	jl     10a006 <kernelMain+0x406>
  109f87:	48 bf 12 fa 10 00 00 	movabs $0x10fa12,%rdi
  109f8e:	00 00 00
  109f91:	e8 fa 04 00 00       	call   10a490 <_ZN4acos3hal12serial_printEPKc>
  109f96:	c7 85 18 ee ff ff 00 	movl   $0x0,-0x11e8(%rbp)
  109f9d:	00 00 00
  109fa0:	8b 85 18 ee ff ff    	mov    -0x11e8(%rbp),%eax
  109fa6:	3b 85 1c ee ff ff    	cmp    -0x11e4(%rbp),%eax
  109fac:	0f 8d 4f 00 00 00    	jge    10a001 <kernelMain+0x401>
  109fb2:	48 bf 2c fa 10 00 00 	movabs $0x10fa2c,%rdi
  109fb9:	00 00 00
  109fbc:	e8 cf 04 00 00       	call   10a490 <_ZN4acos3hal12serial_printEPKc>
  109fc1:	48 63 85 18 ee ff ff 	movslq -0x11e8(%rbp),%rax
  109fc8:	48 8d bd 20 ee ff ff 	lea    -0x11e0(%rbp),%rdi
  109fcf:	48 69 c0 18 01 00 00 	imul   $0x118,%rax,%rax
  109fd6:	48 01 c7             	add    %rax,%rdi
  109fd9:	e8 b2 04 00 00       	call   10a490 <_ZN4acos3hal12serial_printEPKc>
  109fde:	48 bf 04 f9 10 00 00 	movabs $0x10f904,%rdi
  109fe5:	00 00 00
  109fe8:	e8 a3 04 00 00       	call   10a490 <_ZN4acos3hal12serial_printEPKc>
  109fed:	8b 85 18 ee ff ff    	mov    -0x11e8(%rbp),%eax
  109ff3:	83 c0 01             	add    $0x1,%eax
  109ff6:	89 85 18 ee ff ff    	mov    %eax,-0x11e8(%rbp)
  109ffc:	e9 9f ff ff ff       	jmp    109fa0 <kernelMain+0x3a0>
  10a001:	e9 0f 00 00 00       	jmp    10a015 <kernelMain+0x415>
  10a006:	48 bf 2f fa 10 00 00 	movabs $0x10fa2f,%rdi
  10a00d:	00 00 00
  10a010:	e8 7b 04 00 00       	call   10a490 <_ZN4acos3hal12serial_printEPKc>
  10a015:	8a 04 25 c0 f4 10 00 	mov    0x10f4c0,%al
  10a01c:	88 85 17 ee ff ff    	mov    %al,-0x11e9(%rbp)
  10a022:	48 8d bd 17 ee ff ff 	lea    -0x11e9(%rbp),%rdi
  10a029:	48 be 4e fa 10 00 00 	movabs $0x10fa4e,%rsi
  10a030:	00 00 00
  10a033:	e8 18 01 00 00       	call   10a150 <_ZZ10kernelMainENK3$_0clEPKc>
  10a038:	f6 45 f7 01          	testb  $0x1,-0x9(%rbp)
  10a03c:	0f 84 84 00 00 00    	je     10a0c6 <kernelMain+0x4c6>
  10a042:	48 8d bd 17 ee ff ff 	lea    -0x11e9(%rbp),%rdi
  10a049:	48 be 5c fa 10 00 00 	movabs $0x10fa5c,%rsi
  10a050:	00 00 00
  10a053:	e8 f8 00 00 00       	call   10a150 <_ZZ10kernelMainENK3$_0clEPKc>
  10a058:	48 8d bd 17 ee ff ff 	lea    -0x11e9(%rbp),%rdi
  10a05f:	48 be 6d fa 10 00 00 	movabs $0x10fa6d,%rsi
  10a066:	00 00 00
  10a069:	e8 e2 00 00 00       	call   10a150 <_ZZ10kernelMainENK3$_0clEPKc>
  10a06e:	48 8d bd 17 ee ff ff 	lea    -0x11e9(%rbp),%rdi
  10a075:	48 be 7b fa 10 00 00 	movabs $0x10fa7b,%rsi
  10a07c:	00 00 00
  10a07f:	e8 cc 00 00 00       	call   10a150 <_ZZ10kernelMainENK3$_0clEPKc>
  10a084:	48 8d bd 17 ee ff ff 	lea    -0x11e9(%rbp),%rdi
  10a08b:	48 be 88 fa 10 00 00 	movabs $0x10fa88,%rsi
  10a092:	00 00 00
  10a095:	e8 b6 00 00 00       	call   10a150 <_ZZ10kernelMainENK3$_0clEPKc>
  10a09a:	48 8d bd 17 ee ff ff 	lea    -0x11e9(%rbp),%rdi
  10a0a1:	48 be 96 fa 10 00 00 	movabs $0x10fa96,%rsi
  10a0a8:	00 00 00
  10a0ab:	e8 a0 00 00 00       	call   10a150 <_ZZ10kernelMainENK3$_0clEPKc>
  10a0b0:	48 8d bd 17 ee ff ff 	lea    -0x11e9(%rbp),%rdi
  10a0b7:	48 be a5 fa 10 00 00 	movabs $0x10faa5,%rsi
  10a0be:	00 00 00
  10a0c1:	e8 8a 00 00 00       	call   10a150 <_ZZ10kernelMainENK3$_0clEPKc>
  10a0c6:	48 8d bd 17 ee ff ff 	lea    -0x11e9(%rbp),%rdi
  10a0cd:	48 be b6 fa 10 00 00 	movabs $0x10fab6,%rsi
  10a0d4:	00 00 00
  10a0d7:	e8 74 00 00 00       	call   10a150 <_ZZ10kernelMainENK3$_0clEPKc>
  10a0dc:	c7 04 25 60 9a 16 00 	movl   $0x1,0x169a60
  10a0e3:	01 00 00 00
  10a0e7:	31 ff                	xor    %edi,%edi
  10a0e9:	48 be 48 9a 16 00 00 	movabs $0x169a48,%rsi
  10a0f0:	00 00 00
  10a0f3:	e8 e8 c4 ff ff       	call   1065e0 <_ZN4acos9scheduler14enqueue_threadEjPNS0_6ThreadE>
  10a0f8:	e8 03 c6 ff ff       	call   106700 <_ZN4acos9scheduler8scheduleEv>
  10a0fd:	e8 6e 01 00 00       	call   10a270 <_ZL7poll_iov>
  10a102:	e8 f9 c5 ff ff       	call   106700 <_ZN4acos9scheduler8scheduleEv>
  10a107:	f4                   	hlt
  10a108:	e9 f0 ff ff ff       	jmp    10a0fd <kernelMain+0x4fd>
  10a10d:	0f 1f 00             	nopl   (%rax)

000000000010a110 <__cxa_guard_acquire>:
  10a110:	48 89 7c 24 f8       	mov    %rdi,-0x8(%rsp)
  10a115:	48 8b 44 24 f8       	mov    -0x8(%rsp),%rax
  10a11a:	48 83 38 00          	cmpq   $0x0,(%rax)
  10a11e:	0f 94 c0             	sete   %al
  10a121:	24 01                	and    $0x1,%al
  10a123:	0f b6 c0             	movzbl %al,%eax
  10a126:	c3                   	ret
  10a127:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
  10a12e:	00 00

000000000010a130 <__cxa_guard_release>:
  10a130:	48 89 7c 24 f8       	mov    %rdi,-0x8(%rsp)
  10a135:	48 8b 44 24 f8       	mov    -0x8(%rsp),%rax
  10a13a:	48 c7 00 01 00 00 00 	movq   $0x1,(%rax)
  10a141:	c3                   	ret
  10a142:	66 66 66 66 66 2e 0f 	data16 data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
  10a149:	1f 84 00 00 00 00 00

000000000010a150 <_ZZ10kernelMainENK3$_0clEPKc>:
  10a150:	55                   	push   %rbp
  10a151:	48 89 e5             	mov    %rsp,%rbp
  10a154:	48 83 ec 40          	sub    $0x40,%rsp
  10a158:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10a15c:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  10a160:	48 bf c3 fa 10 00 00 	movabs $0x10fac3,%rdi
  10a167:	00 00 00
  10a16a:	e8 21 03 00 00       	call   10a490 <_ZN4acos3hal12serial_printEPKc>
  10a16f:	48 8b 7d f0          	mov    -0x10(%rbp),%rdi
  10a173:	e8 18 03 00 00       	call   10a490 <_ZN4acos3hal12serial_printEPKc>
  10a178:	48 bf 04 f9 10 00 00 	movabs $0x10f904,%rdi
  10a17f:	00 00 00
  10a182:	e8 09 03 00 00       	call   10a490 <_ZN4acos3hal12serial_printEPKc>
  10a187:	48 8b 7d f0          	mov    -0x10(%rbp),%rdi
  10a18b:	31 c0                	xor    %eax,%eax
  10a18d:	89 c6                	mov    %eax,%esi
  10a18f:	e8 4c ec ff ff       	call   108de0 <_ZN4acos3vfs3VFS4openEPKcm>
  10a194:	89 45 ec             	mov    %eax,-0x14(%rbp)
  10a197:	83 7d ec 00          	cmpl   $0x0,-0x14(%rbp)
  10a19b:	0f 8d 14 00 00 00    	jge    10a1b5 <_ZZ10kernelMainENK3$_0clEPKc+0x65>
  10a1a1:	48 bf d3 fa 10 00 00 	movabs $0x10fad3,%rdi
  10a1a8:	00 00 00
  10a1ab:	e8 e0 02 00 00       	call   10a490 <_ZN4acos3hal12serial_printEPKc>
  10a1b0:	e9 ad 00 00 00       	jmp    10a262 <_ZZ10kernelMainENK3$_0clEPKc+0x112>
  10a1b5:	e8 46 c7 ff ff       	call   106900 <_ZN4acos9scheduler14current_threadEv>
  10a1ba:	48 8b 78 20          	mov    0x20(%rax),%rdi
  10a1be:	8b 75 ec             	mov    -0x14(%rbp),%esi
  10a1c1:	e8 1a be ff ff       	call   105fe0 <_ZN4acos9scheduler7Process8get_fileEi>
  10a1c6:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  10a1ca:	48 83 7d e0 00       	cmpq   $0x0,-0x20(%rbp)
  10a1cf:	0f 85 0e 00 00 00    	jne    10a1e3 <_ZZ10kernelMainENK3$_0clEPKc+0x93>
  10a1d5:	48 63 7d ec          	movslq -0x14(%rbp),%rdi
  10a1d9:	e8 72 ed ff ff       	call   108f50 <_ZN4acos3vfs3VFS5closeEm>
  10a1de:	e9 7f 00 00 00       	jmp    10a262 <_ZZ10kernelMainENK3$_0clEPKc+0x112>
  10a1e3:	48 8b 7d e0          	mov    -0x20(%rbp),%rdi
  10a1e7:	e8 f4 f2 ff ff       	call   1094e0 <_ZNK4acos3vfs4File4sizeEv>
  10a1ec:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
  10a1f0:	48 8b 7d d8          	mov    -0x28(%rbp),%rdi
  10a1f4:	e8 57 e5 ff ff       	call   108750 <_ZN4acos6memory7kmallocEm>
  10a1f9:	48 89 45 d0          	mov    %rax,-0x30(%rbp)
  10a1fd:	48 8b 7d e0          	mov    -0x20(%rbp),%rdi
  10a201:	48 8b 75 d0          	mov    -0x30(%rbp),%rsi
  10a205:	48 8b 55 d8          	mov    -0x28(%rbp),%rdx
  10a209:	e8 a2 f1 ff ff       	call   1093b0 <_ZN4acos3vfs4File4readEPvm>
  10a20e:	48 63 7d ec          	movslq -0x14(%rbp),%rdi
  10a212:	e8 39 ed ff ff       	call   108f50 <_ZN4acos3vfs3VFS5closeEm>
  10a217:	48 8b 7d f0          	mov    -0x10(%rbp),%rdi
  10a21b:	48 8b 75 d0          	mov    -0x30(%rbp),%rsi
  10a21f:	48 8b 55 d8          	mov    -0x28(%rbp),%rdx
  10a223:	e8 c8 8a ff ff       	call   102cf0 <_ZN4acos6loader23create_process_from_elfEPKcPKvm>
  10a228:	48 89 45 c8          	mov    %rax,-0x38(%rbp)
  10a22c:	48 8b 7d d0          	mov    -0x30(%rbp),%rdi
  10a230:	e8 eb e5 ff ff       	call   108820 <_ZN4acos6memory5kfreeEPv>
  10a235:	48 83 7d c8 00       	cmpq   $0x0,-0x38(%rbp)
  10a23a:	0f 84 22 00 00 00    	je     10a262 <_ZZ10kernelMainENK3$_0clEPKc+0x112>
  10a240:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  10a244:	48 83 b8 10 3b 00 00 	cmpq   $0x0,0x3b10(%rax)
  10a24b:	00
  10a24c:	0f 84 10 00 00 00    	je     10a262 <_ZZ10kernelMainENK3$_0clEPKc+0x112>
  10a252:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  10a256:	48 8b b8 10 3b 00 00 	mov    0x3b10(%rax),%rdi
  10a25d:	e8 ae c6 ff ff       	call   106910 <_ZN4acos9scheduler11wake_threadEPNS0_6ThreadE>
  10a262:	48 83 c4 40          	add    $0x40,%rsp
  10a266:	5d                   	pop    %rbp
  10a267:	c3                   	ret
  10a268:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  10a26f:	00

000000000010a270 <_ZL7poll_iov>:
  10a270:	55                   	push   %rbp
  10a271:	48 89 e5             	mov    %rsp,%rbp
  10a274:	48 83 ec 10          	sub    $0x10,%rsp
  10a278:	e8 b3 c2 ff ff       	call   106530 <_ZN4acos9scheduler19get_console_blockedEv>
  10a27d:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  10a281:	48 83 7d f8 00       	cmpq   $0x0,-0x8(%rbp)
  10a286:	0f 84 1b 00 00 00    	je     10a2a7 <_ZL7poll_iov+0x37>
  10a28c:	e8 ef 00 00 00       	call   10a380 <_ZN4acos3hal15serial_receivedEv>
  10a291:	a8 01                	test   $0x1,%al
  10a293:	0f 85 05 00 00 00    	jne    10a29e <_ZL7poll_iov+0x2e>
  10a299:	e9 09 00 00 00       	jmp    10a2a7 <_ZL7poll_iov+0x37>
  10a29e:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  10a2a2:	e8 69 c6 ff ff       	call   106910 <_ZN4acos9scheduler11wake_threadEPNS0_6ThreadE>
  10a2a7:	48 83 c4 10          	add    $0x10,%rsp
  10a2ab:	5d                   	pop    %rbp
  10a2ac:	c3                   	ret
  10a2ad:	0f 1f 00             	nopl   (%rax)

000000000010a2b0 <__cxa_atexit>:
  10a2b0:	55                   	push   %rbp
  10a2b1:	48 89 e5             	mov    %rsp,%rbp
  10a2b4:	48 83 ec 18          	sub    $0x18,%rsp
  10a2b8:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10a2bc:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  10a2c0:	48 89 55 e8          	mov    %rdx,-0x18(%rbp)
  10a2c4:	31 c0                	xor    %eax,%eax
  10a2c6:	48 83 c4 18          	add    $0x18,%rsp
  10a2ca:	5d                   	pop    %rbp
  10a2cb:	c3                   	ret
  10a2cc:	0f 1f 40 00          	nopl   0x0(%rax)

000000000010a2d0 <__cxa_guard_abort>:
  10a2d0:	55                   	push   %rbp
  10a2d1:	48 89 e5             	mov    %rsp,%rbp
  10a2d4:	50                   	push   %rax
  10a2d5:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10a2d9:	48 83 c4 08          	add    $0x8,%rsp
  10a2dd:	5d                   	pop    %rbp
  10a2de:	c3                   	ret
  10a2df:	90                   	nop

000000000010a2e0 <_ZN4acos3hal11serial_initEv>:
  10a2e0:	55                   	push   %rbp
  10a2e1:	48 89 e5             	mov    %rsp,%rbp
  10a2e4:	bf f9 03 00 00       	mov    $0x3f9,%edi
  10a2e9:	31 f6                	xor    %esi,%esi
  10a2eb:	e8 60 00 00 00       	call   10a350 <_ZN4acos3halL4outbEth>
  10a2f0:	bf fb 03 00 00       	mov    $0x3fb,%edi
  10a2f5:	be 80 00 00 00       	mov    $0x80,%esi
  10a2fa:	e8 51 00 00 00       	call   10a350 <_ZN4acos3halL4outbEth>
  10a2ff:	bf f8 03 00 00       	mov    $0x3f8,%edi
  10a304:	be 03 00 00 00       	mov    $0x3,%esi
  10a309:	e8 42 00 00 00       	call   10a350 <_ZN4acos3halL4outbEth>
  10a30e:	bf f9 03 00 00       	mov    $0x3f9,%edi
  10a313:	31 f6                	xor    %esi,%esi
  10a315:	e8 36 00 00 00       	call   10a350 <_ZN4acos3halL4outbEth>
  10a31a:	bf fb 03 00 00       	mov    $0x3fb,%edi
  10a31f:	be 03 00 00 00       	mov    $0x3,%esi
  10a324:	e8 27 00 00 00       	call   10a350 <_ZN4acos3halL4outbEth>
  10a329:	bf fa 03 00 00       	mov    $0x3fa,%edi
  10a32e:	be c7 00 00 00       	mov    $0xc7,%esi
  10a333:	e8 18 00 00 00       	call   10a350 <_ZN4acos3halL4outbEth>
  10a338:	bf fc 03 00 00       	mov    $0x3fc,%edi
  10a33d:	be 0b 00 00 00       	mov    $0xb,%esi
  10a342:	e8 09 00 00 00       	call   10a350 <_ZN4acos3halL4outbEth>
  10a347:	5d                   	pop    %rbp
  10a348:	c3                   	ret
  10a349:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

000000000010a350 <_ZN4acos3halL4outbEth>:
  10a350:	55                   	push   %rbp
  10a351:	48 89 e5             	mov    %rsp,%rbp
  10a354:	48 83 ec 04          	sub    $0x4,%rsp
  10a358:	40 88 f0             	mov    %sil,%al
  10a35b:	66 89 f9             	mov    %di,%cx
  10a35e:	66 89 4d fe          	mov    %cx,-0x2(%rbp)
  10a362:	88 45 fd             	mov    %al,-0x3(%rbp)
  10a365:	8a 45 fd             	mov    -0x3(%rbp),%al
  10a368:	66 8b 55 fe          	mov    -0x2(%rbp),%dx
  10a36c:	ee                   	out    %al,(%dx)
  10a36d:	48 83 c4 04          	add    $0x4,%rsp
  10a371:	5d                   	pop    %rbp
  10a372:	c3                   	ret
  10a373:	66 66 66 66 2e 0f 1f 	data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
  10a37a:	84 00 00 00 00 00

000000000010a380 <_ZN4acos3hal15serial_receivedEv>:
  10a380:	55                   	push   %rbp
  10a381:	48 89 e5             	mov    %rsp,%rbp
  10a384:	bf fd 03 00 00       	mov    $0x3fd,%edi
  10a389:	e8 22 00 00 00       	call   10a3b0 <_ZN4acos3halL3inbEt>
  10a38e:	0f b6 c0             	movzbl %al,%eax
  10a391:	83 e0 01             	and    $0x1,%eax
  10a394:	83 f8 00             	cmp    $0x0,%eax
  10a397:	0f 95 c0             	setne  %al
  10a39a:	24 01                	and    $0x1,%al
  10a39c:	0f b6 c0             	movzbl %al,%eax
  10a39f:	5d                   	pop    %rbp
  10a3a0:	c3                   	ret
  10a3a1:	66 66 66 66 66 66 2e 	data16 data16 data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
  10a3a8:	0f 1f 84 00 00 00 00
  10a3af:	00

000000000010a3b0 <_ZN4acos3halL3inbEt>:
  10a3b0:	55                   	push   %rbp
  10a3b1:	48 89 e5             	mov    %rsp,%rbp
  10a3b4:	48 83 ec 04          	sub    $0x4,%rsp
  10a3b8:	66 89 f8             	mov    %di,%ax
  10a3bb:	66 89 45 fe          	mov    %ax,-0x2(%rbp)
  10a3bf:	66 8b 55 fe          	mov    -0x2(%rbp),%dx
  10a3c3:	ec                   	in     (%dx),%al
  10a3c4:	88 45 fd             	mov    %al,-0x3(%rbp)
  10a3c7:	0f b6 45 fd          	movzbl -0x3(%rbp),%eax
  10a3cb:	48 83 c4 04          	add    $0x4,%rsp
  10a3cf:	5d                   	pop    %rbp
  10a3d0:	c3                   	ret
  10a3d1:	66 66 66 66 66 66 2e 	data16 data16 data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
  10a3d8:	0f 1f 84 00 00 00 00
  10a3df:	00

000000000010a3e0 <_ZN4acos3hal11serial_readEv>:
  10a3e0:	55                   	push   %rbp
  10a3e1:	48 89 e5             	mov    %rsp,%rbp
  10a3e4:	e9 00 00 00 00       	jmp    10a3e9 <_ZN4acos3hal11serial_readEv+0x9>
  10a3e9:	e8 92 ff ff ff       	call   10a380 <_ZN4acos3hal15serial_receivedEv>
  10a3ee:	34 ff                	xor    $0xff,%al
  10a3f0:	a8 01                	test   $0x1,%al
  10a3f2:	0f 85 05 00 00 00    	jne    10a3fd <_ZN4acos3hal11serial_readEv+0x1d>
  10a3f8:	e9 05 00 00 00       	jmp    10a402 <_ZN4acos3hal11serial_readEv+0x22>
  10a3fd:	e9 e7 ff ff ff       	jmp    10a3e9 <_ZN4acos3hal11serial_readEv+0x9>
  10a402:	bf f8 03 00 00       	mov    $0x3f8,%edi
  10a407:	e8 a4 ff ff ff       	call   10a3b0 <_ZN4acos3halL3inbEt>
  10a40c:	0f be c0             	movsbl %al,%eax
  10a40f:	5d                   	pop    %rbp
  10a410:	c3                   	ret
  10a411:	66 66 66 66 66 66 2e 	data16 data16 data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
  10a418:	0f 1f 84 00 00 00 00
  10a41f:	00

000000000010a420 <_ZN4acos3hal17is_transmit_emptyEv>:
  10a420:	55                   	push   %rbp
  10a421:	48 89 e5             	mov    %rsp,%rbp
  10a424:	bf fd 03 00 00       	mov    $0x3fd,%edi
  10a429:	e8 82 ff ff ff       	call   10a3b0 <_ZN4acos3halL3inbEt>
  10a42e:	0f b6 c0             	movzbl %al,%eax
  10a431:	83 e0 20             	and    $0x20,%eax
  10a434:	83 f8 00             	cmp    $0x0,%eax
  10a437:	0f 95 c0             	setne  %al
  10a43a:	24 01                	and    $0x1,%al
  10a43c:	0f b6 c0             	movzbl %al,%eax
  10a43f:	5d                   	pop    %rbp
  10a440:	c3                   	ret
  10a441:	66 66 66 66 66 66 2e 	data16 data16 data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
  10a448:	0f 1f 84 00 00 00 00
  10a44f:	00

000000000010a450 <_ZN4acos3hal12serial_writeEc>:
  10a450:	55                   	push   %rbp
  10a451:	48 89 e5             	mov    %rsp,%rbp
  10a454:	48 83 ec 10          	sub    $0x10,%rsp
  10a458:	40 88 f8             	mov    %dil,%al
  10a45b:	88 45 ff             	mov    %al,-0x1(%rbp)
  10a45e:	e8 bd ff ff ff       	call   10a420 <_ZN4acos3hal17is_transmit_emptyEv>
  10a463:	34 ff                	xor    $0xff,%al
  10a465:	a8 01                	test   $0x1,%al
  10a467:	0f 85 05 00 00 00    	jne    10a472 <_ZN4acos3hal12serial_writeEc+0x22>
  10a46d:	e9 05 00 00 00       	jmp    10a477 <_ZN4acos3hal12serial_writeEc+0x27>
  10a472:	e9 e7 ff ff ff       	jmp    10a45e <_ZN4acos3hal12serial_writeEc+0xe>
  10a477:	bf f8 03 00 00       	mov    $0x3f8,%edi
  10a47c:	0f b6 75 ff          	movzbl -0x1(%rbp),%esi
  10a480:	e8 cb fe ff ff       	call   10a350 <_ZN4acos3halL4outbEth>
  10a485:	48 83 c4 10          	add    $0x10,%rsp
  10a489:	5d                   	pop    %rbp
  10a48a:	c3                   	ret
  10a48b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

000000000010a490 <_ZN4acos3hal12serial_printEPKc>:
  10a490:	55                   	push   %rbp
  10a491:	48 89 e5             	mov    %rsp,%rbp
  10a494:	48 83 ec 10          	sub    $0x10,%rsp
  10a498:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10a49c:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10a4a0:	80 38 00             	cmpb   $0x0,(%rax)
  10a4a3:	0f 84 1c 00 00 00    	je     10a4c5 <_ZN4acos3hal12serial_printEPKc+0x35>
  10a4a9:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10a4ad:	48 89 c1             	mov    %rax,%rcx
  10a4b0:	48 83 c1 01          	add    $0x1,%rcx
  10a4b4:	48 89 4d f8          	mov    %rcx,-0x8(%rbp)
  10a4b8:	0f be 38             	movsbl (%rax),%edi
  10a4bb:	e8 90 ff ff ff       	call   10a450 <_ZN4acos3hal12serial_writeEc>
  10a4c0:	e9 d7 ff ff ff       	jmp    10a49c <_ZN4acos3hal12serial_printEPKc+0xc>
  10a4c5:	48 83 c4 10          	add    $0x10,%rsp
  10a4c9:	5d                   	pop    %rbp
  10a4ca:	c3                   	ret
  10a4cb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

000000000010a4d0 <_ZN4acos3hal9font_initEv>:
  10a4d0:	55                   	push   %rbp
  10a4d1:	48 89 e5             	mov    %rsp,%rbp
  10a4d4:	50                   	push   %rax
  10a4d5:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%rbp)
  10a4dc:	81 7d fc 80 00 00 00 	cmpl   $0x80,-0x4(%rbp)
  10a4e3:	0f 8d aa 00 00 00    	jge    10a593 <_ZN4acos3hal9font_initEv+0xc3>
  10a4e9:	c7 45 f8 00 00 00 00 	movl   $0x0,-0x8(%rbp)
  10a4f0:	83 7d f8 08          	cmpl   $0x8,-0x8(%rbp)
  10a4f4:	0f 8d 86 00 00 00    	jge    10a580 <_ZN4acos3hal9font_initEv+0xb0>
  10a4fa:	83 7d fc 20          	cmpl   $0x20,-0x4(%rbp)
  10a4fe:	0f 8c 4c 00 00 00    	jl     10a550 <_ZN4acos3hal9font_initEv+0x80>
  10a504:	83 7d fc 7f          	cmpl   $0x7f,-0x4(%rbp)
  10a508:	0f 8d 42 00 00 00    	jge    10a550 <_ZN4acos3hal9font_initEv+0x80>
  10a50e:	8b 45 fc             	mov    -0x4(%rbp),%eax
  10a511:	83 e8 20             	sub    $0x20,%eax
  10a514:	48 63 c8             	movslq %eax,%rcx
  10a517:	48 b8 d0 f4 10 00 00 	movabs $0x10f4d0,%rax
  10a51e:	00 00 00
  10a521:	48 c1 e1 03          	shl    $0x3,%rcx
  10a525:	48 01 c8             	add    %rcx,%rax
  10a528:	48 63 4d f8          	movslq -0x8(%rbp),%rcx
  10a52c:	8a 14 08             	mov    (%rax,%rcx,1),%dl
  10a52f:	48 63 4d fc          	movslq -0x4(%rbp),%rcx
  10a533:	48 b8 10 d7 16 00 00 	movabs $0x16d710,%rax
  10a53a:	00 00 00
  10a53d:	48 c1 e1 03          	shl    $0x3,%rcx
  10a541:	48 01 c8             	add    %rcx,%rax
  10a544:	48 63 4d f8          	movslq -0x8(%rbp),%rcx
  10a548:	88 14 08             	mov    %dl,(%rax,%rcx,1)
  10a54b:	e9 1d 00 00 00       	jmp    10a56d <_ZN4acos3hal9font_initEv+0x9d>
  10a550:	48 63 4d fc          	movslq -0x4(%rbp),%rcx
  10a554:	48 b8 10 d7 16 00 00 	movabs $0x16d710,%rax
  10a55b:	00 00 00
  10a55e:	48 c1 e1 03          	shl    $0x3,%rcx
  10a562:	48 01 c8             	add    %rcx,%rax
  10a565:	48 63 4d f8          	movslq -0x8(%rbp),%rcx
  10a569:	c6 04 08 00          	movb   $0x0,(%rax,%rcx,1)
  10a56d:	e9 00 00 00 00       	jmp    10a572 <_ZN4acos3hal9font_initEv+0xa2>
  10a572:	8b 45 f8             	mov    -0x8(%rbp),%eax
  10a575:	83 c0 01             	add    $0x1,%eax
  10a578:	89 45 f8             	mov    %eax,-0x8(%rbp)
  10a57b:	e9 70 ff ff ff       	jmp    10a4f0 <_ZN4acos3hal9font_initEv+0x20>
  10a580:	e9 00 00 00 00       	jmp    10a585 <_ZN4acos3hal9font_initEv+0xb5>
  10a585:	8b 45 fc             	mov    -0x4(%rbp),%eax
  10a588:	83 c0 01             	add    $0x1,%eax
  10a58b:	89 45 fc             	mov    %eax,-0x4(%rbp)
  10a58e:	e9 49 ff ff ff       	jmp    10a4dc <_ZN4acos3hal9font_initEv+0xc>
  10a593:	48 83 c4 08          	add    $0x8,%rsp
  10a597:	5d                   	pop    %rbp
  10a598:	c3                   	ret
  10a599:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

000000000010a5a0 <_ZN4acos3hal12console_initEPNS_15FramebufferInfoE>:
  10a5a0:	55                   	push   %rbp
  10a5a1:	48 89 e5             	mov    %rsp,%rbp
  10a5a4:	48 83 ec 10          	sub    $0x10,%rsp
  10a5a8:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10a5ac:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10a5b0:	48 89 04 25 10 db 16 	mov    %rax,0x16db10
  10a5b7:	00
  10a5b8:	e8 13 ff ff ff       	call   10a4d0 <_ZN4acos3hal9font_initEv>
  10a5bd:	48 83 c4 10          	add    $0x10,%rsp
  10a5c1:	5d                   	pop    %rbp
  10a5c2:	c3                   	ret
  10a5c3:	66 66 66 66 2e 0f 1f 	data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
  10a5ca:	84 00 00 00 00 00

000000000010a5d0 <_ZN4acos3hal17console_put_pixelEjjj>:
  10a5d0:	55                   	push   %rbp
  10a5d1:	48 89 e5             	mov    %rsp,%rbp
  10a5d4:	48 83 ec 18          	sub    $0x18,%rsp
  10a5d8:	89 7d fc             	mov    %edi,-0x4(%rbp)
  10a5db:	89 75 f8             	mov    %esi,-0x8(%rbp)
  10a5de:	89 55 f4             	mov    %edx,-0xc(%rbp)
  10a5e1:	48 83 3c 25 10 db 16 	cmpq   $0x0,0x16db10
  10a5e8:	00 00
  10a5ea:	0f 85 05 00 00 00    	jne    10a5f5 <_ZN4acos3hal17console_put_pixelEjjj+0x25>
  10a5f0:	e9 2d 00 00 00       	jmp    10a622 <_ZN4acos3hal17console_put_pixelEjjj+0x52>
  10a5f5:	48 8b 04 25 10 db 16 	mov    0x16db10,%rax
  10a5fc:	00
  10a5fd:	48 8b 00             	mov    (%rax),%rax
  10a600:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
  10a604:	8b 55 f4             	mov    -0xc(%rbp),%edx
  10a607:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  10a60b:	8b 4d f8             	mov    -0x8(%rbp),%ecx
  10a60e:	48 8b 34 25 10 db 16 	mov    0x16db10,%rsi
  10a615:	00
  10a616:	0f af 4e 18          	imul   0x18(%rsi),%ecx
  10a61a:	03 4d fc             	add    -0x4(%rbp),%ecx
  10a61d:	89 c9                	mov    %ecx,%ecx
  10a61f:	89 14 88             	mov    %edx,(%rax,%rcx,4)
  10a622:	48 83 c4 18          	add    $0x18,%rsp
  10a626:	5d                   	pop    %rbp
  10a627:	c3                   	ret
  10a628:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  10a62f:	00

000000000010a630 <_ZN4acos3hal15console_putcharEcjjj>:
  10a630:	55                   	push   %rbp
  10a631:	48 89 e5             	mov    %rsp,%rbp
  10a634:	48 83 ec 20          	sub    $0x20,%rsp
  10a638:	40 88 f8             	mov    %dil,%al
  10a63b:	88 45 ff             	mov    %al,-0x1(%rbp)
  10a63e:	89 75 f8             	mov    %esi,-0x8(%rbp)
  10a641:	89 55 f4             	mov    %edx,-0xc(%rbp)
  10a644:	89 4d f0             	mov    %ecx,-0x10(%rbp)
  10a647:	c7 45 ec 00 00 00 00 	movl   $0x0,-0x14(%rbp)
  10a64e:	83 7d ec 08          	cmpl   $0x8,-0x14(%rbp)
  10a652:	0f 8d 81 00 00 00    	jge    10a6d9 <_ZN4acos3hal15console_putcharEcjjj+0xa9>
  10a658:	c7 45 e8 00 00 00 00 	movl   $0x0,-0x18(%rbp)
  10a65f:	83 7d e8 08          	cmpl   $0x8,-0x18(%rbp)
  10a663:	0f 8d 5d 00 00 00    	jge    10a6c6 <_ZN4acos3hal15console_putcharEcjjj+0x96>
  10a669:	0f b6 45 ff          	movzbl -0x1(%rbp),%eax
  10a66d:	89 c1                	mov    %eax,%ecx
  10a66f:	48 b8 10 d7 16 00 00 	movabs $0x16d710,%rax
  10a676:	00 00 00
  10a679:	48 c1 e1 03          	shl    $0x3,%rcx
  10a67d:	48 01 c8             	add    %rcx,%rax
  10a680:	48 63 4d ec          	movslq -0x14(%rbp),%rcx
  10a684:	0f b6 04 08          	movzbl (%rax,%rcx,1),%eax
  10a688:	8b 4d e8             	mov    -0x18(%rbp),%ecx
  10a68b:	ba 01 00 00 00       	mov    $0x1,%edx
  10a690:	d3 e2                	shl    %cl,%edx
  10a692:	89 d1                	mov    %edx,%ecx
  10a694:	21 c8                	and    %ecx,%eax
  10a696:	83 f8 00             	cmp    $0x0,%eax
  10a699:	0f 84 14 00 00 00    	je     10a6b3 <_ZN4acos3hal15console_putcharEcjjj+0x83>
  10a69f:	8b 7d f8             	mov    -0x8(%rbp),%edi
  10a6a2:	03 7d e8             	add    -0x18(%rbp),%edi
  10a6a5:	8b 75 f4             	mov    -0xc(%rbp),%esi
  10a6a8:	03 75 ec             	add    -0x14(%rbp),%esi
  10a6ab:	8b 55 f0             	mov    -0x10(%rbp),%edx
  10a6ae:	e8 1d ff ff ff       	call   10a5d0 <_ZN4acos3hal17console_put_pixelEjjj>
  10a6b3:	e9 00 00 00 00       	jmp    10a6b8 <_ZN4acos3hal15console_putcharEcjjj+0x88>
  10a6b8:	8b 45 e8             	mov    -0x18(%rbp),%eax
  10a6bb:	83 c0 01             	add    $0x1,%eax
  10a6be:	89 45 e8             	mov    %eax,-0x18(%rbp)
  10a6c1:	e9 99 ff ff ff       	jmp    10a65f <_ZN4acos3hal15console_putcharEcjjj+0x2f>
  10a6c6:	e9 00 00 00 00       	jmp    10a6cb <_ZN4acos3hal15console_putcharEcjjj+0x9b>
  10a6cb:	8b 45 ec             	mov    -0x14(%rbp),%eax
  10a6ce:	83 c0 01             	add    $0x1,%eax
  10a6d1:	89 45 ec             	mov    %eax,-0x14(%rbp)
  10a6d4:	e9 75 ff ff ff       	jmp    10a64e <_ZN4acos3hal15console_putcharEcjjj+0x1e>
  10a6d9:	48 83 c4 20          	add    $0x20,%rsp
  10a6dd:	5d                   	pop    %rbp
  10a6de:	c3                   	ret
  10a6df:	90                   	nop

000000000010a6e0 <_ZN4acos3hal13console_clearEj>:
  10a6e0:	55                   	push   %rbp
  10a6e1:	48 89 e5             	mov    %rsp,%rbp
  10a6e4:	48 83 ec 18          	sub    $0x18,%rsp
  10a6e8:	89 7d fc             	mov    %edi,-0x4(%rbp)
  10a6eb:	48 83 3c 25 10 db 16 	cmpq   $0x0,0x16db10
  10a6f2:	00 00
  10a6f4:	0f 85 05 00 00 00    	jne    10a6ff <_ZN4acos3hal13console_clearEj+0x1f>
  10a6fa:	e9 84 00 00 00       	jmp    10a783 <_ZN4acos3hal13console_clearEj+0xa3>
  10a6ff:	48 8b 04 25 10 db 16 	mov    0x16db10,%rax
  10a706:	00
  10a707:	48 8b 00             	mov    (%rax),%rax
  10a70a:	48 89 45 f0          	mov    %rax,-0x10(%rbp)
  10a70e:	c7 45 ec 00 00 00 00 	movl   $0x0,-0x14(%rbp)
  10a715:	8b 45 ec             	mov    -0x14(%rbp),%eax
  10a718:	48 8b 0c 25 10 db 16 	mov    0x16db10,%rcx
  10a71f:	00
  10a720:	3b 41 14             	cmp    0x14(%rcx),%eax
  10a723:	0f 83 5a 00 00 00    	jae    10a783 <_ZN4acos3hal13console_clearEj+0xa3>
  10a729:	c7 45 e8 00 00 00 00 	movl   $0x0,-0x18(%rbp)
  10a730:	8b 45 e8             	mov    -0x18(%rbp),%eax
  10a733:	48 8b 0c 25 10 db 16 	mov    0x16db10,%rcx
  10a73a:	00
  10a73b:	3b 41 10             	cmp    0x10(%rcx),%eax
  10a73e:	0f 83 2c 00 00 00    	jae    10a770 <_ZN4acos3hal13console_clearEj+0x90>
  10a744:	8b 55 fc             	mov    -0x4(%rbp),%edx
  10a747:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10a74b:	8b 4d ec             	mov    -0x14(%rbp),%ecx
  10a74e:	48 8b 34 25 10 db 16 	mov    0x16db10,%rsi
  10a755:	00
  10a756:	0f af 4e 18          	imul   0x18(%rsi),%ecx
  10a75a:	03 4d e8             	add    -0x18(%rbp),%ecx
  10a75d:	89 c9                	mov    %ecx,%ecx
  10a75f:	89 14 88             	mov    %edx,(%rax,%rcx,4)
  10a762:	8b 45 e8             	mov    -0x18(%rbp),%eax
  10a765:	83 c0 01             	add    $0x1,%eax
  10a768:	89 45 e8             	mov    %eax,-0x18(%rbp)
  10a76b:	e9 c0 ff ff ff       	jmp    10a730 <_ZN4acos3hal13console_clearEj+0x50>
  10a770:	e9 00 00 00 00       	jmp    10a775 <_ZN4acos3hal13console_clearEj+0x95>
  10a775:	8b 45 ec             	mov    -0x14(%rbp),%eax
  10a778:	83 c0 01             	add    $0x1,%eax
  10a77b:	89 45 ec             	mov    %eax,-0x14(%rbp)
  10a77e:	e9 92 ff ff ff       	jmp    10a715 <_ZN4acos3hal13console_clearEj+0x35>
  10a783:	48 83 c4 18          	add    $0x18,%rsp
  10a787:	5d                   	pop    %rbp
  10a788:	c3                   	ret
  10a789:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

000000000010a790 <_ZN4acos3hal13console_printEPKcj>:
  10a790:	55                   	push   %rbp
  10a791:	48 89 e5             	mov    %rsp,%rbp
  10a794:	48 83 ec 10          	sub    $0x10,%rsp
  10a798:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10a79c:	89 75 f4             	mov    %esi,-0xc(%rbp)
  10a79f:	48 83 3c 25 10 db 16 	cmpq   $0x0,0x16db10
  10a7a6:	00 00
  10a7a8:	0f 84 0b 00 00 00    	je     10a7b9 <_ZN4acos3hal13console_printEPKcj+0x29>
  10a7ae:	48 83 7d f8 00       	cmpq   $0x0,-0x8(%rbp)
  10a7b3:	0f 85 05 00 00 00    	jne    10a7be <_ZN4acos3hal13console_printEPKcj+0x2e>
  10a7b9:	e9 cf 00 00 00       	jmp    10a88d <_ZN4acos3hal13console_printEPKcj+0xfd>
  10a7be:	e9 00 00 00 00       	jmp    10a7c3 <_ZN4acos3hal13console_printEPKcj+0x33>
  10a7c3:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10a7c7:	80 38 00             	cmpb   $0x0,(%rax)
  10a7ca:	0f 84 bd 00 00 00    	je     10a88d <_ZN4acos3hal13console_printEPKcj+0xfd>
  10a7d0:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10a7d4:	0f be 00             	movsbl (%rax),%eax
  10a7d7:	83 f8 0a             	cmp    $0xa,%eax
  10a7da:	0f 85 21 00 00 00    	jne    10a801 <_ZN4acos3hal13console_printEPKcj+0x71>
  10a7e0:	c7 04 25 18 db 16 00 	movl   $0x0,0x16db18
  10a7e7:	00 00 00 00
  10a7eb:	8b 04 25 1c db 16 00 	mov    0x16db1c,%eax
  10a7f2:	83 c0 0a             	add    $0xa,%eax
  10a7f5:	89 04 25 1c db 16 00 	mov    %eax,0x16db1c
  10a7fc:	e9 7b 00 00 00       	jmp    10a87c <_ZN4acos3hal13console_printEPKcj+0xec>
  10a801:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10a805:	8a 00                	mov    (%rax),%al
  10a807:	8b 34 25 18 db 16 00 	mov    0x16db18,%esi
  10a80e:	8b 14 25 1c db 16 00 	mov    0x16db1c,%edx
  10a815:	8b 4d f4             	mov    -0xc(%rbp),%ecx
  10a818:	0f be f8             	movsbl %al,%edi
  10a81b:	e8 10 fe ff ff       	call   10a630 <_ZN4acos3hal15console_putcharEcjjj>
  10a820:	8b 04 25 18 db 16 00 	mov    0x16db18,%eax
  10a827:	83 c0 08             	add    $0x8,%eax
  10a82a:	89 04 25 18 db 16 00 	mov    %eax,0x16db18
  10a831:	48 83 3c 25 10 db 16 	cmpq   $0x0,0x16db10
  10a838:	00 00
  10a83a:	0f 84 37 00 00 00    	je     10a877 <_ZN4acos3hal13console_printEPKcj+0xe7>
  10a840:	8b 04 25 18 db 16 00 	mov    0x16db18,%eax
  10a847:	83 c0 08             	add    $0x8,%eax
  10a84a:	48 8b 0c 25 10 db 16 	mov    0x16db10,%rcx
  10a851:	00
  10a852:	3b 41 10             	cmp    0x10(%rcx),%eax
  10a855:	0f 86 1c 00 00 00    	jbe    10a877 <_ZN4acos3hal13console_printEPKcj+0xe7>
  10a85b:	c7 04 25 18 db 16 00 	movl   $0x0,0x16db18
  10a862:	00 00 00 00
  10a866:	8b 04 25 1c db 16 00 	mov    0x16db1c,%eax
  10a86d:	83 c0 0a             	add    $0xa,%eax
  10a870:	89 04 25 1c db 16 00 	mov    %eax,0x16db1c
  10a877:	e9 00 00 00 00       	jmp    10a87c <_ZN4acos3hal13console_printEPKcj+0xec>
  10a87c:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10a880:	48 83 c0 01          	add    $0x1,%rax
  10a884:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  10a888:	e9 36 ff ff ff       	jmp    10a7c3 <_ZN4acos3hal13console_printEPKcj+0x33>
  10a88d:	48 83 c4 10          	add    $0x10,%rsp
  10a891:	5d                   	pop    %rbp
  10a892:	c3                   	ret
  10a893:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
  10a89a:	00 00 00
  10a89d:	0f 1f 00             	nopl   (%rax)

000000000010a8a0 <_ZN4acos3hal3PCI11read_configEhhhh>:
  10a8a0:	55                   	push   %rbp
  10a8a1:	48 89 e5             	mov    %rsp,%rbp
  10a8a4:	48 83 ec 0c          	sub    $0xc,%rsp
  10a8a8:	88 c8                	mov    %cl,%al
  10a8aa:	88 d1                	mov    %dl,%cl
  10a8ac:	40 88 f2             	mov    %sil,%dl
  10a8af:	40 88 fe             	mov    %dil,%sil
  10a8b2:	40 88 75 ff          	mov    %sil,-0x1(%rbp)
  10a8b6:	88 55 fe             	mov    %dl,-0x2(%rbp)
  10a8b9:	88 4d fd             	mov    %cl,-0x3(%rbp)
  10a8bc:	88 45 fc             	mov    %al,-0x4(%rbp)
  10a8bf:	0f b6 45 ff          	movzbl -0x1(%rbp),%eax
  10a8c3:	c1 e0 10             	shl    $0x10,%eax
  10a8c6:	0f b6 4d fe          	movzbl -0x2(%rbp),%ecx
  10a8ca:	c1 e1 0b             	shl    $0xb,%ecx
  10a8cd:	09 c8                	or     %ecx,%eax
  10a8cf:	0f b6 4d fd          	movzbl -0x3(%rbp),%ecx
  10a8d3:	c1 e1 08             	shl    $0x8,%ecx
  10a8d6:	09 c8                	or     %ecx,%eax
  10a8d8:	0f b6 4d fc          	movzbl -0x4(%rbp),%ecx
  10a8dc:	81 e1 fc 00 00 00    	and    $0xfc,%ecx
  10a8e2:	09 c8                	or     %ecx,%eax
  10a8e4:	0d 00 00 00 80       	or     $0x80000000,%eax
  10a8e9:	89 45 f8             	mov    %eax,-0x8(%rbp)
  10a8ec:	8b 45 f8             	mov    -0x8(%rbp),%eax
  10a8ef:	66 ba f8 0c          	mov    $0xcf8,%dx
  10a8f3:	ef                   	out    %eax,(%dx)
  10a8f4:	66 ba fc 0c          	mov    $0xcfc,%dx
  10a8f8:	ed                   	in     (%dx),%eax
  10a8f9:	89 45 f4             	mov    %eax,-0xc(%rbp)
  10a8fc:	8b 45 f4             	mov    -0xc(%rbp),%eax
  10a8ff:	48 83 c4 0c          	add    $0xc,%rsp
  10a903:	5d                   	pop    %rbp
  10a904:	c3                   	ret
  10a905:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  10a90c:	00 00 00 00

000000000010a910 <_ZN4acos3hal3PCI12write_configEhhhhj>:
  10a910:	55                   	push   %rbp
  10a911:	48 89 e5             	mov    %rsp,%rbp
  10a914:	48 83 ec 0c          	sub    $0xc,%rsp
  10a918:	88 c8                	mov    %cl,%al
  10a91a:	88 d1                	mov    %dl,%cl
  10a91c:	40 88 f2             	mov    %sil,%dl
  10a91f:	40 88 fe             	mov    %dil,%sil
  10a922:	40 88 75 ff          	mov    %sil,-0x1(%rbp)
  10a926:	88 55 fe             	mov    %dl,-0x2(%rbp)
  10a929:	88 4d fd             	mov    %cl,-0x3(%rbp)
  10a92c:	88 45 fc             	mov    %al,-0x4(%rbp)
  10a92f:	44 89 45 f8          	mov    %r8d,-0x8(%rbp)
  10a933:	0f b6 45 ff          	movzbl -0x1(%rbp),%eax
  10a937:	c1 e0 10             	shl    $0x10,%eax
  10a93a:	0f b6 4d fe          	movzbl -0x2(%rbp),%ecx
  10a93e:	c1 e1 0b             	shl    $0xb,%ecx
  10a941:	09 c8                	or     %ecx,%eax
  10a943:	0f b6 4d fd          	movzbl -0x3(%rbp),%ecx
  10a947:	c1 e1 08             	shl    $0x8,%ecx
  10a94a:	09 c8                	or     %ecx,%eax
  10a94c:	0f b6 4d fc          	movzbl -0x4(%rbp),%ecx
  10a950:	81 e1 fc 00 00 00    	and    $0xfc,%ecx
  10a956:	09 c8                	or     %ecx,%eax
  10a958:	0d 00 00 00 80       	or     $0x80000000,%eax
  10a95d:	89 45 f4             	mov    %eax,-0xc(%rbp)
  10a960:	8b 45 f4             	mov    -0xc(%rbp),%eax
  10a963:	66 ba f8 0c          	mov    $0xcf8,%dx
  10a967:	ef                   	out    %eax,(%dx)
  10a968:	8b 45 f8             	mov    -0x8(%rbp),%eax
  10a96b:	66 ba fc 0c          	mov    $0xcfc,%dx
  10a96f:	ef                   	out    %eax,(%dx)
  10a970:	48 83 c4 0c          	add    $0xc,%rsp
  10a974:	5d                   	pop    %rbp
  10a975:	c3                   	ret
  10a976:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
  10a97d:	00 00 00

000000000010a980 <_ZN4acos3hal3PCI11find_deviceEhh>:
  10a980:	55                   	push   %rbp
  10a981:	48 89 e5             	mov    %rsp,%rbp
  10a984:	48 83 ec 40          	sub    $0x40,%rsp
  10a988:	40 88 f0             	mov    %sil,%al
  10a98b:	40 88 f9             	mov    %dil,%cl
  10a98e:	88 4d f3             	mov    %cl,-0xd(%rbp)
  10a991:	88 45 f2             	mov    %al,-0xe(%rbp)
  10a994:	66 c7 45 f0 00 00    	movw   $0x0,-0x10(%rbp)
  10a99a:	0f b7 45 f0          	movzwl -0x10(%rbp),%eax
  10a99e:	3d 00 01 00 00       	cmp    $0x100,%eax
  10a9a3:	0f 8d 86 01 00 00    	jge    10ab2f <_ZN4acos3hal3PCI11find_deviceEhh+0x1af>
  10a9a9:	c6 45 ef 00          	movb   $0x0,-0x11(%rbp)
  10a9ad:	0f b6 45 ef          	movzbl -0x11(%rbp),%eax
  10a9b1:	83 f8 20             	cmp    $0x20,%eax
  10a9b4:	0f 8d 5f 01 00 00    	jge    10ab19 <_ZN4acos3hal3PCI11find_deviceEhh+0x199>
  10a9ba:	c6 45 ee 00          	movb   $0x0,-0x12(%rbp)
  10a9be:	0f b6 45 ee          	movzbl -0x12(%rbp),%eax
  10a9c2:	83 f8 08             	cmp    $0x8,%eax
  10a9c5:	0f 8d 3c 01 00 00    	jge    10ab07 <_ZN4acos3hal3PCI11find_deviceEhh+0x187>
  10a9cb:	66 8b 45 f0          	mov    -0x10(%rbp),%ax
  10a9cf:	88 c2                	mov    %al,%dl
  10a9d1:	8a 45 ef             	mov    -0x11(%rbp),%al
  10a9d4:	31 c9                	xor    %ecx,%ecx
  10a9d6:	0f b6 fa             	movzbl %dl,%edi
  10a9d9:	0f b6 f0             	movzbl %al,%esi
  10a9dc:	0f b6 55 ee          	movzbl -0x12(%rbp),%edx
  10a9e0:	e8 bb fe ff ff       	call   10a8a0 <_ZN4acos3hal3PCI11read_configEhhhh>
  10a9e5:	89 45 e8             	mov    %eax,-0x18(%rbp)
  10a9e8:	83 7d e8 ff          	cmpl   $0xffffffff,-0x18(%rbp)
  10a9ec:	0f 84 05 00 00 00    	je     10a9f7 <_ZN4acos3hal3PCI11find_deviceEhh+0x77>
  10a9f2:	e9 00 00 00 00       	jmp    10a9f7 <_ZN4acos3hal3PCI11find_deviceEhh+0x77>
  10a9f7:	8b 45 e8             	mov    -0x18(%rbp),%eax
  10a9fa:	25 ff ff 00 00       	and    $0xffff,%eax
  10a9ff:	3d ff ff 00 00       	cmp    $0xffff,%eax
  10aa04:	0f 85 05 00 00 00    	jne    10aa0f <_ZN4acos3hal3PCI11find_deviceEhh+0x8f>
  10aa0a:	e9 eb 00 00 00       	jmp    10aafa <_ZN4acos3hal3PCI11find_deviceEhh+0x17a>
  10aa0f:	66 8b 45 f0          	mov    -0x10(%rbp),%ax
  10aa13:	88 c2                	mov    %al,%dl
  10aa15:	8a 45 ef             	mov    -0x11(%rbp),%al
  10aa18:	b9 08 00 00 00       	mov    $0x8,%ecx
  10aa1d:	0f b6 fa             	movzbl %dl,%edi
  10aa20:	0f b6 f0             	movzbl %al,%esi
  10aa23:	0f b6 55 ee          	movzbl -0x12(%rbp),%edx
  10aa27:	e8 74 fe ff ff       	call   10a8a0 <_ZN4acos3hal3PCI11read_configEhhhh>
  10aa2c:	89 45 e4             	mov    %eax,-0x1c(%rbp)
  10aa2f:	8b 45 e4             	mov    -0x1c(%rbp),%eax
  10aa32:	c1 e8 18             	shr    $0x18,%eax
  10aa35:	25 ff 00 00 00       	and    $0xff,%eax
  10aa3a:	88 45 e3             	mov    %al,-0x1d(%rbp)
  10aa3d:	8b 45 e4             	mov    -0x1c(%rbp),%eax
  10aa40:	c1 e8 10             	shr    $0x10,%eax
  10aa43:	25 ff 00 00 00       	and    $0xff,%eax
  10aa48:	88 45 e2             	mov    %al,-0x1e(%rbp)
  10aa4b:	0f b6 45 e3          	movzbl -0x1d(%rbp),%eax
  10aa4f:	0f b6 4d f3          	movzbl -0xd(%rbp),%ecx
  10aa53:	39 c8                	cmp    %ecx,%eax
  10aa55:	0f 85 58 00 00 00    	jne    10aab3 <_ZN4acos3hal3PCI11find_deviceEhh+0x133>
  10aa5b:	0f b6 45 e2          	movzbl -0x1e(%rbp),%eax
  10aa5f:	0f b6 4d f2          	movzbl -0xe(%rbp),%ecx
  10aa63:	39 c8                	cmp    %ecx,%eax
  10aa65:	0f 85 48 00 00 00    	jne    10aab3 <_ZN4acos3hal3PCI11find_deviceEhh+0x133>
  10aa6b:	66 8b 45 f0          	mov    -0x10(%rbp),%ax
  10aa6f:	88 45 f4             	mov    %al,-0xc(%rbp)
  10aa72:	8a 45 ef             	mov    -0x11(%rbp),%al
  10aa75:	88 45 f5             	mov    %al,-0xb(%rbp)
  10aa78:	8a 45 ee             	mov    -0x12(%rbp),%al
  10aa7b:	88 45 f6             	mov    %al,-0xa(%rbp)
  10aa7e:	8b 45 e8             	mov    -0x18(%rbp),%eax
  10aa81:	25 ff ff 00 00       	and    $0xffff,%eax
  10aa86:	66 89 45 f8          	mov    %ax,-0x8(%rbp)
  10aa8a:	8b 45 e8             	mov    -0x18(%rbp),%eax
  10aa8d:	c1 e8 10             	shr    $0x10,%eax
  10aa90:	66 89 45 fa          	mov    %ax,-0x6(%rbp)
  10aa94:	8a 45 e3             	mov    -0x1d(%rbp),%al
  10aa97:	88 45 fc             	mov    %al,-0x4(%rbp)
  10aa9a:	8a 45 e2             	mov    -0x1e(%rbp),%al
  10aa9d:	88 45 fd             	mov    %al,-0x3(%rbp)
  10aaa0:	8b 45 e4             	mov    -0x1c(%rbp),%eax
  10aaa3:	c1 e8 08             	shr    $0x8,%eax
  10aaa6:	25 ff 00 00 00       	and    $0xff,%eax
  10aaab:	88 45 fe             	mov    %al,-0x2(%rbp)
  10aaae:	e9 a0 00 00 00       	jmp    10ab53 <_ZN4acos3hal3PCI11find_deviceEhh+0x1d3>
  10aab3:	0f b6 45 ee          	movzbl -0x12(%rbp),%eax
  10aab7:	83 f8 00             	cmp    $0x0,%eax
  10aaba:	0f 85 35 00 00 00    	jne    10aaf5 <_ZN4acos3hal3PCI11find_deviceEhh+0x175>
  10aac0:	66 8b 45 f0          	mov    -0x10(%rbp),%ax
  10aac4:	31 d2                	xor    %edx,%edx
  10aac6:	b9 0c 00 00 00       	mov    $0xc,%ecx
  10aacb:	0f b6 f8             	movzbl %al,%edi
  10aace:	0f b6 75 ef          	movzbl -0x11(%rbp),%esi
  10aad2:	e8 c9 fd ff ff       	call   10a8a0 <_ZN4acos3hal3PCI11read_configEhhhh>
  10aad7:	89 45 dc             	mov    %eax,-0x24(%rbp)
  10aada:	8b 45 dc             	mov    -0x24(%rbp),%eax
  10aadd:	25 00 00 80 00       	and    $0x800000,%eax
  10aae2:	83 f8 00             	cmp    $0x0,%eax
  10aae5:	0f 85 05 00 00 00    	jne    10aaf0 <_ZN4acos3hal3PCI11find_deviceEhh+0x170>
  10aaeb:	e9 17 00 00 00       	jmp    10ab07 <_ZN4acos3hal3PCI11find_deviceEhh+0x187>
  10aaf0:	e9 00 00 00 00       	jmp    10aaf5 <_ZN4acos3hal3PCI11find_deviceEhh+0x175>
  10aaf5:	e9 00 00 00 00       	jmp    10aafa <_ZN4acos3hal3PCI11find_deviceEhh+0x17a>
  10aafa:	8a 45 ee             	mov    -0x12(%rbp),%al
  10aafd:	04 01                	add    $0x1,%al
  10aaff:	88 45 ee             	mov    %al,-0x12(%rbp)
  10ab02:	e9 b7 fe ff ff       	jmp    10a9be <_ZN4acos3hal3PCI11find_deviceEhh+0x3e>
  10ab07:	e9 00 00 00 00       	jmp    10ab0c <_ZN4acos3hal3PCI11find_deviceEhh+0x18c>
  10ab0c:	8a 45 ef             	mov    -0x11(%rbp),%al
  10ab0f:	04 01                	add    $0x1,%al
  10ab11:	88 45 ef             	mov    %al,-0x11(%rbp)
  10ab14:	e9 94 fe ff ff       	jmp    10a9ad <_ZN4acos3hal3PCI11find_deviceEhh+0x2d>
  10ab19:	e9 00 00 00 00       	jmp    10ab1e <_ZN4acos3hal3PCI11find_deviceEhh+0x19e>
  10ab1e:	66 8b 45 f0          	mov    -0x10(%rbp),%ax
  10ab22:	66 83 c0 01          	add    $0x1,%ax
  10ab26:	66 89 45 f0          	mov    %ax,-0x10(%rbp)
  10ab2a:	e9 6b fe ff ff       	jmp    10a99a <_ZN4acos3hal3PCI11find_deviceEhh+0x1a>
  10ab2f:	c6 45 f4 00          	movb   $0x0,-0xc(%rbp)
  10ab33:	c6 45 f5 00          	movb   $0x0,-0xb(%rbp)
  10ab37:	c6 45 f6 00          	movb   $0x0,-0xa(%rbp)
  10ab3b:	66 c7 45 f8 ff ff    	movw   $0xffff,-0x8(%rbp)
  10ab41:	66 c7 45 fa ff ff    	movw   $0xffff,-0x6(%rbp)
  10ab47:	c6 45 fc 00          	movb   $0x0,-0x4(%rbp)
  10ab4b:	c6 45 fd 00          	movb   $0x0,-0x3(%rbp)
  10ab4f:	c6 45 fe 00          	movb   $0x0,-0x2(%rbp)
  10ab53:	8b 45 fc             	mov    -0x4(%rbp),%eax
  10ab56:	89 45 d0             	mov    %eax,-0x30(%rbp)
  10ab59:	48 8b 45 f4          	mov    -0xc(%rbp),%rax
  10ab5d:	48 89 45 c8          	mov    %rax,-0x38(%rbp)
  10ab61:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  10ab65:	8b 55 d0             	mov    -0x30(%rbp),%edx
  10ab68:	48 83 c4 40          	add    $0x40,%rsp
  10ab6c:	5d                   	pop    %rbp
  10ab6d:	c3                   	ret
  10ab6e:	66 90                	xchg   %ax,%ax

000000000010ab70 <_ZN4acos3hal3PCI7get_barERKNS0_9PCIDeviceEh>:
  10ab70:	55                   	push   %rbp
  10ab71:	48 89 e5             	mov    %rsp,%rbp
  10ab74:	48 83 ec 30          	sub    $0x30,%rsp
  10ab78:	40 88 f0             	mov    %sil,%al
  10ab7b:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  10ab7f:	88 45 ef             	mov    %al,-0x11(%rbp)
  10ab82:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10ab86:	40 8a 30             	mov    (%rax),%sil
  10ab89:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10ab8d:	8a 50 01             	mov    0x1(%rax),%dl
  10ab90:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10ab94:	8a 48 02             	mov    0x2(%rax),%cl
  10ab97:	0f b6 45 ef          	movzbl -0x11(%rbp),%eax
  10ab9b:	c1 e0 02             	shl    $0x2,%eax
  10ab9e:	83 c0 10             	add    $0x10,%eax
  10aba1:	40 0f b6 fe          	movzbl %sil,%edi
  10aba5:	0f b6 f2             	movzbl %dl,%esi
  10aba8:	0f b6 d1             	movzbl %cl,%edx
  10abab:	0f b6 c8             	movzbl %al,%ecx
  10abae:	e8 ed fc ff ff       	call   10a8a0 <_ZN4acos3hal3PCI11read_configEhhhh>
  10abb3:	89 45 e8             	mov    %eax,-0x18(%rbp)
  10abb6:	8b 45 e8             	mov    -0x18(%rbp),%eax
  10abb9:	83 e0 01             	and    $0x1,%eax
  10abbc:	83 f8 00             	cmp    $0x0,%eax
  10abbf:	0f 84 0d 00 00 00    	je     10abd2 <_ZN4acos3hal3PCI7get_barERKNS0_9PCIDeviceEh+0x62>
  10abc5:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  10abcc:	00
  10abcd:	e9 6b 00 00 00       	jmp    10ac3d <_ZN4acos3hal3PCI7get_barERKNS0_9PCIDeviceEh+0xcd>
  10abd2:	8b 45 e8             	mov    -0x18(%rbp),%eax
  10abd5:	83 e0 f0             	and    $0xfffffff0,%eax
  10abd8:	89 c0                	mov    %eax,%eax
  10abda:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  10abde:	8b 45 e8             	mov    -0x18(%rbp),%eax
  10abe1:	d1 e8                	shr    $1,%eax
  10abe3:	83 e0 03             	and    $0x3,%eax
  10abe6:	83 f8 00             	cmp    $0x0,%eax
  10abe9:	0f 84 46 00 00 00    	je     10ac35 <_ZN4acos3hal3PCI7get_barERKNS0_9PCIDeviceEh+0xc5>
  10abef:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10abf3:	40 8a 30             	mov    (%rax),%sil
  10abf6:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10abfa:	8a 50 01             	mov    0x1(%rax),%dl
  10abfd:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10ac01:	8a 48 02             	mov    0x2(%rax),%cl
  10ac04:	0f b6 45 ef          	movzbl -0x11(%rbp),%eax
  10ac08:	c1 e0 02             	shl    $0x2,%eax
  10ac0b:	83 c0 10             	add    $0x10,%eax
  10ac0e:	83 c0 04             	add    $0x4,%eax
  10ac11:	40 0f b6 fe          	movzbl %sil,%edi
  10ac15:	0f b6 f2             	movzbl %dl,%esi
  10ac18:	0f b6 d1             	movzbl %cl,%edx
  10ac1b:	0f b6 c8             	movzbl %al,%ecx
  10ac1e:	e8 7d fc ff ff       	call   10a8a0 <_ZN4acos3hal3PCI11read_configEhhhh>
  10ac23:	89 45 dc             	mov    %eax,-0x24(%rbp)
  10ac26:	8b 45 dc             	mov    -0x24(%rbp),%eax
  10ac29:	48 c1 e0 20          	shl    $0x20,%rax
  10ac2d:	48 0b 45 e0          	or     -0x20(%rbp),%rax
  10ac31:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  10ac35:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  10ac39:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  10ac3d:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10ac41:	48 83 c4 30          	add    $0x30,%rsp
  10ac45:	5d                   	pop    %rbp
  10ac46:	c3                   	ret
  10ac47:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
  10ac4e:	00 00

000000000010ac50 <_ZN4acos3hal3PCI20enable_bus_masteringERKNS0_9PCIDeviceE>:
  10ac50:	55                   	push   %rbp
  10ac51:	48 89 e5             	mov    %rsp,%rbp
  10ac54:	48 83 ec 10          	sub    $0x10,%rsp
  10ac58:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10ac5c:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10ac60:	40 8a 30             	mov    (%rax),%sil
  10ac63:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10ac67:	8a 50 01             	mov    0x1(%rax),%dl
  10ac6a:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10ac6e:	b9 04 00 00 00       	mov    $0x4,%ecx
  10ac73:	40 0f b6 fe          	movzbl %sil,%edi
  10ac77:	0f b6 f2             	movzbl %dl,%esi
  10ac7a:	0f b6 50 02          	movzbl 0x2(%rax),%edx
  10ac7e:	e8 1d fc ff ff       	call   10a8a0 <_ZN4acos3hal3PCI11read_configEhhhh>
  10ac83:	89 45 f4             	mov    %eax,-0xc(%rbp)
  10ac86:	8b 45 f4             	mov    -0xc(%rbp),%eax
  10ac89:	83 c8 06             	or     $0x6,%eax
  10ac8c:	89 45 f4             	mov    %eax,-0xc(%rbp)
  10ac8f:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10ac93:	40 8a 30             	mov    (%rax),%sil
  10ac96:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10ac9a:	8a 50 01             	mov    0x1(%rax),%dl
  10ac9d:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10aca1:	8a 40 02             	mov    0x2(%rax),%al
  10aca4:	44 8b 45 f4          	mov    -0xc(%rbp),%r8d
  10aca8:	b9 04 00 00 00       	mov    $0x4,%ecx
  10acad:	40 0f b6 fe          	movzbl %sil,%edi
  10acb1:	0f b6 f2             	movzbl %dl,%esi
  10acb4:	0f b6 d0             	movzbl %al,%edx
  10acb7:	e8 54 fc ff ff       	call   10a910 <_ZN4acos3hal3PCI12write_configEhhhhj>
  10acbc:	48 83 c4 10          	add    $0x10,%rsp
  10acc0:	5d                   	pop    %rbp
  10acc1:	c3                   	ret
  10acc2:	66 66 66 66 66 2e 0f 	data16 data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
  10acc9:	1f 84 00 00 00 00 00

000000000010acd0 <_ZN4acos3hal3PCI15find_capabilityERKNS0_9PCIDeviceEh>:
  10acd0:	55                   	push   %rbp
  10acd1:	48 89 e5             	mov    %rsp,%rbp
  10acd4:	48 83 ec 20          	sub    $0x20,%rsp
  10acd8:	40 88 f0             	mov    %sil,%al
  10acdb:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  10acdf:	88 45 ef             	mov    %al,-0x11(%rbp)
  10ace2:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10ace6:	40 8a 30             	mov    (%rax),%sil
  10ace9:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10aced:	8a 50 01             	mov    0x1(%rax),%dl
  10acf0:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10acf4:	b9 06 00 00 00       	mov    $0x6,%ecx
  10acf9:	40 0f b6 fe          	movzbl %sil,%edi
  10acfd:	0f b6 f2             	movzbl %dl,%esi
  10ad00:	0f b6 50 02          	movzbl 0x2(%rax),%edx
  10ad04:	e8 97 fb ff ff       	call   10a8a0 <_ZN4acos3hal3PCI11read_configEhhhh>
  10ad09:	89 45 e8             	mov    %eax,-0x18(%rbp)
  10ad0c:	8b 45 e8             	mov    -0x18(%rbp),%eax
  10ad0f:	83 e0 10             	and    $0x10,%eax
  10ad12:	83 f8 00             	cmp    $0x0,%eax
  10ad15:	0f 85 09 00 00 00    	jne    10ad24 <_ZN4acos3hal3PCI15find_capabilityERKNS0_9PCIDeviceEh+0x54>
  10ad1b:	c6 45 ff 00          	movb   $0x0,-0x1(%rbp)
  10ad1f:	e9 93 00 00 00       	jmp    10adb7 <_ZN4acos3hal3PCI15find_capabilityERKNS0_9PCIDeviceEh+0xe7>
  10ad24:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10ad28:	40 8a 30             	mov    (%rax),%sil
  10ad2b:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10ad2f:	8a 50 01             	mov    0x1(%rax),%dl
  10ad32:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10ad36:	b9 34 00 00 00       	mov    $0x34,%ecx
  10ad3b:	40 0f b6 fe          	movzbl %sil,%edi
  10ad3f:	0f b6 f2             	movzbl %dl,%esi
  10ad42:	0f b6 50 02          	movzbl 0x2(%rax),%edx
  10ad46:	e8 55 fb ff ff       	call   10a8a0 <_ZN4acos3hal3PCI11read_configEhhhh>
  10ad4b:	88 45 e7             	mov    %al,-0x19(%rbp)
  10ad4e:	80 7d e7 00          	cmpb   $0x0,-0x19(%rbp)
  10ad52:	0f 84 5b 00 00 00    	je     10adb3 <_ZN4acos3hal3PCI15find_capabilityERKNS0_9PCIDeviceEh+0xe3>
  10ad58:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10ad5c:	8a 10                	mov    (%rax),%dl
  10ad5e:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10ad62:	8a 48 01             	mov    0x1(%rax),%cl
  10ad65:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10ad69:	8a 40 02             	mov    0x2(%rax),%al
  10ad6c:	0f b6 fa             	movzbl %dl,%edi
  10ad6f:	0f b6 f1             	movzbl %cl,%esi
  10ad72:	0f b6 d0             	movzbl %al,%edx
  10ad75:	0f b6 4d e7          	movzbl -0x19(%rbp),%ecx
  10ad79:	e8 22 fb ff ff       	call   10a8a0 <_ZN4acos3hal3PCI11read_configEhhhh>
  10ad7e:	89 45 e0             	mov    %eax,-0x20(%rbp)
  10ad81:	8b 45 e0             	mov    -0x20(%rbp),%eax
  10ad84:	25 ff 00 00 00       	and    $0xff,%eax
  10ad89:	0f b6 4d ef          	movzbl -0x11(%rbp),%ecx
  10ad8d:	39 c8                	cmp    %ecx,%eax
  10ad8f:	0f 85 0b 00 00 00    	jne    10ada0 <_ZN4acos3hal3PCI15find_capabilityERKNS0_9PCIDeviceEh+0xd0>
  10ad95:	8a 45 e7             	mov    -0x19(%rbp),%al
  10ad98:	88 45 ff             	mov    %al,-0x1(%rbp)
  10ad9b:	e9 17 00 00 00       	jmp    10adb7 <_ZN4acos3hal3PCI15find_capabilityERKNS0_9PCIDeviceEh+0xe7>
  10ada0:	8b 45 e0             	mov    -0x20(%rbp),%eax
  10ada3:	c1 e8 08             	shr    $0x8,%eax
  10ada6:	25 ff 00 00 00       	and    $0xff,%eax
  10adab:	88 45 e7             	mov    %al,-0x19(%rbp)
  10adae:	e9 9b ff ff ff       	jmp    10ad4e <_ZN4acos3hal3PCI15find_capabilityERKNS0_9PCIDeviceEh+0x7e>
  10adb3:	c6 45 ff 00          	movb   $0x0,-0x1(%rbp)
  10adb7:	0f b6 45 ff          	movzbl -0x1(%rbp),%eax
  10adbb:	48 83 c4 20          	add    $0x20,%rsp
  10adbf:	5d                   	pop    %rbp
  10adc0:	c3                   	ret
  10adc1:	66 66 66 66 66 66 2e 	data16 data16 data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
  10adc8:	0f 1f 84 00 00 00 00
  10adcf:	00

000000000010add0 <_ZN4acos3hal3PCI10enable_msiERKNS0_9PCIDeviceEh>:
  10add0:	55                   	push   %rbp
  10add1:	48 89 e5             	mov    %rsp,%rbp
  10add4:	48 83 ec 20          	sub    $0x20,%rsp
  10add8:	40 88 f0             	mov    %sil,%al
  10addb:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10addf:	88 45 f7             	mov    %al,-0x9(%rbp)
  10ade2:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  10ade6:	be 05 00 00 00       	mov    $0x5,%esi
  10adeb:	e8 e0 fe ff ff       	call   10acd0 <_ZN4acos3hal3PCI15find_capabilityERKNS0_9PCIDeviceEh>
  10adf0:	88 45 f6             	mov    %al,-0xa(%rbp)
  10adf3:	80 7d f6 00          	cmpb   $0x0,-0xa(%rbp)
  10adf7:	0f 85 05 00 00 00    	jne    10ae02 <_ZN4acos3hal3PCI10enable_msiERKNS0_9PCIDeviceEh+0x32>
  10adfd:	e9 4d 01 00 00       	jmp    10af4f <_ZN4acos3hal3PCI10enable_msiERKNS0_9PCIDeviceEh+0x17f>
  10ae02:	c7 45 f0 00 00 e0 fe 	movl   $0xfee00000,-0x10(%rbp)
  10ae09:	0f b6 45 f7          	movzbl -0x9(%rbp),%eax
  10ae0d:	89 45 ec             	mov    %eax,-0x14(%rbp)
  10ae10:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10ae14:	40 8a 30             	mov    (%rax),%sil
  10ae17:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10ae1b:	8a 50 01             	mov    0x1(%rax),%dl
  10ae1e:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10ae22:	8a 48 02             	mov    0x2(%rax),%cl
  10ae25:	0f b6 45 f6          	movzbl -0xa(%rbp),%eax
  10ae29:	83 c0 04             	add    $0x4,%eax
  10ae2c:	44 8b 45 f0          	mov    -0x10(%rbp),%r8d
  10ae30:	40 0f b6 fe          	movzbl %sil,%edi
  10ae34:	0f b6 f2             	movzbl %dl,%esi
  10ae37:	0f b6 d1             	movzbl %cl,%edx
  10ae3a:	0f b6 c8             	movzbl %al,%ecx
  10ae3d:	e8 ce fa ff ff       	call   10a910 <_ZN4acos3hal3PCI12write_configEhhhhj>
  10ae42:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10ae46:	8a 10                	mov    (%rax),%dl
  10ae48:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10ae4c:	8a 48 01             	mov    0x1(%rax),%cl
  10ae4f:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10ae53:	8a 40 02             	mov    0x2(%rax),%al
  10ae56:	0f b6 fa             	movzbl %dl,%edi
  10ae59:	0f b6 f1             	movzbl %cl,%esi
  10ae5c:	0f b6 d0             	movzbl %al,%edx
  10ae5f:	0f b6 4d f6          	movzbl -0xa(%rbp),%ecx
  10ae63:	e8 38 fa ff ff       	call   10a8a0 <_ZN4acos3hal3PCI11read_configEhhhh>
  10ae68:	89 45 e8             	mov    %eax,-0x18(%rbp)
  10ae6b:	8b 45 e8             	mov    -0x18(%rbp),%eax
  10ae6e:	25 00 00 80 00       	and    $0x800000,%eax
  10ae73:	83 f8 00             	cmp    $0x0,%eax
  10ae76:	0f 84 68 00 00 00    	je     10aee4 <_ZN4acos3hal3PCI10enable_msiERKNS0_9PCIDeviceEh+0x114>
  10ae7c:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10ae80:	40 8a 30             	mov    (%rax),%sil
  10ae83:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10ae87:	8a 50 01             	mov    0x1(%rax),%dl
  10ae8a:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10ae8e:	8a 48 02             	mov    0x2(%rax),%cl
  10ae91:	0f b6 45 f6          	movzbl -0xa(%rbp),%eax
  10ae95:	83 c0 08             	add    $0x8,%eax
  10ae98:	45 31 c0             	xor    %r8d,%r8d
  10ae9b:	40 0f b6 fe          	movzbl %sil,%edi
  10ae9f:	0f b6 f2             	movzbl %dl,%esi
  10aea2:	0f b6 d1             	movzbl %cl,%edx
  10aea5:	0f b6 c8             	movzbl %al,%ecx
  10aea8:	e8 63 fa ff ff       	call   10a910 <_ZN4acos3hal3PCI12write_configEhhhhj>
  10aead:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10aeb1:	40 8a 30             	mov    (%rax),%sil
  10aeb4:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10aeb8:	8a 50 01             	mov    0x1(%rax),%dl
  10aebb:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10aebf:	8a 48 02             	mov    0x2(%rax),%cl
  10aec2:	0f b6 45 f6          	movzbl -0xa(%rbp),%eax
  10aec6:	83 c0 0c             	add    $0xc,%eax
  10aec9:	44 8b 45 ec          	mov    -0x14(%rbp),%r8d
  10aecd:	40 0f b6 fe          	movzbl %sil,%edi
  10aed1:	0f b6 f2             	movzbl %dl,%esi
  10aed4:	0f b6 d1             	movzbl %cl,%edx
  10aed7:	0f b6 c8             	movzbl %al,%ecx
  10aeda:	e8 31 fa ff ff       	call   10a910 <_ZN4acos3hal3PCI12write_configEhhhhj>
  10aedf:	e9 32 00 00 00       	jmp    10af16 <_ZN4acos3hal3PCI10enable_msiERKNS0_9PCIDeviceEh+0x146>
  10aee4:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10aee8:	40 8a 30             	mov    (%rax),%sil
  10aeeb:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10aeef:	8a 50 01             	mov    0x1(%rax),%dl
  10aef2:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10aef6:	8a 48 02             	mov    0x2(%rax),%cl
  10aef9:	0f b6 45 f6          	movzbl -0xa(%rbp),%eax
  10aefd:	83 c0 08             	add    $0x8,%eax
  10af00:	44 8b 45 ec          	mov    -0x14(%rbp),%r8d
  10af04:	40 0f b6 fe          	movzbl %sil,%edi
  10af08:	0f b6 f2             	movzbl %dl,%esi
  10af0b:	0f b6 d1             	movzbl %cl,%edx
  10af0e:	0f b6 c8             	movzbl %al,%ecx
  10af11:	e8 fa f9 ff ff       	call   10a910 <_ZN4acos3hal3PCI12write_configEhhhhj>
  10af16:	8b 45 e8             	mov    -0x18(%rbp),%eax
  10af19:	0d 00 00 01 00       	or     $0x10000,%eax
  10af1e:	89 45 e8             	mov    %eax,-0x18(%rbp)
  10af21:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10af25:	40 8a 30             	mov    (%rax),%sil
  10af28:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10af2c:	8a 50 01             	mov    0x1(%rax),%dl
  10af2f:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10af33:	8a 48 02             	mov    0x2(%rax),%cl
  10af36:	8a 45 f6             	mov    -0xa(%rbp),%al
  10af39:	44 8b 45 e8          	mov    -0x18(%rbp),%r8d
  10af3d:	40 0f b6 fe          	movzbl %sil,%edi
  10af41:	0f b6 f2             	movzbl %dl,%esi
  10af44:	0f b6 d1             	movzbl %cl,%edx
  10af47:	0f b6 c8             	movzbl %al,%ecx
  10af4a:	e8 c1 f9 ff ff       	call   10a910 <_ZN4acos3hal3PCI12write_configEhhhhj>
  10af4f:	48 83 c4 20          	add    $0x20,%rsp
  10af53:	5d                   	pop    %rbp
  10af54:	c3                   	ret
  10af55:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
  10af5c:	00 00 00
  10af5f:	90                   	nop

000000000010af60 <_ZN4acos7drivers5input13PS2Controller10wait_writeEv>:
  10af60:	55                   	push   %rbp
  10af61:	48 89 e5             	mov    %rsp,%rbp
  10af64:	48 83 ec 01          	sub    $0x1,%rsp
  10af68:	e4 64                	in     $0x64,%al
  10af6a:	88 45 ff             	mov    %al,-0x1(%rbp)
  10af6d:	0f b6 45 ff          	movzbl -0x1(%rbp),%eax
  10af71:	83 e0 02             	and    $0x2,%eax
  10af74:	83 f8 00             	cmp    $0x0,%eax
  10af77:	0f 85 eb ff ff ff    	jne    10af68 <_ZN4acos7drivers5input13PS2Controller10wait_writeEv+0x8>
  10af7d:	48 83 c4 01          	add    $0x1,%rsp
  10af81:	5d                   	pop    %rbp
  10af82:	c3                   	ret
  10af83:	66 66 66 66 2e 0f 1f 	data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
  10af8a:	84 00 00 00 00 00

000000000010af90 <_ZN4acos7drivers5input13PS2Controller9wait_readEv>:
  10af90:	55                   	push   %rbp
  10af91:	48 89 e5             	mov    %rsp,%rbp
  10af94:	48 83 ec 01          	sub    $0x1,%rsp
  10af98:	e4 64                	in     $0x64,%al
  10af9a:	88 45 ff             	mov    %al,-0x1(%rbp)
  10af9d:	0f b6 45 ff          	movzbl -0x1(%rbp),%eax
  10afa1:	83 e0 01             	and    $0x1,%eax
  10afa4:	83 f8 00             	cmp    $0x0,%eax
  10afa7:	0f 95 c0             	setne  %al
  10afaa:	34 ff                	xor    $0xff,%al
  10afac:	a8 01                	test   $0x1,%al
  10afae:	0f 85 e4 ff ff ff    	jne    10af98 <_ZN4acos7drivers5input13PS2Controller9wait_readEv+0x8>
  10afb4:	48 83 c4 01          	add    $0x1,%rsp
  10afb8:	5d                   	pop    %rbp
  10afb9:	c3                   	ret
  10afba:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

000000000010afc0 <_ZN4acos7drivers5input13PS2Controller13write_commandEh>:
  10afc0:	55                   	push   %rbp
  10afc1:	48 89 e5             	mov    %rsp,%rbp
  10afc4:	48 83 ec 10          	sub    $0x10,%rsp
  10afc8:	40 88 f8             	mov    %dil,%al
  10afcb:	88 45 ff             	mov    %al,-0x1(%rbp)
  10afce:	e8 8d ff ff ff       	call   10af60 <_ZN4acos7drivers5input13PS2Controller10wait_writeEv>
  10afd3:	8a 45 ff             	mov    -0x1(%rbp),%al
  10afd6:	e6 64                	out    %al,$0x64
  10afd8:	48 83 c4 10          	add    $0x10,%rsp
  10afdc:	5d                   	pop    %rbp
  10afdd:	c3                   	ret
  10afde:	66 90                	xchg   %ax,%ax

000000000010afe0 <_ZN4acos7drivers5input13PS2Controller9read_dataEv>:
  10afe0:	55                   	push   %rbp
  10afe1:	48 89 e5             	mov    %rsp,%rbp
  10afe4:	48 83 ec 10          	sub    $0x10,%rsp
  10afe8:	e8 a3 ff ff ff       	call   10af90 <_ZN4acos7drivers5input13PS2Controller9wait_readEv>
  10afed:	e4 60                	in     $0x60,%al
  10afef:	88 45 ff             	mov    %al,-0x1(%rbp)
  10aff2:	0f b6 45 ff          	movzbl -0x1(%rbp),%eax
  10aff6:	48 83 c4 10          	add    $0x10,%rsp
  10affa:	5d                   	pop    %rbp
  10affb:	c3                   	ret
  10affc:	0f 1f 40 00          	nopl   0x0(%rax)

000000000010b000 <_ZN4acos7drivers5input13PS2Controller10write_dataEh>:
  10b000:	55                   	push   %rbp
  10b001:	48 89 e5             	mov    %rsp,%rbp
  10b004:	48 83 ec 10          	sub    $0x10,%rsp
  10b008:	40 88 f8             	mov    %dil,%al
  10b00b:	88 45 ff             	mov    %al,-0x1(%rbp)
  10b00e:	e8 4d ff ff ff       	call   10af60 <_ZN4acos7drivers5input13PS2Controller10wait_writeEv>
  10b013:	8a 45 ff             	mov    -0x1(%rbp),%al
  10b016:	e6 60                	out    %al,$0x60
  10b018:	48 83 c4 10          	add    $0x10,%rsp
  10b01c:	5d                   	pop    %rbp
  10b01d:	c3                   	ret
  10b01e:	66 90                	xchg   %ax,%ax

000000000010b020 <_ZN4acos7drivers5input13PS2Controller4initEv>:
  10b020:	55                   	push   %rbp
  10b021:	48 89 e5             	mov    %rsp,%rbp
  10b024:	48 83 ec 10          	sub    $0x10,%rsp
  10b028:	bf ad 00 00 00       	mov    $0xad,%edi
  10b02d:	e8 8e ff ff ff       	call   10afc0 <_ZN4acos7drivers5input13PS2Controller13write_commandEh>
  10b032:	bf a7 00 00 00       	mov    $0xa7,%edi
  10b037:	e8 84 ff ff ff       	call   10afc0 <_ZN4acos7drivers5input13PS2Controller13write_commandEh>
  10b03c:	e4 64                	in     $0x64,%al
  10b03e:	88 45 ff             	mov    %al,-0x1(%rbp)
  10b041:	0f b6 45 ff          	movzbl -0x1(%rbp),%eax
  10b045:	83 e0 01             	and    $0x1,%eax
  10b048:	83 f8 00             	cmp    $0x0,%eax
  10b04b:	0f 84 05 00 00 00    	je     10b056 <_ZN4acos7drivers5input13PS2Controller4initEv+0x36>
  10b051:	e8 8a ff ff ff       	call   10afe0 <_ZN4acos7drivers5input13PS2Controller9read_dataEv>
  10b056:	bf 20 00 00 00       	mov    $0x20,%edi
  10b05b:	e8 60 ff ff ff       	call   10afc0 <_ZN4acos7drivers5input13PS2Controller13write_commandEh>
  10b060:	e8 7b ff ff ff       	call   10afe0 <_ZN4acos7drivers5input13PS2Controller9read_dataEv>
  10b065:	88 45 fe             	mov    %al,-0x2(%rbp)
  10b068:	0f b6 45 fe          	movzbl -0x2(%rbp),%eax
  10b06c:	83 c8 03             	or     $0x3,%eax
  10b06f:	88 45 fe             	mov    %al,-0x2(%rbp)
  10b072:	bf 60 00 00 00       	mov    $0x60,%edi
  10b077:	e8 44 ff ff ff       	call   10afc0 <_ZN4acos7drivers5input13PS2Controller13write_commandEh>
  10b07c:	0f b6 7d fe          	movzbl -0x2(%rbp),%edi
  10b080:	e8 7b ff ff ff       	call   10b000 <_ZN4acos7drivers5input13PS2Controller10write_dataEh>
  10b085:	bf ae 00 00 00       	mov    $0xae,%edi
  10b08a:	e8 31 ff ff ff       	call   10afc0 <_ZN4acos7drivers5input13PS2Controller13write_commandEh>
  10b08f:	bf a8 00 00 00       	mov    $0xa8,%edi
  10b094:	e8 27 ff ff ff       	call   10afc0 <_ZN4acos7drivers5input13PS2Controller13write_commandEh>
  10b099:	48 83 c4 10          	add    $0x10,%rsp
  10b09d:	5d                   	pop    %rbp
  10b09e:	c3                   	ret
  10b09f:	90                   	nop

000000000010b0a0 <_ZN4acos7drivers5input13PS2Controller16handle_interruptEv>:
  10b0a0:	55                   	push   %rbp
  10b0a1:	48 89 e5             	mov    %rsp,%rbp
  10b0a4:	48 83 ec 01          	sub    $0x1,%rsp
  10b0a8:	e4 60                	in     $0x60,%al
  10b0aa:	88 45 ff             	mov    %al,-0x1(%rbp)
  10b0ad:	48 83 c4 01          	add    $0x1,%rsp
  10b0b1:	5d                   	pop    %rbp
  10b0b2:	c3                   	ret
  10b0b3:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
  10b0ba:	00 00 00
  10b0bd:	0f 1f 00             	nopl   (%rax)

000000000010b0c0 <_ZN4acos8graphics15GraphicsManager16register_displayEPNS0_13DisplayDeviceE>:
  10b0c0:	55                   	push   %rbp
  10b0c1:	48 89 e5             	mov    %rsp,%rbp
  10b0c4:	50                   	push   %rax
  10b0c5:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10b0c9:	48 83 7d f8 00       	cmpq   $0x0,-0x8(%rbp)
  10b0ce:	0f 84 2f 00 00 00    	je     10b103 <_ZN4acos8graphics15GraphicsManager16register_displayEPNS0_13DisplayDeviceE+0x43>
  10b0d4:	83 3c 25 40 db 16 00 	cmpl   $0x4,0x16db40
  10b0db:	04
  10b0dc:	0f 83 21 00 00 00    	jae    10b103 <_ZN4acos8graphics15GraphicsManager16register_displayEPNS0_13DisplayDeviceE+0x43>
  10b0e2:	48 8b 4d f8          	mov    -0x8(%rbp),%rcx
  10b0e6:	8b 04 25 40 db 16 00 	mov    0x16db40,%eax
  10b0ed:	89 c2                	mov    %eax,%edx
  10b0ef:	83 c2 01             	add    $0x1,%edx
  10b0f2:	89 14 25 40 db 16 00 	mov    %edx,0x16db40
  10b0f9:	89 c0                	mov    %eax,%eax
  10b0fb:	48 89 0c c5 20 db 16 	mov    %rcx,0x16db20(,%rax,8)
  10b102:	00
  10b103:	48 83 c4 08          	add    $0x8,%rsp
  10b107:	5d                   	pop    %rbp
  10b108:	c3                   	ret
  10b109:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

000000000010b110 <_ZN4acos8graphics15GraphicsManager15primary_displayEv>:
  10b110:	55                   	push   %rbp
  10b111:	48 89 e5             	mov    %rsp,%rbp
  10b114:	50                   	push   %rax
  10b115:	83 3c 25 40 db 16 00 	cmpl   $0x0,0x16db40
  10b11c:	00
  10b11d:	0f 86 11 00 00 00    	jbe    10b134 <_ZN4acos8graphics15GraphicsManager15primary_displayEv+0x24>
  10b123:	48 8b 04 25 20 db 16 	mov    0x16db20,%rax
  10b12a:	00
  10b12b:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  10b12f:	e9 08 00 00 00       	jmp    10b13c <_ZN4acos8graphics15GraphicsManager15primary_displayEv+0x2c>
  10b134:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  10b13b:	00
  10b13c:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10b140:	48 83 c4 08          	add    $0x8,%rsp
  10b144:	5d                   	pop    %rbp
  10b145:	c3                   	ret
  10b146:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
  10b14d:	00 00 00

000000000010b150 <_ZN4acos8graphics15GraphicsManager4initEv>:
  10b150:	55                   	push   %rbp
  10b151:	48 89 e5             	mov    %rsp,%rbp
  10b154:	31 c0                	xor    %eax,%eax
  10b156:	89 c7                	mov    %eax,%edi
  10b158:	e8 03 00 00 00       	call   10b160 <_ZN4acos8graphics15GraphicsManager4initEPNS_15FramebufferInfoE>
  10b15d:	5d                   	pop    %rbp
  10b15e:	c3                   	ret
  10b15f:	90                   	nop

000000000010b160 <_ZN4acos8graphics15GraphicsManager4initEPNS_15FramebufferInfoE>:
  10b160:	55                   	push   %rbp
  10b161:	48 89 e5             	mov    %rsp,%rbp
  10b164:	48 83 ec 20          	sub    $0x20,%rsp
  10b168:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10b16c:	c7 04 25 40 db 16 00 	movl   $0x0,0x16db40
  10b173:	00 00 00 00
  10b177:	c7 45 f4 00 00 00 00 	movl   $0x0,-0xc(%rbp)
  10b17e:	83 7d f4 04          	cmpl   $0x4,-0xc(%rbp)
  10b182:	0f 83 1d 00 00 00    	jae    10b1a5 <_ZN4acos8graphics15GraphicsManager4initEPNS_15FramebufferInfoE+0x45>
  10b188:	8b 45 f4             	mov    -0xc(%rbp),%eax
  10b18b:	48 c7 04 c5 20 db 16 	movq   $0x0,0x16db20(,%rax,8)
  10b192:	00 00 00 00 00
  10b197:	8b 45 f4             	mov    -0xc(%rbp),%eax
  10b19a:	83 c0 01             	add    $0x1,%eax
  10b19d:	89 45 f4             	mov    %eax,-0xc(%rbp)
  10b1a0:	e9 d9 ff ff ff       	jmp    10b17e <_ZN4acos8graphics15GraphicsManager4initEPNS_15FramebufferInfoE+0x1e>
  10b1a5:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  10b1a9:	e8 b2 00 00 00       	call   10b260 <_ZN4acos8graphics12_GLOBAL__N_122valid_boot_framebufferEPNS_15FramebufferInfoE>
  10b1ae:	a8 01                	test   $0x1,%al
  10b1b0:	0f 85 22 00 00 00    	jne    10b1d8 <_ZN4acos8graphics15GraphicsManager4initEPNS_15FramebufferInfoE+0x78>
  10b1b6:	e8 25 01 00 00       	call   10b2e0 <_ZN4acos8graphics12_GLOBAL__N_112boot_displayEv>
  10b1bb:	48 89 c7             	mov    %rax,%rdi
  10b1be:	31 c0                	xor    %eax,%eax
  10b1c0:	89 c6                	mov    %eax,%esi
  10b1c2:	e8 59 01 00 00       	call   10b320 <_ZN4acos8graphics12_GLOBAL__N_122BootFramebufferDisplay6attachEPNS0_11FramebufferE>
  10b1c7:	48 c7 04 25 48 db 16 	movq   $0x0,0x16db48
  10b1ce:	00 00 00 00 00
  10b1d3:	e9 78 00 00 00       	jmp    10b250 <_ZN4acos8graphics15GraphicsManager4initEPNS_15FramebufferInfoE+0xf0>
  10b1d8:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10b1dc:	48 8b 30             	mov    (%rax),%rsi
  10b1df:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10b1e3:	48 8b 50 08          	mov    0x8(%rax),%rdx
  10b1e7:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10b1eb:	8b 48 10             	mov    0x10(%rax),%ecx
  10b1ee:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10b1f2:	44 8b 40 14          	mov    0x14(%rax),%r8d
  10b1f6:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10b1fa:	44 8b 48 18          	mov    0x18(%rax),%r9d
  10b1fe:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10b202:	8b 40 1c             	mov    0x1c(%rax),%eax
  10b205:	48 bf 50 db 16 00 00 	movabs $0x16db50,%rdi
  10b20c:	00 00 00
  10b20f:	89 04 24             	mov    %eax,(%rsp)
  10b212:	e8 c9 02 00 00       	call   10b4e0 <_ZN4acos8graphics11FramebufferC1Emmjjjj>
  10b217:	48 b8 50 db 16 00 00 	movabs $0x16db50,%rax
  10b21e:	00 00 00
  10b221:	48 89 04 25 48 db 16 	mov    %rax,0x16db48
  10b228:	00
  10b229:	e8 b2 00 00 00       	call   10b2e0 <_ZN4acos8graphics12_GLOBAL__N_112boot_displayEv>
  10b22e:	48 89 c7             	mov    %rax,%rdi
  10b231:	48 8b 34 25 48 db 16 	mov    0x16db48,%rsi
  10b238:	00
  10b239:	e8 e2 00 00 00       	call   10b320 <_ZN4acos8graphics12_GLOBAL__N_122BootFramebufferDisplay6attachEPNS0_11FramebufferE>
  10b23e:	e8 9d 00 00 00       	call   10b2e0 <_ZN4acos8graphics12_GLOBAL__N_112boot_displayEv>
  10b243:	48 89 c7             	mov    %rax,%rdi
  10b246:	e8 75 fe ff ff       	call   10b0c0 <_ZN4acos8graphics15GraphicsManager16register_displayEPNS0_13DisplayDeviceE>
  10b24b:	e8 20 25 00 00       	call   10d770 <_ZN4acos8graphics11FontManager10initializeEv>
  10b250:	48 83 c4 20          	add    $0x20,%rsp
  10b254:	5d                   	pop    %rbp
  10b255:	c3                   	ret
  10b256:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
  10b25d:	00 00 00

000000000010b260 <_ZN4acos8graphics12_GLOBAL__N_122valid_boot_framebufferEPNS_15FramebufferInfoE>:
  10b260:	55                   	push   %rbp
  10b261:	48 89 e5             	mov    %rsp,%rbp
  10b264:	48 83 ec 10          	sub    $0x10,%rsp
  10b268:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10b26c:	31 c0                	xor    %eax,%eax
  10b26e:	48 83 7d f8 00       	cmpq   $0x0,-0x8(%rbp)
  10b273:	88 45 f7             	mov    %al,-0x9(%rbp)
  10b276:	0f 84 47 00 00 00    	je     10b2c3 <_ZN4acos8graphics12_GLOBAL__N_122valid_boot_framebufferEPNS_15FramebufferInfoE+0x63>
  10b27c:	48 8b 4d f8          	mov    -0x8(%rbp),%rcx
  10b280:	31 c0                	xor    %eax,%eax
  10b282:	48 83 39 00          	cmpq   $0x0,(%rcx)
  10b286:	88 45 f7             	mov    %al,-0x9(%rbp)
  10b289:	0f 84 34 00 00 00    	je     10b2c3 <_ZN4acos8graphics12_GLOBAL__N_122valid_boot_framebufferEPNS_15FramebufferInfoE+0x63>
  10b28f:	48 8b 4d f8          	mov    -0x8(%rbp),%rcx
  10b293:	31 c0                	xor    %eax,%eax
  10b295:	83 79 10 00          	cmpl   $0x0,0x10(%rcx)
  10b299:	88 45 f7             	mov    %al,-0x9(%rbp)
  10b29c:	0f 84 21 00 00 00    	je     10b2c3 <_ZN4acos8graphics12_GLOBAL__N_122valid_boot_framebufferEPNS_15FramebufferInfoE+0x63>
  10b2a2:	48 8b 4d f8          	mov    -0x8(%rbp),%rcx
  10b2a6:	31 c0                	xor    %eax,%eax
  10b2a8:	83 79 14 00          	cmpl   $0x0,0x14(%rcx)
  10b2ac:	88 45 f7             	mov    %al,-0x9(%rbp)
  10b2af:	0f 84 0e 00 00 00    	je     10b2c3 <_ZN4acos8graphics12_GLOBAL__N_122valid_boot_framebufferEPNS_15FramebufferInfoE+0x63>
  10b2b5:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10b2b9:	83 78 18 00          	cmpl   $0x0,0x18(%rax)
  10b2bd:	0f 95 c0             	setne  %al
  10b2c0:	88 45 f7             	mov    %al,-0x9(%rbp)
  10b2c3:	8a 45 f7             	mov    -0x9(%rbp),%al
  10b2c6:	24 01                	and    $0x1,%al
  10b2c8:	0f b6 c0             	movzbl %al,%eax
  10b2cb:	48 83 c4 10          	add    $0x10,%rsp
  10b2cf:	5d                   	pop    %rbp
  10b2d0:	c3                   	ret
  10b2d1:	66 66 66 66 66 66 2e 	data16 data16 data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
  10b2d8:	0f 1f 84 00 00 00 00
  10b2df:	00

000000000010b2e0 <_ZN4acos8graphics12_GLOBAL__N_112boot_displayEv>:
  10b2e0:	55                   	push   %rbp
  10b2e1:	48 89 e5             	mov    %rsp,%rbp
  10b2e4:	48 83 3c 25 88 db 16 	cmpq   $0x0,0x16db88
  10b2eb:	00 00
  10b2ed:	0f 85 21 00 00 00    	jne    10b314 <_ZN4acos8graphics12_GLOBAL__N_112boot_displayEv+0x34>
  10b2f3:	48 bf 90 db 16 00 00 	movabs $0x16db90,%rdi
  10b2fa:	00 00 00
  10b2fd:	e8 4e 00 00 00       	call   10b350 <_ZN4acos8graphics12_GLOBAL__N_122BootFramebufferDisplayC2Ev>
  10b302:	48 b8 90 db 16 00 00 	movabs $0x16db90,%rax
  10b309:	00 00 00
  10b30c:	48 89 04 25 88 db 16 	mov    %rax,0x16db88
  10b313:	00
  10b314:	48 8b 04 25 88 db 16 	mov    0x16db88,%rax
  10b31b:	00
  10b31c:	5d                   	pop    %rbp
  10b31d:	c3                   	ret
  10b31e:	66 90                	xchg   %ax,%ax

000000000010b320 <_ZN4acos8graphics12_GLOBAL__N_122BootFramebufferDisplay6attachEPNS0_11FramebufferE>:
  10b320:	55                   	push   %rbp
  10b321:	48 89 e5             	mov    %rsp,%rbp
  10b324:	48 83 ec 10          	sub    $0x10,%rsp
  10b328:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10b32c:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  10b330:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10b334:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
  10b338:	48 89 48 08          	mov    %rcx,0x8(%rax)
  10b33c:	48 83 7d f0 00       	cmpq   $0x0,-0x10(%rbp)
  10b341:	0f 95 c1             	setne  %cl
  10b344:	80 e1 01             	and    $0x1,%cl
  10b347:	88 48 10             	mov    %cl,0x10(%rax)
  10b34a:	48 83 c4 10          	add    $0x10,%rsp
  10b34e:	5d                   	pop    %rbp
  10b34f:	c3                   	ret

000000000010b350 <_ZN4acos8graphics12_GLOBAL__N_122BootFramebufferDisplayC2Ev>:
  10b350:	55                   	push   %rbp
  10b351:	48 89 e5             	mov    %rsp,%rbp
  10b354:	48 83 ec 10          	sub    $0x10,%rsp
  10b358:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10b35c:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  10b360:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  10b364:	e8 07 3b 00 00       	call   10ee70 <_ZN4acos8graphics13DisplayDeviceC2Ev>
  10b369:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10b36d:	48 b9 c8 f7 10 00 00 	movabs $0x10f7c8,%rcx
  10b374:	00 00 00
  10b377:	48 83 c1 10          	add    $0x10,%rcx
  10b37b:	48 89 08             	mov    %rcx,(%rax)
  10b37e:	48 c7 40 08 00 00 00 	movq   $0x0,0x8(%rax)
  10b385:	00
  10b386:	c6 40 10 00          	movb   $0x0,0x10(%rax)
  10b38a:	48 83 c4 10          	add    $0x10,%rsp
  10b38e:	5d                   	pop    %rbp
  10b38f:	c3                   	ret

000000000010b390 <_ZN4acos8graphics12_GLOBAL__N_122BootFramebufferDisplayD2Ev>:
  10b390:	55                   	push   %rbp
  10b391:	48 89 e5             	mov    %rsp,%rbp
  10b394:	48 83 ec 10          	sub    $0x10,%rsp
  10b398:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10b39c:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  10b3a0:	e8 fb 3a 00 00       	call   10eea0 <_ZN4acos8graphics13DisplayDeviceD2Ev>
  10b3a5:	48 83 c4 10          	add    $0x10,%rsp
  10b3a9:	5d                   	pop    %rbp
  10b3aa:	c3                   	ret
  10b3ab:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

000000000010b3b0 <_ZN4acos8graphics12_GLOBAL__N_122BootFramebufferDisplayD0Ev>:
  10b3b0:	55                   	push   %rbp
  10b3b1:	48 89 e5             	mov    %rsp,%rbp
  10b3b4:	48 83 ec 10          	sub    $0x10,%rsp
  10b3b8:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10b3bc:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  10b3c0:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  10b3c4:	e8 c7 ff ff ff       	call   10b390 <_ZN4acos8graphics12_GLOBAL__N_122BootFramebufferDisplayD2Ev>
  10b3c9:	48 8b 7d f0          	mov    -0x10(%rbp),%rdi
  10b3cd:	e8 5e 50 ff ff       	call   100430 <_ZdlPv>
  10b3d2:	48 83 c4 10          	add    $0x10,%rsp
  10b3d6:	5d                   	pop    %rbp
  10b3d7:	c3                   	ret
  10b3d8:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  10b3df:	00

000000000010b3e0 <_ZN4acos8graphics12_GLOBAL__N_122BootFramebufferDisplay10initializeEv>:
  10b3e0:	55                   	push   %rbp
  10b3e1:	48 89 e5             	mov    %rsp,%rbp
  10b3e4:	48 83 ec 18          	sub    $0x18,%rsp
  10b3e8:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10b3ec:	48 8b 4d f8          	mov    -0x8(%rbp),%rcx
  10b3f0:	48 89 4d e8          	mov    %rcx,-0x18(%rbp)
  10b3f4:	31 c0                	xor    %eax,%eax
  10b3f6:	f6 41 10 01          	testb  $0x1,0x10(%rcx)
  10b3fa:	88 45 f7             	mov    %al,-0x9(%rbp)
  10b3fd:	0f 84 0f 00 00 00    	je     10b412 <_ZN4acos8graphics12_GLOBAL__N_122BootFramebufferDisplay10initializeEv+0x32>
  10b403:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  10b407:	48 83 78 08 00       	cmpq   $0x0,0x8(%rax)
  10b40c:	0f 95 c0             	setne  %al
  10b40f:	88 45 f7             	mov    %al,-0x9(%rbp)
  10b412:	8a 45 f7             	mov    -0x9(%rbp),%al
  10b415:	24 01                	and    $0x1,%al
  10b417:	0f b6 c0             	movzbl %al,%eax
  10b41a:	48 83 c4 18          	add    $0x18,%rsp
  10b41e:	5d                   	pop    %rbp
  10b41f:	c3                   	ret

000000000010b420 <_ZN4acos8graphics12_GLOBAL__N_122BootFramebufferDisplay15get_framebufferEv>:
  10b420:	55                   	push   %rbp
  10b421:	48 89 e5             	mov    %rsp,%rbp
  10b424:	50                   	push   %rax
  10b425:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10b429:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10b42d:	48 8b 40 08          	mov    0x8(%rax),%rax
  10b431:	48 83 c4 08          	add    $0x8,%rsp
  10b435:	5d                   	pop    %rbp
  10b436:	c3                   	ret
  10b437:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
  10b43e:	00 00

000000000010b440 <_ZNK4acos8graphics12_GLOBAL__N_122BootFramebufferDisplay5widthEv>:
  10b440:	55                   	push   %rbp
  10b441:	48 89 e5             	mov    %rsp,%rbp
  10b444:	48 83 ec 20          	sub    $0x20,%rsp
  10b448:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10b44c:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10b450:	48 89 45 f0          	mov    %rax,-0x10(%rbp)
  10b454:	48 83 78 08 00       	cmpq   $0x0,0x8(%rax)
  10b459:	0f 84 15 00 00 00    	je     10b474 <_ZNK4acos8graphics12_GLOBAL__N_122BootFramebufferDisplay5widthEv+0x34>
  10b45f:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10b463:	48 8b 78 08          	mov    0x8(%rax),%rdi
  10b467:	e8 f4 36 00 00       	call   10eb60 <_ZNK4acos8graphics11Framebuffer5widthEv>
  10b46c:	89 45 ec             	mov    %eax,-0x14(%rbp)
  10b46f:	e9 0a 00 00 00       	jmp    10b47e <_ZNK4acos8graphics12_GLOBAL__N_122BootFramebufferDisplay5widthEv+0x3e>
  10b474:	31 c0                	xor    %eax,%eax
  10b476:	89 45 ec             	mov    %eax,-0x14(%rbp)
  10b479:	e9 00 00 00 00       	jmp    10b47e <_ZNK4acos8graphics12_GLOBAL__N_122BootFramebufferDisplay5widthEv+0x3e>
  10b47e:	8b 45 ec             	mov    -0x14(%rbp),%eax
  10b481:	48 83 c4 20          	add    $0x20,%rsp
  10b485:	5d                   	pop    %rbp
  10b486:	c3                   	ret
  10b487:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
  10b48e:	00 00

000000000010b490 <_ZNK4acos8graphics12_GLOBAL__N_122BootFramebufferDisplay6heightEv>:
  10b490:	55                   	push   %rbp
  10b491:	48 89 e5             	mov    %rsp,%rbp
  10b494:	48 83 ec 20          	sub    $0x20,%rsp
  10b498:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10b49c:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10b4a0:	48 89 45 f0          	mov    %rax,-0x10(%rbp)
  10b4a4:	48 83 78 08 00       	cmpq   $0x0,0x8(%rax)
  10b4a9:	0f 84 15 00 00 00    	je     10b4c4 <_ZNK4acos8graphics12_GLOBAL__N_122BootFramebufferDisplay6heightEv+0x34>
  10b4af:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10b4b3:	48 8b 78 08          	mov    0x8(%rax),%rdi
  10b4b7:	e8 c4 36 00 00       	call   10eb80 <_ZNK4acos8graphics11Framebuffer6heightEv>
  10b4bc:	89 45 ec             	mov    %eax,-0x14(%rbp)
  10b4bf:	e9 0a 00 00 00       	jmp    10b4ce <_ZNK4acos8graphics12_GLOBAL__N_122BootFramebufferDisplay6heightEv+0x3e>
  10b4c4:	31 c0                	xor    %eax,%eax
  10b4c6:	89 45 ec             	mov    %eax,-0x14(%rbp)
  10b4c9:	e9 00 00 00 00       	jmp    10b4ce <_ZNK4acos8graphics12_GLOBAL__N_122BootFramebufferDisplay6heightEv+0x3e>
  10b4ce:	8b 45 ec             	mov    -0x14(%rbp),%eax
  10b4d1:	48 83 c4 20          	add    $0x20,%rsp
  10b4d5:	5d                   	pop    %rbp
  10b4d6:	c3                   	ret
  10b4d7:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
  10b4de:	00 00

000000000010b4e0 <_ZN4acos8graphics11FramebufferC1Emmjjjj>:
  10b4e0:	55                   	push   %rbp
  10b4e1:	48 89 e5             	mov    %rsp,%rbp
  10b4e4:	48 83 ec 28          	sub    $0x28,%rsp
  10b4e8:	8b 45 10             	mov    0x10(%rbp),%eax
  10b4eb:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10b4ef:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  10b4f3:	48 89 55 e8          	mov    %rdx,-0x18(%rbp)
  10b4f7:	89 4d e4             	mov    %ecx,-0x1c(%rbp)
  10b4fa:	44 89 45 e0          	mov    %r8d,-0x20(%rbp)
  10b4fe:	44 89 4d dc          	mov    %r9d,-0x24(%rbp)
  10b502:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10b506:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
  10b50a:	48 89 08             	mov    %rcx,(%rax)
  10b50d:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  10b511:	48 89 48 08          	mov    %rcx,0x8(%rax)
  10b515:	8b 4d e4             	mov    -0x1c(%rbp),%ecx
  10b518:	89 48 10             	mov    %ecx,0x10(%rax)
  10b51b:	8b 4d e0             	mov    -0x20(%rbp),%ecx
  10b51e:	89 48 14             	mov    %ecx,0x14(%rax)
  10b521:	8b 4d dc             	mov    -0x24(%rbp),%ecx
  10b524:	89 48 18             	mov    %ecx,0x18(%rax)
  10b527:	8b 4d 10             	mov    0x10(%rbp),%ecx
  10b52a:	89 48 1c             	mov    %ecx,0x1c(%rax)
  10b52d:	48 83 c4 28          	add    $0x28,%rsp
  10b531:	5d                   	pop    %rbp
  10b532:	c3                   	ret
  10b533:	66 66 66 66 2e 0f 1f 	data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
  10b53a:	84 00 00 00 00 00

000000000010b540 <_ZN4acos8graphics11Framebuffer9put_pixelEjjj>:
  10b540:	55                   	push   %rbp
  10b541:	48 89 e5             	mov    %rsp,%rbp
  10b544:	48 83 ec 28          	sub    $0x28,%rsp
  10b548:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10b54c:	89 75 f4             	mov    %esi,-0xc(%rbp)
  10b54f:	89 55 f0             	mov    %edx,-0x10(%rbp)
  10b552:	89 4d ec             	mov    %ecx,-0x14(%rbp)
  10b555:	48 8b 4d f8          	mov    -0x8(%rbp),%rcx
  10b559:	48 89 4d d8          	mov    %rcx,-0x28(%rbp)
  10b55d:	8b 45 f4             	mov    -0xc(%rbp),%eax
  10b560:	3b 41 10             	cmp    0x10(%rcx),%eax
  10b563:	0f 83 10 00 00 00    	jae    10b579 <_ZN4acos8graphics11Framebuffer9put_pixelEjjj+0x39>
  10b569:	48 8b 4d d8          	mov    -0x28(%rbp),%rcx
  10b56d:	8b 45 f0             	mov    -0x10(%rbp),%eax
  10b570:	3b 41 14             	cmp    0x14(%rcx),%eax
  10b573:	0f 82 05 00 00 00    	jb     10b57e <_ZN4acos8graphics11Framebuffer9put_pixelEjjj+0x3e>
  10b579:	e9 21 00 00 00       	jmp    10b59f <_ZN4acos8graphics11Framebuffer9put_pixelEjjj+0x5f>
  10b57e:	48 8b 75 d8          	mov    -0x28(%rbp),%rsi
  10b582:	48 8b 06             	mov    (%rsi),%rax
  10b585:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  10b589:	8b 55 ec             	mov    -0x14(%rbp),%edx
  10b58c:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  10b590:	8b 4d f0             	mov    -0x10(%rbp),%ecx
  10b593:	0f af 4e 18          	imul   0x18(%rsi),%ecx
  10b597:	03 4d f4             	add    -0xc(%rbp),%ecx
  10b59a:	89 c9                	mov    %ecx,%ecx
  10b59c:	89 14 88             	mov    %edx,(%rax,%rcx,4)
  10b59f:	48 83 c4 28          	add    $0x28,%rsp
  10b5a3:	5d                   	pop    %rbp
  10b5a4:	c3                   	ret
  10b5a5:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  10b5ac:	00 00 00 00

000000000010b5b0 <_ZNK4acos8graphics11Framebuffer9get_pixelEjj>:
  10b5b0:	55                   	push   %rbp
  10b5b1:	48 89 e5             	mov    %rsp,%rbp
  10b5b4:	48 83 ec 28          	sub    $0x28,%rsp
  10b5b8:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  10b5bc:	89 75 ec             	mov    %esi,-0x14(%rbp)
  10b5bf:	89 55 e8             	mov    %edx,-0x18(%rbp)
  10b5c2:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
  10b5c6:	48 89 4d d8          	mov    %rcx,-0x28(%rbp)
  10b5ca:	8b 45 ec             	mov    -0x14(%rbp),%eax
  10b5cd:	3b 41 10             	cmp    0x10(%rcx),%eax
  10b5d0:	0f 83 10 00 00 00    	jae    10b5e6 <_ZNK4acos8graphics11Framebuffer9get_pixelEjj+0x36>
  10b5d6:	48 8b 4d d8          	mov    -0x28(%rbp),%rcx
  10b5da:	8b 45 e8             	mov    -0x18(%rbp),%eax
  10b5dd:	3b 41 14             	cmp    0x14(%rcx),%eax
  10b5e0:	0f 82 0c 00 00 00    	jb     10b5f2 <_ZNK4acos8graphics11Framebuffer9get_pixelEjj+0x42>
  10b5e6:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%rbp)
  10b5ed:	e9 21 00 00 00       	jmp    10b613 <_ZNK4acos8graphics11Framebuffer9get_pixelEjj+0x63>
  10b5f2:	48 8b 55 d8          	mov    -0x28(%rbp),%rdx
  10b5f6:	48 8b 02             	mov    (%rdx),%rax
  10b5f9:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  10b5fd:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  10b601:	8b 4d e8             	mov    -0x18(%rbp),%ecx
  10b604:	0f af 4a 18          	imul   0x18(%rdx),%ecx
  10b608:	03 4d ec             	add    -0x14(%rbp),%ecx
  10b60b:	89 c9                	mov    %ecx,%ecx
  10b60d:	8b 04 88             	mov    (%rax,%rcx,4),%eax
  10b610:	89 45 fc             	mov    %eax,-0x4(%rbp)
  10b613:	8b 45 fc             	mov    -0x4(%rbp),%eax
  10b616:	48 83 c4 28          	add    $0x28,%rsp
  10b61a:	5d                   	pop    %rbp
  10b61b:	c3                   	ret
  10b61c:	0f 1f 40 00          	nopl   0x0(%rax)

000000000010b620 <_ZN4acos8graphics11Framebuffer5clearEj>:
  10b620:	55                   	push   %rbp
  10b621:	48 89 e5             	mov    %rsp,%rbp
  10b624:	48 83 ec 10          	sub    $0x10,%rsp
  10b628:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10b62c:	89 75 f4             	mov    %esi,-0xc(%rbp)
  10b62f:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  10b633:	8b 4f 10             	mov    0x10(%rdi),%ecx
  10b636:	44 8b 47 14          	mov    0x14(%rdi),%r8d
  10b63a:	44 8b 4d f4          	mov    -0xc(%rbp),%r9d
  10b63e:	31 d2                	xor    %edx,%edx
  10b640:	89 d6                	mov    %edx,%esi
  10b642:	e8 09 00 00 00       	call   10b650 <_ZN4acos8graphics11Framebuffer9fill_rectEjjjjj>
  10b647:	48 83 c4 10          	add    $0x10,%rsp
  10b64b:	5d                   	pop    %rbp
  10b64c:	c3                   	ret
  10b64d:	0f 1f 00             	nopl   (%rax)

000000000010b650 <_ZN4acos8graphics11Framebuffer9fill_rectEjjjjj>:
  10b650:	55                   	push   %rbp
  10b651:	48 89 e5             	mov    %rsp,%rbp
  10b654:	48 83 ec 40          	sub    $0x40,%rsp
  10b658:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10b65c:	89 75 f4             	mov    %esi,-0xc(%rbp)
  10b65f:	89 55 f0             	mov    %edx,-0x10(%rbp)
  10b662:	89 4d ec             	mov    %ecx,-0x14(%rbp)
  10b665:	44 89 45 e8          	mov    %r8d,-0x18(%rbp)
  10b669:	44 89 4d e4          	mov    %r9d,-0x1c(%rbp)
  10b66d:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10b671:	48 89 45 d0          	mov    %rax,-0x30(%rbp)
  10b675:	8b 45 f0             	mov    -0x10(%rbp),%eax
  10b678:	89 45 e0             	mov    %eax,-0x20(%rbp)
  10b67b:	8b 4d e0             	mov    -0x20(%rbp),%ecx
  10b67e:	8b 55 f0             	mov    -0x10(%rbp),%edx
  10b681:	03 55 e8             	add    -0x18(%rbp),%edx
  10b684:	31 c0                	xor    %eax,%eax
  10b686:	39 d1                	cmp    %edx,%ecx
  10b688:	88 45 cf             	mov    %al,-0x31(%rbp)
  10b68b:	0f 83 10 00 00 00    	jae    10b6a1 <_ZN4acos8graphics11Framebuffer9fill_rectEjjjjj+0x51>
  10b691:	48 8b 4d d0          	mov    -0x30(%rbp),%rcx
  10b695:	8b 45 e0             	mov    -0x20(%rbp),%eax
  10b698:	3b 41 14             	cmp    0x14(%rcx),%eax
  10b69b:	0f 92 c0             	setb   %al
  10b69e:	88 45 cf             	mov    %al,-0x31(%rbp)
  10b6a1:	8a 45 cf             	mov    -0x31(%rbp),%al
  10b6a4:	a8 01                	test   $0x1,%al
  10b6a6:	0f 85 05 00 00 00    	jne    10b6b1 <_ZN4acos8graphics11Framebuffer9fill_rectEjjjjj+0x61>
  10b6ac:	e9 6f 00 00 00       	jmp    10b720 <_ZN4acos8graphics11Framebuffer9fill_rectEjjjjj+0xd0>
  10b6b1:	8b 45 f4             	mov    -0xc(%rbp),%eax
  10b6b4:	89 45 dc             	mov    %eax,-0x24(%rbp)
  10b6b7:	8b 4d dc             	mov    -0x24(%rbp),%ecx
  10b6ba:	8b 55 f4             	mov    -0xc(%rbp),%edx
  10b6bd:	03 55 ec             	add    -0x14(%rbp),%edx
  10b6c0:	31 c0                	xor    %eax,%eax
  10b6c2:	39 d1                	cmp    %edx,%ecx
  10b6c4:	88 45 ce             	mov    %al,-0x32(%rbp)
  10b6c7:	0f 83 10 00 00 00    	jae    10b6dd <_ZN4acos8graphics11Framebuffer9fill_rectEjjjjj+0x8d>
  10b6cd:	48 8b 4d d0          	mov    -0x30(%rbp),%rcx
  10b6d1:	8b 45 dc             	mov    -0x24(%rbp),%eax
  10b6d4:	3b 41 10             	cmp    0x10(%rcx),%eax
  10b6d7:	0f 92 c0             	setb   %al
  10b6da:	88 45 ce             	mov    %al,-0x32(%rbp)
  10b6dd:	8a 45 ce             	mov    -0x32(%rbp),%al
  10b6e0:	a8 01                	test   $0x1,%al
  10b6e2:	0f 85 05 00 00 00    	jne    10b6ed <_ZN4acos8graphics11Framebuffer9fill_rectEjjjjj+0x9d>
  10b6e8:	e9 20 00 00 00       	jmp    10b70d <_ZN4acos8graphics11Framebuffer9fill_rectEjjjjj+0xbd>
  10b6ed:	48 8b 7d d0          	mov    -0x30(%rbp),%rdi
  10b6f1:	8b 75 dc             	mov    -0x24(%rbp),%esi
  10b6f4:	8b 55 e0             	mov    -0x20(%rbp),%edx
  10b6f7:	8b 4d e4             	mov    -0x1c(%rbp),%ecx
  10b6fa:	e8 41 fe ff ff       	call   10b540 <_ZN4acos8graphics11Framebuffer9put_pixelEjjj>
  10b6ff:	8b 45 dc             	mov    -0x24(%rbp),%eax
  10b702:	83 c0 01             	add    $0x1,%eax
  10b705:	89 45 dc             	mov    %eax,-0x24(%rbp)
  10b708:	e9 aa ff ff ff       	jmp    10b6b7 <_ZN4acos8graphics11Framebuffer9fill_rectEjjjjj+0x67>
  10b70d:	e9 00 00 00 00       	jmp    10b712 <_ZN4acos8graphics11Framebuffer9fill_rectEjjjjj+0xc2>
  10b712:	8b 45 e0             	mov    -0x20(%rbp),%eax
  10b715:	83 c0 01             	add    $0x1,%eax
  10b718:	89 45 e0             	mov    %eax,-0x20(%rbp)
  10b71b:	e9 5b ff ff ff       	jmp    10b67b <_ZN4acos8graphics11Framebuffer9fill_rectEjjjjj+0x2b>
  10b720:	48 83 c4 40          	add    $0x40,%rsp
  10b724:	5d                   	pop    %rbp
  10b725:	c3                   	ret
  10b726:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
  10b72d:	00 00 00

000000000010b730 <_ZN4acos8graphics8RendererC1EPNS0_11FramebufferE>:
  10b730:	55                   	push   %rbp
  10b731:	48 89 e5             	mov    %rsp,%rbp
  10b734:	48 83 ec 10          	sub    $0x10,%rsp
  10b738:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10b73c:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  10b740:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10b744:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
  10b748:	48 89 08             	mov    %rcx,(%rax)
  10b74b:	c6 40 18 00          	movb   $0x0,0x18(%rax)
  10b74f:	48 83 c4 10          	add    $0x10,%rsp
  10b753:	5d                   	pop    %rbp
  10b754:	c3                   	ret
  10b755:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  10b75c:	00 00 00 00

000000000010b760 <_ZN4acos8graphics8Renderer10draw_pixelEjjj>:
  10b760:	55                   	push   %rbp
  10b761:	48 89 e5             	mov    %rsp,%rbp
  10b764:	48 83 ec 20          	sub    $0x20,%rsp
  10b768:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10b76c:	89 75 f4             	mov    %esi,-0xc(%rbp)
  10b76f:	89 55 f0             	mov    %edx,-0x10(%rbp)
  10b772:	89 4d ec             	mov    %ecx,-0x14(%rbp)
  10b775:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  10b779:	48 89 7d e0          	mov    %rdi,-0x20(%rbp)
  10b77d:	8b 75 f4             	mov    -0xc(%rbp),%esi
  10b780:	8b 55 f0             	mov    -0x10(%rbp),%edx
  10b783:	e8 38 37 00 00       	call   10eec0 <_ZNK4acos8graphics8Renderer10is_clippedEjj>
  10b788:	a8 01                	test   $0x1,%al
  10b78a:	0f 85 05 00 00 00    	jne    10b795 <_ZN4acos8graphics8Renderer10draw_pixelEjjj+0x35>
  10b790:	e9 05 00 00 00       	jmp    10b79a <_ZN4acos8graphics8Renderer10draw_pixelEjjj+0x3a>
  10b795:	e9 15 00 00 00       	jmp    10b7af <_ZN4acos8graphics8Renderer10draw_pixelEjjj+0x4f>
  10b79a:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  10b79e:	48 8b 38             	mov    (%rax),%rdi
  10b7a1:	8b 75 f4             	mov    -0xc(%rbp),%esi
  10b7a4:	8b 55 f0             	mov    -0x10(%rbp),%edx
  10b7a7:	8b 4d ec             	mov    -0x14(%rbp),%ecx
  10b7aa:	e8 91 fd ff ff       	call   10b540 <_ZN4acos8graphics11Framebuffer9put_pixelEjjj>
  10b7af:	48 83 c4 20          	add    $0x20,%rsp
  10b7b3:	5d                   	pop    %rbp
  10b7b4:	c3                   	ret
  10b7b5:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  10b7bc:	00 00 00 00

000000000010b7c0 <_ZN4acos8graphics8Renderer11blend_pixelEjjjh>:
  10b7c0:	55                   	push   %rbp
  10b7c1:	48 89 e5             	mov    %rsp,%rbp
  10b7c4:	48 83 ec 30          	sub    $0x30,%rsp
  10b7c8:	44 88 c0             	mov    %r8b,%al
  10b7cb:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10b7cf:	89 75 f4             	mov    %esi,-0xc(%rbp)
  10b7d2:	89 55 f0             	mov    %edx,-0x10(%rbp)
  10b7d5:	89 4d ec             	mov    %ecx,-0x14(%rbp)
  10b7d8:	88 45 eb             	mov    %al,-0x15(%rbp)
  10b7db:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  10b7df:	48 89 7d d0          	mov    %rdi,-0x30(%rbp)
  10b7e3:	8b 75 f4             	mov    -0xc(%rbp),%esi
  10b7e6:	8b 55 f0             	mov    -0x10(%rbp),%edx
  10b7e9:	e8 d2 36 00 00       	call   10eec0 <_ZNK4acos8graphics8Renderer10is_clippedEjj>
  10b7ee:	a8 01                	test   $0x1,%al
  10b7f0:	0f 85 05 00 00 00    	jne    10b7fb <_ZN4acos8graphics8Renderer11blend_pixelEjjjh+0x3b>
  10b7f6:	e9 05 00 00 00       	jmp    10b800 <_ZN4acos8graphics8Renderer11blend_pixelEjjjh+0x40>
  10b7fb:	e9 e2 00 00 00       	jmp    10b8e2 <_ZN4acos8graphics8Renderer11blend_pixelEjjjh+0x122>
  10b800:	0f b6 45 eb          	movzbl -0x15(%rbp),%eax
  10b804:	3d ff 00 00 00       	cmp    $0xff,%eax
  10b809:	0f 85 1a 00 00 00    	jne    10b829 <_ZN4acos8graphics8Renderer11blend_pixelEjjjh+0x69>
  10b80f:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  10b813:	48 8b 38             	mov    (%rax),%rdi
  10b816:	8b 75 f4             	mov    -0xc(%rbp),%esi
  10b819:	8b 55 f0             	mov    -0x10(%rbp),%edx
  10b81c:	8b 4d ec             	mov    -0x14(%rbp),%ecx
  10b81f:	e8 1c fd ff ff       	call   10b540 <_ZN4acos8graphics11Framebuffer9put_pixelEjjj>
  10b824:	e9 b9 00 00 00       	jmp    10b8e2 <_ZN4acos8graphics8Renderer11blend_pixelEjjjh+0x122>
  10b829:	0f b6 45 eb          	movzbl -0x15(%rbp),%eax
  10b82d:	83 f8 00             	cmp    $0x0,%eax
  10b830:	0f 85 05 00 00 00    	jne    10b83b <_ZN4acos8graphics8Renderer11blend_pixelEjjjh+0x7b>
  10b836:	e9 a7 00 00 00       	jmp    10b8e2 <_ZN4acos8graphics8Renderer11blend_pixelEjjjh+0x122>
  10b83b:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  10b83f:	48 8b 38             	mov    (%rax),%rdi
  10b842:	8b 75 f4             	mov    -0xc(%rbp),%esi
  10b845:	8b 55 f0             	mov    -0x10(%rbp),%edx
  10b848:	e8 63 fd ff ff       	call   10b5b0 <_ZNK4acos8graphics11Framebuffer9get_pixelEjj>
  10b84d:	89 c1                	mov    %eax,%ecx
  10b84f:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  10b853:	89 4d e4             	mov    %ecx,-0x1c(%rbp)
  10b856:	8b 4d ec             	mov    -0x14(%rbp),%ecx
  10b859:	81 e1 ff 00 ff 00    	and    $0xff00ff,%ecx
  10b85f:	0f b6 55 eb          	movzbl -0x15(%rbp),%edx
  10b863:	0f af ca             	imul   %edx,%ecx
  10b866:	8b 55 e4             	mov    -0x1c(%rbp),%edx
  10b869:	81 e2 ff 00 ff 00    	and    $0xff00ff,%edx
  10b86f:	0f b6 7d eb          	movzbl -0x15(%rbp),%edi
  10b873:	be ff 00 00 00       	mov    $0xff,%esi
  10b878:	29 fe                	sub    %edi,%esi
  10b87a:	0f af d6             	imul   %esi,%edx
  10b87d:	01 d1                	add    %edx,%ecx
  10b87f:	89 4d e0             	mov    %ecx,-0x20(%rbp)
  10b882:	8b 4d ec             	mov    -0x14(%rbp),%ecx
  10b885:	81 e1 00 ff 00 00    	and    $0xff00,%ecx
  10b88b:	0f b6 55 eb          	movzbl -0x15(%rbp),%edx
  10b88f:	0f af ca             	imul   %edx,%ecx
  10b892:	8b 55 e4             	mov    -0x1c(%rbp),%edx
  10b895:	81 e2 00 ff 00 00    	and    $0xff00,%edx
  10b89b:	0f b6 7d eb          	movzbl -0x15(%rbp),%edi
  10b89f:	be ff 00 00 00       	mov    $0xff,%esi
  10b8a4:	29 fe                	sub    %edi,%esi
  10b8a6:	0f af d6             	imul   %esi,%edx
  10b8a9:	01 d1                	add    %edx,%ecx
  10b8ab:	89 4d dc             	mov    %ecx,-0x24(%rbp)
  10b8ae:	8b 4d e0             	mov    -0x20(%rbp),%ecx
  10b8b1:	c1 e9 08             	shr    $0x8,%ecx
  10b8b4:	81 e1 ff 00 ff 00    	and    $0xff00ff,%ecx
  10b8ba:	8b 55 dc             	mov    -0x24(%rbp),%edx
  10b8bd:	c1 ea 08             	shr    $0x8,%edx
  10b8c0:	81 e2 00 ff 00 00    	and    $0xff00,%edx
  10b8c6:	09 d1                	or     %edx,%ecx
  10b8c8:	89 4d d8             	mov    %ecx,-0x28(%rbp)
  10b8cb:	48 8b 38             	mov    (%rax),%rdi
  10b8ce:	8b 75 f4             	mov    -0xc(%rbp),%esi
  10b8d1:	8b 55 f0             	mov    -0x10(%rbp),%edx
  10b8d4:	8b 4d d8             	mov    -0x28(%rbp),%ecx
  10b8d7:	81 c9 00 00 00 ff    	or     $0xff000000,%ecx
  10b8dd:	e8 5e fc ff ff       	call   10b540 <_ZN4acos8graphics11Framebuffer9put_pixelEjjj>
  10b8e2:	48 83 c4 30          	add    $0x30,%rsp
  10b8e6:	5d                   	pop    %rbp
  10b8e7:	c3                   	ret
  10b8e8:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  10b8ef:	00

000000000010b8f0 <_ZN4acos8graphics8Renderer9draw_lineEjjjjj>:
  10b8f0:	55                   	push   %rbp
  10b8f1:	48 89 e5             	mov    %rsp,%rbp
  10b8f4:	48 83 ec 70          	sub    $0x70,%rsp
  10b8f8:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10b8fc:	89 75 f4             	mov    %esi,-0xc(%rbp)
  10b8ff:	89 55 f0             	mov    %edx,-0x10(%rbp)
  10b902:	89 4d ec             	mov    %ecx,-0x14(%rbp)
  10b905:	44 89 45 e8          	mov    %r8d,-0x18(%rbp)
  10b909:	44 89 4d e4          	mov    %r9d,-0x1c(%rbp)
  10b90d:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10b911:	48 89 45 98          	mov    %rax,-0x68(%rbp)
  10b915:	8b 45 f4             	mov    -0xc(%rbp),%eax
  10b918:	89 45 e0             	mov    %eax,-0x20(%rbp)
  10b91b:	8b 45 f0             	mov    -0x10(%rbp),%eax
  10b91e:	89 45 dc             	mov    %eax,-0x24(%rbp)
  10b921:	8b 45 ec             	mov    -0x14(%rbp),%eax
  10b924:	89 45 d8             	mov    %eax,-0x28(%rbp)
  10b927:	8b 45 e8             	mov    -0x18(%rbp),%eax
  10b92a:	89 45 d4             	mov    %eax,-0x2c(%rbp)
  10b92d:	8b 7d d4             	mov    -0x2c(%rbp),%edi
  10b930:	2b 7d dc             	sub    -0x24(%rbp),%edi
  10b933:	e8 98 01 00 00       	call   10bad0 <_ZN4acos8graphics12_GLOBAL__N_13absIiEET_S3_>
  10b938:	89 45 a0             	mov    %eax,-0x60(%rbp)
  10b93b:	8b 7d d8             	mov    -0x28(%rbp),%edi
  10b93e:	2b 7d e0             	sub    -0x20(%rbp),%edi
  10b941:	e8 8a 01 00 00       	call   10bad0 <_ZN4acos8graphics12_GLOBAL__N_13absIiEET_S3_>
  10b946:	89 c1                	mov    %eax,%ecx
  10b948:	8b 45 a0             	mov    -0x60(%rbp),%eax
  10b94b:	39 c8                	cmp    %ecx,%eax
  10b94d:	0f 9f c0             	setg   %al
  10b950:	24 01                	and    $0x1,%al
  10b952:	88 45 d3             	mov    %al,-0x2d(%rbp)
  10b955:	f6 45 d3 01          	testb  $0x1,-0x2d(%rbp)
  10b959:	0f 84 1a 00 00 00    	je     10b979 <_ZN4acos8graphics8Renderer9draw_lineEjjjjj+0x89>
  10b95f:	48 8d 7d e0          	lea    -0x20(%rbp),%rdi
  10b963:	48 8d 75 dc          	lea    -0x24(%rbp),%rsi
  10b967:	e8 94 01 00 00       	call   10bb00 <_ZN4acos8graphics12_GLOBAL__N_14swapIiEEvRT_S4_>
  10b96c:	48 8d 7d d8          	lea    -0x28(%rbp),%rdi
  10b970:	48 8d 75 d4          	lea    -0x2c(%rbp),%rsi
  10b974:	e8 87 01 00 00       	call   10bb00 <_ZN4acos8graphics12_GLOBAL__N_14swapIiEEvRT_S4_>
  10b979:	8b 45 e0             	mov    -0x20(%rbp),%eax
  10b97c:	3b 45 d8             	cmp    -0x28(%rbp),%eax
  10b97f:	0f 8e 1a 00 00 00    	jle    10b99f <_ZN4acos8graphics8Renderer9draw_lineEjjjjj+0xaf>
  10b985:	48 8d 7d e0          	lea    -0x20(%rbp),%rdi
  10b989:	48 8d 75 d8          	lea    -0x28(%rbp),%rsi
  10b98d:	e8 6e 01 00 00       	call   10bb00 <_ZN4acos8graphics12_GLOBAL__N_14swapIiEEvRT_S4_>
  10b992:	48 8d 7d dc          	lea    -0x24(%rbp),%rdi
  10b996:	48 8d 75 d4          	lea    -0x2c(%rbp),%rsi
  10b99a:	e8 61 01 00 00       	call   10bb00 <_ZN4acos8graphics12_GLOBAL__N_14swapIiEEvRT_S4_>
  10b99f:	48 8b 45 98          	mov    -0x68(%rbp),%rax
  10b9a3:	48 8d 4d d3          	lea    -0x2d(%rbp),%rcx
  10b9a7:	48 89 4d b8          	mov    %rcx,-0x48(%rbp)
  10b9ab:	48 89 45 c0          	mov    %rax,-0x40(%rbp)
  10b9af:	48 8d 45 e4          	lea    -0x1c(%rbp),%rax
  10b9b3:	48 89 45 c8          	mov    %rax,-0x38(%rbp)
  10b9b7:	8b 45 d8             	mov    -0x28(%rbp),%eax
  10b9ba:	2b 45 e0             	sub    -0x20(%rbp),%eax
  10b9bd:	89 45 b4             	mov    %eax,-0x4c(%rbp)
  10b9c0:	8b 45 d4             	mov    -0x2c(%rbp),%eax
  10b9c3:	2b 45 dc             	sub    -0x24(%rbp),%eax
  10b9c6:	89 45 b0             	mov    %eax,-0x50(%rbp)
  10b9c9:	83 7d b4 00          	cmpl   $0x0,-0x4c(%rbp)
  10b9cd:	0f 85 12 00 00 00    	jne    10b9e5 <_ZN4acos8graphics8Renderer9draw_lineEjjjjj+0xf5>
  10b9d3:	f3 0f 10 05 15 42 00 	movss  0x4215(%rip),%xmm0        # 10fbf0 <_ZTVN4acos8graphics13DisplayDeviceE+0x40>
  10b9da:	00
  10b9db:	f3 0f 11 45 94       	movss  %xmm0,-0x6c(%rbp)
  10b9e0:	e9 13 00 00 00       	jmp    10b9f8 <_ZN4acos8graphics8Renderer9draw_lineEjjjjj+0x108>
  10b9e5:	f3 0f 2a 45 b0       	cvtsi2ssl -0x50(%rbp),%xmm0
  10b9ea:	f3 0f 2a 4d b4       	cvtsi2ssl -0x4c(%rbp),%xmm1
  10b9ef:	f3 0f 5e c1          	divss  %xmm1,%xmm0
  10b9f3:	f3 0f 11 45 94       	movss  %xmm0,-0x6c(%rbp)
  10b9f8:	f3 0f 10 45 94       	movss  -0x6c(%rbp),%xmm0
  10b9fd:	f3 0f 11 45 ac       	movss  %xmm0,-0x54(%rbp)
  10ba02:	f3 0f 2a 45 dc       	cvtsi2ssl -0x24(%rbp),%xmm0
  10ba07:	f3 0f 58 45 ac       	addss  -0x54(%rbp),%xmm0
  10ba0c:	f3 0f 11 45 a8       	movss  %xmm0,-0x58(%rbp)
  10ba11:	8b 75 e0             	mov    -0x20(%rbp),%esi
  10ba14:	8b 55 dc             	mov    -0x24(%rbp),%edx
  10ba17:	48 8d 7d b8          	lea    -0x48(%rbp),%rdi
  10ba1b:	f3 0f 10 05 cd 41 00 	movss  0x41cd(%rip),%xmm0        # 10fbf0 <_ZTVN4acos8graphics13DisplayDeviceE+0x40>
  10ba22:	00
  10ba23:	e8 18 01 00 00       	call   10bb40 <_ZZN4acos8graphics8Renderer9draw_lineEjjjjjENK3$_0clEiif>
  10ba28:	8b 75 d8             	mov    -0x28(%rbp),%esi
  10ba2b:	8b 55 d4             	mov    -0x2c(%rbp),%edx
  10ba2e:	48 8d 7d b8          	lea    -0x48(%rbp),%rdi
  10ba32:	f3 0f 10 05 b6 41 00 	movss  0x41b6(%rip),%xmm0        # 10fbf0 <_ZTVN4acos8graphics13DisplayDeviceE+0x40>
  10ba39:	00
  10ba3a:	e8 01 01 00 00       	call   10bb40 <_ZZN4acos8graphics8Renderer9draw_lineEjjjjjENK3$_0clEiif>
  10ba3f:	8b 45 e0             	mov    -0x20(%rbp),%eax
  10ba42:	83 c0 01             	add    $0x1,%eax
  10ba45:	89 45 a4             	mov    %eax,-0x5c(%rbp)
  10ba48:	8b 45 a4             	mov    -0x5c(%rbp),%eax
  10ba4b:	3b 45 d8             	cmp    -0x28(%rbp),%eax
  10ba4e:	0f 8d 72 00 00 00    	jge    10bac6 <_ZN4acos8graphics8Renderer9draw_lineEjjjjj+0x1d6>
  10ba54:	8b 75 a4             	mov    -0x5c(%rbp),%esi
  10ba57:	f3 0f 2c 55 a8       	cvttss2si -0x58(%rbp),%edx
  10ba5c:	f3 0f 10 4d a8       	movss  -0x58(%rbp),%xmm1
  10ba61:	f3 0f 2c 45 a8       	cvttss2si -0x58(%rbp),%eax
  10ba66:	f3 0f 2a c0          	cvtsi2ss %eax,%xmm0
  10ba6a:	f3 0f 5c c8          	subss  %xmm0,%xmm1
  10ba6e:	f3 0f 10 05 7a 41 00 	movss  0x417a(%rip),%xmm0        # 10fbf0 <_ZTVN4acos8graphics13DisplayDeviceE+0x40>
  10ba75:	00
  10ba76:	f3 0f 5c c1          	subss  %xmm1,%xmm0
  10ba7a:	48 8d 7d b8          	lea    -0x48(%rbp),%rdi
  10ba7e:	e8 bd 00 00 00       	call   10bb40 <_ZZN4acos8graphics8Renderer9draw_lineEjjjjjENK3$_0clEiif>
  10ba83:	8b 75 a4             	mov    -0x5c(%rbp),%esi
  10ba86:	f3 0f 2c 55 a8       	cvttss2si -0x58(%rbp),%edx
  10ba8b:	83 c2 01             	add    $0x1,%edx
  10ba8e:	f3 0f 10 45 a8       	movss  -0x58(%rbp),%xmm0
  10ba93:	f3 0f 2c 45 a8       	cvttss2si -0x58(%rbp),%eax
  10ba98:	f3 0f 2a c8          	cvtsi2ss %eax,%xmm1
  10ba9c:	f3 0f 5c c1          	subss  %xmm1,%xmm0
  10baa0:	48 8d 7d b8          	lea    -0x48(%rbp),%rdi
  10baa4:	e8 97 00 00 00       	call   10bb40 <_ZZN4acos8graphics8Renderer9draw_lineEjjjjjENK3$_0clEiif>
  10baa9:	f3 0f 10 45 ac       	movss  -0x54(%rbp),%xmm0
  10baae:	f3 0f 58 45 a8       	addss  -0x58(%rbp),%xmm0
  10bab3:	f3 0f 11 45 a8       	movss  %xmm0,-0x58(%rbp)
  10bab8:	8b 45 a4             	mov    -0x5c(%rbp),%eax
  10babb:	83 c0 01             	add    $0x1,%eax
  10babe:	89 45 a4             	mov    %eax,-0x5c(%rbp)
  10bac1:	e9 82 ff ff ff       	jmp    10ba48 <_ZN4acos8graphics8Renderer9draw_lineEjjjjj+0x158>
  10bac6:	48 83 c4 70          	add    $0x70,%rsp
  10baca:	5d                   	pop    %rbp
  10bacb:	c3                   	ret
  10bacc:	0f 1f 40 00          	nopl   0x0(%rax)

000000000010bad0 <_ZN4acos8graphics12_GLOBAL__N_13absIiEET_S3_>:
  10bad0:	55                   	push   %rbp
  10bad1:	48 89 e5             	mov    %rsp,%rbp
  10bad4:	50                   	push   %rax
  10bad5:	89 7d fc             	mov    %edi,-0x4(%rbp)
  10bad8:	83 7d fc 00          	cmpl   $0x0,-0x4(%rbp)
  10badc:	0f 8d 0d 00 00 00    	jge    10baef <_ZN4acos8graphics12_GLOBAL__N_13absIiEET_S3_+0x1f>
  10bae2:	31 c0                	xor    %eax,%eax
  10bae4:	2b 45 fc             	sub    -0x4(%rbp),%eax
  10bae7:	89 45 f8             	mov    %eax,-0x8(%rbp)
  10baea:	e9 06 00 00 00       	jmp    10baf5 <_ZN4acos8graphics12_GLOBAL__N_13absIiEET_S3_+0x25>
  10baef:	8b 45 fc             	mov    -0x4(%rbp),%eax
  10baf2:	89 45 f8             	mov    %eax,-0x8(%rbp)
  10baf5:	8b 45 f8             	mov    -0x8(%rbp),%eax
  10baf8:	48 83 c4 08          	add    $0x8,%rsp
  10bafc:	5d                   	pop    %rbp
  10bafd:	c3                   	ret
  10bafe:	66 90                	xchg   %ax,%ax

000000000010bb00 <_ZN4acos8graphics12_GLOBAL__N_14swapIiEEvRT_S4_>:
  10bb00:	55                   	push   %rbp
  10bb01:	48 89 e5             	mov    %rsp,%rbp
  10bb04:	48 83 ec 18          	sub    $0x18,%rsp
  10bb08:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10bb0c:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  10bb10:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10bb14:	8b 00                	mov    (%rax),%eax
  10bb16:	89 45 ec             	mov    %eax,-0x14(%rbp)
  10bb19:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10bb1d:	8b 08                	mov    (%rax),%ecx
  10bb1f:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10bb23:	89 08                	mov    %ecx,(%rax)
  10bb25:	8b 4d ec             	mov    -0x14(%rbp),%ecx
  10bb28:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10bb2c:	89 08                	mov    %ecx,(%rax)
  10bb2e:	48 83 c4 18          	add    $0x18,%rsp
  10bb32:	5d                   	pop    %rbp
  10bb33:	c3                   	ret
  10bb34:	66 66 66 2e 0f 1f 84 	data16 data16 cs nopw 0x0(%rax,%rax,1)
  10bb3b:	00 00 00 00 00

000000000010bb40 <_ZZN4acos8graphics8Renderer9draw_lineEjjjjjENK3$_0clEiif>:
  10bb40:	55                   	push   %rbp
  10bb41:	48 89 e5             	mov    %rsp,%rbp
  10bb44:	48 83 ec 30          	sub    $0x30,%rsp
  10bb48:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10bb4c:	89 75 f4             	mov    %esi,-0xc(%rbp)
  10bb4f:	89 55 f0             	mov    %edx,-0x10(%rbp)
  10bb52:	f3 0f 11 45 ec       	movss  %xmm0,-0x14(%rbp)
  10bb57:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10bb5b:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
  10bb5f:	48 8b 48 08          	mov    0x8(%rax),%rcx
  10bb63:	48 89 4d e0          	mov    %rcx,-0x20(%rbp)
  10bb67:	48 8b 00             	mov    (%rax),%rax
  10bb6a:	f6 00 01             	testb  $0x1,(%rax)
  10bb6d:	0f 84 37 00 00 00    	je     10bbaa <_ZZN4acos8graphics8Renderer9draw_lineEjjjjjENK3$_0clEiif+0x6a>
  10bb73:	48 8b 7d e0          	mov    -0x20(%rbp),%rdi
  10bb77:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  10bb7b:	8b 75 f0             	mov    -0x10(%rbp),%esi
  10bb7e:	8b 55 f4             	mov    -0xc(%rbp),%edx
  10bb81:	48 8b 40 10          	mov    0x10(%rax),%rax
  10bb85:	8b 08                	mov    (%rax),%ecx
  10bb87:	f3 0f 10 45 ec       	movss  -0x14(%rbp),%xmm0
  10bb8c:	f3 0f 10 0d 60 40 00 	movss  0x4060(%rip),%xmm1        # 10fbf4 <_ZTVN4acos8graphics13DisplayDeviceE+0x44>
  10bb93:	00
  10bb94:	f3 0f 59 c1          	mulss  %xmm1,%xmm0
  10bb98:	f3 0f 2c c0          	cvttss2si %xmm0,%eax
  10bb9c:	44 0f b6 c0          	movzbl %al,%r8d
  10bba0:	e8 1b fc ff ff       	call   10b7c0 <_ZN4acos8graphics8Renderer11blend_pixelEjjjh>
  10bba5:	e9 32 00 00 00       	jmp    10bbdc <_ZZN4acos8graphics8Renderer9draw_lineEjjjjjENK3$_0clEiif+0x9c>
  10bbaa:	48 8b 7d e0          	mov    -0x20(%rbp),%rdi
  10bbae:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  10bbb2:	8b 75 f4             	mov    -0xc(%rbp),%esi
  10bbb5:	8b 55 f0             	mov    -0x10(%rbp),%edx
  10bbb8:	48 8b 40 10          	mov    0x10(%rax),%rax
  10bbbc:	8b 08                	mov    (%rax),%ecx
  10bbbe:	f3 0f 10 45 ec       	movss  -0x14(%rbp),%xmm0
  10bbc3:	f3 0f 10 0d 29 40 00 	movss  0x4029(%rip),%xmm1        # 10fbf4 <_ZTVN4acos8graphics13DisplayDeviceE+0x44>
  10bbca:	00
  10bbcb:	f3 0f 59 c1          	mulss  %xmm1,%xmm0
  10bbcf:	f3 0f 2c c0          	cvttss2si %xmm0,%eax
  10bbd3:	44 0f b6 c0          	movzbl %al,%r8d
  10bbd7:	e8 e4 fb ff ff       	call   10b7c0 <_ZN4acos8graphics8Renderer11blend_pixelEjjjh>
  10bbdc:	48 83 c4 30          	add    $0x30,%rsp
  10bbe0:	5d                   	pop    %rbp
  10bbe1:	c3                   	ret
  10bbe2:	66 66 66 66 66 2e 0f 	data16 data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
  10bbe9:	1f 84 00 00 00 00 00

000000000010bbf0 <_ZN4acos8graphics8Renderer9draw_rectEjjjjj>:
  10bbf0:	55                   	push   %rbp
  10bbf1:	48 89 e5             	mov    %rsp,%rbp
  10bbf4:	48 83 ec 30          	sub    $0x30,%rsp
  10bbf8:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10bbfc:	89 75 f4             	mov    %esi,-0xc(%rbp)
  10bbff:	89 55 f0             	mov    %edx,-0x10(%rbp)
  10bc02:	89 4d ec             	mov    %ecx,-0x14(%rbp)
  10bc05:	44 89 45 e8          	mov    %r8d,-0x18(%rbp)
  10bc09:	44 89 4d e4          	mov    %r9d,-0x1c(%rbp)
  10bc0d:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10bc11:	48 89 45 d0          	mov    %rax,-0x30(%rbp)
  10bc15:	8b 45 f4             	mov    -0xc(%rbp),%eax
  10bc18:	89 45 e0             	mov    %eax,-0x20(%rbp)
  10bc1b:	8b 45 e0             	mov    -0x20(%rbp),%eax
  10bc1e:	8b 4d f4             	mov    -0xc(%rbp),%ecx
  10bc21:	03 4d ec             	add    -0x14(%rbp),%ecx
  10bc24:	39 c8                	cmp    %ecx,%eax
  10bc26:	0f 83 38 00 00 00    	jae    10bc64 <_ZN4acos8graphics8Renderer9draw_rectEjjjjj+0x74>
  10bc2c:	48 8b 7d d0          	mov    -0x30(%rbp),%rdi
  10bc30:	8b 75 e0             	mov    -0x20(%rbp),%esi
  10bc33:	8b 55 f0             	mov    -0x10(%rbp),%edx
  10bc36:	8b 4d e4             	mov    -0x1c(%rbp),%ecx
  10bc39:	e8 22 fb ff ff       	call   10b760 <_ZN4acos8graphics8Renderer10draw_pixelEjjj>
  10bc3e:	48 8b 7d d0          	mov    -0x30(%rbp),%rdi
  10bc42:	8b 75 e0             	mov    -0x20(%rbp),%esi
  10bc45:	8b 55 f0             	mov    -0x10(%rbp),%edx
  10bc48:	03 55 e8             	add    -0x18(%rbp),%edx
  10bc4b:	83 ea 01             	sub    $0x1,%edx
  10bc4e:	8b 4d e4             	mov    -0x1c(%rbp),%ecx
  10bc51:	e8 0a fb ff ff       	call   10b760 <_ZN4acos8graphics8Renderer10draw_pixelEjjj>
  10bc56:	8b 45 e0             	mov    -0x20(%rbp),%eax
  10bc59:	83 c0 01             	add    $0x1,%eax
  10bc5c:	89 45 e0             	mov    %eax,-0x20(%rbp)
  10bc5f:	e9 b7 ff ff ff       	jmp    10bc1b <_ZN4acos8graphics8Renderer9draw_rectEjjjjj+0x2b>
  10bc64:	8b 45 f0             	mov    -0x10(%rbp),%eax
  10bc67:	89 45 dc             	mov    %eax,-0x24(%rbp)
  10bc6a:	8b 45 dc             	mov    -0x24(%rbp),%eax
  10bc6d:	8b 4d f0             	mov    -0x10(%rbp),%ecx
  10bc70:	03 4d e8             	add    -0x18(%rbp),%ecx
  10bc73:	39 c8                	cmp    %ecx,%eax
  10bc75:	0f 83 38 00 00 00    	jae    10bcb3 <_ZN4acos8graphics8Renderer9draw_rectEjjjjj+0xc3>
  10bc7b:	48 8b 7d d0          	mov    -0x30(%rbp),%rdi
  10bc7f:	8b 75 f4             	mov    -0xc(%rbp),%esi
  10bc82:	8b 55 dc             	mov    -0x24(%rbp),%edx
  10bc85:	8b 4d e4             	mov    -0x1c(%rbp),%ecx
  10bc88:	e8 d3 fa ff ff       	call   10b760 <_ZN4acos8graphics8Renderer10draw_pixelEjjj>
  10bc8d:	48 8b 7d d0          	mov    -0x30(%rbp),%rdi
  10bc91:	8b 75 f4             	mov    -0xc(%rbp),%esi
  10bc94:	03 75 ec             	add    -0x14(%rbp),%esi
  10bc97:	83 ee 01             	sub    $0x1,%esi
  10bc9a:	8b 55 dc             	mov    -0x24(%rbp),%edx
  10bc9d:	8b 4d e4             	mov    -0x1c(%rbp),%ecx
  10bca0:	e8 bb fa ff ff       	call   10b760 <_ZN4acos8graphics8Renderer10draw_pixelEjjj>
  10bca5:	8b 45 dc             	mov    -0x24(%rbp),%eax
  10bca8:	83 c0 01             	add    $0x1,%eax
  10bcab:	89 45 dc             	mov    %eax,-0x24(%rbp)
  10bcae:	e9 b7 ff ff ff       	jmp    10bc6a <_ZN4acos8graphics8Renderer9draw_rectEjjjjj+0x7a>
  10bcb3:	48 83 c4 30          	add    $0x30,%rsp
  10bcb7:	5d                   	pop    %rbp
  10bcb8:	c3                   	ret
  10bcb9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

000000000010bcc0 <_ZN4acos8graphics8Renderer9fill_rectEjjjjj>:
  10bcc0:	55                   	push   %rbp
  10bcc1:	48 89 e5             	mov    %rsp,%rbp
  10bcc4:	48 83 ec 30          	sub    $0x30,%rsp
  10bcc8:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10bccc:	89 75 f4             	mov    %esi,-0xc(%rbp)
  10bccf:	89 55 f0             	mov    %edx,-0x10(%rbp)
  10bcd2:	89 4d ec             	mov    %ecx,-0x14(%rbp)
  10bcd5:	44 89 45 e8          	mov    %r8d,-0x18(%rbp)
  10bcd9:	44 89 4d e4          	mov    %r9d,-0x1c(%rbp)
  10bcdd:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10bce1:	48 89 45 d0          	mov    %rax,-0x30(%rbp)
  10bce5:	8b 45 f0             	mov    -0x10(%rbp),%eax
  10bce8:	89 45 e0             	mov    %eax,-0x20(%rbp)
  10bceb:	8b 45 e0             	mov    -0x20(%rbp),%eax
  10bcee:	8b 4d f0             	mov    -0x10(%rbp),%ecx
  10bcf1:	03 4d e8             	add    -0x18(%rbp),%ecx
  10bcf4:	39 c8                	cmp    %ecx,%eax
  10bcf6:	0f 83 4a 00 00 00    	jae    10bd46 <_ZN4acos8graphics8Renderer9fill_rectEjjjjj+0x86>
  10bcfc:	8b 45 f4             	mov    -0xc(%rbp),%eax
  10bcff:	89 45 dc             	mov    %eax,-0x24(%rbp)
  10bd02:	8b 45 dc             	mov    -0x24(%rbp),%eax
  10bd05:	8b 4d f4             	mov    -0xc(%rbp),%ecx
  10bd08:	03 4d ec             	add    -0x14(%rbp),%ecx
  10bd0b:	39 c8                	cmp    %ecx,%eax
  10bd0d:	0f 83 20 00 00 00    	jae    10bd33 <_ZN4acos8graphics8Renderer9fill_rectEjjjjj+0x73>
  10bd13:	48 8b 7d d0          	mov    -0x30(%rbp),%rdi
  10bd17:	8b 75 dc             	mov    -0x24(%rbp),%esi
  10bd1a:	8b 55 e0             	mov    -0x20(%rbp),%edx
  10bd1d:	8b 4d e4             	mov    -0x1c(%rbp),%ecx
  10bd20:	e8 3b fa ff ff       	call   10b760 <_ZN4acos8graphics8Renderer10draw_pixelEjjj>
  10bd25:	8b 45 dc             	mov    -0x24(%rbp),%eax
  10bd28:	83 c0 01             	add    $0x1,%eax
  10bd2b:	89 45 dc             	mov    %eax,-0x24(%rbp)
  10bd2e:	e9 cf ff ff ff       	jmp    10bd02 <_ZN4acos8graphics8Renderer9fill_rectEjjjjj+0x42>
  10bd33:	e9 00 00 00 00       	jmp    10bd38 <_ZN4acos8graphics8Renderer9fill_rectEjjjjj+0x78>
  10bd38:	8b 45 e0             	mov    -0x20(%rbp),%eax
  10bd3b:	83 c0 01             	add    $0x1,%eax
  10bd3e:	89 45 e0             	mov    %eax,-0x20(%rbp)
  10bd41:	e9 a5 ff ff ff       	jmp    10bceb <_ZN4acos8graphics8Renderer9fill_rectEjjjjj+0x2b>
  10bd46:	48 83 c4 30          	add    $0x30,%rsp
  10bd4a:	5d                   	pop    %rbp
  10bd4b:	c3                   	ret
  10bd4c:	0f 1f 40 00          	nopl   0x0(%rax)

000000000010bd50 <_ZN4acos8graphics8Renderer9draw_charEcjjjNS0_4Font5StyleE>:
  10bd50:	55                   	push   %rbp
  10bd51:	48 89 e5             	mov    %rsp,%rbp
  10bd54:	48 83 ec 60          	sub    $0x60,%rsp
  10bd58:	40 88 f0             	mov    %sil,%al
  10bd5b:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10bd5f:	88 45 f7             	mov    %al,-0x9(%rbp)
  10bd62:	89 55 f0             	mov    %edx,-0x10(%rbp)
  10bd65:	89 4d ec             	mov    %ecx,-0x14(%rbp)
  10bd68:	44 89 45 e8          	mov    %r8d,-0x18(%rbp)
  10bd6c:	44 89 4d e4          	mov    %r9d,-0x1c(%rbp)
  10bd70:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10bd74:	48 89 45 a8          	mov    %rax,-0x58(%rbp)
  10bd78:	e8 c3 17 00 00       	call   10d540 <_ZN4acos8graphics4Font11get_defaultEv>
  10bd7d:	48 89 c1             	mov    %rax,%rcx
  10bd80:	48 8b 45 a8          	mov    -0x58(%rbp),%rax
  10bd84:	48 89 4d d8          	mov    %rcx,-0x28(%rbp)
  10bd88:	48 8d 4d d8          	lea    -0x28(%rbp),%rcx
  10bd8c:	48 89 4d b0          	mov    %rcx,-0x50(%rbp)
  10bd90:	48 8d 4d f7          	lea    -0x9(%rbp),%rcx
  10bd94:	48 89 4d b8          	mov    %rcx,-0x48(%rbp)
  10bd98:	48 89 45 c0          	mov    %rax,-0x40(%rbp)
  10bd9c:	48 8d 45 e8          	lea    -0x18(%rbp),%rax
  10bda0:	48 89 45 c8          	mov    %rax,-0x38(%rbp)
  10bda4:	48 8d 45 e4          	lea    -0x1c(%rbp),%rax
  10bda8:	48 89 45 d0          	mov    %rax,-0x30(%rbp)
  10bdac:	8b 75 f0             	mov    -0x10(%rbp),%esi
  10bdaf:	8b 55 ec             	mov    -0x14(%rbp),%edx
  10bdb2:	48 8d 7d b0          	lea    -0x50(%rbp),%rdi
  10bdb6:	e8 25 00 00 00       	call   10bde0 <_ZZN4acos8graphics8Renderer9draw_charEcjjjNS0_4Font5StyleEENK3$_0clEjj>
  10bdbb:	83 7d e4 01          	cmpl   $0x1,-0x1c(%rbp)
  10bdbf:	0f 85 12 00 00 00    	jne    10bdd7 <_ZN4acos8graphics8Renderer9draw_charEcjjjNS0_4Font5StyleE+0x87>
  10bdc5:	8b 75 f0             	mov    -0x10(%rbp),%esi
  10bdc8:	83 c6 01             	add    $0x1,%esi
  10bdcb:	8b 55 ec             	mov    -0x14(%rbp),%edx
  10bdce:	48 8d 7d b0          	lea    -0x50(%rbp),%rdi
  10bdd2:	e8 09 00 00 00       	call   10bde0 <_ZZN4acos8graphics8Renderer9draw_charEcjjjNS0_4Font5StyleEENK3$_0clEjj>
  10bdd7:	48 83 c4 60          	add    $0x60,%rsp
  10bddb:	5d                   	pop    %rbp
  10bddc:	c3                   	ret
  10bddd:	0f 1f 00             	nopl   (%rax)

000000000010bde0 <_ZZN4acos8graphics8Renderer9draw_charEcjjjNS0_4Font5StyleEENK3$_0clEjj>:
  10bde0:	55                   	push   %rbp
  10bde1:	48 89 e5             	mov    %rsp,%rbp
  10bde4:	48 83 ec 50          	sub    $0x50,%rsp
  10bde8:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10bdec:	89 75 f4             	mov    %esi,-0xc(%rbp)
  10bdef:	89 55 f0             	mov    %edx,-0x10(%rbp)
  10bdf2:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10bdf6:	48 89 45 b0          	mov    %rax,-0x50(%rbp)
  10bdfa:	48 8b 48 10          	mov    0x10(%rax),%rcx
  10bdfe:	48 89 4d b8          	mov    %rcx,-0x48(%rbp)
  10be02:	48 8b 00             	mov    (%rax),%rax
  10be05:	48 83 38 00          	cmpq   $0x0,(%rax)
  10be09:	0f 84 17 00 00 00    	je     10be26 <_ZZN4acos8graphics8Renderer9draw_charEcjjjNS0_4Font5StyleEENK3$_0clEjj+0x46>
  10be0f:	48 8b 45 b0          	mov    -0x50(%rbp),%rax
  10be13:	48 8b 00             	mov    (%rax),%rax
  10be16:	48 8b 38             	mov    (%rax),%rdi
  10be19:	e8 42 31 00 00       	call   10ef60 <_ZNK4acos8graphics4Font8is_validEv>
  10be1e:	a8 01                	test   $0x1,%al
  10be20:	0f 85 80 00 00 00    	jne    10bea6 <_ZZN4acos8graphics8Renderer9draw_charEcjjjNS0_4Font5StyleEENK3$_0clEjj+0xc6>
  10be26:	48 8b 45 b0          	mov    -0x50(%rbp),%rax
  10be2a:	48 8b 40 08          	mov    0x8(%rax),%rax
  10be2e:	0f b6 00             	movzbl (%rax),%eax
  10be31:	83 f8 20             	cmp    $0x20,%eax
  10be34:	0f 8e 67 00 00 00    	jle    10bea1 <_ZZN4acos8graphics8Renderer9draw_charEcjjjNS0_4Font5StyleEENK3$_0clEjj+0xc1>
  10be3a:	c7 45 ec 01 00 00 00 	movl   $0x1,-0x14(%rbp)
  10be41:	83 7d ec 07          	cmpl   $0x7,-0x14(%rbp)
  10be45:	0f 8d 51 00 00 00    	jge    10be9c <_ZZN4acos8graphics8Renderer9draw_charEcjjjNS0_4Font5StyleEENK3$_0clEjj+0xbc>
  10be4b:	c7 45 e8 01 00 00 00 	movl   $0x1,-0x18(%rbp)
  10be52:	83 7d e8 06          	cmpl   $0x6,-0x18(%rbp)
  10be56:	0f 8d 2d 00 00 00    	jge    10be89 <_ZZN4acos8graphics8Renderer9draw_charEcjjjNS0_4Font5StyleEENK3$_0clEjj+0xa9>
  10be5c:	48 8b 7d b8          	mov    -0x48(%rbp),%rdi
  10be60:	48 8b 45 b0          	mov    -0x50(%rbp),%rax
  10be64:	8b 75 f4             	mov    -0xc(%rbp),%esi
  10be67:	03 75 e8             	add    -0x18(%rbp),%esi
  10be6a:	8b 55 f0             	mov    -0x10(%rbp),%edx
  10be6d:	03 55 ec             	add    -0x14(%rbp),%edx
  10be70:	48 8b 40 18          	mov    0x18(%rax),%rax
  10be74:	8b 08                	mov    (%rax),%ecx
  10be76:	e8 e5 f8 ff ff       	call   10b760 <_ZN4acos8graphics8Renderer10draw_pixelEjjj>
  10be7b:	8b 45 e8             	mov    -0x18(%rbp),%eax
  10be7e:	83 c0 01             	add    $0x1,%eax
  10be81:	89 45 e8             	mov    %eax,-0x18(%rbp)
  10be84:	e9 c9 ff ff ff       	jmp    10be52 <_ZZN4acos8graphics8Renderer9draw_charEcjjjNS0_4Font5StyleEENK3$_0clEjj+0x72>
  10be89:	e9 00 00 00 00       	jmp    10be8e <_ZZN4acos8graphics8Renderer9draw_charEcjjjNS0_4Font5StyleEENK3$_0clEjj+0xae>
  10be8e:	8b 45 ec             	mov    -0x14(%rbp),%eax
  10be91:	83 c0 01             	add    $0x1,%eax
  10be94:	89 45 ec             	mov    %eax,-0x14(%rbp)
  10be97:	e9 a5 ff ff ff       	jmp    10be41 <_ZZN4acos8graphics8Renderer9draw_charEcjjjNS0_4Font5StyleEENK3$_0clEjj+0x61>
  10be9c:	e9 00 00 00 00       	jmp    10bea1 <_ZZN4acos8graphics8Renderer9draw_charEcjjjNS0_4Font5StyleEENK3$_0clEjj+0xc1>
  10bea1:	e9 28 01 00 00       	jmp    10bfce <_ZZN4acos8graphics8Renderer9draw_charEcjjjNS0_4Font5StyleEENK3$_0clEjj+0x1ee>
  10bea6:	48 8b 45 b0          	mov    -0x50(%rbp),%rax
  10beaa:	48 8b 08             	mov    (%rax),%rcx
  10bead:	48 8b 39             	mov    (%rcx),%rdi
  10beb0:	48 8b 40 08          	mov    0x8(%rax),%rax
  10beb4:	0f be 30             	movsbl (%rax),%esi
  10beb7:	e8 c4 13 00 00       	call   10d280 <_ZNK4acos8graphics4Font9get_glyphEc>
  10bebc:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  10bec0:	48 83 7d e0 00       	cmpq   $0x0,-0x20(%rbp)
  10bec5:	0f 85 05 00 00 00    	jne    10bed0 <_ZZN4acos8graphics8Renderer9draw_charEcjjjNS0_4Font5StyleEENK3$_0clEjj+0xf0>
  10becb:	e9 fe 00 00 00       	jmp    10bfce <_ZZN4acos8graphics8Renderer9draw_charEcjjjNS0_4Font5StyleEENK3$_0clEjj+0x1ee>
  10bed0:	48 8b 45 b0          	mov    -0x50(%rbp),%rax
  10bed4:	48 8b 00             	mov    (%rax),%rax
  10bed7:	48 8b 38             	mov    (%rax),%rdi
  10beda:	e8 a1 30 00 00       	call   10ef80 <_ZNK4acos8graphics4Font5widthEv>
  10bedf:	89 c1                	mov    %eax,%ecx
  10bee1:	48 8b 45 b0          	mov    -0x50(%rbp),%rax
  10bee5:	89 4d dc             	mov    %ecx,-0x24(%rbp)
  10bee8:	48 8b 00             	mov    (%rax),%rax
  10beeb:	48 8b 38             	mov    (%rax),%rdi
  10beee:	e8 ad 30 00 00       	call   10efa0 <_ZNK4acos8graphics4Font6heightEv>
  10bef3:	89 45 d8             	mov    %eax,-0x28(%rbp)
  10bef6:	8b 45 dc             	mov    -0x24(%rbp),%eax
  10bef9:	83 c0 07             	add    $0x7,%eax
  10befc:	c1 e8 03             	shr    $0x3,%eax
  10beff:	89 45 d4             	mov    %eax,-0x2c(%rbp)
  10bf02:	c7 45 d0 00 00 00 00 	movl   $0x0,-0x30(%rbp)
  10bf09:	8b 45 d0             	mov    -0x30(%rbp),%eax
  10bf0c:	3b 45 d8             	cmp    -0x28(%rbp),%eax
  10bf0f:	0f 83 b9 00 00 00    	jae    10bfce <_ZZN4acos8graphics8Renderer9draw_charEcjjjNS0_4Font5StyleEENK3$_0clEjj+0x1ee>
  10bf15:	c7 45 cc 00 00 00 00 	movl   $0x0,-0x34(%rbp)
  10bf1c:	8b 45 cc             	mov    -0x34(%rbp),%eax
  10bf1f:	3b 45 dc             	cmp    -0x24(%rbp),%eax
  10bf22:	0f 83 93 00 00 00    	jae    10bfbb <_ZZN4acos8graphics8Renderer9draw_charEcjjjNS0_4Font5StyleEENK3$_0clEjj+0x1db>
  10bf28:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  10bf2c:	8b 4d d0             	mov    -0x30(%rbp),%ecx
  10bf2f:	0f af 4d d4          	imul   -0x2c(%rbp),%ecx
  10bf33:	8b 55 cc             	mov    -0x34(%rbp),%edx
  10bf36:	c1 ea 03             	shr    $0x3,%edx
  10bf39:	01 d1                	add    %edx,%ecx
  10bf3b:	89 c9                	mov    %ecx,%ecx
  10bf3d:	8a 04 08             	mov    (%rax,%rcx,1),%al
  10bf40:	88 45 cb             	mov    %al,-0x35(%rbp)
  10bf43:	0f b6 45 cb          	movzbl -0x35(%rbp),%eax
  10bf47:	8b 55 cc             	mov    -0x34(%rbp),%edx
  10bf4a:	83 e2 07             	and    $0x7,%edx
  10bf4d:	b9 07 00 00 00       	mov    $0x7,%ecx
  10bf52:	29 d1                	sub    %edx,%ecx
  10bf54:	d3 f8                	sar    %cl,%eax
  10bf56:	83 e0 01             	and    $0x1,%eax
  10bf59:	83 f8 00             	cmp    $0x0,%eax
  10bf5c:	0f 84 46 00 00 00    	je     10bfa8 <_ZZN4acos8graphics8Renderer9draw_charEcjjjNS0_4Font5StyleEENK3$_0clEjj+0x1c8>
  10bf62:	48 8b 45 b0          	mov    -0x50(%rbp),%rax
  10bf66:	c7 45 c4 00 00 00 00 	movl   $0x0,-0x3c(%rbp)
  10bf6d:	48 8b 40 20          	mov    0x20(%rax),%rax
  10bf71:	83 38 02             	cmpl   $0x2,(%rax)
  10bf74:	0f 85 0c 00 00 00    	jne    10bf86 <_ZZN4acos8graphics8Renderer9draw_charEcjjjNS0_4Font5StyleEENK3$_0clEjj+0x1a6>
  10bf7a:	8b 45 d8             	mov    -0x28(%rbp),%eax
  10bf7d:	2b 45 d0             	sub    -0x30(%rbp),%eax
  10bf80:	c1 e8 02             	shr    $0x2,%eax
  10bf83:	89 45 c4             	mov    %eax,-0x3c(%rbp)
  10bf86:	48 8b 7d b8          	mov    -0x48(%rbp),%rdi
  10bf8a:	48 8b 45 b0          	mov    -0x50(%rbp),%rax
  10bf8e:	8b 75 f4             	mov    -0xc(%rbp),%esi
  10bf91:	03 75 cc             	add    -0x34(%rbp),%esi
  10bf94:	03 75 c4             	add    -0x3c(%rbp),%esi
  10bf97:	8b 55 f0             	mov    -0x10(%rbp),%edx
  10bf9a:	03 55 d0             	add    -0x30(%rbp),%edx
  10bf9d:	48 8b 40 18          	mov    0x18(%rax),%rax
  10bfa1:	8b 08                	mov    (%rax),%ecx
  10bfa3:	e8 b8 f7 ff ff       	call   10b760 <_ZN4acos8graphics8Renderer10draw_pixelEjjj>
  10bfa8:	e9 00 00 00 00       	jmp    10bfad <_ZZN4acos8graphics8Renderer9draw_charEcjjjNS0_4Font5StyleEENK3$_0clEjj+0x1cd>
  10bfad:	8b 45 cc             	mov    -0x34(%rbp),%eax
  10bfb0:	83 c0 01             	add    $0x1,%eax
  10bfb3:	89 45 cc             	mov    %eax,-0x34(%rbp)
  10bfb6:	e9 61 ff ff ff       	jmp    10bf1c <_ZZN4acos8graphics8Renderer9draw_charEcjjjNS0_4Font5StyleEENK3$_0clEjj+0x13c>
  10bfbb:	e9 00 00 00 00       	jmp    10bfc0 <_ZZN4acos8graphics8Renderer9draw_charEcjjjNS0_4Font5StyleEENK3$_0clEjj+0x1e0>
  10bfc0:	8b 45 d0             	mov    -0x30(%rbp),%eax
  10bfc3:	83 c0 01             	add    $0x1,%eax
  10bfc6:	89 45 d0             	mov    %eax,-0x30(%rbp)
  10bfc9:	e9 3b ff ff ff       	jmp    10bf09 <_ZZN4acos8graphics8Renderer9draw_charEcjjjNS0_4Font5StyleEENK3$_0clEjj+0x129>
  10bfce:	48 83 c4 50          	add    $0x50,%rsp
  10bfd2:	5d                   	pop    %rbp
  10bfd3:	c3                   	ret
  10bfd4:	66 66 66 2e 0f 1f 84 	data16 data16 cs nopw 0x0(%rax,%rax,1)
  10bfdb:	00 00 00 00 00

000000000010bfe0 <_ZN4acos8graphics8Renderer9draw_textEPKcjjjNS0_4Font9AlignmentENS4_5StyleEi>:
  10bfe0:	55                   	push   %rbp
  10bfe1:	48 89 e5             	mov    %rsp,%rbp
  10bfe4:	48 81 ec 80 00 00 00 	sub    $0x80,%rsp
  10bfeb:	8b 45 18             	mov    0x18(%rbp),%eax
  10bfee:	8b 45 10             	mov    0x10(%rbp),%eax
  10bff1:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10bff5:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  10bff9:	89 55 ec             	mov    %edx,-0x14(%rbp)
  10bffc:	89 4d e8             	mov    %ecx,-0x18(%rbp)
  10bfff:	44 89 45 e4          	mov    %r8d,-0x1c(%rbp)
  10c003:	44 89 4d e0          	mov    %r9d,-0x20(%rbp)
  10c007:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10c00b:	48 89 45 a0          	mov    %rax,-0x60(%rbp)
  10c00f:	48 83 7d f0 00       	cmpq   $0x0,-0x10(%rbp)
  10c014:	0f 85 05 00 00 00    	jne    10c01f <_ZN4acos8graphics8Renderer9draw_textEPKcjjjNS0_4Font9AlignmentENS4_5StyleEi+0x3f>
  10c01a:	e9 e4 01 00 00       	jmp    10c203 <_ZN4acos8graphics8Renderer9draw_textEPKcjjjNS0_4Font9AlignmentENS4_5StyleEi+0x223>
  10c01f:	e8 1c 15 00 00       	call   10d540 <_ZN4acos8graphics4Font11get_defaultEv>
  10c024:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
  10c028:	48 83 7d d8 00       	cmpq   $0x0,-0x28(%rbp)
  10c02d:	0f 84 27 00 00 00    	je     10c05a <_ZN4acos8graphics8Renderer9draw_textEPKcjjjNS0_4Font9AlignmentENS4_5StyleEi+0x7a>
  10c033:	48 8b 7d d8          	mov    -0x28(%rbp),%rdi
  10c037:	e8 24 2f 00 00       	call   10ef60 <_ZNK4acos8graphics4Font8is_validEv>
  10c03c:	a8 01                	test   $0x1,%al
  10c03e:	0f 85 05 00 00 00    	jne    10c049 <_ZN4acos8graphics8Renderer9draw_textEPKcjjjNS0_4Font9AlignmentENS4_5StyleEi+0x69>
  10c044:	e9 11 00 00 00       	jmp    10c05a <_ZN4acos8graphics8Renderer9draw_textEPKcjjjNS0_4Font9AlignmentENS4_5StyleEi+0x7a>
  10c049:	48 8b 7d d8          	mov    -0x28(%rbp),%rdi
  10c04d:	e8 2e 2f 00 00       	call   10ef80 <_ZNK4acos8graphics4Font5widthEv>
  10c052:	89 45 9c             	mov    %eax,-0x64(%rbp)
  10c055:	e9 0d 00 00 00       	jmp    10c067 <_ZN4acos8graphics8Renderer9draw_textEPKcjjjNS0_4Font9AlignmentENS4_5StyleEi+0x87>
  10c05a:	b8 08 00 00 00       	mov    $0x8,%eax
  10c05f:	89 45 9c             	mov    %eax,-0x64(%rbp)
  10c062:	e9 00 00 00 00       	jmp    10c067 <_ZN4acos8graphics8Renderer9draw_textEPKcjjjNS0_4Font9AlignmentENS4_5StyleEi+0x87>
  10c067:	8b 45 9c             	mov    -0x64(%rbp),%eax
  10c06a:	89 45 d4             	mov    %eax,-0x2c(%rbp)
  10c06d:	48 83 7d d8 00       	cmpq   $0x0,-0x28(%rbp)
  10c072:	0f 84 27 00 00 00    	je     10c09f <_ZN4acos8graphics8Renderer9draw_textEPKcjjjNS0_4Font9AlignmentENS4_5StyleEi+0xbf>
  10c078:	48 8b 7d d8          	mov    -0x28(%rbp),%rdi
  10c07c:	e8 df 2e 00 00       	call   10ef60 <_ZNK4acos8graphics4Font8is_validEv>
  10c081:	a8 01                	test   $0x1,%al
  10c083:	0f 85 05 00 00 00    	jne    10c08e <_ZN4acos8graphics8Renderer9draw_textEPKcjjjNS0_4Font9AlignmentENS4_5StyleEi+0xae>
  10c089:	e9 11 00 00 00       	jmp    10c09f <_ZN4acos8graphics8Renderer9draw_textEPKcjjjNS0_4Font9AlignmentENS4_5StyleEi+0xbf>
  10c08e:	48 8b 7d d8          	mov    -0x28(%rbp),%rdi
  10c092:	e8 09 2f 00 00       	call   10efa0 <_ZNK4acos8graphics4Font6heightEv>
  10c097:	89 45 98             	mov    %eax,-0x68(%rbp)
  10c09a:	e9 0d 00 00 00       	jmp    10c0ac <_ZN4acos8graphics8Renderer9draw_textEPKcjjjNS0_4Font9AlignmentENS4_5StyleEi+0xcc>
  10c09f:	b8 0a 00 00 00       	mov    $0xa,%eax
  10c0a4:	89 45 98             	mov    %eax,-0x68(%rbp)
  10c0a7:	e9 00 00 00 00       	jmp    10c0ac <_ZN4acos8graphics8Renderer9draw_textEPKcjjjNS0_4Font9AlignmentENS4_5StyleEi+0xcc>
  10c0ac:	8b 45 98             	mov    -0x68(%rbp),%eax
  10c0af:	89 45 d0             	mov    %eax,-0x30(%rbp)
  10c0b2:	8b 45 e8             	mov    -0x18(%rbp),%eax
  10c0b5:	89 45 cc             	mov    %eax,-0x34(%rbp)
  10c0b8:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10c0bc:	48 89 45 c0          	mov    %rax,-0x40(%rbp)
  10c0c0:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  10c0c4:	80 38 00             	cmpb   $0x0,(%rax)
  10c0c7:	0f 84 36 01 00 00    	je     10c203 <_ZN4acos8graphics8Renderer9draw_textEPKcjjjNS0_4Font9AlignmentENS4_5StyleEi+0x223>
  10c0cd:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  10c0d1:	48 89 45 b8          	mov    %rax,-0x48(%rbp)
  10c0d5:	c7 45 b4 00 00 00 00 	movl   $0x0,-0x4c(%rbp)
  10c0dc:	48 8b 4d b8          	mov    -0x48(%rbp),%rcx
  10c0e0:	31 c0                	xor    %eax,%eax
  10c0e2:	80 39 00             	cmpb   $0x0,(%rcx)
  10c0e5:	88 45 97             	mov    %al,-0x69(%rbp)
  10c0e8:	0f 84 10 00 00 00    	je     10c0fe <_ZN4acos8graphics8Renderer9draw_textEPKcjjjNS0_4Font9AlignmentENS4_5StyleEi+0x11e>
  10c0ee:	48 8b 45 b8          	mov    -0x48(%rbp),%rax
  10c0f2:	0f be 00             	movsbl (%rax),%eax
  10c0f5:	83 f8 0a             	cmp    $0xa,%eax
  10c0f8:	0f 95 c0             	setne  %al
  10c0fb:	88 45 97             	mov    %al,-0x69(%rbp)
  10c0fe:	8a 45 97             	mov    -0x69(%rbp),%al
  10c101:	a8 01                	test   $0x1,%al
  10c103:	0f 85 05 00 00 00    	jne    10c10e <_ZN4acos8graphics8Renderer9draw_textEPKcjjjNS0_4Font9AlignmentENS4_5StyleEi+0x12e>
  10c109:	e9 1a 00 00 00       	jmp    10c128 <_ZN4acos8graphics8Renderer9draw_textEPKcjjjNS0_4Font9AlignmentENS4_5StyleEi+0x148>
  10c10e:	8b 45 b4             	mov    -0x4c(%rbp),%eax
  10c111:	83 c0 01             	add    $0x1,%eax
  10c114:	89 45 b4             	mov    %eax,-0x4c(%rbp)
  10c117:	48 8b 45 b8          	mov    -0x48(%rbp),%rax
  10c11b:	48 83 c0 01          	add    $0x1,%rax
  10c11f:	48 89 45 b8          	mov    %rax,-0x48(%rbp)
  10c123:	e9 b4 ff ff ff       	jmp    10c0dc <_ZN4acos8graphics8Renderer9draw_textEPKcjjjNS0_4Font9AlignmentENS4_5StyleEi+0xfc>
  10c128:	8b 45 b4             	mov    -0x4c(%rbp),%eax
  10c12b:	8b 4d d4             	mov    -0x2c(%rbp),%ecx
  10c12e:	03 4d 18             	add    0x18(%rbp),%ecx
  10c131:	0f af c1             	imul   %ecx,%eax
  10c134:	89 45 b0             	mov    %eax,-0x50(%rbp)
  10c137:	8b 45 ec             	mov    -0x14(%rbp),%eax
  10c13a:	89 45 ac             	mov    %eax,-0x54(%rbp)
  10c13d:	83 7d e0 01          	cmpl   $0x1,-0x20(%rbp)
  10c141:	0f 85 12 00 00 00    	jne    10c159 <_ZN4acos8graphics8Renderer9draw_textEPKcjjjNS0_4Font9AlignmentENS4_5StyleEi+0x179>
  10c147:	8b 45 ec             	mov    -0x14(%rbp),%eax
  10c14a:	8b 4d b0             	mov    -0x50(%rbp),%ecx
  10c14d:	d1 e9                	shr    $1,%ecx
  10c14f:	29 c8                	sub    %ecx,%eax
  10c151:	89 45 ac             	mov    %eax,-0x54(%rbp)
  10c154:	e9 18 00 00 00       	jmp    10c171 <_ZN4acos8graphics8Renderer9draw_textEPKcjjjNS0_4Font9AlignmentENS4_5StyleEi+0x191>
  10c159:	83 7d e0 02          	cmpl   $0x2,-0x20(%rbp)
  10c15d:	0f 85 09 00 00 00    	jne    10c16c <_ZN4acos8graphics8Renderer9draw_textEPKcjjjNS0_4Font9AlignmentENS4_5StyleEi+0x18c>
  10c163:	8b 45 ec             	mov    -0x14(%rbp),%eax
  10c166:	2b 45 b0             	sub    -0x50(%rbp),%eax
  10c169:	89 45 ac             	mov    %eax,-0x54(%rbp)
  10c16c:	e9 00 00 00 00       	jmp    10c171 <_ZN4acos8graphics8Renderer9draw_textEPKcjjjNS0_4Font9AlignmentENS4_5StyleEi+0x191>
  10c171:	c7 45 a8 00 00 00 00 	movl   $0x0,-0x58(%rbp)
  10c178:	8b 45 a8             	mov    -0x58(%rbp),%eax
  10c17b:	3b 45 b4             	cmp    -0x4c(%rbp),%eax
  10c17e:	0f 83 40 00 00 00    	jae    10c1c4 <_ZN4acos8graphics8Renderer9draw_textEPKcjjjNS0_4Font9AlignmentENS4_5StyleEi+0x1e4>
  10c184:	48 8b 7d a0          	mov    -0x60(%rbp),%rdi
  10c188:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  10c18c:	8b 4d a8             	mov    -0x58(%rbp),%ecx
  10c18f:	8a 04 08             	mov    (%rax,%rcx,1),%al
  10c192:	8b 55 ac             	mov    -0x54(%rbp),%edx
  10c195:	8b 4d a8             	mov    -0x58(%rbp),%ecx
  10c198:	8b 75 d4             	mov    -0x2c(%rbp),%esi
  10c19b:	03 75 18             	add    0x18(%rbp),%esi
  10c19e:	0f af ce             	imul   %esi,%ecx
  10c1a1:	01 ca                	add    %ecx,%edx
  10c1a3:	8b 4d cc             	mov    -0x34(%rbp),%ecx
  10c1a6:	44 8b 45 e4          	mov    -0x1c(%rbp),%r8d
  10c1aa:	44 8b 4d 10          	mov    0x10(%rbp),%r9d
  10c1ae:	0f be f0             	movsbl %al,%esi
  10c1b1:	e8 9a fb ff ff       	call   10bd50 <_ZN4acos8graphics8Renderer9draw_charEcjjjNS0_4Font5StyleE>
  10c1b6:	8b 45 a8             	mov    -0x58(%rbp),%eax
  10c1b9:	83 c0 01             	add    $0x1,%eax
  10c1bc:	89 45 a8             	mov    %eax,-0x58(%rbp)
  10c1bf:	e9 b4 ff ff ff       	jmp    10c178 <_ZN4acos8graphics8Renderer9draw_textEPKcjjjNS0_4Font9AlignmentENS4_5StyleEi+0x198>
  10c1c4:	8b 45 d0             	mov    -0x30(%rbp),%eax
  10c1c7:	03 45 cc             	add    -0x34(%rbp),%eax
  10c1ca:	89 45 cc             	mov    %eax,-0x34(%rbp)
  10c1cd:	48 8b 45 b8          	mov    -0x48(%rbp),%rax
  10c1d1:	0f be 00             	movsbl (%rax),%eax
  10c1d4:	83 f8 0a             	cmp    $0xa,%eax
  10c1d7:	0f 85 11 00 00 00    	jne    10c1ee <_ZN4acos8graphics8Renderer9draw_textEPKcjjjNS0_4Font9AlignmentENS4_5StyleEi+0x20e>
  10c1dd:	48 8b 45 b8          	mov    -0x48(%rbp),%rax
  10c1e1:	48 83 c0 01          	add    $0x1,%rax
  10c1e5:	48 89 45 88          	mov    %rax,-0x78(%rbp)
  10c1e9:	e9 08 00 00 00       	jmp    10c1f6 <_ZN4acos8graphics8Renderer9draw_textEPKcjjjNS0_4Font9AlignmentENS4_5StyleEi+0x216>
  10c1ee:	48 8b 45 b8          	mov    -0x48(%rbp),%rax
  10c1f2:	48 89 45 88          	mov    %rax,-0x78(%rbp)
  10c1f6:	48 8b 45 88          	mov    -0x78(%rbp),%rax
  10c1fa:	48 89 45 c0          	mov    %rax,-0x40(%rbp)
  10c1fe:	e9 bd fe ff ff       	jmp    10c0c0 <_ZN4acos8graphics8Renderer9draw_textEPKcjjjNS0_4Font9AlignmentENS4_5StyleEi+0xe0>
  10c203:	48 81 c4 80 00 00 00 	add    $0x80,%rsp
  10c20a:	5d                   	pop    %rbp
  10c20b:	c3                   	ret
  10c20c:	0f 1f 40 00          	nopl   0x0(%rax)

000000000010c210 <_ZN4acos8graphics8Renderer12measure_textEPKcRjS4_i>:
  10c210:	55                   	push   %rbp
  10c211:	48 89 e5             	mov    %rsp,%rbp
  10c214:	48 83 ec 30          	sub    $0x30,%rsp
  10c218:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10c21c:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  10c220:	48 89 55 e8          	mov    %rdx,-0x18(%rbp)
  10c224:	48 89 4d e0          	mov    %rcx,-0x20(%rbp)
  10c228:	44 89 45 dc          	mov    %r8d,-0x24(%rbp)
  10c22c:	48 8b 7d f0          	mov    -0x10(%rbp),%rdi
  10c230:	48 8b 75 e8          	mov    -0x18(%rbp),%rsi
  10c234:	48 8b 55 e0          	mov    -0x20(%rbp),%rdx
  10c238:	8b 4d dc             	mov    -0x24(%rbp),%ecx
  10c23b:	e8 10 13 00 00       	call   10d550 <_ZN4acos8graphics4Font22measure_string_defaultEPKcRjS4_i>
  10c240:	48 83 c4 30          	add    $0x30,%rsp
  10c244:	5d                   	pop    %rbp
  10c245:	c3                   	ret
  10c246:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
  10c24d:	00 00 00

000000000010c250 <_ZN4acos8graphics8Renderer11draw_circleEjjjj>:
  10c250:	55                   	push   %rbp
  10c251:	48 89 e5             	mov    %rsp,%rbp
  10c254:	48 83 ec 40          	sub    $0x40,%rsp
  10c258:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10c25c:	89 75 f4             	mov    %esi,-0xc(%rbp)
  10c25f:	89 55 f0             	mov    %edx,-0x10(%rbp)
  10c262:	89 4d ec             	mov    %ecx,-0x14(%rbp)
  10c265:	44 89 45 e8          	mov    %r8d,-0x18(%rbp)
  10c269:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10c26d:	48 89 45 c8          	mov    %rax,-0x38(%rbp)
  10c271:	8b 45 ec             	mov    -0x14(%rbp),%eax
  10c274:	89 45 e4             	mov    %eax,-0x1c(%rbp)
  10c277:	31 c0                	xor    %eax,%eax
  10c279:	2b 45 e4             	sub    -0x1c(%rbp),%eax
  10c27c:	89 45 e0             	mov    %eax,-0x20(%rbp)
  10c27f:	8b 45 e0             	mov    -0x20(%rbp),%eax
  10c282:	3b 45 e4             	cmp    -0x1c(%rbp),%eax
  10c285:	0f 8f 27 01 00 00    	jg     10c3b2 <_ZN4acos8graphics8Renderer11draw_circleEjjjj+0x162>
  10c28b:	31 c0                	xor    %eax,%eax
  10c28d:	2b 45 e4             	sub    -0x1c(%rbp),%eax
  10c290:	89 45 dc             	mov    %eax,-0x24(%rbp)
  10c293:	8b 45 dc             	mov    -0x24(%rbp),%eax
  10c296:	3b 45 e4             	cmp    -0x1c(%rbp),%eax
  10c299:	0f 8f 00 01 00 00    	jg     10c39f <_ZN4acos8graphics8Renderer11draw_circleEjjjj+0x14f>
  10c29f:	8b 45 dc             	mov    -0x24(%rbp),%eax
  10c2a2:	0f af 45 dc          	imul   -0x24(%rbp),%eax
  10c2a6:	8b 4d e0             	mov    -0x20(%rbp),%ecx
  10c2a9:	0f af 4d e0          	imul   -0x20(%rbp),%ecx
  10c2ad:	01 c8                	add    %ecx,%eax
  10c2af:	f3 0f 2a c0          	cvtsi2ss %eax,%xmm0
  10c2b3:	e8 08 01 00 00       	call   10c3c0 <_ZN4acos8graphics12_GLOBAL__N_14sqrtEf>
  10c2b8:	f3 0f 11 45 d8       	movss  %xmm0,-0x28(%rbp)
  10c2bd:	f3 0f 10 4d d8       	movss  -0x28(%rbp),%xmm1
  10c2c2:	f3 0f 2a 45 e4       	cvtsi2ssl -0x1c(%rbp),%xmm0
  10c2c7:	f3 0f 10 15 29 39 00 	movss  0x3929(%rip),%xmm2        # 10fbf8 <_ZTVN4acos8graphics13DisplayDeviceE+0x48>
  10c2ce:	00
  10c2cf:	f3 0f 58 c2          	addss  %xmm2,%xmm0
  10c2d3:	0f 2e c1             	ucomiss %xmm1,%xmm0
  10c2d6:	0f 82 b0 00 00 00    	jb     10c38c <_ZN4acos8graphics8Renderer11draw_circleEjjjj+0x13c>
  10c2dc:	f3 0f 10 05 0c 39 00 	movss  0x390c(%rip),%xmm0        # 10fbf0 <_ZTVN4acos8graphics13DisplayDeviceE+0x40>
  10c2e3:	00
  10c2e4:	f3 0f 11 45 d4       	movss  %xmm0,-0x2c(%rbp)
  10c2e9:	f3 0f 10 45 d8       	movss  -0x28(%rbp),%xmm0
  10c2ee:	f3 0f 2a 4d e4       	cvtsi2ssl -0x1c(%rbp),%xmm1
  10c2f3:	f3 0f 10 15 fd 38 00 	movss  0x38fd(%rip),%xmm2        # 10fbf8 <_ZTVN4acos8graphics13DisplayDeviceE+0x48>
  10c2fa:	00
  10c2fb:	f3 0f 5c ca          	subss  %xmm2,%xmm1
  10c2ff:	0f 2e c1             	ucomiss %xmm1,%xmm0
  10c302:	0f 86 2b 00 00 00    	jbe    10c333 <_ZN4acos8graphics8Renderer11draw_circleEjjjj+0xe3>
  10c308:	f3 0f 10 4d d8       	movss  -0x28(%rbp),%xmm1
  10c30d:	f3 0f 2a 45 e4       	cvtsi2ssl -0x1c(%rbp),%xmm0
  10c312:	f3 0f 10 15 de 38 00 	movss  0x38de(%rip),%xmm2        # 10fbf8 <_ZTVN4acos8graphics13DisplayDeviceE+0x48>
  10c319:	00
  10c31a:	f3 0f 5c c2          	subss  %xmm2,%xmm0
  10c31e:	f3 0f 5c c8          	subss  %xmm0,%xmm1
  10c322:	f3 0f 10 05 c6 38 00 	movss  0x38c6(%rip),%xmm0        # 10fbf0 <_ZTVN4acos8graphics13DisplayDeviceE+0x40>
  10c329:	00
  10c32a:	f3 0f 5c c1          	subss  %xmm1,%xmm0
  10c32e:	f3 0f 11 45 d4       	movss  %xmm0,-0x2c(%rbp)
  10c333:	f3 0f 10 45 d8       	movss  -0x28(%rbp),%xmm0
  10c338:	f3 0f 2a 4d e4       	cvtsi2ssl -0x1c(%rbp),%xmm1
  10c33d:	f3 0f 10 15 b7 38 00 	movss  0x38b7(%rip),%xmm2        # 10fbfc <_ZTVN4acos8graphics13DisplayDeviceE+0x4c>
  10c344:	00
  10c345:	f3 0f 5c ca          	subss  %xmm2,%xmm1
  10c349:	0f 2e c1             	ucomiss %xmm1,%xmm0
  10c34c:	0f 86 35 00 00 00    	jbe    10c387 <_ZN4acos8graphics8Renderer11draw_circleEjjjj+0x137>
  10c352:	48 8b 7d c8          	mov    -0x38(%rbp),%rdi
  10c356:	8b 75 f4             	mov    -0xc(%rbp),%esi
  10c359:	8b 45 dc             	mov    -0x24(%rbp),%eax
  10c35c:	01 c6                	add    %eax,%esi
  10c35e:	8b 55 f0             	mov    -0x10(%rbp),%edx
  10c361:	8b 45 e0             	mov    -0x20(%rbp),%eax
  10c364:	01 c2                	add    %eax,%edx
  10c366:	8b 4d e8             	mov    -0x18(%rbp),%ecx
  10c369:	f3 0f 10 45 d4       	movss  -0x2c(%rbp),%xmm0
  10c36e:	f3 0f 10 0d 7e 38 00 	movss  0x387e(%rip),%xmm1        # 10fbf4 <_ZTVN4acos8graphics13DisplayDeviceE+0x44>
  10c375:	00
  10c376:	f3 0f 59 c1          	mulss  %xmm1,%xmm0
  10c37a:	f3 0f 2c c0          	cvttss2si %xmm0,%eax
  10c37e:	44 0f b6 c0          	movzbl %al,%r8d
  10c382:	e8 39 f4 ff ff       	call   10b7c0 <_ZN4acos8graphics8Renderer11blend_pixelEjjjh>
  10c387:	e9 00 00 00 00       	jmp    10c38c <_ZN4acos8graphics8Renderer11draw_circleEjjjj+0x13c>
  10c38c:	e9 00 00 00 00       	jmp    10c391 <_ZN4acos8graphics8Renderer11draw_circleEjjjj+0x141>
  10c391:	8b 45 dc             	mov    -0x24(%rbp),%eax
  10c394:	83 c0 01             	add    $0x1,%eax
  10c397:	89 45 dc             	mov    %eax,-0x24(%rbp)
  10c39a:	e9 f4 fe ff ff       	jmp    10c293 <_ZN4acos8graphics8Renderer11draw_circleEjjjj+0x43>
  10c39f:	e9 00 00 00 00       	jmp    10c3a4 <_ZN4acos8graphics8Renderer11draw_circleEjjjj+0x154>
  10c3a4:	8b 45 e0             	mov    -0x20(%rbp),%eax
  10c3a7:	83 c0 01             	add    $0x1,%eax
  10c3aa:	89 45 e0             	mov    %eax,-0x20(%rbp)
  10c3ad:	e9 cd fe ff ff       	jmp    10c27f <_ZN4acos8graphics8Renderer11draw_circleEjjjj+0x2f>
  10c3b2:	48 83 c4 40          	add    $0x40,%rsp
  10c3b6:	5d                   	pop    %rbp
  10c3b7:	c3                   	ret
  10c3b8:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  10c3bf:	00

000000000010c3c0 <_ZN4acos8graphics12_GLOBAL__N_14sqrtEf>:
  10c3c0:	55                   	push   %rbp
  10c3c1:	48 89 e5             	mov    %rsp,%rbp
  10c3c4:	48 83 ec 10          	sub    $0x10,%rsp
  10c3c8:	f3 0f 11 45 f8       	movss  %xmm0,-0x8(%rbp)
  10c3cd:	0f 57 c0             	xorps  %xmm0,%xmm0
  10c3d0:	0f 2e 45 f8          	ucomiss -0x8(%rbp),%xmm0
  10c3d4:	0f 86 0d 00 00 00    	jbe    10c3e7 <_ZN4acos8graphics12_GLOBAL__N_14sqrtEf+0x27>
  10c3da:	0f 57 c0             	xorps  %xmm0,%xmm0
  10c3dd:	f3 0f 11 45 fc       	movss  %xmm0,-0x4(%rbp)
  10c3e2:	e9 79 00 00 00       	jmp    10c460 <_ZN4acos8graphics12_GLOBAL__N_14sqrtEf+0xa0>
  10c3e7:	f3 0f 10 05 01 38 00 	movss  0x3801(%rip),%xmm0        # 10fbf0 <_ZTVN4acos8graphics13DisplayDeviceE+0x40>
  10c3ee:	00
  10c3ef:	f3 0f 11 45 f4       	movss  %xmm0,-0xc(%rbp)
  10c3f4:	c7 45 f0 00 00 00 00 	movl   $0x0,-0x10(%rbp)
  10c3fb:	83 7d f0 0a          	cmpl   $0xa,-0x10(%rbp)
  10c3ff:	0f 8d 51 00 00 00    	jge    10c456 <_ZN4acos8graphics12_GLOBAL__N_14sqrtEf+0x96>
  10c405:	f3 0f 10 4d f4       	movss  -0xc(%rbp),%xmm1
  10c40a:	f3 0f 10 55 f4       	movss  -0xc(%rbp),%xmm2
  10c40f:	f3 0f 10 45 f8       	movss  -0x8(%rbp),%xmm0
  10c414:	66 0f 7e c0          	movd   %xmm0,%eax
  10c418:	35 00 00 00 80       	xor    $0x80000000,%eax
  10c41d:	66 0f 6e c0          	movd   %eax,%xmm0
  10c421:	f3 0f 59 ca          	mulss  %xmm2,%xmm1
  10c425:	f3 0f 58 c8          	addss  %xmm0,%xmm1
  10c429:	f3 0f 10 05 cf 37 00 	movss  0x37cf(%rip),%xmm0        # 10fc00 <_ZTVN4acos8graphics13DisplayDeviceE+0x50>
  10c430:	00
  10c431:	f3 0f 59 45 f4       	mulss  -0xc(%rbp),%xmm0
  10c436:	f3 0f 5e c8          	divss  %xmm0,%xmm1
  10c43a:	f3 0f 10 45 f4       	movss  -0xc(%rbp),%xmm0
  10c43f:	f3 0f 5c c1          	subss  %xmm1,%xmm0
  10c443:	f3 0f 11 45 f4       	movss  %xmm0,-0xc(%rbp)
  10c448:	8b 45 f0             	mov    -0x10(%rbp),%eax
  10c44b:	83 c0 01             	add    $0x1,%eax
  10c44e:	89 45 f0             	mov    %eax,-0x10(%rbp)
  10c451:	e9 a5 ff ff ff       	jmp    10c3fb <_ZN4acos8graphics12_GLOBAL__N_14sqrtEf+0x3b>
  10c456:	f3 0f 10 45 f4       	movss  -0xc(%rbp),%xmm0
  10c45b:	f3 0f 11 45 fc       	movss  %xmm0,-0x4(%rbp)
  10c460:	f3 0f 10 45 fc       	movss  -0x4(%rbp),%xmm0
  10c465:	48 83 c4 10          	add    $0x10,%rsp
  10c469:	5d                   	pop    %rbp
  10c46a:	c3                   	ret
  10c46b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

000000000010c470 <_ZN4acos8graphics8Renderer11fill_circleEjjjj>:
  10c470:	55                   	push   %rbp
  10c471:	48 89 e5             	mov    %rsp,%rbp
  10c474:	48 83 ec 40          	sub    $0x40,%rsp
  10c478:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10c47c:	89 75 f4             	mov    %esi,-0xc(%rbp)
  10c47f:	89 55 f0             	mov    %edx,-0x10(%rbp)
  10c482:	89 4d ec             	mov    %ecx,-0x14(%rbp)
  10c485:	44 89 45 e8          	mov    %r8d,-0x18(%rbp)
  10c489:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10c48d:	48 89 45 c8          	mov    %rax,-0x38(%rbp)
  10c491:	8b 45 ec             	mov    -0x14(%rbp),%eax
  10c494:	89 45 e4             	mov    %eax,-0x1c(%rbp)
  10c497:	8b 45 e8             	mov    -0x18(%rbp),%eax
  10c49a:	c1 e8 18             	shr    $0x18,%eax
  10c49d:	25 ff 00 00 00       	and    $0xff,%eax
  10c4a2:	88 45 e3             	mov    %al,-0x1d(%rbp)
  10c4a5:	31 c0                	xor    %eax,%eax
  10c4a7:	2b 45 e4             	sub    -0x1c(%rbp),%eax
  10c4aa:	89 45 dc             	mov    %eax,-0x24(%rbp)
  10c4ad:	8b 45 dc             	mov    -0x24(%rbp),%eax
  10c4b0:	3b 45 e4             	cmp    -0x1c(%rbp),%eax
  10c4b3:	0f 8f 2d 01 00 00    	jg     10c5e6 <_ZN4acos8graphics8Renderer11fill_circleEjjjj+0x176>
  10c4b9:	31 c0                	xor    %eax,%eax
  10c4bb:	2b 45 e4             	sub    -0x1c(%rbp),%eax
  10c4be:	89 45 d8             	mov    %eax,-0x28(%rbp)
  10c4c1:	8b 45 d8             	mov    -0x28(%rbp),%eax
  10c4c4:	3b 45 e4             	cmp    -0x1c(%rbp),%eax
  10c4c7:	0f 8f 06 01 00 00    	jg     10c5d3 <_ZN4acos8graphics8Renderer11fill_circleEjjjj+0x163>
  10c4cd:	8b 45 d8             	mov    -0x28(%rbp),%eax
  10c4d0:	0f af 45 d8          	imul   -0x28(%rbp),%eax
  10c4d4:	8b 4d dc             	mov    -0x24(%rbp),%ecx
  10c4d7:	0f af 4d dc          	imul   -0x24(%rbp),%ecx
  10c4db:	01 c8                	add    %ecx,%eax
  10c4dd:	f3 0f 2a c0          	cvtsi2ss %eax,%xmm0
  10c4e1:	e8 da fe ff ff       	call   10c3c0 <_ZN4acos8graphics12_GLOBAL__N_14sqrtEf>
  10c4e6:	f3 0f 11 45 d4       	movss  %xmm0,-0x2c(%rbp)
  10c4eb:	f3 0f 10 4d d4       	movss  -0x2c(%rbp),%xmm1
  10c4f0:	f3 0f 2a 45 e4       	cvtsi2ssl -0x1c(%rbp),%xmm0
  10c4f5:	f3 0f 10 15 fb 36 00 	movss  0x36fb(%rip),%xmm2        # 10fbf8 <_ZTVN4acos8graphics13DisplayDeviceE+0x48>
  10c4fc:	00
  10c4fd:	f3 0f 5c c2          	subss  %xmm2,%xmm0
  10c501:	0f 2e c1             	ucomiss %xmm1,%xmm0
  10c504:	0f 82 22 00 00 00    	jb     10c52c <_ZN4acos8graphics8Renderer11fill_circleEjjjj+0xbc>
  10c50a:	48 8b 7d c8          	mov    -0x38(%rbp),%rdi
  10c50e:	8b 75 f4             	mov    -0xc(%rbp),%esi
  10c511:	03 75 d8             	add    -0x28(%rbp),%esi
  10c514:	8b 55 f0             	mov    -0x10(%rbp),%edx
  10c517:	03 55 dc             	add    -0x24(%rbp),%edx
  10c51a:	8b 4d e8             	mov    -0x18(%rbp),%ecx
  10c51d:	44 0f b6 45 e3       	movzbl -0x1d(%rbp),%r8d
  10c522:	e8 99 f2 ff ff       	call   10b7c0 <_ZN4acos8graphics8Renderer11blend_pixelEjjjh>
  10c527:	e9 94 00 00 00       	jmp    10c5c0 <_ZN4acos8graphics8Renderer11fill_circleEjjjj+0x150>
  10c52c:	f3 0f 10 4d d4       	movss  -0x2c(%rbp),%xmm1
  10c531:	f3 0f 2a 45 e4       	cvtsi2ssl -0x1c(%rbp),%xmm0
  10c536:	f3 0f 10 15 ba 36 00 	movss  0x36ba(%rip),%xmm2        # 10fbf8 <_ZTVN4acos8graphics13DisplayDeviceE+0x48>
  10c53d:	00
  10c53e:	f3 0f 58 c2          	addss  %xmm2,%xmm0
  10c542:	0f 2e c1             	ucomiss %xmm1,%xmm0
  10c545:	0f 82 70 00 00 00    	jb     10c5bb <_ZN4acos8graphics8Renderer11fill_circleEjjjj+0x14b>
  10c54b:	48 8b 7d c8          	mov    -0x38(%rbp),%rdi
  10c54f:	f3 0f 10 4d d4       	movss  -0x2c(%rbp),%xmm1
  10c554:	f3 0f 2a 45 e4       	cvtsi2ssl -0x1c(%rbp),%xmm0
  10c559:	f3 0f 10 15 a3 36 00 	movss  0x36a3(%rip),%xmm2        # 10fc04 <_ZTVN4acos8graphics13DisplayDeviceE+0x54>
  10c560:	00
  10c561:	f3 0f 58 c2          	addss  %xmm2,%xmm0
  10c565:	f3 0f 5c c8          	subss  %xmm0,%xmm1
  10c569:	f3 0f 10 05 7f 36 00 	movss  0x367f(%rip),%xmm0        # 10fbf0 <_ZTVN4acos8graphics13DisplayDeviceE+0x40>
  10c570:	00
  10c571:	f3 0f 5c c1          	subss  %xmm1,%xmm0
  10c575:	0f b6 45 e3          	movzbl -0x1d(%rbp),%eax
  10c579:	f3 0f 2a d0          	cvtsi2ss %eax,%xmm2
  10c57d:	f3 0f 10 0d 6f 36 00 	movss  0x366f(%rip),%xmm1        # 10fbf4 <_ZTVN4acos8graphics13DisplayDeviceE+0x44>
  10c584:	00
  10c585:	f3 0f 5e d1          	divss  %xmm1,%xmm2
  10c589:	f3 0f 59 c2          	mulss  %xmm2,%xmm0
  10c58d:	f3 0f 11 45 d0       	movss  %xmm0,-0x30(%rbp)
  10c592:	8b 75 f4             	mov    -0xc(%rbp),%esi
  10c595:	8b 45 d8             	mov    -0x28(%rbp),%eax
  10c598:	01 c6                	add    %eax,%esi
  10c59a:	8b 55 f0             	mov    -0x10(%rbp),%edx
  10c59d:	8b 45 dc             	mov    -0x24(%rbp),%eax
  10c5a0:	01 c2                	add    %eax,%edx
  10c5a2:	8b 4d e8             	mov    -0x18(%rbp),%ecx
  10c5a5:	f3 0f 10 45 d0       	movss  -0x30(%rbp),%xmm0
  10c5aa:	f3 0f 59 c1          	mulss  %xmm1,%xmm0
  10c5ae:	f3 0f 2c c0          	cvttss2si %xmm0,%eax
  10c5b2:	44 0f b6 c0          	movzbl %al,%r8d
  10c5b6:	e8 05 f2 ff ff       	call   10b7c0 <_ZN4acos8graphics8Renderer11blend_pixelEjjjh>
  10c5bb:	e9 00 00 00 00       	jmp    10c5c0 <_ZN4acos8graphics8Renderer11fill_circleEjjjj+0x150>
  10c5c0:	e9 00 00 00 00       	jmp    10c5c5 <_ZN4acos8graphics8Renderer11fill_circleEjjjj+0x155>
  10c5c5:	8b 45 d8             	mov    -0x28(%rbp),%eax
  10c5c8:	83 c0 01             	add    $0x1,%eax
  10c5cb:	89 45 d8             	mov    %eax,-0x28(%rbp)
  10c5ce:	e9 ee fe ff ff       	jmp    10c4c1 <_ZN4acos8graphics8Renderer11fill_circleEjjjj+0x51>
  10c5d3:	e9 00 00 00 00       	jmp    10c5d8 <_ZN4acos8graphics8Renderer11fill_circleEjjjj+0x168>
  10c5d8:	8b 45 dc             	mov    -0x24(%rbp),%eax
  10c5db:	83 c0 01             	add    $0x1,%eax
  10c5de:	89 45 dc             	mov    %eax,-0x24(%rbp)
  10c5e1:	e9 c7 fe ff ff       	jmp    10c4ad <_ZN4acos8graphics8Renderer11fill_circleEjjjj+0x3d>
  10c5e6:	48 83 c4 40          	add    $0x40,%rsp
  10c5ea:	5d                   	pop    %rbp
  10c5eb:	c3                   	ret
  10c5ec:	0f 1f 40 00          	nopl   0x0(%rax)

000000000010c5f0 <_ZN4acos8graphics8Renderer17draw_rounded_rectEjjjjjj>:
  10c5f0:	55                   	push   %rbp
  10c5f1:	48 89 e5             	mov    %rsp,%rbp
  10c5f4:	48 83 ec 40          	sub    $0x40,%rsp
  10c5f8:	8b 45 10             	mov    0x10(%rbp),%eax
  10c5fb:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10c5ff:	89 75 f4             	mov    %esi,-0xc(%rbp)
  10c602:	89 55 f0             	mov    %edx,-0x10(%rbp)
  10c605:	89 4d ec             	mov    %ecx,-0x14(%rbp)
  10c608:	44 89 45 e8          	mov    %r8d,-0x18(%rbp)
  10c60c:	44 89 4d e4          	mov    %r9d,-0x1c(%rbp)
  10c610:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  10c614:	48 89 7d c0          	mov    %rdi,-0x40(%rbp)
  10c618:	8b 75 f4             	mov    -0xc(%rbp),%esi
  10c61b:	03 75 e4             	add    -0x1c(%rbp),%esi
  10c61e:	8b 55 f0             	mov    -0x10(%rbp),%edx
  10c621:	8b 4d f4             	mov    -0xc(%rbp),%ecx
  10c624:	03 4d ec             	add    -0x14(%rbp),%ecx
  10c627:	2b 4d e4             	sub    -0x1c(%rbp),%ecx
  10c62a:	44 8b 45 f0          	mov    -0x10(%rbp),%r8d
  10c62e:	44 8b 4d 10          	mov    0x10(%rbp),%r9d
  10c632:	e8 b9 f2 ff ff       	call   10b8f0 <_ZN4acos8graphics8Renderer9draw_lineEjjjjj>
  10c637:	48 8b 7d c0          	mov    -0x40(%rbp),%rdi
  10c63b:	8b 75 f4             	mov    -0xc(%rbp),%esi
  10c63e:	03 75 e4             	add    -0x1c(%rbp),%esi
  10c641:	8b 55 f0             	mov    -0x10(%rbp),%edx
  10c644:	03 55 e8             	add    -0x18(%rbp),%edx
  10c647:	83 ea 01             	sub    $0x1,%edx
  10c64a:	8b 4d f4             	mov    -0xc(%rbp),%ecx
  10c64d:	03 4d ec             	add    -0x14(%rbp),%ecx
  10c650:	2b 4d e4             	sub    -0x1c(%rbp),%ecx
  10c653:	44 8b 45 f0          	mov    -0x10(%rbp),%r8d
  10c657:	44 03 45 e8          	add    -0x18(%rbp),%r8d
  10c65b:	41 83 e8 01          	sub    $0x1,%r8d
  10c65f:	44 8b 4d 10          	mov    0x10(%rbp),%r9d
  10c663:	e8 88 f2 ff ff       	call   10b8f0 <_ZN4acos8graphics8Renderer9draw_lineEjjjjj>
  10c668:	48 8b 7d c0          	mov    -0x40(%rbp),%rdi
  10c66c:	8b 75 f4             	mov    -0xc(%rbp),%esi
  10c66f:	8b 55 f0             	mov    -0x10(%rbp),%edx
  10c672:	03 55 e4             	add    -0x1c(%rbp),%edx
  10c675:	8b 4d f4             	mov    -0xc(%rbp),%ecx
  10c678:	44 8b 45 f0          	mov    -0x10(%rbp),%r8d
  10c67c:	44 03 45 e8          	add    -0x18(%rbp),%r8d
  10c680:	44 2b 45 e4          	sub    -0x1c(%rbp),%r8d
  10c684:	44 8b 4d 10          	mov    0x10(%rbp),%r9d
  10c688:	e8 63 f2 ff ff       	call   10b8f0 <_ZN4acos8graphics8Renderer9draw_lineEjjjjj>
  10c68d:	48 8b 7d c0          	mov    -0x40(%rbp),%rdi
  10c691:	8b 75 f4             	mov    -0xc(%rbp),%esi
  10c694:	03 75 ec             	add    -0x14(%rbp),%esi
  10c697:	83 ee 01             	sub    $0x1,%esi
  10c69a:	8b 55 f0             	mov    -0x10(%rbp),%edx
  10c69d:	03 55 e4             	add    -0x1c(%rbp),%edx
  10c6a0:	8b 4d f4             	mov    -0xc(%rbp),%ecx
  10c6a3:	03 4d ec             	add    -0x14(%rbp),%ecx
  10c6a6:	83 e9 01             	sub    $0x1,%ecx
  10c6a9:	44 8b 45 f0          	mov    -0x10(%rbp),%r8d
  10c6ad:	44 03 45 e8          	add    -0x18(%rbp),%r8d
  10c6b1:	44 2b 45 e4          	sub    -0x1c(%rbp),%r8d
  10c6b5:	44 8b 4d 10          	mov    0x10(%rbp),%r9d
  10c6b9:	e8 32 f2 ff ff       	call   10b8f0 <_ZN4acos8graphics8Renderer9draw_lineEjjjjj>
  10c6be:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  10c6c2:	48 8d 4d e4          	lea    -0x1c(%rbp),%rcx
  10c6c6:	48 89 4d c8          	mov    %rcx,-0x38(%rbp)
  10c6ca:	48 89 45 d0          	mov    %rax,-0x30(%rbp)
  10c6ce:	48 8d 45 10          	lea    0x10(%rbp),%rax
  10c6d2:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
  10c6d6:	8b 75 f4             	mov    -0xc(%rbp),%esi
  10c6d9:	03 75 e4             	add    -0x1c(%rbp),%esi
  10c6dc:	8b 55 f0             	mov    -0x10(%rbp),%edx
  10c6df:	03 55 e4             	add    -0x1c(%rbp),%edx
  10c6e2:	48 8d 7d c8          	lea    -0x38(%rbp),%rdi
  10c6e6:	41 b8 01 00 00 00    	mov    $0x1,%r8d
  10c6ec:	44 89 c1             	mov    %r8d,%ecx
  10c6ef:	e8 6c 00 00 00       	call   10c760 <_ZZN4acos8graphics8Renderer17draw_rounded_rectEjjjjjjENK3$_0clEiibb>
  10c6f4:	8b 75 f4             	mov    -0xc(%rbp),%esi
  10c6f7:	03 75 ec             	add    -0x14(%rbp),%esi
  10c6fa:	2b 75 e4             	sub    -0x1c(%rbp),%esi
  10c6fd:	8b 55 f0             	mov    -0x10(%rbp),%edx
  10c700:	03 55 e4             	add    -0x1c(%rbp),%edx
  10c703:	48 8d 7d c8          	lea    -0x38(%rbp),%rdi
  10c707:	b9 01 00 00 00       	mov    $0x1,%ecx
  10c70c:	45 31 c0             	xor    %r8d,%r8d
  10c70f:	e8 4c 00 00 00       	call   10c760 <_ZZN4acos8graphics8Renderer17draw_rounded_rectEjjjjjjENK3$_0clEiibb>
  10c714:	8b 75 f4             	mov    -0xc(%rbp),%esi
  10c717:	03 75 e4             	add    -0x1c(%rbp),%esi
  10c71a:	8b 55 f0             	mov    -0x10(%rbp),%edx
  10c71d:	03 55 e8             	add    -0x18(%rbp),%edx
  10c720:	2b 55 e4             	sub    -0x1c(%rbp),%edx
  10c723:	48 8d 7d c8          	lea    -0x38(%rbp),%rdi
  10c727:	31 c9                	xor    %ecx,%ecx
  10c729:	41 b8 01 00 00 00    	mov    $0x1,%r8d
  10c72f:	e8 2c 00 00 00       	call   10c760 <_ZZN4acos8graphics8Renderer17draw_rounded_rectEjjjjjjENK3$_0clEiibb>
  10c734:	8b 75 f4             	mov    -0xc(%rbp),%esi
  10c737:	03 75 ec             	add    -0x14(%rbp),%esi
  10c73a:	2b 75 e4             	sub    -0x1c(%rbp),%esi
  10c73d:	8b 55 f0             	mov    -0x10(%rbp),%edx
  10c740:	03 55 e8             	add    -0x18(%rbp),%edx
  10c743:	2b 55 e4             	sub    -0x1c(%rbp),%edx
  10c746:	48 8d 7d c8          	lea    -0x38(%rbp),%rdi
  10c74a:	45 31 c0             	xor    %r8d,%r8d
  10c74d:	44 89 c1             	mov    %r8d,%ecx
  10c750:	e8 0b 00 00 00       	call   10c760 <_ZZN4acos8graphics8Renderer17draw_rounded_rectEjjjjjjENK3$_0clEiibb>
  10c755:	48 83 c4 40          	add    $0x40,%rsp
  10c759:	5d                   	pop    %rbp
  10c75a:	c3                   	ret
  10c75b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

000000000010c760 <_ZZN4acos8graphics8Renderer17draw_rounded_rectEjjjjjjENK3$_0clEiibb>:
  10c760:	55                   	push   %rbp
  10c761:	48 89 e5             	mov    %rsp,%rbp
  10c764:	48 83 ec 50          	sub    $0x50,%rsp
  10c768:	44 88 c0             	mov    %r8b,%al
  10c76b:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10c76f:	89 75 f4             	mov    %esi,-0xc(%rbp)
  10c772:	89 55 f0             	mov    %edx,-0x10(%rbp)
  10c775:	80 e1 01             	and    $0x1,%cl
  10c778:	88 4d ef             	mov    %cl,-0x11(%rbp)
  10c77b:	24 01                	and    $0x1,%al
  10c77d:	88 45 ee             	mov    %al,-0x12(%rbp)
  10c780:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10c784:	48 89 45 c0          	mov    %rax,-0x40(%rbp)
  10c788:	48 8b 48 08          	mov    0x8(%rax),%rcx
  10c78c:	48 89 4d c8          	mov    %rcx,-0x38(%rbp)
  10c790:	48 8b 08             	mov    (%rax),%rcx
  10c793:	31 c0                	xor    %eax,%eax
  10c795:	2b 01                	sub    (%rcx),%eax
  10c797:	89 45 e8             	mov    %eax,-0x18(%rbp)
  10c79a:	83 7d e8 00          	cmpl   $0x0,-0x18(%rbp)
  10c79e:	0f 8f 8d 01 00 00    	jg     10c931 <_ZZN4acos8graphics8Renderer17draw_rounded_rectEjjjjjjENK3$_0clEiibb+0x1d1>
  10c7a4:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  10c7a8:	48 8b 08             	mov    (%rax),%rcx
  10c7ab:	31 c0                	xor    %eax,%eax
  10c7ad:	2b 01                	sub    (%rcx),%eax
  10c7af:	89 45 e4             	mov    %eax,-0x1c(%rbp)
  10c7b2:	83 7d e4 00          	cmpl   $0x0,-0x1c(%rbp)
  10c7b6:	0f 8f 62 01 00 00    	jg     10c91e <_ZZN4acos8graphics8Renderer17draw_rounded_rectEjjjjjjENK3$_0clEiibb+0x1be>
  10c7bc:	8b 45 e4             	mov    -0x1c(%rbp),%eax
  10c7bf:	0f af c0             	imul   %eax,%eax
  10c7c2:	8b 4d e8             	mov    -0x18(%rbp),%ecx
  10c7c5:	0f af c9             	imul   %ecx,%ecx
  10c7c8:	01 c8                	add    %ecx,%eax
  10c7ca:	f3 0f 2a c0          	cvtsi2ss %eax,%xmm0
  10c7ce:	e8 ed fb ff ff       	call   10c3c0 <_ZN4acos8graphics12_GLOBAL__N_14sqrtEf>
  10c7d3:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  10c7d7:	f3 0f 11 45 e0       	movss  %xmm0,-0x20(%rbp)
  10c7dc:	f3 0f 10 45 e0       	movss  -0x20(%rbp),%xmm0
  10c7e1:	48 8b 00             	mov    (%rax),%rax
  10c7e4:	8b 00                	mov    (%rax),%eax
  10c7e6:	f3 48 0f 2a c8       	cvtsi2ss %rax,%xmm1
  10c7eb:	f3 0f 10 15 09 34 00 	movss  0x3409(%rip),%xmm2        # 10fbfc <_ZTVN4acos8graphics13DisplayDeviceE+0x4c>
  10c7f2:	00
  10c7f3:	f3 0f 5c ca          	subss  %xmm2,%xmm1
  10c7f7:	0f 2e c1             	ucomiss %xmm1,%xmm0
  10c7fa:	0f 86 0b 01 00 00    	jbe    10c90b <_ZZN4acos8graphics8Renderer17draw_rounded_rectEjjjjjjENK3$_0clEiibb+0x1ab>
  10c800:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  10c804:	f3 0f 10 4d e0       	movss  -0x20(%rbp),%xmm1
  10c809:	48 8b 00             	mov    (%rax),%rax
  10c80c:	8b 00                	mov    (%rax),%eax
  10c80e:	f3 48 0f 2a c0       	cvtsi2ss %rax,%xmm0
  10c813:	f3 0f 10 15 dd 33 00 	movss  0x33dd(%rip),%xmm2        # 10fbf8 <_ZTVN4acos8graphics13DisplayDeviceE+0x48>
  10c81a:	00
  10c81b:	f3 0f 58 c2          	addss  %xmm2,%xmm0
  10c81f:	0f 2e c1             	ucomiss %xmm1,%xmm0
  10c822:	0f 82 e3 00 00 00    	jb     10c90b <_ZZN4acos8graphics8Renderer17draw_rounded_rectEjjjjjjENK3$_0clEiibb+0x1ab>
  10c828:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  10c82c:	c7 45 dc 00 00 80 3f 	movl   $0x3f800000,-0x24(%rbp)
  10c833:	f3 0f 10 45 e0       	movss  -0x20(%rbp),%xmm0
  10c838:	48 8b 00             	mov    (%rax),%rax
  10c83b:	8b 00                	mov    (%rax),%eax
  10c83d:	f3 48 0f 2a c8       	cvtsi2ss %rax,%xmm1
  10c842:	f3 0f 10 15 ae 33 00 	movss  0x33ae(%rip),%xmm2        # 10fbf8 <_ZTVN4acos8graphics13DisplayDeviceE+0x48>
  10c849:	00
  10c84a:	f3 0f 5c ca          	subss  %xmm2,%xmm1
  10c84e:	0f 2e c1             	ucomiss %xmm1,%xmm0
  10c851:	0f 86 34 00 00 00    	jbe    10c88b <_ZZN4acos8graphics8Renderer17draw_rounded_rectEjjjjjjENK3$_0clEiibb+0x12b>
  10c857:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  10c85b:	f3 0f 10 4d e0       	movss  -0x20(%rbp),%xmm1
  10c860:	48 8b 00             	mov    (%rax),%rax
  10c863:	8b 00                	mov    (%rax),%eax
  10c865:	f3 48 0f 2a c0       	cvtsi2ss %rax,%xmm0
  10c86a:	f3 0f 10 15 86 33 00 	movss  0x3386(%rip),%xmm2        # 10fbf8 <_ZTVN4acos8graphics13DisplayDeviceE+0x48>
  10c871:	00
  10c872:	f3 0f 5c c2          	subss  %xmm2,%xmm0
  10c876:	f3 0f 5c c8          	subss  %xmm0,%xmm1
  10c87a:	f3 0f 10 05 6e 33 00 	movss  0x336e(%rip),%xmm0        # 10fbf0 <_ZTVN4acos8graphics13DisplayDeviceE+0x40>
  10c881:	00
  10c882:	f3 0f 5c c1          	subss  %xmm1,%xmm0
  10c886:	f3 0f 11 45 dc       	movss  %xmm0,-0x24(%rbp)
  10c88b:	f6 45 ee 01          	testb  $0x1,-0x12(%rbp)
  10c88f:	0f 84 0e 00 00 00    	je     10c8a3 <_ZZN4acos8graphics8Renderer17draw_rounded_rectEjjjjjjENK3$_0clEiibb+0x143>
  10c895:	8b 45 f4             	mov    -0xc(%rbp),%eax
  10c898:	03 45 e4             	add    -0x1c(%rbp),%eax
  10c89b:	89 45 bc             	mov    %eax,-0x44(%rbp)
  10c89e:	e9 09 00 00 00       	jmp    10c8ac <_ZZN4acos8graphics8Renderer17draw_rounded_rectEjjjjjjENK3$_0clEiibb+0x14c>
  10c8a3:	8b 45 f4             	mov    -0xc(%rbp),%eax
  10c8a6:	2b 45 e4             	sub    -0x1c(%rbp),%eax
  10c8a9:	89 45 bc             	mov    %eax,-0x44(%rbp)
  10c8ac:	8b 45 bc             	mov    -0x44(%rbp),%eax
  10c8af:	89 45 d8             	mov    %eax,-0x28(%rbp)
  10c8b2:	f6 45 ef 01          	testb  $0x1,-0x11(%rbp)
  10c8b6:	0f 84 0e 00 00 00    	je     10c8ca <_ZZN4acos8graphics8Renderer17draw_rounded_rectEjjjjjjENK3$_0clEiibb+0x16a>
  10c8bc:	8b 45 f0             	mov    -0x10(%rbp),%eax
  10c8bf:	03 45 e8             	add    -0x18(%rbp),%eax
  10c8c2:	89 45 b8             	mov    %eax,-0x48(%rbp)
  10c8c5:	e9 09 00 00 00       	jmp    10c8d3 <_ZZN4acos8graphics8Renderer17draw_rounded_rectEjjjjjjENK3$_0clEiibb+0x173>
  10c8ca:	8b 45 f0             	mov    -0x10(%rbp),%eax
  10c8cd:	2b 45 e8             	sub    -0x18(%rbp),%eax
  10c8d0:	89 45 b8             	mov    %eax,-0x48(%rbp)
  10c8d3:	48 8b 7d c8          	mov    -0x38(%rbp),%rdi
  10c8d7:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  10c8db:	8b 4d b8             	mov    -0x48(%rbp),%ecx
  10c8de:	89 4d d4             	mov    %ecx,-0x2c(%rbp)
  10c8e1:	8b 75 d8             	mov    -0x28(%rbp),%esi
  10c8e4:	8b 55 d4             	mov    -0x2c(%rbp),%edx
  10c8e7:	48 8b 40 10          	mov    0x10(%rax),%rax
  10c8eb:	8b 08                	mov    (%rax),%ecx
  10c8ed:	f3 0f 10 45 dc       	movss  -0x24(%rbp),%xmm0
  10c8f2:	f3 0f 10 0d fa 32 00 	movss  0x32fa(%rip),%xmm1        # 10fbf4 <_ZTVN4acos8graphics13DisplayDeviceE+0x44>
  10c8f9:	00
  10c8fa:	f3 0f 59 c1          	mulss  %xmm1,%xmm0
  10c8fe:	f3 0f 2c c0          	cvttss2si %xmm0,%eax
  10c902:	44 0f b6 c0          	movzbl %al,%r8d
  10c906:	e8 b5 ee ff ff       	call   10b7c0 <_ZN4acos8graphics8Renderer11blend_pixelEjjjh>
  10c90b:	e9 00 00 00 00       	jmp    10c910 <_ZZN4acos8graphics8Renderer17draw_rounded_rectEjjjjjjENK3$_0clEiibb+0x1b0>
  10c910:	8b 45 e4             	mov    -0x1c(%rbp),%eax
  10c913:	83 c0 01             	add    $0x1,%eax
  10c916:	89 45 e4             	mov    %eax,-0x1c(%rbp)
  10c919:	e9 94 fe ff ff       	jmp    10c7b2 <_ZZN4acos8graphics8Renderer17draw_rounded_rectEjjjjjjENK3$_0clEiibb+0x52>
  10c91e:	e9 00 00 00 00       	jmp    10c923 <_ZZN4acos8graphics8Renderer17draw_rounded_rectEjjjjjjENK3$_0clEiibb+0x1c3>
  10c923:	8b 45 e8             	mov    -0x18(%rbp),%eax
  10c926:	83 c0 01             	add    $0x1,%eax
  10c929:	89 45 e8             	mov    %eax,-0x18(%rbp)
  10c92c:	e9 69 fe ff ff       	jmp    10c79a <_ZZN4acos8graphics8Renderer17draw_rounded_rectEjjjjjjENK3$_0clEiibb+0x3a>
  10c931:	48 83 c4 50          	add    $0x50,%rsp
  10c935:	5d                   	pop    %rbp
  10c936:	c3                   	ret
  10c937:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
  10c93e:	00 00

000000000010c940 <_ZN4acos8graphics8Renderer17fill_rounded_rectEjjjjjj>:
  10c940:	55                   	push   %rbp
  10c941:	48 89 e5             	mov    %rsp,%rbp
  10c944:	48 83 ec 50          	sub    $0x50,%rsp
  10c948:	8b 45 10             	mov    0x10(%rbp),%eax
  10c94b:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10c94f:	89 75 f4             	mov    %esi,-0xc(%rbp)
  10c952:	89 55 f0             	mov    %edx,-0x10(%rbp)
  10c955:	89 4d ec             	mov    %ecx,-0x14(%rbp)
  10c958:	44 89 45 e8          	mov    %r8d,-0x18(%rbp)
  10c95c:	44 89 4d e4          	mov    %r9d,-0x1c(%rbp)
  10c960:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  10c964:	48 89 7d c0          	mov    %rdi,-0x40(%rbp)
  10c968:	8b 45 10             	mov    0x10(%rbp),%eax
  10c96b:	c1 e8 18             	shr    $0x18,%eax
  10c96e:	25 ff 00 00 00       	and    $0xff,%eax
  10c973:	88 45 e3             	mov    %al,-0x1d(%rbp)
  10c976:	8b 75 f4             	mov    -0xc(%rbp),%esi
  10c979:	03 75 e4             	add    -0x1c(%rbp),%esi
  10c97c:	8b 55 f0             	mov    -0x10(%rbp),%edx
  10c97f:	8b 4d ec             	mov    -0x14(%rbp),%ecx
  10c982:	8b 45 e4             	mov    -0x1c(%rbp),%eax
  10c985:	d1 e0                	shl    $1,%eax
  10c987:	29 c1                	sub    %eax,%ecx
  10c989:	44 8b 45 e8          	mov    -0x18(%rbp),%r8d
  10c98d:	44 8b 4d 10          	mov    0x10(%rbp),%r9d
  10c991:	0f b6 45 e3          	movzbl -0x1d(%rbp),%eax
  10c995:	89 04 24             	mov    %eax,(%rsp)
  10c998:	e8 13 01 00 00       	call   10cab0 <_ZN4acos8graphics8Renderer10blend_rectEjjjjjh>
  10c99d:	48 8b 7d c0          	mov    -0x40(%rbp),%rdi
  10c9a1:	8b 75 f4             	mov    -0xc(%rbp),%esi
  10c9a4:	8b 55 f0             	mov    -0x10(%rbp),%edx
  10c9a7:	03 55 e4             	add    -0x1c(%rbp),%edx
  10c9aa:	8b 4d e4             	mov    -0x1c(%rbp),%ecx
  10c9ad:	44 8b 45 e8          	mov    -0x18(%rbp),%r8d
  10c9b1:	8b 45 e4             	mov    -0x1c(%rbp),%eax
  10c9b4:	d1 e0                	shl    $1,%eax
  10c9b6:	41 29 c0             	sub    %eax,%r8d
  10c9b9:	44 8b 4d 10          	mov    0x10(%rbp),%r9d
  10c9bd:	0f b6 45 e3          	movzbl -0x1d(%rbp),%eax
  10c9c1:	89 04 24             	mov    %eax,(%rsp)
  10c9c4:	e8 e7 00 00 00       	call   10cab0 <_ZN4acos8graphics8Renderer10blend_rectEjjjjjh>
  10c9c9:	48 8b 7d c0          	mov    -0x40(%rbp),%rdi
  10c9cd:	8b 75 f4             	mov    -0xc(%rbp),%esi
  10c9d0:	03 75 ec             	add    -0x14(%rbp),%esi
  10c9d3:	2b 75 e4             	sub    -0x1c(%rbp),%esi
  10c9d6:	8b 55 f0             	mov    -0x10(%rbp),%edx
  10c9d9:	03 55 e4             	add    -0x1c(%rbp),%edx
  10c9dc:	8b 4d e4             	mov    -0x1c(%rbp),%ecx
  10c9df:	44 8b 45 e8          	mov    -0x18(%rbp),%r8d
  10c9e3:	8b 45 e4             	mov    -0x1c(%rbp),%eax
  10c9e6:	d1 e0                	shl    $1,%eax
  10c9e8:	41 29 c0             	sub    %eax,%r8d
  10c9eb:	44 8b 4d 10          	mov    0x10(%rbp),%r9d
  10c9ef:	0f b6 45 e3          	movzbl -0x1d(%rbp),%eax
  10c9f3:	89 04 24             	mov    %eax,(%rsp)
  10c9f6:	e8 b5 00 00 00       	call   10cab0 <_ZN4acos8graphics8Renderer10blend_rectEjjjjjh>
  10c9fb:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  10c9ff:	48 89 45 c8          	mov    %rax,-0x38(%rbp)
  10ca03:	48 8d 45 10          	lea    0x10(%rbp),%rax
  10ca07:	48 89 45 d0          	mov    %rax,-0x30(%rbp)
  10ca0b:	48 8d 45 e3          	lea    -0x1d(%rbp),%rax
  10ca0f:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
  10ca13:	8b 75 f4             	mov    -0xc(%rbp),%esi
  10ca16:	03 75 e4             	add    -0x1c(%rbp),%esi
  10ca19:	8b 55 f0             	mov    -0x10(%rbp),%edx
  10ca1c:	03 55 e4             	add    -0x1c(%rbp),%edx
  10ca1f:	8b 4d e4             	mov    -0x1c(%rbp),%ecx
  10ca22:	48 8d 7d c8          	lea    -0x38(%rbp),%rdi
  10ca26:	41 b9 01 00 00 00    	mov    $0x1,%r9d
  10ca2c:	45 89 c8             	mov    %r9d,%r8d
  10ca2f:	e8 1c 01 00 00       	call   10cb50 <_ZZN4acos8graphics8Renderer17fill_rounded_rectEjjjjjjENK3$_0clEjjjbb>
  10ca34:	8b 75 f4             	mov    -0xc(%rbp),%esi
  10ca37:	03 75 ec             	add    -0x14(%rbp),%esi
  10ca3a:	2b 75 e4             	sub    -0x1c(%rbp),%esi
  10ca3d:	8b 55 f0             	mov    -0x10(%rbp),%edx
  10ca40:	03 55 e4             	add    -0x1c(%rbp),%edx
  10ca43:	8b 4d e4             	mov    -0x1c(%rbp),%ecx
  10ca46:	48 8d 7d c8          	lea    -0x38(%rbp),%rdi
  10ca4a:	41 b8 01 00 00 00    	mov    $0x1,%r8d
  10ca50:	45 31 c9             	xor    %r9d,%r9d
  10ca53:	e8 f8 00 00 00       	call   10cb50 <_ZZN4acos8graphics8Renderer17fill_rounded_rectEjjjjjjENK3$_0clEjjjbb>
  10ca58:	8b 75 f4             	mov    -0xc(%rbp),%esi
  10ca5b:	03 75 e4             	add    -0x1c(%rbp),%esi
  10ca5e:	8b 55 f0             	mov    -0x10(%rbp),%edx
  10ca61:	03 55 e8             	add    -0x18(%rbp),%edx
  10ca64:	2b 55 e4             	sub    -0x1c(%rbp),%edx
  10ca67:	8b 4d e4             	mov    -0x1c(%rbp),%ecx
  10ca6a:	48 8d 7d c8          	lea    -0x38(%rbp),%rdi
  10ca6e:	45 31 c0             	xor    %r8d,%r8d
  10ca71:	41 b9 01 00 00 00    	mov    $0x1,%r9d
  10ca77:	e8 d4 00 00 00       	call   10cb50 <_ZZN4acos8graphics8Renderer17fill_rounded_rectEjjjjjjENK3$_0clEjjjbb>
  10ca7c:	8b 75 f4             	mov    -0xc(%rbp),%esi
  10ca7f:	03 75 ec             	add    -0x14(%rbp),%esi
  10ca82:	2b 75 e4             	sub    -0x1c(%rbp),%esi
  10ca85:	8b 55 f0             	mov    -0x10(%rbp),%edx
  10ca88:	03 55 e8             	add    -0x18(%rbp),%edx
  10ca8b:	2b 55 e4             	sub    -0x1c(%rbp),%edx
  10ca8e:	8b 4d e4             	mov    -0x1c(%rbp),%ecx
  10ca91:	48 8d 7d c8          	lea    -0x38(%rbp),%rdi
  10ca95:	45 31 c9             	xor    %r9d,%r9d
  10ca98:	45 89 c8             	mov    %r9d,%r8d
  10ca9b:	e8 b0 00 00 00       	call   10cb50 <_ZZN4acos8graphics8Renderer17fill_rounded_rectEjjjjjjENK3$_0clEjjjbb>
  10caa0:	48 83 c4 50          	add    $0x50,%rsp
  10caa4:	5d                   	pop    %rbp
  10caa5:	c3                   	ret
  10caa6:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
  10caad:	00 00 00

000000000010cab0 <_ZN4acos8graphics8Renderer10blend_rectEjjjjjh>:
  10cab0:	55                   	push   %rbp
  10cab1:	48 89 e5             	mov    %rsp,%rbp
  10cab4:	48 83 ec 30          	sub    $0x30,%rsp
  10cab8:	8a 45 10             	mov    0x10(%rbp),%al
  10cabb:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10cabf:	89 75 f4             	mov    %esi,-0xc(%rbp)
  10cac2:	89 55 f0             	mov    %edx,-0x10(%rbp)
  10cac5:	89 4d ec             	mov    %ecx,-0x14(%rbp)
  10cac8:	44 89 45 e8          	mov    %r8d,-0x18(%rbp)
  10cacc:	44 89 4d e4          	mov    %r9d,-0x1c(%rbp)
  10cad0:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10cad4:	48 89 45 d0          	mov    %rax,-0x30(%rbp)
  10cad8:	8b 45 f0             	mov    -0x10(%rbp),%eax
  10cadb:	89 45 e0             	mov    %eax,-0x20(%rbp)
  10cade:	8b 45 e0             	mov    -0x20(%rbp),%eax
  10cae1:	8b 4d f0             	mov    -0x10(%rbp),%ecx
  10cae4:	03 4d e8             	add    -0x18(%rbp),%ecx
  10cae7:	39 c8                	cmp    %ecx,%eax
  10cae9:	0f 83 4f 00 00 00    	jae    10cb3e <_ZN4acos8graphics8Renderer10blend_rectEjjjjjh+0x8e>
  10caef:	8b 45 f4             	mov    -0xc(%rbp),%eax
  10caf2:	89 45 dc             	mov    %eax,-0x24(%rbp)
  10caf5:	8b 45 dc             	mov    -0x24(%rbp),%eax
  10caf8:	8b 4d f4             	mov    -0xc(%rbp),%ecx
  10cafb:	03 4d ec             	add    -0x14(%rbp),%ecx
  10cafe:	39 c8                	cmp    %ecx,%eax
  10cb00:	0f 83 25 00 00 00    	jae    10cb2b <_ZN4acos8graphics8Renderer10blend_rectEjjjjjh+0x7b>
  10cb06:	48 8b 7d d0          	mov    -0x30(%rbp),%rdi
  10cb0a:	8b 75 dc             	mov    -0x24(%rbp),%esi
  10cb0d:	8b 55 e0             	mov    -0x20(%rbp),%edx
  10cb10:	8b 4d e4             	mov    -0x1c(%rbp),%ecx
  10cb13:	44 0f b6 45 10       	movzbl 0x10(%rbp),%r8d
  10cb18:	e8 a3 ec ff ff       	call   10b7c0 <_ZN4acos8graphics8Renderer11blend_pixelEjjjh>
  10cb1d:	8b 45 dc             	mov    -0x24(%rbp),%eax
  10cb20:	83 c0 01             	add    $0x1,%eax
  10cb23:	89 45 dc             	mov    %eax,-0x24(%rbp)
  10cb26:	e9 ca ff ff ff       	jmp    10caf5 <_ZN4acos8graphics8Renderer10blend_rectEjjjjjh+0x45>
  10cb2b:	e9 00 00 00 00       	jmp    10cb30 <_ZN4acos8graphics8Renderer10blend_rectEjjjjjh+0x80>
  10cb30:	8b 45 e0             	mov    -0x20(%rbp),%eax
  10cb33:	83 c0 01             	add    $0x1,%eax
  10cb36:	89 45 e0             	mov    %eax,-0x20(%rbp)
  10cb39:	e9 a0 ff ff ff       	jmp    10cade <_ZN4acos8graphics8Renderer10blend_rectEjjjjjh+0x2e>
  10cb3e:	48 83 c4 30          	add    $0x30,%rsp
  10cb42:	5d                   	pop    %rbp
  10cb43:	c3                   	ret
  10cb44:	66 66 66 2e 0f 1f 84 	data16 data16 cs nopw 0x0(%rax,%rax,1)
  10cb4b:	00 00 00 00 00

000000000010cb50 <_ZZN4acos8graphics8Renderer17fill_rounded_rectEjjjjjjENK3$_0clEjjjbb>:
  10cb50:	55                   	push   %rbp
  10cb51:	48 89 e5             	mov    %rsp,%rbp
  10cb54:	48 83 ec 60          	sub    $0x60,%rsp
  10cb58:	44 89 45 b0          	mov    %r8d,-0x50(%rbp)
  10cb5c:	89 c8                	mov    %ecx,%eax
  10cb5e:	8b 4d b0             	mov    -0x50(%rbp),%ecx
  10cb61:	89 45 b4             	mov    %eax,-0x4c(%rbp)
  10cb64:	89 d0                	mov    %edx,%eax
  10cb66:	8b 55 b4             	mov    -0x4c(%rbp),%edx
  10cb69:	89 45 b8             	mov    %eax,-0x48(%rbp)
  10cb6c:	89 f0                	mov    %esi,%eax
  10cb6e:	8b 75 b8             	mov    -0x48(%rbp),%esi
  10cb71:	89 45 bc             	mov    %eax,-0x44(%rbp)
  10cb74:	49 89 f8             	mov    %rdi,%r8
  10cb77:	8b 7d bc             	mov    -0x44(%rbp),%edi
  10cb7a:	44 88 c8             	mov    %r9b,%al
  10cb7d:	4c 89 45 f8          	mov    %r8,-0x8(%rbp)
  10cb81:	89 7d f4             	mov    %edi,-0xc(%rbp)
  10cb84:	89 75 f0             	mov    %esi,-0x10(%rbp)
  10cb87:	89 55 ec             	mov    %edx,-0x14(%rbp)
  10cb8a:	80 e1 01             	and    $0x1,%cl
  10cb8d:	88 4d eb             	mov    %cl,-0x15(%rbp)
  10cb90:	24 01                	and    $0x1,%al
  10cb92:	88 45 ea             	mov    %al,-0x16(%rbp)
  10cb95:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10cb99:	48 89 45 c0          	mov    %rax,-0x40(%rbp)
  10cb9d:	48 8b 00             	mov    (%rax),%rax
  10cba0:	48 89 45 c8          	mov    %rax,-0x38(%rbp)
  10cba4:	31 c0                	xor    %eax,%eax
  10cba6:	2b 45 ec             	sub    -0x14(%rbp),%eax
  10cba9:	89 45 e4             	mov    %eax,-0x1c(%rbp)
  10cbac:	83 7d e4 00          	cmpl   $0x0,-0x1c(%rbp)
  10cbb0:	0f 8f 86 01 00 00    	jg     10cd3c <_ZZN4acos8graphics8Renderer17fill_rounded_rectEjjjjjjENK3$_0clEjjjbb+0x1ec>
  10cbb6:	31 c0                	xor    %eax,%eax
  10cbb8:	2b 45 ec             	sub    -0x14(%rbp),%eax
  10cbbb:	89 45 e0             	mov    %eax,-0x20(%rbp)
  10cbbe:	83 7d e0 00          	cmpl   $0x0,-0x20(%rbp)
  10cbc2:	0f 8f 61 01 00 00    	jg     10cd29 <_ZZN4acos8graphics8Renderer17fill_rounded_rectEjjjjjjENK3$_0clEjjjbb+0x1d9>
  10cbc8:	8b 45 e0             	mov    -0x20(%rbp),%eax
  10cbcb:	0f af 45 e0          	imul   -0x20(%rbp),%eax
  10cbcf:	8b 4d e4             	mov    -0x1c(%rbp),%ecx
  10cbd2:	0f af 4d e4          	imul   -0x1c(%rbp),%ecx
  10cbd6:	01 c8                	add    %ecx,%eax
  10cbd8:	f3 0f 2a c0          	cvtsi2ss %eax,%xmm0
  10cbdc:	e8 df f7 ff ff       	call   10c3c0 <_ZN4acos8graphics12_GLOBAL__N_14sqrtEf>
  10cbe1:	f3 0f 11 45 dc       	movss  %xmm0,-0x24(%rbp)
  10cbe6:	f6 45 ea 01          	testb  $0x1,-0x16(%rbp)
  10cbea:	0f 84 0e 00 00 00    	je     10cbfe <_ZZN4acos8graphics8Renderer17fill_rounded_rectEjjjjjjENK3$_0clEjjjbb+0xae>
  10cbf0:	8b 45 f4             	mov    -0xc(%rbp),%eax
  10cbf3:	03 45 e0             	add    -0x20(%rbp),%eax
  10cbf6:	89 45 ac             	mov    %eax,-0x54(%rbp)
  10cbf9:	e9 09 00 00 00       	jmp    10cc07 <_ZZN4acos8graphics8Renderer17fill_rounded_rectEjjjjjjENK3$_0clEjjjbb+0xb7>
  10cbfe:	8b 45 f4             	mov    -0xc(%rbp),%eax
  10cc01:	2b 45 e0             	sub    -0x20(%rbp),%eax
  10cc04:	89 45 ac             	mov    %eax,-0x54(%rbp)
  10cc07:	8b 45 ac             	mov    -0x54(%rbp),%eax
  10cc0a:	89 45 d8             	mov    %eax,-0x28(%rbp)
  10cc0d:	f6 45 eb 01          	testb  $0x1,-0x15(%rbp)
  10cc11:	0f 84 0e 00 00 00    	je     10cc25 <_ZZN4acos8graphics8Renderer17fill_rounded_rectEjjjjjjENK3$_0clEjjjbb+0xd5>
  10cc17:	8b 45 f0             	mov    -0x10(%rbp),%eax
  10cc1a:	03 45 e4             	add    -0x1c(%rbp),%eax
  10cc1d:	89 45 a8             	mov    %eax,-0x58(%rbp)
  10cc20:	e9 09 00 00 00       	jmp    10cc2e <_ZZN4acos8graphics8Renderer17fill_rounded_rectEjjjjjjENK3$_0clEjjjbb+0xde>
  10cc25:	8b 45 f0             	mov    -0x10(%rbp),%eax
  10cc28:	2b 45 e4             	sub    -0x1c(%rbp),%eax
  10cc2b:	89 45 a8             	mov    %eax,-0x58(%rbp)
  10cc2e:	8b 45 a8             	mov    -0x58(%rbp),%eax
  10cc31:	89 45 d4             	mov    %eax,-0x2c(%rbp)
  10cc34:	f3 0f 10 4d dc       	movss  -0x24(%rbp),%xmm1
  10cc39:	8b 45 ec             	mov    -0x14(%rbp),%eax
  10cc3c:	f3 48 0f 2a c0       	cvtsi2ss %rax,%xmm0
  10cc41:	f3 0f 10 15 af 2f 00 	movss  0x2faf(%rip),%xmm2        # 10fbf8 <_ZTVN4acos8graphics13DisplayDeviceE+0x48>
  10cc48:	00
  10cc49:	f3 0f 5c c2          	subss  %xmm2,%xmm0
  10cc4d:	0f 2e c1             	ucomiss %xmm1,%xmm0
  10cc50:	0f 82 26 00 00 00    	jb     10cc7c <_ZZN4acos8graphics8Renderer17fill_rounded_rectEjjjjjjENK3$_0clEjjjbb+0x12c>
  10cc56:	48 8b 7d c8          	mov    -0x38(%rbp),%rdi
  10cc5a:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  10cc5e:	8b 75 d8             	mov    -0x28(%rbp),%esi
  10cc61:	8b 55 d4             	mov    -0x2c(%rbp),%edx
  10cc64:	48 8b 48 08          	mov    0x8(%rax),%rcx
  10cc68:	8b 09                	mov    (%rcx),%ecx
  10cc6a:	48 8b 40 10          	mov    0x10(%rax),%rax
  10cc6e:	44 0f b6 00          	movzbl (%rax),%r8d
  10cc72:	e8 49 eb ff ff       	call   10b7c0 <_ZN4acos8graphics8Renderer11blend_pixelEjjjh>
  10cc77:	e9 9a 00 00 00       	jmp    10cd16 <_ZZN4acos8graphics8Renderer17fill_rounded_rectEjjjjjjENK3$_0clEjjjbb+0x1c6>
  10cc7c:	f3 0f 10 4d dc       	movss  -0x24(%rbp),%xmm1
  10cc81:	8b 45 ec             	mov    -0x14(%rbp),%eax
  10cc84:	f3 48 0f 2a c0       	cvtsi2ss %rax,%xmm0
  10cc89:	f3 0f 10 15 67 2f 00 	movss  0x2f67(%rip),%xmm2        # 10fbf8 <_ZTVN4acos8graphics13DisplayDeviceE+0x48>
  10cc90:	00
  10cc91:	f3 0f 58 c2          	addss  %xmm2,%xmm0
  10cc95:	0f 2e c1             	ucomiss %xmm1,%xmm0
  10cc98:	0f 82 73 00 00 00    	jb     10cd11 <_ZZN4acos8graphics8Renderer17fill_rounded_rectEjjjjjjENK3$_0clEjjjbb+0x1c1>
  10cc9e:	48 8b 7d c8          	mov    -0x38(%rbp),%rdi
  10cca2:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
  10cca6:	f3 0f 10 4d dc       	movss  -0x24(%rbp),%xmm1
  10ccab:	8b 4d ec             	mov    -0x14(%rbp),%ecx
  10ccae:	f3 48 0f 2a c1       	cvtsi2ss %rcx,%xmm0
  10ccb3:	f3 0f 10 15 49 2f 00 	movss  0x2f49(%rip),%xmm2        # 10fc04 <_ZTVN4acos8graphics13DisplayDeviceE+0x54>
  10ccba:	00
  10ccbb:	f3 0f 58 c2          	addss  %xmm2,%xmm0
  10ccbf:	f3 0f 5c c8          	subss  %xmm0,%xmm1
  10ccc3:	f3 0f 10 05 25 2f 00 	movss  0x2f25(%rip),%xmm0        # 10fbf0 <_ZTVN4acos8graphics13DisplayDeviceE+0x40>
  10ccca:	00
  10cccb:	f3 0f 5c c1          	subss  %xmm1,%xmm0
  10cccf:	48 8b 48 10          	mov    0x10(%rax),%rcx
  10ccd3:	0f b6 09             	movzbl (%rcx),%ecx
  10ccd6:	f3 0f 2a d1          	cvtsi2ss %ecx,%xmm2
  10ccda:	f3 0f 10 0d 12 2f 00 	movss  0x2f12(%rip),%xmm1        # 10fbf4 <_ZTVN4acos8graphics13DisplayDeviceE+0x44>
  10cce1:	00
  10cce2:	f3 0f 5e d1          	divss  %xmm1,%xmm2
  10cce6:	f3 0f 59 c2          	mulss  %xmm2,%xmm0
  10ccea:	f3 0f 11 45 d0       	movss  %xmm0,-0x30(%rbp)
  10ccef:	8b 75 d8             	mov    -0x28(%rbp),%esi
  10ccf2:	8b 55 d4             	mov    -0x2c(%rbp),%edx
  10ccf5:	48 8b 40 08          	mov    0x8(%rax),%rax
  10ccf9:	8b 08                	mov    (%rax),%ecx
  10ccfb:	f3 0f 10 45 d0       	movss  -0x30(%rbp),%xmm0
  10cd00:	f3 0f 59 c1          	mulss  %xmm1,%xmm0
  10cd04:	f3 0f 2c c0          	cvttss2si %xmm0,%eax
  10cd08:	44 0f b6 c0          	movzbl %al,%r8d
  10cd0c:	e8 af ea ff ff       	call   10b7c0 <_ZN4acos8graphics8Renderer11blend_pixelEjjjh>
  10cd11:	e9 00 00 00 00       	jmp    10cd16 <_ZZN4acos8graphics8Renderer17fill_rounded_rectEjjjjjjENK3$_0clEjjjbb+0x1c6>
  10cd16:	e9 00 00 00 00       	jmp    10cd1b <_ZZN4acos8graphics8Renderer17fill_rounded_rectEjjjjjjENK3$_0clEjjjbb+0x1cb>
  10cd1b:	8b 45 e0             	mov    -0x20(%rbp),%eax
  10cd1e:	83 c0 01             	add    $0x1,%eax
  10cd21:	89 45 e0             	mov    %eax,-0x20(%rbp)
  10cd24:	e9 95 fe ff ff       	jmp    10cbbe <_ZZN4acos8graphics8Renderer17fill_rounded_rectEjjjjjjENK3$_0clEjjjbb+0x6e>
  10cd29:	e9 00 00 00 00       	jmp    10cd2e <_ZZN4acos8graphics8Renderer17fill_rounded_rectEjjjjjjENK3$_0clEjjjbb+0x1de>
  10cd2e:	8b 45 e4             	mov    -0x1c(%rbp),%eax
  10cd31:	83 c0 01             	add    $0x1,%eax
  10cd34:	89 45 e4             	mov    %eax,-0x1c(%rbp)
  10cd37:	e9 70 fe ff ff       	jmp    10cbac <_ZZN4acos8graphics8Renderer17fill_rounded_rectEjjjjjjENK3$_0clEjjjbb+0x5c>
  10cd3c:	48 83 c4 60          	add    $0x60,%rsp
  10cd40:	5d                   	pop    %rbp
  10cd41:	c3                   	ret
  10cd42:	66 66 66 66 66 2e 0f 	data16 data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
  10cd49:	1f 84 00 00 00 00 00

000000000010cd50 <_ZN4acos8graphics8Renderer18draw_gradient_rectEjjjjRKNS_3abi8GradientE>:
  10cd50:	55                   	push   %rbp
  10cd51:	48 89 e5             	mov    %rsp,%rbp
  10cd54:	48 83 ec 60          	sub    $0x60,%rsp
  10cd58:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10cd5c:	89 75 f4             	mov    %esi,-0xc(%rbp)
  10cd5f:	89 55 f0             	mov    %edx,-0x10(%rbp)
  10cd62:	89 4d ec             	mov    %ecx,-0x14(%rbp)
  10cd65:	44 89 45 e8          	mov    %r8d,-0x18(%rbp)
  10cd69:	4c 89 4d e0          	mov    %r9,-0x20(%rbp)
  10cd6d:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10cd71:	48 89 45 b8          	mov    %rax,-0x48(%rbp)
  10cd75:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  10cd79:	8b 00                	mov    (%rax),%eax
  10cd7b:	89 45 dc             	mov    %eax,-0x24(%rbp)
  10cd7e:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  10cd82:	8b 40 04             	mov    0x4(%rax),%eax
  10cd85:	89 45 d8             	mov    %eax,-0x28(%rbp)
  10cd88:	c7 45 d4 00 00 00 00 	movl   $0x0,-0x2c(%rbp)
  10cd8f:	8b 45 d4             	mov    -0x2c(%rbp),%eax
  10cd92:	89 45 b4             	mov    %eax,-0x4c(%rbp)
  10cd95:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  10cd99:	f6 40 08 01          	testb  $0x1,0x8(%rax)
  10cd9d:	0f 84 0b 00 00 00    	je     10cdae <_ZN4acos8graphics8Renderer18draw_gradient_rectEjjjjRKNS_3abi8GradientE+0x5e>
  10cda3:	8b 45 ec             	mov    -0x14(%rbp),%eax
  10cda6:	89 45 b0             	mov    %eax,-0x50(%rbp)
  10cda9:	e9 06 00 00 00       	jmp    10cdb4 <_ZN4acos8graphics8Renderer18draw_gradient_rectEjjjjRKNS_3abi8GradientE+0x64>
  10cdae:	8b 45 e8             	mov    -0x18(%rbp),%eax
  10cdb1:	89 45 b0             	mov    %eax,-0x50(%rbp)
  10cdb4:	8b 45 b4             	mov    -0x4c(%rbp),%eax
  10cdb7:	8b 4d b0             	mov    -0x50(%rbp),%ecx
  10cdba:	39 c8                	cmp    %ecx,%eax
  10cdbc:	0f 83 7a 01 00 00    	jae    10cf3c <_ZN4acos8graphics8Renderer18draw_gradient_rectEjjjjRKNS_3abi8GradientE+0x1ec>
  10cdc2:	8b 45 d4             	mov    -0x2c(%rbp),%eax
  10cdc5:	f3 48 0f 2a c0       	cvtsi2ss %rax,%xmm0
  10cdca:	f3 0f 11 45 ac       	movss  %xmm0,-0x54(%rbp)
  10cdcf:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  10cdd3:	f6 40 08 01          	testb  $0x1,0x8(%rax)
  10cdd7:	0f 84 0b 00 00 00    	je     10cde8 <_ZN4acos8graphics8Renderer18draw_gradient_rectEjjjjRKNS_3abi8GradientE+0x98>
  10cddd:	8b 45 ec             	mov    -0x14(%rbp),%eax
  10cde0:	89 45 a8             	mov    %eax,-0x58(%rbp)
  10cde3:	e9 06 00 00 00       	jmp    10cdee <_ZN4acos8graphics8Renderer18draw_gradient_rectEjjjjRKNS_3abi8GradientE+0x9e>
  10cde8:	8b 45 e8             	mov    -0x18(%rbp),%eax
  10cdeb:	89 45 a8             	mov    %eax,-0x58(%rbp)
  10cdee:	f3 0f 10 45 ac       	movss  -0x54(%rbp),%xmm0
  10cdf3:	8b 45 a8             	mov    -0x58(%rbp),%eax
  10cdf6:	89 c0                	mov    %eax,%eax
  10cdf8:	f3 48 0f 2a c8       	cvtsi2ss %rax,%xmm1
  10cdfd:	f3 0f 5e c1          	divss  %xmm1,%xmm0
  10ce01:	f3 0f 11 45 d0       	movss  %xmm0,-0x30(%rbp)
  10ce06:	0f b6 4d dc          	movzbl -0x24(%rbp),%ecx
  10ce0a:	f3 0f 2a c9          	cvtsi2ss %ecx,%xmm1
  10ce0e:	0f b6 45 d8          	movzbl -0x28(%rbp),%eax
  10ce12:	29 c8                	sub    %ecx,%eax
  10ce14:	f3 0f 2a c0          	cvtsi2ss %eax,%xmm0
  10ce18:	f3 0f 10 55 d0       	movss  -0x30(%rbp),%xmm2
  10ce1d:	f3 0f 59 c2          	mulss  %xmm2,%xmm0
  10ce21:	f3 0f 58 c1          	addss  %xmm1,%xmm0
  10ce25:	f3 0f 2c c0          	cvttss2si %xmm0,%eax
  10ce29:	88 45 cf             	mov    %al,-0x31(%rbp)
  10ce2c:	0f b6 4d dd          	movzbl -0x23(%rbp),%ecx
  10ce30:	f3 0f 2a c9          	cvtsi2ss %ecx,%xmm1
  10ce34:	0f b6 45 d9          	movzbl -0x27(%rbp),%eax
  10ce38:	29 c8                	sub    %ecx,%eax
  10ce3a:	f3 0f 2a c0          	cvtsi2ss %eax,%xmm0
  10ce3e:	f3 0f 10 55 d0       	movss  -0x30(%rbp),%xmm2
  10ce43:	f3 0f 59 c2          	mulss  %xmm2,%xmm0
  10ce47:	f3 0f 58 c1          	addss  %xmm1,%xmm0
  10ce4b:	f3 0f 2c c0          	cvttss2si %xmm0,%eax
  10ce4f:	88 45 ce             	mov    %al,-0x32(%rbp)
  10ce52:	0f b6 4d de          	movzbl -0x22(%rbp),%ecx
  10ce56:	f3 0f 2a c9          	cvtsi2ss %ecx,%xmm1
  10ce5a:	0f b6 45 da          	movzbl -0x26(%rbp),%eax
  10ce5e:	29 c8                	sub    %ecx,%eax
  10ce60:	f3 0f 2a c0          	cvtsi2ss %eax,%xmm0
  10ce64:	f3 0f 10 55 d0       	movss  -0x30(%rbp),%xmm2
  10ce69:	f3 0f 59 c2          	mulss  %xmm2,%xmm0
  10ce6d:	f3 0f 58 c1          	addss  %xmm1,%xmm0
  10ce71:	f3 0f 2c c0          	cvttss2si %xmm0,%eax
  10ce75:	88 45 cd             	mov    %al,-0x33(%rbp)
  10ce78:	0f b6 4d df          	movzbl -0x21(%rbp),%ecx
  10ce7c:	f3 0f 2a c9          	cvtsi2ss %ecx,%xmm1
  10ce80:	0f b6 45 db          	movzbl -0x25(%rbp),%eax
  10ce84:	29 c8                	sub    %ecx,%eax
  10ce86:	f3 0f 2a c0          	cvtsi2ss %eax,%xmm0
  10ce8a:	f3 0f 10 55 d0       	movss  -0x30(%rbp),%xmm2
  10ce8f:	f3 0f 59 c2          	mulss  %xmm2,%xmm0
  10ce93:	f3 0f 58 c1          	addss  %xmm1,%xmm0
  10ce97:	f3 0f 2c c0          	cvttss2si %xmm0,%eax
  10ce9b:	88 45 cc             	mov    %al,-0x34(%rbp)
  10ce9e:	8a 55 cf             	mov    -0x31(%rbp),%dl
  10cea1:	8a 4d ce             	mov    -0x32(%rbp),%cl
  10cea4:	8a 45 cd             	mov    -0x33(%rbp),%al
  10cea7:	48 8d 7d c4          	lea    -0x3c(%rbp),%rdi
  10ceab:	0f b6 f2             	movzbl %dl,%esi
  10ceae:	0f b6 d1             	movzbl %cl,%edx
  10ceb1:	0f b6 c8             	movzbl %al,%ecx
  10ceb4:	44 0f b6 45 cc       	movzbl -0x34(%rbp),%r8d
  10ceb9:	e8 02 21 00 00       	call   10efc0 <_ZN4acos3abi5ColorC2Ehhhh>
  10cebe:	48 8d 7d c4          	lea    -0x3c(%rbp),%rdi
  10cec2:	e8 39 21 00 00       	call   10f000 <_ZNK4acos3abi5Color7to_argbEv>
  10cec7:	89 45 c8             	mov    %eax,-0x38(%rbp)
  10ceca:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  10cece:	f6 40 08 01          	testb  $0x1,0x8(%rax)
  10ced2:	0f 84 2b 00 00 00    	je     10cf03 <_ZN4acos8graphics8Renderer18draw_gradient_rectEjjjjRKNS_3abi8GradientE+0x1b3>
  10ced8:	48 8b 7d b8          	mov    -0x48(%rbp),%rdi
  10cedc:	8b 75 f4             	mov    -0xc(%rbp),%esi
  10cedf:	03 75 d4             	add    -0x2c(%rbp),%esi
  10cee2:	8b 55 f0             	mov    -0x10(%rbp),%edx
  10cee5:	44 8b 45 e8          	mov    -0x18(%rbp),%r8d
  10cee9:	44 8b 4d c8          	mov    -0x38(%rbp),%r9d
  10ceed:	b9 01 00 00 00       	mov    $0x1,%ecx
  10cef2:	0f b6 45 cc          	movzbl -0x34(%rbp),%eax
  10cef6:	89 04 24             	mov    %eax,(%rsp)
  10cef9:	e8 b2 fb ff ff       	call   10cab0 <_ZN4acos8graphics8Renderer10blend_rectEjjjjjh>
  10cefe:	e9 26 00 00 00       	jmp    10cf29 <_ZN4acos8graphics8Renderer18draw_gradient_rectEjjjjRKNS_3abi8GradientE+0x1d9>
  10cf03:	48 8b 7d b8          	mov    -0x48(%rbp),%rdi
  10cf07:	8b 75 f4             	mov    -0xc(%rbp),%esi
  10cf0a:	8b 55 f0             	mov    -0x10(%rbp),%edx
  10cf0d:	03 55 d4             	add    -0x2c(%rbp),%edx
  10cf10:	8b 4d ec             	mov    -0x14(%rbp),%ecx
  10cf13:	44 8b 4d c8          	mov    -0x38(%rbp),%r9d
  10cf17:	41 b8 01 00 00 00    	mov    $0x1,%r8d
  10cf1d:	0f b6 45 cc          	movzbl -0x34(%rbp),%eax
  10cf21:	89 04 24             	mov    %eax,(%rsp)
  10cf24:	e8 87 fb ff ff       	call   10cab0 <_ZN4acos8graphics8Renderer10blend_rectEjjjjjh>
  10cf29:	e9 00 00 00 00       	jmp    10cf2e <_ZN4acos8graphics8Renderer18draw_gradient_rectEjjjjRKNS_3abi8GradientE+0x1de>
  10cf2e:	8b 45 d4             	mov    -0x2c(%rbp),%eax
  10cf31:	83 c0 01             	add    $0x1,%eax
  10cf34:	89 45 d4             	mov    %eax,-0x2c(%rbp)
  10cf37:	e9 53 fe ff ff       	jmp    10cd8f <_ZN4acos8graphics8Renderer18draw_gradient_rectEjjjjRKNS_3abi8GradientE+0x3f>
  10cf3c:	48 83 c4 60          	add    $0x60,%rsp
  10cf40:	5d                   	pop    %rbp
  10cf41:	c3                   	ret
  10cf42:	66 66 66 66 66 2e 0f 	data16 data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
  10cf49:	1f 84 00 00 00 00 00

000000000010cf50 <_ZN4acos8graphics8Renderer11draw_borderEjjjjjj>:
  10cf50:	55                   	push   %rbp
  10cf51:	48 89 e5             	mov    %rsp,%rbp
  10cf54:	48 83 ec 30          	sub    $0x30,%rsp
  10cf58:	8b 45 10             	mov    0x10(%rbp),%eax
  10cf5b:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10cf5f:	89 75 f4             	mov    %esi,-0xc(%rbp)
  10cf62:	89 55 f0             	mov    %edx,-0x10(%rbp)
  10cf65:	89 4d ec             	mov    %ecx,-0x14(%rbp)
  10cf68:	44 89 45 e8          	mov    %r8d,-0x18(%rbp)
  10cf6c:	44 89 4d e4          	mov    %r9d,-0x1c(%rbp)
  10cf70:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10cf74:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
  10cf78:	c7 45 e0 00 00 00 00 	movl   $0x0,-0x20(%rbp)
  10cf7f:	8b 45 e0             	mov    -0x20(%rbp),%eax
  10cf82:	3b 45 10             	cmp    0x10(%rbp),%eax
  10cf85:	0f 83 3d 00 00 00    	jae    10cfc8 <_ZN4acos8graphics8Renderer11draw_borderEjjjjjj+0x78>
  10cf8b:	48 8b 7d d8          	mov    -0x28(%rbp),%rdi
  10cf8f:	8b 75 f4             	mov    -0xc(%rbp),%esi
  10cf92:	03 75 e0             	add    -0x20(%rbp),%esi
  10cf95:	8b 55 f0             	mov    -0x10(%rbp),%edx
  10cf98:	03 55 e0             	add    -0x20(%rbp),%edx
  10cf9b:	8b 4d ec             	mov    -0x14(%rbp),%ecx
  10cf9e:	8b 45 e0             	mov    -0x20(%rbp),%eax
  10cfa1:	d1 e0                	shl    $1,%eax
  10cfa3:	29 c1                	sub    %eax,%ecx
  10cfa5:	44 8b 45 e8          	mov    -0x18(%rbp),%r8d
  10cfa9:	8b 45 e0             	mov    -0x20(%rbp),%eax
  10cfac:	d1 e0                	shl    $1,%eax
  10cfae:	41 29 c0             	sub    %eax,%r8d
  10cfb1:	44 8b 4d e4          	mov    -0x1c(%rbp),%r9d
  10cfb5:	e8 36 ec ff ff       	call   10bbf0 <_ZN4acos8graphics8Renderer9draw_rectEjjjjj>
  10cfba:	8b 45 e0             	mov    -0x20(%rbp),%eax
  10cfbd:	83 c0 01             	add    $0x1,%eax
  10cfc0:	89 45 e0             	mov    %eax,-0x20(%rbp)
  10cfc3:	e9 b7 ff ff ff       	jmp    10cf7f <_ZN4acos8graphics8Renderer11draw_borderEjjjjjj+0x2f>
  10cfc8:	48 83 c4 30          	add    $0x30,%rsp
  10cfcc:	5d                   	pop    %rbp
  10cfcd:	c3                   	ret
  10cfce:	66 90                	xchg   %ax,%ax

000000000010cfd0 <_ZN4acos8graphics8Renderer11draw_shadowEjjjjjh>:
  10cfd0:	55                   	push   %rbp
  10cfd1:	48 89 e5             	mov    %rsp,%rbp
  10cfd4:	48 83 ec 40          	sub    $0x40,%rsp
  10cfd8:	8a 45 10             	mov    0x10(%rbp),%al
  10cfdb:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10cfdf:	89 75 f4             	mov    %esi,-0xc(%rbp)
  10cfe2:	89 55 f0             	mov    %edx,-0x10(%rbp)
  10cfe5:	89 4d ec             	mov    %ecx,-0x14(%rbp)
  10cfe8:	44 89 45 e8          	mov    %r8d,-0x18(%rbp)
  10cfec:	44 89 4d e4          	mov    %r9d,-0x1c(%rbp)
  10cff0:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  10cff4:	48 89 7d d8          	mov    %rdi,-0x28(%rbp)
  10cff8:	8b 75 f4             	mov    -0xc(%rbp),%esi
  10cffb:	03 75 e4             	add    -0x1c(%rbp),%esi
  10cffe:	8b 55 f0             	mov    -0x10(%rbp),%edx
  10d001:	03 55 e4             	add    -0x1c(%rbp),%edx
  10d004:	8b 4d ec             	mov    -0x14(%rbp),%ecx
  10d007:	44 8b 45 e8          	mov    -0x18(%rbp),%r8d
  10d00b:	41 b9 00 00 00 ff    	mov    $0xff000000,%r9d
  10d011:	0f b6 45 10          	movzbl 0x10(%rbp),%eax
  10d015:	89 04 24             	mov    %eax,(%rsp)
  10d018:	e8 93 fa ff ff       	call   10cab0 <_ZN4acos8graphics8Renderer10blend_rectEjjjjjh>
  10d01d:	83 7d e4 02          	cmpl   $0x2,-0x1c(%rbp)
  10d021:	0f 86 42 00 00 00    	jbe    10d069 <_ZN4acos8graphics8Renderer11draw_shadowEjjjjjh+0x99>
  10d027:	48 8b 7d d8          	mov    -0x28(%rbp),%rdi
  10d02b:	8b 75 f4             	mov    -0xc(%rbp),%esi
  10d02e:	03 75 e4             	add    -0x1c(%rbp),%esi
  10d031:	83 c6 02             	add    $0x2,%esi
  10d034:	8b 45 f0             	mov    -0x10(%rbp),%eax
  10d037:	03 45 e4             	add    -0x1c(%rbp),%eax
  10d03a:	83 c0 02             	add    $0x2,%eax
  10d03d:	89 45 d4             	mov    %eax,-0x2c(%rbp)
  10d040:	8b 4d ec             	mov    -0x14(%rbp),%ecx
  10d043:	44 8b 45 e8          	mov    -0x18(%rbp),%r8d
  10d047:	0f b6 45 10          	movzbl 0x10(%rbp),%eax
  10d04b:	41 b9 02 00 00 00    	mov    $0x2,%r9d
  10d051:	99                   	cltd
  10d052:	41 f7 f9             	idiv   %r9d
  10d055:	8b 55 d4             	mov    -0x2c(%rbp),%edx
  10d058:	41 b9 00 00 00 ff    	mov    $0xff000000,%r9d
  10d05e:	0f b6 c0             	movzbl %al,%eax
  10d061:	89 04 24             	mov    %eax,(%rsp)
  10d064:	e8 47 fa ff ff       	call   10cab0 <_ZN4acos8graphics8Renderer10blend_rectEjjjjjh>
  10d069:	48 83 c4 40          	add    $0x40,%rsp
  10d06d:	5d                   	pop    %rbp
  10d06e:	c3                   	ret
  10d06f:	90                   	nop

000000000010d070 <_ZN4acos8graphics8Renderer13set_clip_rectERKNS_3abi8ClipRectE>:
  10d070:	55                   	push   %rbp
  10d071:	48 89 e5             	mov    %rsp,%rbp
  10d074:	48 83 ec 10          	sub    $0x10,%rsp
  10d078:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10d07c:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  10d080:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10d084:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
  10d088:	48 8b 11             	mov    (%rcx),%rdx
  10d08b:	48 89 50 08          	mov    %rdx,0x8(%rax)
  10d08f:	48 8b 49 08          	mov    0x8(%rcx),%rcx
  10d093:	48 89 48 10          	mov    %rcx,0x10(%rax)
  10d097:	c6 40 18 01          	movb   $0x1,0x18(%rax)
  10d09b:	48 83 c4 10          	add    $0x10,%rsp
  10d09f:	5d                   	pop    %rbp
  10d0a0:	c3                   	ret
  10d0a1:	66 66 66 66 66 66 2e 	data16 data16 data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
  10d0a8:	0f 1f 84 00 00 00 00
  10d0af:	00

000000000010d0b0 <_ZN4acos8graphics8Renderer15clear_clip_rectEv>:
  10d0b0:	55                   	push   %rbp
  10d0b1:	48 89 e5             	mov    %rsp,%rbp
  10d0b4:	50                   	push   %rax
  10d0b5:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10d0b9:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10d0bd:	c6 40 18 00          	movb   $0x0,0x18(%rax)
  10d0c1:	48 83 c4 08          	add    $0x8,%rsp
  10d0c5:	5d                   	pop    %rbp
  10d0c6:	c3                   	ret
  10d0c7:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
  10d0ce:	00 00

000000000010d0d0 <_ZN4acos8graphics7SurfaceC1Ejj>:
  10d0d0:	55                   	push   %rbp
  10d0d1:	48 89 e5             	mov    %rsp,%rbp
  10d0d4:	48 83 ec 20          	sub    $0x20,%rsp
  10d0d8:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10d0dc:	89 75 f4             	mov    %esi,-0xc(%rbp)
  10d0df:	89 55 f0             	mov    %edx,-0x10(%rbp)
  10d0e2:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10d0e6:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
  10d0ea:	8b 4d f4             	mov    -0xc(%rbp),%ecx
  10d0ed:	89 08                	mov    %ecx,(%rax)
  10d0ef:	8b 4d f0             	mov    -0x10(%rbp),%ecx
  10d0f2:	89 48 04             	mov    %ecx,0x4(%rax)
  10d0f5:	8b 45 f4             	mov    -0xc(%rbp),%eax
  10d0f8:	0f af 45 f0          	imul   -0x10(%rbp),%eax
  10d0fc:	c1 e0 02             	shl    $0x2,%eax
  10d0ff:	89 c0                	mov    %eax,%eax
  10d101:	89 c7                	mov    %eax,%edi
  10d103:	e8 48 b6 ff ff       	call   108750 <_ZN4acos6memory7kmallocEm>
  10d108:	48 89 c1             	mov    %rax,%rcx
  10d10b:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  10d10f:	48 89 48 08          	mov    %rcx,0x8(%rax)
  10d113:	48 83 c4 20          	add    $0x20,%rsp
  10d117:	5d                   	pop    %rbp
  10d118:	c3                   	ret
  10d119:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

000000000010d120 <_ZN4acos8graphics7SurfaceD1Ev>:
  10d120:	55                   	push   %rbp
  10d121:	48 89 e5             	mov    %rsp,%rbp
  10d124:	50                   	push   %rax
  10d125:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10d129:	48 83 c4 08          	add    $0x8,%rsp
  10d12d:	5d                   	pop    %rbp
  10d12e:	c3                   	ret
  10d12f:	90                   	nop

000000000010d130 <_ZN4acos8graphics4FontC1EPKhm>:
  10d130:	55                   	push   %rbp
  10d131:	48 89 e5             	mov    %rsp,%rbp
  10d134:	48 83 ec 28          	sub    $0x28,%rsp
  10d138:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10d13c:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  10d140:	48 89 55 e8          	mov    %rdx,-0x18(%rbp)
  10d144:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10d148:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
  10d14c:	c6 00 00             	movb   $0x0,(%rax)
  10d14f:	c7 40 04 00 00 00 00 	movl   $0x0,0x4(%rax)
  10d156:	c7 40 08 00 00 00 00 	movl   $0x0,0x8(%rax)
  10d15d:	c7 40 0c 00 00 00 00 	movl   $0x0,0xc(%rax)
  10d164:	c7 40 10 00 00 00 00 	movl   $0x0,0x10(%rax)
  10d16b:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
  10d16f:	48 89 48 18          	mov    %rcx,0x18(%rax)
  10d173:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  10d177:	48 89 48 20          	mov    %rcx,0x20(%rax)
  10d17b:	c6 40 28 00          	movb   $0x0,0x28(%rax)
  10d17f:	48 83 7d f0 00       	cmpq   $0x0,-0x10(%rbp)
  10d184:	0f 84 0b 00 00 00    	je     10d195 <_ZN4acos8graphics4FontC1EPKhm+0x65>
  10d18a:	48 83 7d e8 04       	cmpq   $0x4,-0x18(%rbp)
  10d18f:	0f 83 05 00 00 00    	jae    10d19a <_ZN4acos8graphics4FontC1EPKhm+0x6a>
  10d195:	e9 d7 00 00 00       	jmp    10d271 <_ZN4acos8graphics4FontC1EPKhm+0x141>
  10d19a:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10d19e:	0f b6 00             	movzbl (%rax),%eax
  10d1a1:	83 f8 36             	cmp    $0x36,%eax
  10d1a4:	0f 85 45 00 00 00    	jne    10d1ef <_ZN4acos8graphics4FontC1EPKhm+0xbf>
  10d1aa:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10d1ae:	0f b6 40 01          	movzbl 0x1(%rax),%eax
  10d1b2:	83 f8 04             	cmp    $0x4,%eax
  10d1b5:	0f 85 34 00 00 00    	jne    10d1ef <_ZN4acos8graphics4FontC1EPKhm+0xbf>
  10d1bb:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  10d1bf:	c6 40 28 00          	movb   $0x0,0x28(%rax)
  10d1c3:	c7 40 04 08 00 00 00 	movl   $0x8,0x4(%rax)
  10d1ca:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
  10d1ce:	0f b6 49 03          	movzbl 0x3(%rcx),%ecx
  10d1d2:	89 48 08             	mov    %ecx,0x8(%rax)
  10d1d5:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
  10d1d9:	0f b6 49 03          	movzbl 0x3(%rcx),%ecx
  10d1dd:	89 48 0c             	mov    %ecx,0xc(%rax)
  10d1e0:	c7 40 10 04 00 00 00 	movl   $0x4,0x10(%rax)
  10d1e7:	c6 00 01             	movb   $0x1,(%rax)
  10d1ea:	e9 82 00 00 00       	jmp    10d271 <_ZN4acos8graphics4FontC1EPKhm+0x141>
  10d1ef:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10d1f3:	0f b6 00             	movzbl (%rax),%eax
  10d1f6:	83 f8 72             	cmp    $0x72,%eax
  10d1f9:	0f 85 72 00 00 00    	jne    10d271 <_ZN4acos8graphics4FontC1EPKhm+0x141>
  10d1ff:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10d203:	0f b6 40 01          	movzbl 0x1(%rax),%eax
  10d207:	3d b5 00 00 00       	cmp    $0xb5,%eax
  10d20c:	0f 85 5f 00 00 00    	jne    10d271 <_ZN4acos8graphics4FontC1EPKhm+0x141>
  10d212:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10d216:	0f b6 40 02          	movzbl 0x2(%rax),%eax
  10d21a:	83 f8 4a             	cmp    $0x4a,%eax
  10d21d:	0f 85 4e 00 00 00    	jne    10d271 <_ZN4acos8graphics4FontC1EPKhm+0x141>
  10d223:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10d227:	0f b6 40 03          	movzbl 0x3(%rax),%eax
  10d22b:	3d 86 00 00 00       	cmp    $0x86,%eax
  10d230:	0f 85 3b 00 00 00    	jne    10d271 <_ZN4acos8graphics4FontC1EPKhm+0x141>
  10d236:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  10d23a:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
  10d23e:	48 89 4d e0          	mov    %rcx,-0x20(%rbp)
  10d242:	c6 40 28 01          	movb   $0x1,0x28(%rax)
  10d246:	48 8b 4d e0          	mov    -0x20(%rbp),%rcx
  10d24a:	8b 49 1c             	mov    0x1c(%rcx),%ecx
  10d24d:	89 48 04             	mov    %ecx,0x4(%rax)
  10d250:	48 8b 4d e0          	mov    -0x20(%rbp),%rcx
  10d254:	8b 49 18             	mov    0x18(%rcx),%ecx
  10d257:	89 48 08             	mov    %ecx,0x8(%rax)
  10d25a:	48 8b 4d e0          	mov    -0x20(%rbp),%rcx
  10d25e:	8b 49 14             	mov    0x14(%rcx),%ecx
  10d261:	89 48 0c             	mov    %ecx,0xc(%rax)
  10d264:	48 8b 4d e0          	mov    -0x20(%rbp),%rcx
  10d268:	8b 49 08             	mov    0x8(%rcx),%ecx
  10d26b:	89 48 10             	mov    %ecx,0x10(%rax)
  10d26e:	c6 00 01             	movb   $0x1,(%rax)
  10d271:	48 83 c4 28          	add    $0x28,%rsp
  10d275:	5d                   	pop    %rbp
  10d276:	c3                   	ret
  10d277:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
  10d27e:	00 00

000000000010d280 <_ZNK4acos8graphics4Font9get_glyphEc>:
  10d280:	55                   	push   %rbp
  10d281:	48 89 e5             	mov    %rsp,%rbp
  10d284:	48 83 ec 20          	sub    $0x20,%rsp
  10d288:	40 88 f0             	mov    %sil,%al
  10d28b:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  10d28f:	88 45 ef             	mov    %al,-0x11(%rbp)
  10d292:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10d296:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  10d29a:	f6 00 01             	testb  $0x1,(%rax)
  10d29d:	0f 84 0f 00 00 00    	je     10d2b2 <_ZNK4acos8graphics4Font9get_glyphEc+0x32>
  10d2a3:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  10d2a7:	48 83 78 18 00       	cmpq   $0x0,0x18(%rax)
  10d2ac:	0f 85 0d 00 00 00    	jne    10d2bf <_ZNK4acos8graphics4Font9get_glyphEc+0x3f>
  10d2b2:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  10d2b9:	00
  10d2ba:	e9 25 00 00 00       	jmp    10d2e4 <_ZNK4acos8graphics4Font9get_glyphEc+0x64>
  10d2bf:	48 8b 55 e0          	mov    -0x20(%rbp),%rdx
  10d2c3:	0f b6 45 ef          	movzbl -0x11(%rbp),%eax
  10d2c7:	89 45 e8             	mov    %eax,-0x18(%rbp)
  10d2ca:	48 8b 42 18          	mov    0x18(%rdx),%rax
  10d2ce:	8b 4a 10             	mov    0x10(%rdx),%ecx
  10d2d1:	48 01 c8             	add    %rcx,%rax
  10d2d4:	8b 4d e8             	mov    -0x18(%rbp),%ecx
  10d2d7:	0f af 4a 0c          	imul   0xc(%rdx),%ecx
  10d2db:	89 c9                	mov    %ecx,%ecx
  10d2dd:	48 01 c8             	add    %rcx,%rax
  10d2e0:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  10d2e4:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10d2e8:	48 83 c4 20          	add    $0x20,%rsp
  10d2ec:	5d                   	pop    %rbp
  10d2ed:	c3                   	ret
  10d2ee:	66 90                	xchg   %ax,%ax

000000000010d2f0 <_ZNK4acos8graphics4Font12measure_charEcRjS2_>:
  10d2f0:	55                   	push   %rbp
  10d2f1:	48 89 e5             	mov    %rsp,%rbp
  10d2f4:	48 83 ec 30          	sub    $0x30,%rsp
  10d2f8:	40 88 f0             	mov    %sil,%al
  10d2fb:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10d2ff:	88 45 f7             	mov    %al,-0x9(%rbp)
  10d302:	48 89 55 e8          	mov    %rdx,-0x18(%rbp)
  10d306:	48 89 4d e0          	mov    %rcx,-0x20(%rbp)
  10d30a:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10d30e:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
  10d312:	f6 00 01             	testb  $0x1,(%rax)
  10d315:	0f 84 0f 00 00 00    	je     10d32a <_ZNK4acos8graphics4Font12measure_charEcRjS2_+0x3a>
  10d31b:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  10d31f:	8b 40 04             	mov    0x4(%rax),%eax
  10d322:	89 45 d4             	mov    %eax,-0x2c(%rbp)
  10d325:	e9 0d 00 00 00       	jmp    10d337 <_ZNK4acos8graphics4Font12measure_charEcRjS2_+0x47>
  10d32a:	b8 08 00 00 00       	mov    $0x8,%eax
  10d32f:	89 45 d4             	mov    %eax,-0x2c(%rbp)
  10d332:	e9 00 00 00 00       	jmp    10d337 <_ZNK4acos8graphics4Font12measure_charEcRjS2_+0x47>
  10d337:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  10d33b:	8b 55 d4             	mov    -0x2c(%rbp),%edx
  10d33e:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  10d342:	89 11                	mov    %edx,(%rcx)
  10d344:	f6 00 01             	testb  $0x1,(%rax)
  10d347:	0f 84 0f 00 00 00    	je     10d35c <_ZNK4acos8graphics4Font12measure_charEcRjS2_+0x6c>
  10d34d:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  10d351:	8b 40 08             	mov    0x8(%rax),%eax
  10d354:	89 45 d0             	mov    %eax,-0x30(%rbp)
  10d357:	e9 0d 00 00 00       	jmp    10d369 <_ZNK4acos8graphics4Font12measure_charEcRjS2_+0x79>
  10d35c:	b8 0a 00 00 00       	mov    $0xa,%eax
  10d361:	89 45 d0             	mov    %eax,-0x30(%rbp)
  10d364:	e9 00 00 00 00       	jmp    10d369 <_ZNK4acos8graphics4Font12measure_charEcRjS2_+0x79>
  10d369:	8b 4d d0             	mov    -0x30(%rbp),%ecx
  10d36c:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  10d370:	89 08                	mov    %ecx,(%rax)
  10d372:	48 83 c4 30          	add    $0x30,%rsp
  10d376:	5d                   	pop    %rbp
  10d377:	c3                   	ret
  10d378:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  10d37f:	00

000000000010d380 <_ZNK4acos8graphics4Font14measure_stringEPKcRjS4_i>:
  10d380:	55                   	push   %rbp
  10d381:	48 89 e5             	mov    %rsp,%rbp
  10d384:	48 83 ec 58          	sub    $0x58,%rsp
  10d388:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10d38c:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  10d390:	48 89 55 e8          	mov    %rdx,-0x18(%rbp)
  10d394:	48 89 4d e0          	mov    %rcx,-0x20(%rbp)
  10d398:	44 89 45 dc          	mov    %r8d,-0x24(%rbp)
  10d39c:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10d3a0:	48 89 45 b0          	mov    %rax,-0x50(%rbp)
  10d3a4:	48 83 7d f0 00       	cmpq   $0x0,-0x10(%rbp)
  10d3a9:	0f 85 19 00 00 00    	jne    10d3c8 <_ZNK4acos8graphics4Font14measure_stringEPKcRjS4_i+0x48>
  10d3af:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  10d3b3:	c7 00 00 00 00 00    	movl   $0x0,(%rax)
  10d3b9:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  10d3bd:	c7 00 00 00 00 00    	movl   $0x0,(%rax)
  10d3c3:	e9 44 01 00 00       	jmp    10d50c <_ZNK4acos8graphics4Font14measure_stringEPKcRjS4_i+0x18c>
  10d3c8:	48 8b 45 b0          	mov    -0x50(%rbp),%rax
  10d3cc:	f6 00 01             	testb  $0x1,(%rax)
  10d3cf:	0f 84 0f 00 00 00    	je     10d3e4 <_ZNK4acos8graphics4Font14measure_stringEPKcRjS4_i+0x64>
  10d3d5:	48 8b 45 b0          	mov    -0x50(%rbp),%rax
  10d3d9:	8b 40 04             	mov    0x4(%rax),%eax
  10d3dc:	89 45 ac             	mov    %eax,-0x54(%rbp)
  10d3df:	e9 0d 00 00 00       	jmp    10d3f1 <_ZNK4acos8graphics4Font14measure_stringEPKcRjS4_i+0x71>
  10d3e4:	b8 08 00 00 00       	mov    $0x8,%eax
  10d3e9:	89 45 ac             	mov    %eax,-0x54(%rbp)
  10d3ec:	e9 00 00 00 00       	jmp    10d3f1 <_ZNK4acos8graphics4Font14measure_stringEPKcRjS4_i+0x71>
  10d3f1:	48 8b 45 b0          	mov    -0x50(%rbp),%rax
  10d3f5:	8b 4d ac             	mov    -0x54(%rbp),%ecx
  10d3f8:	89 4d d8             	mov    %ecx,-0x28(%rbp)
  10d3fb:	f6 00 01             	testb  $0x1,(%rax)
  10d3fe:	0f 84 0f 00 00 00    	je     10d413 <_ZNK4acos8graphics4Font14measure_stringEPKcRjS4_i+0x93>
  10d404:	48 8b 45 b0          	mov    -0x50(%rbp),%rax
  10d408:	8b 40 08             	mov    0x8(%rax),%eax
  10d40b:	89 45 a8             	mov    %eax,-0x58(%rbp)
  10d40e:	e9 0d 00 00 00       	jmp    10d420 <_ZNK4acos8graphics4Font14measure_stringEPKcRjS4_i+0xa0>
  10d413:	b8 0a 00 00 00       	mov    $0xa,%eax
  10d418:	89 45 a8             	mov    %eax,-0x58(%rbp)
  10d41b:	e9 00 00 00 00       	jmp    10d420 <_ZNK4acos8graphics4Font14measure_stringEPKcRjS4_i+0xa0>
  10d420:	8b 45 a8             	mov    -0x58(%rbp),%eax
  10d423:	89 45 d4             	mov    %eax,-0x2c(%rbp)
  10d426:	c7 45 d0 00 00 00 00 	movl   $0x0,-0x30(%rbp)
  10d42d:	c7 45 cc 00 00 00 00 	movl   $0x0,-0x34(%rbp)
  10d434:	c7 45 c8 00 00 00 00 	movl   $0x0,-0x38(%rbp)
  10d43b:	c6 45 c7 00          	movb   $0x0,-0x39(%rbp)
  10d43f:	48 c7 45 b8 00 00 00 	movq   $0x0,-0x48(%rbp)
  10d446:	00
  10d447:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10d44b:	48 8b 4d b8          	mov    -0x48(%rbp),%rcx
  10d44f:	80 3c 08 00          	cmpb   $0x0,(%rax,%rcx,1)
  10d453:	0f 84 72 00 00 00    	je     10d4cb <_ZNK4acos8graphics4Font14measure_stringEPKcRjS4_i+0x14b>
  10d459:	c6 45 c7 01          	movb   $0x1,-0x39(%rbp)
  10d45d:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10d461:	48 8b 4d b8          	mov    -0x48(%rbp),%rcx
  10d465:	0f be 04 08          	movsbl (%rax,%rcx,1),%eax
  10d469:	83 f8 0a             	cmp    $0xa,%eax
  10d46c:	0f 85 27 00 00 00    	jne    10d499 <_ZNK4acos8graphics4Font14measure_stringEPKcRjS4_i+0x119>
  10d472:	8b 45 cc             	mov    -0x34(%rbp),%eax
  10d475:	3b 45 d0             	cmp    -0x30(%rbp),%eax
  10d478:	0f 86 06 00 00 00    	jbe    10d484 <_ZNK4acos8graphics4Font14measure_stringEPKcRjS4_i+0x104>
  10d47e:	8b 45 cc             	mov    -0x34(%rbp),%eax
  10d481:	89 45 d0             	mov    %eax,-0x30(%rbp)
  10d484:	c7 45 cc 00 00 00 00 	movl   $0x0,-0x34(%rbp)
  10d48b:	8b 45 d4             	mov    -0x2c(%rbp),%eax
  10d48e:	03 45 c8             	add    -0x38(%rbp),%eax
  10d491:	89 45 c8             	mov    %eax,-0x38(%rbp)
  10d494:	e9 1c 00 00 00       	jmp    10d4b5 <_ZNK4acos8graphics4Font14measure_stringEPKcRjS4_i+0x135>
  10d499:	83 7d cc 00          	cmpl   $0x0,-0x34(%rbp)
  10d49d:	0f 86 09 00 00 00    	jbe    10d4ac <_ZNK4acos8graphics4Font14measure_stringEPKcRjS4_i+0x12c>
  10d4a3:	8b 45 dc             	mov    -0x24(%rbp),%eax
  10d4a6:	03 45 cc             	add    -0x34(%rbp),%eax
  10d4a9:	89 45 cc             	mov    %eax,-0x34(%rbp)
  10d4ac:	8b 45 d8             	mov    -0x28(%rbp),%eax
  10d4af:	03 45 cc             	add    -0x34(%rbp),%eax
  10d4b2:	89 45 cc             	mov    %eax,-0x34(%rbp)
  10d4b5:	e9 00 00 00 00       	jmp    10d4ba <_ZNK4acos8graphics4Font14measure_stringEPKcRjS4_i+0x13a>
  10d4ba:	48 8b 45 b8          	mov    -0x48(%rbp),%rax
  10d4be:	48 83 c0 01          	add    $0x1,%rax
  10d4c2:	48 89 45 b8          	mov    %rax,-0x48(%rbp)
  10d4c6:	e9 7c ff ff ff       	jmp    10d447 <_ZNK4acos8graphics4Font14measure_stringEPKcRjS4_i+0xc7>
  10d4cb:	8b 45 cc             	mov    -0x34(%rbp),%eax
  10d4ce:	3b 45 d0             	cmp    -0x30(%rbp),%eax
  10d4d1:	0f 86 06 00 00 00    	jbe    10d4dd <_ZNK4acos8graphics4Font14measure_stringEPKcRjS4_i+0x15d>
  10d4d7:	8b 45 cc             	mov    -0x34(%rbp),%eax
  10d4da:	89 45 d0             	mov    %eax,-0x30(%rbp)
  10d4dd:	f6 45 c7 01          	testb  $0x1,-0x39(%rbp)
  10d4e1:	0f 84 13 00 00 00    	je     10d4fa <_ZNK4acos8graphics4Font14measure_stringEPKcRjS4_i+0x17a>
  10d4e7:	83 7d cc 00          	cmpl   $0x0,-0x34(%rbp)
  10d4eb:	0f 86 09 00 00 00    	jbe    10d4fa <_ZNK4acos8graphics4Font14measure_stringEPKcRjS4_i+0x17a>
  10d4f1:	8b 45 d4             	mov    -0x2c(%rbp),%eax
  10d4f4:	03 45 c8             	add    -0x38(%rbp),%eax
  10d4f7:	89 45 c8             	mov    %eax,-0x38(%rbp)
  10d4fa:	8b 4d d0             	mov    -0x30(%rbp),%ecx
  10d4fd:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  10d501:	89 08                	mov    %ecx,(%rax)
  10d503:	8b 4d c8             	mov    -0x38(%rbp),%ecx
  10d506:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  10d50a:	89 08                	mov    %ecx,(%rax)
  10d50c:	48 83 c4 58          	add    $0x58,%rsp
  10d510:	5d                   	pop    %rbp
  10d511:	c3                   	ret
  10d512:	66 66 66 66 66 2e 0f 	data16 data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
  10d519:	1f 84 00 00 00 00 00

000000000010d520 <_ZN4acos8graphics4Font11set_defaultEPS1_>:
  10d520:	55                   	push   %rbp
  10d521:	48 89 e5             	mov    %rsp,%rbp
  10d524:	50                   	push   %rax
  10d525:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10d529:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10d52d:	48 89 04 25 a8 db 16 	mov    %rax,0x16dba8
  10d534:	00
  10d535:	48 83 c4 08          	add    $0x8,%rsp
  10d539:	5d                   	pop    %rbp
  10d53a:	c3                   	ret
  10d53b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

000000000010d540 <_ZN4acos8graphics4Font11get_defaultEv>:
  10d540:	55                   	push   %rbp
  10d541:	48 89 e5             	mov    %rsp,%rbp
  10d544:	48 8b 04 25 a8 db 16 	mov    0x16dba8,%rax
  10d54b:	00
  10d54c:	5d                   	pop    %rbp
  10d54d:	c3                   	ret
  10d54e:	66 90                	xchg   %ax,%ax

000000000010d550 <_ZN4acos8graphics4Font22measure_string_defaultEPKcRjS4_i>:
  10d550:	55                   	push   %rbp
  10d551:	48 89 e5             	mov    %rsp,%rbp
  10d554:	48 83 ec 40          	sub    $0x40,%rsp
  10d558:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10d55c:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  10d560:	48 89 55 e8          	mov    %rdx,-0x18(%rbp)
  10d564:	89 4d e4             	mov    %ecx,-0x1c(%rbp)
  10d567:	48 83 3c 25 a8 db 16 	cmpq   $0x0,0x16dba8
  10d56e:	00 00
  10d570:	0f 84 22 00 00 00    	je     10d598 <_ZN4acos8graphics4Font22measure_string_defaultEPKcRjS4_i+0x48>
  10d576:	48 8b 3c 25 a8 db 16 	mov    0x16dba8,%rdi
  10d57d:	00
  10d57e:	48 8b 75 f8          	mov    -0x8(%rbp),%rsi
  10d582:	48 8b 55 f0          	mov    -0x10(%rbp),%rdx
  10d586:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  10d58a:	44 8b 45 e4          	mov    -0x1c(%rbp),%r8d
  10d58e:	e8 ed fd ff ff       	call   10d380 <_ZNK4acos8graphics4Font14measure_stringEPKcRjS4_i>
  10d593:	e9 0a 01 00 00       	jmp    10d6a2 <_ZN4acos8graphics4Font22measure_string_defaultEPKcRjS4_i+0x152>
  10d598:	48 83 7d f8 00       	cmpq   $0x0,-0x8(%rbp)
  10d59d:	0f 85 19 00 00 00    	jne    10d5bc <_ZN4acos8graphics4Font22measure_string_defaultEPKcRjS4_i+0x6c>
  10d5a3:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10d5a7:	c7 00 00 00 00 00    	movl   $0x0,(%rax)
  10d5ad:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  10d5b1:	c7 00 00 00 00 00    	movl   $0x0,(%rax)
  10d5b7:	e9 e6 00 00 00       	jmp    10d6a2 <_ZN4acos8graphics4Font22measure_string_defaultEPKcRjS4_i+0x152>
  10d5bc:	c7 45 e0 00 00 00 00 	movl   $0x0,-0x20(%rbp)
  10d5c3:	c7 45 dc 00 00 00 00 	movl   $0x0,-0x24(%rbp)
  10d5ca:	c7 45 d8 00 00 00 00 	movl   $0x0,-0x28(%rbp)
  10d5d1:	c6 45 d7 00          	movb   $0x0,-0x29(%rbp)
  10d5d5:	48 c7 45 c8 00 00 00 	movq   $0x0,-0x38(%rbp)
  10d5dc:	00
  10d5dd:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10d5e1:	48 8b 4d c8          	mov    -0x38(%rbp),%rcx
  10d5e5:	80 3c 08 00          	cmpb   $0x0,(%rax,%rcx,1)
  10d5e9:	0f 84 72 00 00 00    	je     10d661 <_ZN4acos8graphics4Font22measure_string_defaultEPKcRjS4_i+0x111>
  10d5ef:	c6 45 d7 01          	movb   $0x1,-0x29(%rbp)
  10d5f3:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10d5f7:	48 8b 4d c8          	mov    -0x38(%rbp),%rcx
  10d5fb:	0f be 04 08          	movsbl (%rax,%rcx,1),%eax
  10d5ff:	83 f8 0a             	cmp    $0xa,%eax
  10d602:	0f 85 27 00 00 00    	jne    10d62f <_ZN4acos8graphics4Font22measure_string_defaultEPKcRjS4_i+0xdf>
  10d608:	8b 45 dc             	mov    -0x24(%rbp),%eax
  10d60b:	3b 45 e0             	cmp    -0x20(%rbp),%eax
  10d60e:	0f 86 06 00 00 00    	jbe    10d61a <_ZN4acos8graphics4Font22measure_string_defaultEPKcRjS4_i+0xca>
  10d614:	8b 45 dc             	mov    -0x24(%rbp),%eax
  10d617:	89 45 e0             	mov    %eax,-0x20(%rbp)
  10d61a:	c7 45 dc 00 00 00 00 	movl   $0x0,-0x24(%rbp)
  10d621:	8b 45 d8             	mov    -0x28(%rbp),%eax
  10d624:	83 c0 0a             	add    $0xa,%eax
  10d627:	89 45 d8             	mov    %eax,-0x28(%rbp)
  10d62a:	e9 1c 00 00 00       	jmp    10d64b <_ZN4acos8graphics4Font22measure_string_defaultEPKcRjS4_i+0xfb>
  10d62f:	83 7d dc 00          	cmpl   $0x0,-0x24(%rbp)
  10d633:	0f 86 09 00 00 00    	jbe    10d642 <_ZN4acos8graphics4Font22measure_string_defaultEPKcRjS4_i+0xf2>
  10d639:	8b 45 e4             	mov    -0x1c(%rbp),%eax
  10d63c:	03 45 dc             	add    -0x24(%rbp),%eax
  10d63f:	89 45 dc             	mov    %eax,-0x24(%rbp)
  10d642:	8b 45 dc             	mov    -0x24(%rbp),%eax
  10d645:	83 c0 08             	add    $0x8,%eax
  10d648:	89 45 dc             	mov    %eax,-0x24(%rbp)
  10d64b:	e9 00 00 00 00       	jmp    10d650 <_ZN4acos8graphics4Font22measure_string_defaultEPKcRjS4_i+0x100>
  10d650:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
  10d654:	48 83 c0 01          	add    $0x1,%rax
  10d658:	48 89 45 c8          	mov    %rax,-0x38(%rbp)
  10d65c:	e9 7c ff ff ff       	jmp    10d5dd <_ZN4acos8graphics4Font22measure_string_defaultEPKcRjS4_i+0x8d>
  10d661:	8b 45 dc             	mov    -0x24(%rbp),%eax
  10d664:	3b 45 e0             	cmp    -0x20(%rbp),%eax
  10d667:	0f 86 06 00 00 00    	jbe    10d673 <_ZN4acos8graphics4Font22measure_string_defaultEPKcRjS4_i+0x123>
  10d66d:	8b 45 dc             	mov    -0x24(%rbp),%eax
  10d670:	89 45 e0             	mov    %eax,-0x20(%rbp)
  10d673:	f6 45 d7 01          	testb  $0x1,-0x29(%rbp)
  10d677:	0f 84 13 00 00 00    	je     10d690 <_ZN4acos8graphics4Font22measure_string_defaultEPKcRjS4_i+0x140>
  10d67d:	83 7d dc 00          	cmpl   $0x0,-0x24(%rbp)
  10d681:	0f 86 09 00 00 00    	jbe    10d690 <_ZN4acos8graphics4Font22measure_string_defaultEPKcRjS4_i+0x140>
  10d687:	8b 45 d8             	mov    -0x28(%rbp),%eax
  10d68a:	83 c0 0a             	add    $0xa,%eax
  10d68d:	89 45 d8             	mov    %eax,-0x28(%rbp)
  10d690:	8b 4d e0             	mov    -0x20(%rbp),%ecx
  10d693:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10d697:	89 08                	mov    %ecx,(%rax)
  10d699:	8b 4d d8             	mov    -0x28(%rbp),%ecx
  10d69c:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  10d6a0:	89 08                	mov    %ecx,(%rax)
  10d6a2:	48 83 c4 40          	add    $0x40,%rsp
  10d6a6:	5d                   	pop    %rbp
  10d6a7:	c3                   	ret
  10d6a8:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  10d6af:	00

000000000010d6b0 <__cxx_global_var_init>:
  10d6b0:	55                   	push   %rbp
  10d6b1:	48 89 e5             	mov    %rsp,%rbp
  10d6b4:	48 bf b0 db 16 00 00 	movabs $0x16dbb0,%rdi
  10d6bb:	00 00 00
  10d6be:	e8 7d 19 00 00       	call   10f040 <_ZN4acos8graphics4FontC2Ev>
  10d6c3:	5d                   	pop    %rbp
  10d6c4:	c3                   	ret
  10d6c5:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  10d6cc:	00 00 00 00

000000000010d6d0 <__cxx_global_var_init.1>:
  10d6d0:	55                   	push   %rbp
  10d6d1:	48 89 e5             	mov    %rsp,%rbp
  10d6d4:	48 bf e0 db 16 00 00 	movabs $0x16dbe0,%rdi
  10d6db:	00 00 00
  10d6de:	e8 5d 19 00 00       	call   10f040 <_ZN4acos8graphics4FontC2Ev>
  10d6e3:	5d                   	pop    %rbp
  10d6e4:	c3                   	ret
  10d6e5:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  10d6ec:	00 00 00 00

000000000010d6f0 <__cxx_global_var_init.2>:
  10d6f0:	55                   	push   %rbp
  10d6f1:	48 89 e5             	mov    %rsp,%rbp
  10d6f4:	48 bf 10 dc 16 00 00 	movabs $0x16dc10,%rdi
  10d6fb:	00 00 00
  10d6fe:	e8 3d 19 00 00       	call   10f040 <_ZN4acos8graphics4FontC2Ev>
  10d703:	5d                   	pop    %rbp
  10d704:	c3                   	ret
  10d705:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  10d70c:	00 00 00 00

000000000010d710 <__cxx_global_var_init.3>:
  10d710:	55                   	push   %rbp
  10d711:	48 89 e5             	mov    %rsp,%rbp
  10d714:	48 83 ec 10          	sub    $0x10,%rsp
  10d718:	48 b8 40 dc 16 00 00 	movabs $0x16dc40,%rax
  10d71f:	00 00 00
  10d722:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  10d726:	e9 00 00 00 00       	jmp    10d72b <__cxx_global_var_init.3+0x1b>
  10d72b:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  10d72f:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  10d733:	e8 08 19 00 00       	call   10f040 <_ZN4acos8graphics4FontC2Ev>
  10d738:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10d73c:	48 83 c0 30          	add    $0x30,%rax
  10d740:	48 b9 40 dc 16 00 00 	movabs $0x16dc40,%rcx
  10d747:	00 00 00
  10d74a:	48 81 c1 90 00 00 00 	add    $0x90,%rcx
  10d751:	48 39 c8             	cmp    %rcx,%rax
  10d754:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  10d758:	0f 85 cd ff ff ff    	jne    10d72b <__cxx_global_var_init.3+0x1b>
  10d75e:	48 83 c4 10          	add    $0x10,%rsp
  10d762:	5d                   	pop    %rbp
  10d763:	c3                   	ret
  10d764:	66 66 66 2e 0f 1f 84 	data16 data16 cs nopw 0x0(%rax,%rax,1)
  10d76b:	00 00 00 00 00

000000000010d770 <_ZN4acos8graphics11FontManager10initializeEv>:
  10d770:	55                   	push   %rbp
  10d771:	48 89 e5             	mov    %rsp,%rbp
  10d774:	48 83 ec 70          	sub    $0x70,%rsp
  10d778:	48 8d 7d d0          	lea    -0x30(%rbp),%rdi
  10d77c:	e8 0f 19 00 00       	call   10f090 <_ZN4acos8graphics16get_builtin_fontEv>
  10d781:	48 bf 40 dc 16 00 00 	movabs $0x16dc40,%rdi
  10d788:	00 00 00
  10d78b:	48 8d 75 d0          	lea    -0x30(%rbp),%rsi
  10d78f:	ba 29 00 00 00       	mov    $0x29,%edx
  10d794:	e8 67 28 ff ff       	call   100000 <memcpy>
  10d799:	48 bf 40 dc 16 00 00 	movabs $0x16dc40,%rdi
  10d7a0:	00 00 00
  10d7a3:	e8 b8 17 00 00       	call   10ef60 <_ZNK4acos8graphics4Font8is_validEv>
  10d7a8:	a8 01                	test   $0x1,%al
  10d7aa:	0f 85 05 00 00 00    	jne    10d7b5 <_ZN4acos8graphics11FontManager10initializeEv+0x45>
  10d7b0:	e9 2d 00 00 00       	jmp    10d7e2 <_ZN4acos8graphics11FontManager10initializeEv+0x72>
  10d7b5:	48 bf 40 dc 16 00 00 	movabs $0x16dc40,%rdi
  10d7bc:	00 00 00
  10d7bf:	e8 5c fd ff ff       	call   10d520 <_ZN4acos8graphics4Font11set_defaultEPS1_>
  10d7c4:	48 bf b0 db 16 00 00 	movabs $0x16dbb0,%rdi
  10d7cb:	00 00 00
  10d7ce:	48 be 40 dc 16 00 00 	movabs $0x16dc40,%rsi
  10d7d5:	00 00 00
  10d7d8:	ba 29 00 00 00       	mov    $0x29,%edx
  10d7dd:	e8 1e 28 ff ff       	call   100000 <memcpy>
  10d7e2:	8b 04 25 10 45 15 00 	mov    0x154510,%eax
  10d7e9:	89 c2                	mov    %eax,%edx
  10d7eb:	48 8d 7d 90          	lea    -0x70(%rbp),%rdi
  10d7ef:	48 be 80 25 11 00 00 	movabs $0x112580,%rsi
  10d7f6:	00 00 00
  10d7f9:	e8 e2 18 00 00       	call   10f0e0 <_ZN4acos4SpanIKhEC2EPS1_m>
  10d7fe:	48 8b 75 90          	mov    -0x70(%rbp),%rsi
  10d802:	48 8b 55 98          	mov    -0x68(%rbp),%rdx
  10d806:	48 8d 7d a0          	lea    -0x60(%rbp),%rdi
  10d80a:	e8 01 19 00 00       	call   10f110 <_ZN4acos8graphics4FontC2ENS_4SpanIKhEE>
  10d80f:	48 bf 40 dc 16 00 00 	movabs $0x16dc40,%rdi
  10d816:	00 00 00
  10d819:	48 83 c7 30          	add    $0x30,%rdi
  10d81d:	48 8d 75 a0          	lea    -0x60(%rbp),%rsi
  10d821:	ba 29 00 00 00       	mov    $0x29,%edx
  10d826:	e8 d5 27 ff ff       	call   100000 <memcpy>
  10d82b:	48 bf 40 dc 16 00 00 	movabs $0x16dc40,%rdi
  10d832:	00 00 00
  10d835:	48 83 c7 30          	add    $0x30,%rdi
  10d839:	e8 22 17 00 00       	call   10ef60 <_ZNK4acos8graphics4Font8is_validEv>
  10d83e:	a8 01                	test   $0x1,%al
  10d840:	0f 85 05 00 00 00    	jne    10d84b <_ZN4acos8graphics11FontManager10initializeEv+0xdb>
  10d846:	e9 22 00 00 00       	jmp    10d86d <_ZN4acos8graphics11FontManager10initializeEv+0xfd>
  10d84b:	48 bf 10 dc 16 00 00 	movabs $0x16dc10,%rdi
  10d852:	00 00 00
  10d855:	48 be 40 dc 16 00 00 	movabs $0x16dc40,%rsi
  10d85c:	00 00 00
  10d85f:	48 83 c6 30          	add    $0x30,%rsi
  10d863:	ba 29 00 00 00       	mov    $0x29,%edx
  10d868:	e8 93 27 ff ff       	call   100000 <memcpy>
  10d86d:	48 bf e0 db 16 00 00 	movabs $0x16dbe0,%rdi
  10d874:	00 00 00
  10d877:	48 be 10 dc 16 00 00 	movabs $0x16dc10,%rsi
  10d87e:	00 00 00
  10d881:	ba 29 00 00 00       	mov    $0x29,%edx
  10d886:	e8 75 27 ff ff       	call   100000 <memcpy>
  10d88b:	c6 04 25 d0 dc 16 00 	movb   $0x1,0x16dcd0
  10d892:	01
  10d893:	48 bf b0 db 16 00 00 	movabs $0x16dbb0,%rdi
  10d89a:	00 00 00
  10d89d:	e8 be 16 00 00       	call   10ef60 <_ZNK4acos8graphics4Font8is_validEv>
  10d8a2:	24 01                	and    $0x1,%al
  10d8a4:	0f b6 c0             	movzbl %al,%eax
  10d8a7:	48 83 c4 70          	add    $0x70,%rsp
  10d8ab:	5d                   	pop    %rbp
  10d8ac:	c3                   	ret
  10d8ad:	0f 1f 00             	nopl   (%rax)

000000000010d8b0 <_ZN4acos8graphics11FontManager8get_fontENS1_6FontIDE>:
  10d8b0:	55                   	push   %rbp
  10d8b1:	48 89 e5             	mov    %rsp,%rbp
  10d8b4:	48 83 ec 10          	sub    $0x10,%rsp
  10d8b8:	89 7d f4             	mov    %edi,-0xc(%rbp)
  10d8bb:	f6 04 25 d0 dc 16 00 	testb  $0x1,0x16dcd0
  10d8c2:	01
  10d8c3:	0f 85 0d 00 00 00    	jne    10d8d6 <_ZN4acos8graphics11FontManager8get_fontENS1_6FontIDE+0x26>
  10d8c9:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  10d8d0:	00
  10d8d1:	e9 db 00 00 00       	jmp    10d9b1 <_ZN4acos8graphics11FontManager8get_fontENS1_6FontIDE+0x101>
  10d8d6:	8b 45 f4             	mov    -0xc(%rbp),%eax
  10d8d9:	89 45 f0             	mov    %eax,-0x10(%rbp)
  10d8dc:	83 e8 02             	sub    $0x2,%eax
  10d8df:	0f 82 27 00 00 00    	jb     10d90c <_ZN4acos8graphics11FontManager8get_fontENS1_6FontIDE+0x5c>
  10d8e5:	e9 00 00 00 00       	jmp    10d8ea <_ZN4acos8graphics11FontManager8get_fontENS1_6FontIDE+0x3a>
  10d8ea:	8b 45 f0             	mov    -0x10(%rbp),%eax
  10d8ed:	83 e8 02             	sub    $0x2,%eax
  10d8f0:	0f 84 43 00 00 00    	je     10d939 <_ZN4acos8graphics11FontManager8get_fontENS1_6FontIDE+0x89>
  10d8f6:	e9 00 00 00 00       	jmp    10d8fb <_ZN4acos8graphics11FontManager8get_fontENS1_6FontIDE+0x4b>
  10d8fb:	8b 45 f0             	mov    -0x10(%rbp),%eax
  10d8fe:	83 e8 03             	sub    $0x3,%eax
  10d901:	0f 84 67 00 00 00    	je     10d96e <_ZN4acos8graphics11FontManager8get_fontENS1_6FontIDE+0xbe>
  10d907:	e9 97 00 00 00       	jmp    10d9a3 <_ZN4acos8graphics11FontManager8get_fontENS1_6FontIDE+0xf3>
  10d90c:	48 bf b0 db 16 00 00 	movabs $0x16dbb0,%rdi
  10d913:	00 00 00
  10d916:	e8 45 16 00 00       	call   10ef60 <_ZNK4acos8graphics4Font8is_validEv>
  10d91b:	88 c2                	mov    %al,%dl
  10d91d:	31 c0                	xor    %eax,%eax
  10d91f:	48 b9 b0 db 16 00 00 	movabs $0x16dbb0,%rcx
  10d926:	00 00 00
  10d929:	f6 c2 01             	test   $0x1,%dl
  10d92c:	48 0f 45 c1          	cmovne %rcx,%rax
  10d930:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  10d934:	e9 78 00 00 00       	jmp    10d9b1 <_ZN4acos8graphics11FontManager8get_fontENS1_6FontIDE+0x101>
  10d939:	48 bf e0 db 16 00 00 	movabs $0x16dbe0,%rdi
  10d940:	00 00 00
  10d943:	e8 18 16 00 00       	call   10ef60 <_ZNK4acos8graphics4Font8is_validEv>
  10d948:	88 c2                	mov    %al,%dl
  10d94a:	48 b8 b0 db 16 00 00 	movabs $0x16dbb0,%rax
  10d951:	00 00 00
  10d954:	48 b9 e0 db 16 00 00 	movabs $0x16dbe0,%rcx
  10d95b:	00 00 00
  10d95e:	f6 c2 01             	test   $0x1,%dl
  10d961:	48 0f 45 c1          	cmovne %rcx,%rax
  10d965:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  10d969:	e9 43 00 00 00       	jmp    10d9b1 <_ZN4acos8graphics11FontManager8get_fontENS1_6FontIDE+0x101>
  10d96e:	48 bf 10 dc 16 00 00 	movabs $0x16dc10,%rdi
  10d975:	00 00 00
  10d978:	e8 e3 15 00 00       	call   10ef60 <_ZNK4acos8graphics4Font8is_validEv>
  10d97d:	88 c2                	mov    %al,%dl
  10d97f:	48 b8 b0 db 16 00 00 	movabs $0x16dbb0,%rax
  10d986:	00 00 00
  10d989:	48 b9 10 dc 16 00 00 	movabs $0x16dc10,%rcx
  10d990:	00 00 00
  10d993:	f6 c2 01             	test   $0x1,%dl
  10d996:	48 0f 45 c1          	cmovne %rcx,%rax
  10d99a:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  10d99e:	e9 0e 00 00 00       	jmp    10d9b1 <_ZN4acos8graphics11FontManager8get_fontENS1_6FontIDE+0x101>
  10d9a3:	48 b8 b0 db 16 00 00 	movabs $0x16dbb0,%rax
  10d9aa:	00 00 00
  10d9ad:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  10d9b1:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10d9b5:	48 83 c4 10          	add    $0x10,%rsp
  10d9b9:	5d                   	pop    %rbp
  10d9ba:	c3                   	ret
  10d9bb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

000000000010d9c0 <_ZN4acos8graphics11FontManager14load_font_dataENS1_6FontIDE>:
  10d9c0:	55                   	push   %rbp
  10d9c1:	48 89 e5             	mov    %rsp,%rbp
  10d9c4:	48 83 ec 20          	sub    $0x20,%rsp
  10d9c8:	89 7d ec             	mov    %edi,-0x14(%rbp)
  10d9cb:	48 8d 7d f0          	lea    -0x10(%rbp),%rdi
  10d9cf:	e8 8c 17 00 00       	call   10f160 <_ZN4acos4SpanIKhEC2Ev>
  10d9d4:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10d9d8:	48 8b 55 f8          	mov    -0x8(%rbp),%rdx
  10d9dc:	48 83 c4 20          	add    $0x20,%rsp
  10d9e0:	5d                   	pop    %rbp
  10d9e1:	c3                   	ret
  10d9e2:	66 66 66 66 66 2e 0f 	data16 data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
  10d9e9:	1f 84 00 00 00 00 00

000000000010d9f0 <_GLOBAL__sub_I_font_manager.cpp>:
  10d9f0:	55                   	push   %rbp
  10d9f1:	48 89 e5             	mov    %rsp,%rbp
  10d9f4:	e8 b7 fc ff ff       	call   10d6b0 <__cxx_global_var_init>
  10d9f9:	e8 d2 fc ff ff       	call   10d6d0 <__cxx_global_var_init.1>
  10d9fe:	e8 ed fc ff ff       	call   10d6f0 <__cxx_global_var_init.2>
  10da03:	e8 08 fd ff ff       	call   10d710 <__cxx_global_var_init.3>
  10da08:	5d                   	pop    %rbp
  10da09:	c3                   	ret
  10da0a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

000000000010da10 <_ZN4acos5input12InputManager15register_deviceEPNS0_11InputDeviceE>:
  10da10:	55                   	push   %rbp
  10da11:	48 89 e5             	mov    %rsp,%rbp
  10da14:	50                   	push   %rax
  10da15:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10da19:	83 3c 25 20 dd 16 00 	cmpl   $0x8,0x16dd20
  10da20:	08
  10da21:	0f 83 21 00 00 00    	jae    10da48 <_ZN4acos5input12InputManager15register_deviceEPNS0_11InputDeviceE+0x38>
  10da27:	48 8b 4d f8          	mov    -0x8(%rbp),%rcx
  10da2b:	8b 04 25 20 dd 16 00 	mov    0x16dd20,%eax
  10da32:	89 c2                	mov    %eax,%edx
  10da34:	83 c2 01             	add    $0x1,%edx
  10da37:	89 14 25 20 dd 16 00 	mov    %edx,0x16dd20
  10da3e:	89 c0                	mov    %eax,%eax
  10da40:	48 89 0c c5 e0 dc 16 	mov    %rcx,0x16dce0(,%rax,8)
  10da47:	00
  10da48:	48 83 c4 08          	add    $0x8,%rsp
  10da4c:	5d                   	pop    %rbp
  10da4d:	c3                   	ret
  10da4e:	66 90                	xchg   %ax,%ax

000000000010da50 <_ZN4acos5input12InputManager10push_eventERKNS_3abi10InputEventE>:
  10da50:	55                   	push   %rbp
  10da51:	48 89 e5             	mov    %rsp,%rbp
  10da54:	50                   	push   %rax
  10da55:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10da59:	48 83 3c 25 40 e1 16 	cmpq   $0x40,0x16e140
  10da60:	00 40
  10da62:	0f 83 57 00 00 00    	jae    10dabf <_ZN4acos5input12InputManager10push_eventERKNS_3abi10InputEventE+0x6f>
  10da68:	48 8b 4d f8          	mov    -0x8(%rbp),%rcx
  10da6c:	48 8b 14 25 38 e1 16 	mov    0x16e138,%rdx
  10da73:	00
  10da74:	48 b8 30 dd 16 00 00 	movabs $0x16dd30,%rax
  10da7b:	00 00 00
  10da7e:	48 c1 e2 04          	shl    $0x4,%rdx
  10da82:	48 01 d0             	add    %rdx,%rax
  10da85:	48 8b 11             	mov    (%rcx),%rdx
  10da88:	48 89 10             	mov    %rdx,(%rax)
  10da8b:	48 8b 49 08          	mov    0x8(%rcx),%rcx
  10da8f:	48 89 48 08          	mov    %rcx,0x8(%rax)
  10da93:	48 8b 04 25 38 e1 16 	mov    0x16e138,%rax
  10da9a:	00
  10da9b:	48 83 c0 01          	add    $0x1,%rax
  10da9f:	48 83 e0 3f          	and    $0x3f,%rax
  10daa3:	48 89 04 25 38 e1 16 	mov    %rax,0x16e138
  10daaa:	00
  10daab:	48 8b 04 25 40 e1 16 	mov    0x16e140,%rax
  10dab2:	00
  10dab3:	48 83 c0 01          	add    $0x1,%rax
  10dab7:	48 89 04 25 40 e1 16 	mov    %rax,0x16e140
  10dabe:	00
  10dabf:	48 83 c4 08          	add    $0x8,%rsp
  10dac3:	5d                   	pop    %rbp
  10dac4:	c3                   	ret
  10dac5:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  10dacc:	00 00 00 00

000000000010dad0 <_ZN4acos5input12InputManager9pop_eventERNS_3abi10InputEventE>:
  10dad0:	55                   	push   %rbp
  10dad1:	48 89 e5             	mov    %rsp,%rbp
  10dad4:	48 83 ec 10          	sub    $0x10,%rsp
  10dad8:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  10dadc:	48 83 3c 25 40 e1 16 	cmpq   $0x0,0x16e140
  10dae3:	00 00
  10dae5:	0f 85 09 00 00 00    	jne    10daf4 <_ZN4acos5input12InputManager9pop_eventERNS_3abi10InputEventE+0x24>
  10daeb:	c6 45 ff 00          	movb   $0x0,-0x1(%rbp)
  10daef:	e9 5b 00 00 00       	jmp    10db4f <_ZN4acos5input12InputManager9pop_eventERNS_3abi10InputEventE+0x7f>
  10daf4:	48 8b 04 25 30 e1 16 	mov    0x16e130,%rax
  10dafb:	00
  10dafc:	48 b9 30 dd 16 00 00 	movabs $0x16dd30,%rcx
  10db03:	00 00 00
  10db06:	48 c1 e0 04          	shl    $0x4,%rax
  10db0a:	48 01 c1             	add    %rax,%rcx
  10db0d:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10db11:	48 8b 11             	mov    (%rcx),%rdx
  10db14:	48 89 10             	mov    %rdx,(%rax)
  10db17:	48 8b 49 08          	mov    0x8(%rcx),%rcx
  10db1b:	48 89 48 08          	mov    %rcx,0x8(%rax)
  10db1f:	48 8b 04 25 30 e1 16 	mov    0x16e130,%rax
  10db26:	00
  10db27:	48 83 c0 01          	add    $0x1,%rax
  10db2b:	48 83 e0 3f          	and    $0x3f,%rax
  10db2f:	48 89 04 25 30 e1 16 	mov    %rax,0x16e130
  10db36:	00
  10db37:	48 8b 04 25 40 e1 16 	mov    0x16e140,%rax
  10db3e:	00
  10db3f:	48 83 c0 ff          	add    $0xffffffffffffffff,%rax
  10db43:	48 89 04 25 40 e1 16 	mov    %rax,0x16e140
  10db4a:	00
  10db4b:	c6 45 ff 01          	movb   $0x1,-0x1(%rbp)
  10db4f:	8a 45 ff             	mov    -0x1(%rbp),%al
  10db52:	24 01                	and    $0x1,%al
  10db54:	0f b6 c0             	movzbl %al,%eax
  10db57:	48 83 c4 10          	add    $0x10,%rsp
  10db5b:	5d                   	pop    %rbp
  10db5c:	c3                   	ret
  10db5d:	0f 1f 00             	nopl   (%rax)

000000000010db60 <_ZN4acos5input12InputManager4initEv>:
  10db60:	55                   	push   %rbp
  10db61:	48 89 e5             	mov    %rsp,%rbp
  10db64:	5d                   	pop    %rbp
  10db65:	c3                   	ret
  10db66:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
  10db6d:	00 00 00

000000000010db70 <_ZN4acos5audio12AudioManager4initEv>:
  10db70:	55                   	push   %rbp
  10db71:	48 89 e5             	mov    %rsp,%rbp
  10db74:	c7 04 25 d0 e1 16 00 	movl   $0x0,0x16e1d0
  10db7b:	00 00 00 00
  10db7f:	5d                   	pop    %rbp
  10db80:	c3                   	ret
  10db81:	66 66 66 66 66 66 2e 	data16 data16 data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
  10db88:	0f 1f 84 00 00 00 00
  10db8f:	00

000000000010db90 <_ZN4acos5audio12AudioManager15register_deviceEPNS0_11AudioDeviceE>:
  10db90:	55                   	push   %rbp
  10db91:	48 89 e5             	mov    %rsp,%rbp
  10db94:	50                   	push   %rax
  10db95:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10db99:	83 3c 25 d0 e1 16 00 	cmpl   $0x10,0x16e1d0
  10dba0:	10
  10dba1:	0f 83 21 00 00 00    	jae    10dbc8 <_ZN4acos5audio12AudioManager15register_deviceEPNS0_11AudioDeviceE+0x38>
  10dba7:	48 8b 4d f8          	mov    -0x8(%rbp),%rcx
  10dbab:	8b 04 25 d0 e1 16 00 	mov    0x16e1d0,%eax
  10dbb2:	89 c2                	mov    %eax,%edx
  10dbb4:	83 c2 01             	add    $0x1,%edx
  10dbb7:	89 14 25 d0 e1 16 00 	mov    %edx,0x16e1d0
  10dbbe:	89 c0                	mov    %eax,%eax
  10dbc0:	48 89 0c c5 50 e1 16 	mov    %rcx,0x16e150(,%rax,8)
  10dbc7:	00
  10dbc8:	48 83 c4 08          	add    $0x8,%rsp
  10dbcc:	5d                   	pop    %rbp
  10dbcd:	c3                   	ret
  10dbce:	66 90                	xchg   %ax,%ax

000000000010dbd0 <_ZN4acos5audio12AudioManager10get_deviceEj>:
  10dbd0:	55                   	push   %rbp
  10dbd1:	48 89 e5             	mov    %rsp,%rbp
  10dbd4:	48 83 ec 10          	sub    $0x10,%rsp
  10dbd8:	89 7d f4             	mov    %edi,-0xc(%rbp)
  10dbdb:	c7 45 f0 00 00 00 00 	movl   $0x0,-0x10(%rbp)
  10dbe2:	8b 45 f0             	mov    -0x10(%rbp),%eax
  10dbe5:	3b 04 25 d0 e1 16 00 	cmp    0x16e1d0,%eax
  10dbec:	0f 83 40 00 00 00    	jae    10dc32 <_ZN4acos5audio12AudioManager10get_deviceEj+0x62>
  10dbf2:	8b 45 f0             	mov    -0x10(%rbp),%eax
  10dbf5:	48 8b 3c c5 50 e1 16 	mov    0x16e150(,%rax,8),%rdi
  10dbfc:	00
  10dbfd:	e8 ce 15 00 00       	call   10f1d0 <_ZNK4acos5audio11AudioDevice2idEv>
  10dc02:	3b 45 f4             	cmp    -0xc(%rbp),%eax
  10dc05:	0f 85 14 00 00 00    	jne    10dc1f <_ZN4acos5audio12AudioManager10get_deviceEj+0x4f>
  10dc0b:	8b 45 f0             	mov    -0x10(%rbp),%eax
  10dc0e:	48 8b 04 c5 50 e1 16 	mov    0x16e150(,%rax,8),%rax
  10dc15:	00
  10dc16:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  10dc1a:	e9 1b 00 00 00       	jmp    10dc3a <_ZN4acos5audio12AudioManager10get_deviceEj+0x6a>
  10dc1f:	e9 00 00 00 00       	jmp    10dc24 <_ZN4acos5audio12AudioManager10get_deviceEj+0x54>
  10dc24:	8b 45 f0             	mov    -0x10(%rbp),%eax
  10dc27:	83 c0 01             	add    $0x1,%eax
  10dc2a:	89 45 f0             	mov    %eax,-0x10(%rbp)
  10dc2d:	e9 b0 ff ff ff       	jmp    10dbe2 <_ZN4acos5audio12AudioManager10get_deviceEj+0x12>
  10dc32:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  10dc39:	00
  10dc3a:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10dc3e:	48 83 c4 10          	add    $0x10,%rsp
  10dc42:	5d                   	pop    %rbp
  10dc43:	c3                   	ret
  10dc44:	66 66 66 2e 0f 1f 84 	data16 data16 cs nopw 0x0(%rax,%rax,1)
  10dc4b:	00 00 00 00 00

000000000010dc50 <_ZN4acos5audio12AudioManager12device_countEv>:
  10dc50:	55                   	push   %rbp
  10dc51:	48 89 e5             	mov    %rsp,%rbp
  10dc54:	8b 04 25 d0 e1 16 00 	mov    0x16e1d0,%eax
  10dc5b:	5d                   	pop    %rbp
  10dc5c:	c3                   	ret
  10dc5d:	0f 1f 00             	nopl   (%rax)

000000000010dc60 <_ZN4acos5audio11AudioDeviceC1EjPKcPNS0_11AudioDriverE>:
  10dc60:	55                   	push   %rbp
  10dc61:	48 89 e5             	mov    %rsp,%rbp
  10dc64:	48 83 ec 30          	sub    $0x30,%rsp
  10dc68:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10dc6c:	89 75 f4             	mov    %esi,-0xc(%rbp)
  10dc6f:	48 89 55 e8          	mov    %rdx,-0x18(%rbp)
  10dc73:	48 89 4d e0          	mov    %rcx,-0x20(%rbp)
  10dc77:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10dc7b:	8b 4d f4             	mov    -0xc(%rbp),%ecx
  10dc7e:	89 08                	mov    %ecx,(%rax)
  10dc80:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  10dc84:	48 89 48 08          	mov    %rcx,0x8(%rax)
  10dc88:	48 8b 4d e0          	mov    -0x20(%rbp),%rcx
  10dc8c:	48 89 48 10          	mov    %rcx,0x10(%rax)
  10dc90:	c6 45 d4 01          	movb   $0x1,-0x2c(%rbp)
  10dc94:	c6 45 d5 00          	movb   $0x0,-0x2b(%rbp)
  10dc98:	c6 45 d6 00          	movb   $0x0,-0x2a(%rbp)
  10dc9c:	c7 45 d8 80 bb 00 00 	movl   $0xbb80,-0x28(%rbp)
  10dca3:	c7 45 dc 02 00 00 00 	movl   $0x2,-0x24(%rbp)
  10dcaa:	48 8b 4d d4          	mov    -0x2c(%rbp),%rcx
  10dcae:	48 89 48 18          	mov    %rcx,0x18(%rax)
  10dcb2:	8b 4d dc             	mov    -0x24(%rbp),%ecx
  10dcb5:	89 48 20             	mov    %ecx,0x20(%rax)
  10dcb8:	48 83 c4 30          	add    $0x30,%rsp
  10dcbc:	5d                   	pop    %rbp
  10dcbd:	c3                   	ret
  10dcbe:	66 90                	xchg   %ax,%ax

000000000010dcc0 <_ZN4acos7drivers5audio11VirtIOSoundC1Ev>:
  10dcc0:	55                   	push   %rbp
  10dcc1:	48 89 e5             	mov    %rsp,%rbp
  10dcc4:	48 83 ec 10          	sub    $0x10,%rsp
  10dcc8:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10dccc:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  10dcd0:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  10dcd4:	e8 17 15 00 00       	call   10f1f0 <_ZN4acos5audio11AudioDriverC2Ev>
  10dcd9:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10dcdd:	48 b9 08 f8 10 00 00 	movabs $0x10f808,%rcx
  10dce4:	00 00 00
  10dce7:	48 83 c1 10          	add    $0x10,%rcx
  10dceb:	48 89 08             	mov    %rcx,(%rax)
  10dcee:	48 83 c4 10          	add    $0x10,%rsp
  10dcf2:	5d                   	pop    %rbp
  10dcf3:	c3                   	ret
  10dcf4:	66 66 66 2e 0f 1f 84 	data16 data16 cs nopw 0x0(%rax,%rax,1)
  10dcfb:	00 00 00 00 00

000000000010dd00 <_ZN4acos7drivers5audio11VirtIOSound10initializeEv>:
  10dd00:	55                   	push   %rbp
  10dd01:	48 89 e5             	mov    %rsp,%rbp
  10dd04:	50                   	push   %rax
  10dd05:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10dd09:	b0 01                	mov    $0x1,%al
  10dd0b:	24 01                	and    $0x1,%al
  10dd0d:	0f b6 c0             	movzbl %al,%eax
  10dd10:	48 83 c4 08          	add    $0x8,%rsp
  10dd14:	5d                   	pop    %rbp
  10dd15:	c3                   	ret
  10dd16:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
  10dd1d:	00 00 00

000000000010dd20 <_ZN4acos7drivers5audio11VirtIOSound8shutdownEv>:
  10dd20:	55                   	push   %rbp
  10dd21:	48 89 e5             	mov    %rsp,%rbp
  10dd24:	50                   	push   %rax
  10dd25:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10dd29:	48 83 c4 08          	add    $0x8,%rsp
  10dd2d:	5d                   	pop    %rbp
  10dd2e:	c3                   	ret
  10dd2f:	90                   	nop

000000000010dd30 <_ZN4acos7drivers5audio11VirtIOSound13create_streamEjRKNS_5audio12StreamConfigE>:
  10dd30:	55                   	push   %rbp
  10dd31:	48 89 e5             	mov    %rsp,%rbp
  10dd34:	48 83 ec 18          	sub    $0x18,%rsp
  10dd38:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10dd3c:	89 75 f4             	mov    %esi,-0xc(%rbp)
  10dd3f:	48 89 55 e8          	mov    %rdx,-0x18(%rbp)
  10dd43:	b0 01                	mov    $0x1,%al
  10dd45:	24 01                	and    $0x1,%al
  10dd47:	0f b6 c0             	movzbl %al,%eax
  10dd4a:	48 83 c4 18          	add    $0x18,%rsp
  10dd4e:	5d                   	pop    %rbp
  10dd4f:	c3                   	ret

000000000010dd50 <_ZN4acos7drivers5audio11VirtIOSound14destroy_streamEj>:
  10dd50:	55                   	push   %rbp
  10dd51:	48 89 e5             	mov    %rsp,%rbp
  10dd54:	48 83 ec 10          	sub    $0x10,%rsp
  10dd58:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10dd5c:	89 75 f4             	mov    %esi,-0xc(%rbp)
  10dd5f:	48 83 c4 10          	add    $0x10,%rsp
  10dd63:	5d                   	pop    %rbp
  10dd64:	c3                   	ret
  10dd65:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  10dd6c:	00 00 00 00

000000000010dd70 <_ZN4acos7drivers5audio11VirtIOSound13submit_bufferEjPKvm>:
  10dd70:	55                   	push   %rbp
  10dd71:	48 89 e5             	mov    %rsp,%rbp
  10dd74:	48 83 ec 20          	sub    $0x20,%rsp
  10dd78:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10dd7c:	89 75 f4             	mov    %esi,-0xc(%rbp)
  10dd7f:	48 89 55 e8          	mov    %rdx,-0x18(%rbp)
  10dd83:	48 89 4d e0          	mov    %rcx,-0x20(%rbp)
  10dd87:	b0 01                	mov    $0x1,%al
  10dd89:	24 01                	and    $0x1,%al
  10dd8b:	0f b6 c0             	movzbl %al,%eax
  10dd8e:	48 83 c4 20          	add    $0x20,%rsp
  10dd92:	5d                   	pop    %rbp
  10dd93:	c3                   	ret
  10dd94:	66 66 66 2e 0f 1f 84 	data16 data16 cs nopw 0x0(%rax,%rax,1)
  10dd9b:	00 00 00 00 00

000000000010dda0 <_ZN4acos7drivers5audio11VirtIOSound5pauseEj>:
  10dda0:	55                   	push   %rbp
  10dda1:	48 89 e5             	mov    %rsp,%rbp
  10dda4:	48 83 ec 10          	sub    $0x10,%rsp
  10dda8:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10ddac:	89 75 f4             	mov    %esi,-0xc(%rbp)
  10ddaf:	48 83 c4 10          	add    $0x10,%rsp
  10ddb3:	5d                   	pop    %rbp
  10ddb4:	c3                   	ret
  10ddb5:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  10ddbc:	00 00 00 00

000000000010ddc0 <_ZN4acos7drivers5audio11VirtIOSound6resumeEj>:
  10ddc0:	55                   	push   %rbp
  10ddc1:	48 89 e5             	mov    %rsp,%rbp
  10ddc4:	48 83 ec 10          	sub    $0x10,%rsp
  10ddc8:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10ddcc:	89 75 f4             	mov    %esi,-0xc(%rbp)
  10ddcf:	48 83 c4 10          	add    $0x10,%rsp
  10ddd3:	5d                   	pop    %rbp
  10ddd4:	c3                   	ret
  10ddd5:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  10dddc:	00 00 00 00

000000000010dde0 <_ZN4acos7drivers5audio11VirtIOSound4stopEj>:
  10dde0:	55                   	push   %rbp
  10dde1:	48 89 e5             	mov    %rsp,%rbp
  10dde4:	48 83 ec 10          	sub    $0x10,%rsp
  10dde8:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10ddec:	89 75 f4             	mov    %esi,-0xc(%rbp)
  10ddef:	48 83 c4 10          	add    $0x10,%rsp
  10ddf3:	5d                   	pop    %rbp
  10ddf4:	c3                   	ret
  10ddf5:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
  10ddfc:	00 00 00
  10ddff:	90                   	nop

000000000010de00 <_ZN4acos3smp10SmpManager4initEv>:
  10de00:	55                   	push   %rbp
  10de01:	48 89 e5             	mov    %rsp,%rbp
  10de04:	e8 87 00 00 00       	call   10de90 <_ZN4acos3smp3Cpu8init_bspEv>
  10de09:	5d                   	pop    %rbp
  10de0a:	c3                   	ret
  10de0b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

000000000010de10 <_ZN4acos3smp10SmpManager8boot_apsEv>:
  10de10:	55                   	push   %rbp
  10de11:	48 89 e5             	mov    %rsp,%rbp
  10de14:	48 83 ec 10          	sub    $0x10,%rsp
  10de18:	e8 73 14 00 00       	call   10f290 <_ZN4acos4arch6x86_644MADT9cpu_countEv>
  10de1d:	89 45 fc             	mov    %eax,-0x4(%rbp)
  10de20:	c7 45 f8 00 00 00 00 	movl   $0x0,-0x8(%rbp)
  10de27:	8b 45 f8             	mov    -0x8(%rbp),%eax
  10de2a:	3b 45 fc             	cmp    -0x4(%rbp),%eax
  10de2d:	0f 83 48 00 00 00    	jae    10de7b <_ZN4acos3smp10SmpManager8boot_apsEv+0x6b>
  10de33:	8b 7d f8             	mov    -0x8(%rbp),%edi
  10de36:	e8 65 14 00 00       	call   10f2a0 <_ZN4acos4arch6x86_644MADT11get_apic_idEj>
  10de3b:	89 45 f4             	mov    %eax,-0xc(%rbp)
  10de3e:	8b 45 f4             	mov    -0xc(%rbp),%eax
  10de41:	89 45 f0             	mov    %eax,-0x10(%rbp)
  10de44:	e8 17 06 00 00       	call   10e460 <_ZN4acos4arch6x86_649LocalApic6get_idEv>
  10de49:	89 c1                	mov    %eax,%ecx
  10de4b:	8b 45 f0             	mov    -0x10(%rbp),%eax
  10de4e:	39 c8                	cmp    %ecx,%eax
  10de50:	0f 84 12 00 00 00    	je     10de68 <_ZN4acos3smp10SmpManager8boot_apsEv+0x58>
  10de56:	8b 7d f4             	mov    -0xc(%rbp),%edi
  10de59:	31 f6                	xor    %esi,%esi
  10de5b:	e8 40 06 00 00       	call   10e4a0 <_ZN4acos4arch6x86_649LocalApic8send_ipiEjh>
  10de60:	8b 7d f4             	mov    -0xc(%rbp),%edi
  10de63:	e8 98 00 00 00       	call   10df00 <_ZN4acos3smp3Cpu7init_apEj>
  10de68:	e9 00 00 00 00       	jmp    10de6d <_ZN4acos3smp10SmpManager8boot_apsEv+0x5d>
  10de6d:	8b 45 f8             	mov    -0x8(%rbp),%eax
  10de70:	83 c0 01             	add    $0x1,%eax
  10de73:	89 45 f8             	mov    %eax,-0x8(%rbp)
  10de76:	e9 ac ff ff ff       	jmp    10de27 <_ZN4acos3smp10SmpManager8boot_apsEv+0x17>
  10de7b:	48 83 c4 10          	add    $0x10,%rsp
  10de7f:	5d                   	pop    %rbp
  10de80:	c3                   	ret
  10de81:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
  10de88:	00 00 00
  10de8b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

000000000010de90 <_ZN4acos3smp3Cpu8init_bspEv>:
  10de90:	55                   	push   %rbp
  10de91:	48 89 e5             	mov    %rsp,%rbp
  10de94:	48 83 ec 10          	sub    $0x10,%rsp
  10de98:	e8 c3 05 00 00       	call   10e460 <_ZN4acos4arch6x86_649LocalApic6get_idEv>
  10de9d:	89 04 25 10 e2 16 00 	mov    %eax,0x16e210
  10dea4:	c6 04 25 28 e2 16 00 	movb   $0x1,0x16e228
  10deab:	01
  10deac:	c7 04 25 2c e2 16 00 	movl   $0x0,0x16e22c
  10deb3:	00 00 00 00
  10deb7:	c7 04 25 00 f2 16 00 	movl   $0x1,0x16f200
  10debe:	01 00 00 00
  10dec2:	48 b8 00 e2 16 00 00 	movabs $0x16e200,%rax
  10dec9:	00 00 00
  10decc:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  10ded0:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10ded4:	89 45 f4             	mov    %eax,-0xc(%rbp)
  10ded7:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10dedb:	48 c1 e8 20          	shr    $0x20,%rax
  10dedf:	89 45 f0             	mov    %eax,-0x10(%rbp)
  10dee2:	8b 45 f4             	mov    -0xc(%rbp),%eax
  10dee5:	8b 55 f0             	mov    -0x10(%rbp),%edx
  10dee8:	b9 01 01 00 c0       	mov    $0xc0000101,%ecx
  10deed:	0f 30                	wrmsr
  10deef:	48 83 c4 10          	add    $0x10,%rsp
  10def3:	5d                   	pop    %rbp
  10def4:	c3                   	ret
  10def5:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  10defc:	00 00 00 00

000000000010df00 <_ZN4acos3smp3Cpu7init_apEj>:
  10df00:	55                   	push   %rbp
  10df01:	48 89 e5             	mov    %rsp,%rbp
  10df04:	48 83 ec 04          	sub    $0x4,%rsp
  10df08:	89 7d fc             	mov    %edi,-0x4(%rbp)
  10df0b:	83 3c 25 00 f2 16 00 	cmpl   $0x40,0x16f200
  10df12:	40
  10df13:	0f 83 73 00 00 00    	jae    10df8c <_ZN4acos3smp3Cpu7init_apEj+0x8c>
  10df19:	8b 4d fc             	mov    -0x4(%rbp),%ecx
  10df1c:	8b 04 25 00 f2 16 00 	mov    0x16f200,%eax
  10df23:	89 c2                	mov    %eax,%edx
  10df25:	48 b8 00 e2 16 00 00 	movabs $0x16e200,%rax
  10df2c:	00 00 00
  10df2f:	48 c1 e2 06          	shl    $0x6,%rdx
  10df33:	48 01 d0             	add    %rdx,%rax
  10df36:	89 48 10             	mov    %ecx,0x10(%rax)
  10df39:	8b 04 25 00 f2 16 00 	mov    0x16f200,%eax
  10df40:	89 c1                	mov    %eax,%ecx
  10df42:	48 b8 00 e2 16 00 00 	movabs $0x16e200,%rax
  10df49:	00 00 00
  10df4c:	48 c1 e1 06          	shl    $0x6,%rcx
  10df50:	48 01 c8             	add    %rcx,%rax
  10df53:	c6 40 28 00          	movb   $0x0,0x28(%rax)
  10df57:	8b 0c 25 00 f2 16 00 	mov    0x16f200,%ecx
  10df5e:	8b 04 25 00 f2 16 00 	mov    0x16f200,%eax
  10df65:	89 c2                	mov    %eax,%edx
  10df67:	48 b8 00 e2 16 00 00 	movabs $0x16e200,%rax
  10df6e:	00 00 00
  10df71:	48 c1 e2 06          	shl    $0x6,%rdx
  10df75:	48 01 d0             	add    %rdx,%rax
  10df78:	89 48 2c             	mov    %ecx,0x2c(%rax)
  10df7b:	8b 04 25 00 f2 16 00 	mov    0x16f200,%eax
  10df82:	83 c0 01             	add    $0x1,%eax
  10df85:	89 04 25 00 f2 16 00 	mov    %eax,0x16f200
  10df8c:	48 83 c4 04          	add    $0x4,%rsp
  10df90:	5d                   	pop    %rbp
  10df91:	c3                   	ret
  10df92:	66 66 66 66 66 2e 0f 	data16 data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
  10df99:	1f 84 00 00 00 00 00

000000000010dfa0 <_ZN4acos3smp3Cpu7currentEv>:
  10dfa0:	55                   	push   %rbp
  10dfa1:	48 89 e5             	mov    %rsp,%rbp
  10dfa4:	48 83 ec 10          	sub    $0x10,%rsp
  10dfa8:	b9 01 01 00 c0       	mov    $0xc0000101,%ecx
  10dfad:	0f 32                	rdmsr
  10dfaf:	89 45 fc             	mov    %eax,-0x4(%rbp)
  10dfb2:	89 55 f8             	mov    %edx,-0x8(%rbp)
  10dfb5:	8b 45 f8             	mov    -0x8(%rbp),%eax
  10dfb8:	48 c1 e0 20          	shl    $0x20,%rax
  10dfbc:	8b 4d fc             	mov    -0x4(%rbp),%ecx
  10dfbf:	48 09 c8             	or     %rcx,%rax
  10dfc2:	48 89 45 f0          	mov    %rax,-0x10(%rbp)
  10dfc6:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10dfca:	48 83 c4 10          	add    $0x10,%rsp
  10dfce:	5d                   	pop    %rbp
  10dfcf:	c3                   	ret

000000000010dfd0 <_ZN4acos3smp3Ipi4sendEjNS0_7IpiTypeE>:
  10dfd0:	55                   	push   %rbp
  10dfd1:	48 89 e5             	mov    %rsp,%rbp
  10dfd4:	48 83 ec 10          	sub    $0x10,%rsp
  10dfd8:	89 7d fc             	mov    %edi,-0x4(%rbp)
  10dfdb:	89 75 f8             	mov    %esi,-0x8(%rbp)
  10dfde:	8b 45 f8             	mov    -0x8(%rbp),%eax
  10dfe1:	0f b6 c0             	movzbl %al,%eax
  10dfe4:	83 c0 40             	add    $0x40,%eax
  10dfe7:	88 45 f7             	mov    %al,-0x9(%rbp)
  10dfea:	8b 7d fc             	mov    -0x4(%rbp),%edi
  10dfed:	0f b6 75 f7          	movzbl -0x9(%rbp),%esi
  10dff1:	e8 aa 04 00 00       	call   10e4a0 <_ZN4acos4arch6x86_649LocalApic8send_ipiEjh>
  10dff6:	48 83 c4 10          	add    $0x10,%rsp
  10dffa:	5d                   	pop    %rbp
  10dffb:	c3                   	ret
  10dffc:	0f 1f 40 00          	nopl   0x0(%rax)

000000000010e000 <_ZN4acos3smp3Ipi9broadcastENS0_7IpiTypeE>:
  10e000:	55                   	push   %rbp
  10e001:	48 89 e5             	mov    %rsp,%rbp
  10e004:	48 83 ec 18          	sub    $0x18,%rsp
  10e008:	89 7d fc             	mov    %edi,-0x4(%rbp)
  10e00b:	8b 45 fc             	mov    -0x4(%rbp),%eax
  10e00e:	0f b6 c0             	movzbl %al,%eax
  10e011:	83 c0 40             	add    $0x40,%eax
  10e014:	88 45 fb             	mov    %al,-0x5(%rbp)
  10e017:	b8 00 03 e0 fe       	mov    $0xfee00300,%eax
  10e01c:	48 89 45 f0          	mov    %rax,-0x10(%rbp)
  10e020:	0f b6 45 fb          	movzbl -0x5(%rbp),%eax
  10e024:	25 ff 00 00 00       	and    $0xff,%eax
  10e029:	0d 00 05 00 00       	or     $0x500,%eax
  10e02e:	0d 00 40 00 00       	or     $0x4000,%eax
  10e033:	0d 00 00 04 00       	or     $0x40000,%eax
  10e038:	89 45 ec             	mov    %eax,-0x14(%rbp)
  10e03b:	8b 4d ec             	mov    -0x14(%rbp),%ecx
  10e03e:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10e042:	89 08                	mov    %ecx,(%rax)
  10e044:	48 83 c4 18          	add    $0x18,%rsp
  10e048:	5d                   	pop    %rbp
  10e049:	c3                   	ret
  10e04a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

000000000010e050 <_ZN4acos3smp3Ipi6handleENS0_7IpiTypeE>:
  10e050:	55                   	push   %rbp
  10e051:	48 89 e5             	mov    %rsp,%rbp
  10e054:	48 83 ec 10          	sub    $0x10,%rsp
  10e058:	89 7d fc             	mov    %edi,-0x4(%rbp)
  10e05b:	8b 45 fc             	mov    -0x4(%rbp),%eax
  10e05e:	89 45 f8             	mov    %eax,-0x8(%rbp)
  10e061:	85 c0                	test   %eax,%eax
  10e063:	0f 84 27 00 00 00    	je     10e090 <_ZN4acos3smp3Ipi6handleENS0_7IpiTypeE+0x40>
  10e069:	e9 00 00 00 00       	jmp    10e06e <_ZN4acos3smp3Ipi6handleENS0_7IpiTypeE+0x1e>
  10e06e:	8b 45 f8             	mov    -0x8(%rbp),%eax
  10e071:	83 e8 01             	sub    $0x1,%eax
  10e074:	0f 84 26 00 00 00    	je     10e0a0 <_ZN4acos3smp3Ipi6handleENS0_7IpiTypeE+0x50>
  10e07a:	e9 00 00 00 00       	jmp    10e07f <_ZN4acos3smp3Ipi6handleENS0_7IpiTypeE+0x2f>
  10e07f:	8b 45 f8             	mov    -0x8(%rbp),%eax
  10e082:	83 e8 03             	sub    $0x3,%eax
  10e085:	0f 84 0f 00 00 00    	je     10e09a <_ZN4acos3smp3Ipi6handleENS0_7IpiTypeE+0x4a>
  10e08b:	e9 1b 00 00 00       	jmp    10e0ab <_ZN4acos3smp3Ipi6handleENS0_7IpiTypeE+0x5b>
  10e090:	e8 6b 86 ff ff       	call   106700 <_ZN4acos9scheduler8scheduleEv>
  10e095:	e9 16 00 00 00       	jmp    10e0b0 <_ZN4acos3smp3Ipi6handleENS0_7IpiTypeE+0x60>
  10e09a:	f4                   	hlt
  10e09b:	e9 10 00 00 00       	jmp    10e0b0 <_ZN4acos3smp3Ipi6handleENS0_7IpiTypeE+0x60>
  10e0a0:	0f 20 d8             	mov    %cr3,%rax
  10e0a3:	0f 22 d8             	mov    %rax,%cr3
  10e0a6:	e9 05 00 00 00       	jmp    10e0b0 <_ZN4acos3smp3Ipi6handleENS0_7IpiTypeE+0x60>
  10e0ab:	e9 00 00 00 00       	jmp    10e0b0 <_ZN4acos3smp3Ipi6handleENS0_7IpiTypeE+0x60>
  10e0b0:	48 83 c4 10          	add    $0x10,%rsp
  10e0b4:	5d                   	pop    %rbp
  10e0b5:	c3                   	ret
  10e0b6:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
  10e0bd:	00 00 00

000000000010e0c0 <_ZN4acos3smp12LoadBalancer7balanceEv>:
  10e0c0:	55                   	push   %rbp
  10e0c1:	48 89 e5             	mov    %rsp,%rbp
  10e0c4:	48 83 ec 40          	sub    $0x40,%rsp
  10e0c8:	e8 f3 11 00 00       	call   10f2c0 <_ZN4acos3smp3Cpu5countEv>
  10e0cd:	89 45 fc             	mov    %eax,-0x4(%rbp)
  10e0d0:	83 7d fc 01          	cmpl   $0x1,-0x4(%rbp)
  10e0d4:	0f 87 05 00 00 00    	ja     10e0df <_ZN4acos3smp12LoadBalancer7balanceEv+0x1f>
  10e0da:	e9 5c 01 00 00       	jmp    10e23b <_ZN4acos3smp12LoadBalancer7balanceEv+0x17b>
  10e0df:	c7 45 f8 ff ff ff ff 	movl   $0xffffffff,-0x8(%rbp)
  10e0e6:	c7 45 f4 00 00 00 00 	movl   $0x0,-0xc(%rbp)
  10e0ed:	c7 45 f0 00 00 00 00 	movl   $0x0,-0x10(%rbp)
  10e0f4:	8b 45 f0             	mov    -0x10(%rbp),%eax
  10e0f7:	3b 45 fc             	cmp    -0x4(%rbp),%eax
  10e0fa:	0f 83 40 00 00 00    	jae    10e140 <_ZN4acos3smp12LoadBalancer7balanceEv+0x80>
  10e100:	e8 3b 84 ff ff       	call   106540 <_ZN4acos9scheduler14get_run_queuesEv>
  10e105:	8b 4d f0             	mov    -0x10(%rbp),%ecx
  10e108:	48 6b c9 18          	imul   $0x18,%rcx,%rcx
  10e10c:	48 01 c8             	add    %rcx,%rax
  10e10f:	8b 40 10             	mov    0x10(%rax),%eax
  10e112:	89 45 ec             	mov    %eax,-0x14(%rbp)
  10e115:	8b 45 ec             	mov    -0x14(%rbp),%eax
  10e118:	3b 45 f8             	cmp    -0x8(%rbp),%eax
  10e11b:	0f 83 0c 00 00 00    	jae    10e12d <_ZN4acos3smp12LoadBalancer7balanceEv+0x6d>
  10e121:	8b 45 ec             	mov    -0x14(%rbp),%eax
  10e124:	89 45 f8             	mov    %eax,-0x8(%rbp)
  10e127:	8b 45 f0             	mov    -0x10(%rbp),%eax
  10e12a:	89 45 f4             	mov    %eax,-0xc(%rbp)
  10e12d:	e9 00 00 00 00       	jmp    10e132 <_ZN4acos3smp12LoadBalancer7balanceEv+0x72>
  10e132:	8b 45 f0             	mov    -0x10(%rbp),%eax
  10e135:	83 c0 01             	add    $0x1,%eax
  10e138:	89 45 f0             	mov    %eax,-0x10(%rbp)
  10e13b:	e9 b4 ff ff ff       	jmp    10e0f4 <_ZN4acos3smp12LoadBalancer7balanceEv+0x34>
  10e140:	c7 45 e8 00 00 00 00 	movl   $0x0,-0x18(%rbp)
  10e147:	8b 45 e8             	mov    -0x18(%rbp),%eax
  10e14a:	3b 45 fc             	cmp    -0x4(%rbp),%eax
  10e14d:	0f 83 e8 00 00 00    	jae    10e23b <_ZN4acos3smp12LoadBalancer7balanceEv+0x17b>
  10e153:	8b 45 e8             	mov    -0x18(%rbp),%eax
  10e156:	3b 45 f4             	cmp    -0xc(%rbp),%eax
  10e159:	0f 85 05 00 00 00    	jne    10e164 <_ZN4acos3smp12LoadBalancer7balanceEv+0xa4>
  10e15f:	e9 c9 00 00 00       	jmp    10e22d <_ZN4acos3smp12LoadBalancer7balanceEv+0x16d>
  10e164:	e8 d7 83 ff ff       	call   106540 <_ZN4acos9scheduler14get_run_queuesEv>
  10e169:	8b 4d e8             	mov    -0x18(%rbp),%ecx
  10e16c:	48 6b c9 18          	imul   $0x18,%rcx,%rcx
  10e170:	48 01 c8             	add    %rcx,%rax
  10e173:	8b 40 10             	mov    0x10(%rax),%eax
  10e176:	03 45 f8             	add    -0x8(%rbp),%eax
  10e179:	d1 e8                	shr    $1,%eax
  10e17b:	89 45 e4             	mov    %eax,-0x1c(%rbp)
  10e17e:	e8 bd 83 ff ff       	call   106540 <_ZN4acos9scheduler14get_run_queuesEv>
  10e183:	8b 4d e8             	mov    -0x18(%rbp),%ecx
  10e186:	48 6b c9 18          	imul   $0x18,%rcx,%rcx
  10e18a:	48 01 c8             	add    %rcx,%rax
  10e18d:	8b 48 10             	mov    0x10(%rax),%ecx
  10e190:	31 c0                	xor    %eax,%eax
  10e192:	3b 4d e4             	cmp    -0x1c(%rbp),%ecx
  10e195:	88 45 d7             	mov    %al,-0x29(%rbp)
  10e198:	0f 86 19 00 00 00    	jbe    10e1b7 <_ZN4acos3smp12LoadBalancer7balanceEv+0xf7>
  10e19e:	e8 9d 83 ff ff       	call   106540 <_ZN4acos9scheduler14get_run_queuesEv>
  10e1a3:	8b 4d e8             	mov    -0x18(%rbp),%ecx
  10e1a6:	48 6b c9 18          	imul   $0x18,%rcx,%rcx
  10e1aa:	48 01 c8             	add    %rcx,%rax
  10e1ad:	48 83 38 00          	cmpq   $0x0,(%rax)
  10e1b1:	0f 95 c0             	setne  %al
  10e1b4:	88 45 d7             	mov    %al,-0x29(%rbp)
  10e1b7:	8a 45 d7             	mov    -0x29(%rbp),%al
  10e1ba:	a8 01                	test   $0x1,%al
  10e1bc:	0f 85 05 00 00 00    	jne    10e1c7 <_ZN4acos3smp12LoadBalancer7balanceEv+0x107>
  10e1c2:	e9 61 00 00 00       	jmp    10e228 <_ZN4acos3smp12LoadBalancer7balanceEv+0x168>
  10e1c7:	e8 74 83 ff ff       	call   106540 <_ZN4acos9scheduler14get_run_queuesEv>
  10e1cc:	8b 4d e8             	mov    -0x18(%rbp),%ecx
  10e1cf:	48 6b c9 18          	imul   $0x18,%rcx,%rcx
  10e1d3:	48 01 c8             	add    %rcx,%rax
  10e1d6:	48 8b 00             	mov    (%rax),%rax
  10e1d9:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
  10e1dd:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
  10e1e1:	48 8b 40 38          	mov    0x38(%rax),%rax
  10e1e5:	48 89 45 c8          	mov    %rax,-0x38(%rbp)
  10e1e9:	e8 52 83 ff ff       	call   106540 <_ZN4acos9scheduler14get_run_queuesEv>
  10e1ee:	48 8b 4d c8          	mov    -0x38(%rbp),%rcx
  10e1f2:	8b 55 e8             	mov    -0x18(%rbp),%edx
  10e1f5:	48 6b d2 18          	imul   $0x18,%rdx,%rdx
  10e1f9:	48 01 d0             	add    %rdx,%rax
  10e1fc:	48 89 08             	mov    %rcx,(%rax)
  10e1ff:	e8 3c 83 ff ff       	call   106540 <_ZN4acos9scheduler14get_run_queuesEv>
  10e204:	8b 4d e8             	mov    -0x18(%rbp),%ecx
  10e207:	48 6b c9 18          	imul   $0x18,%rcx,%rcx
  10e20b:	48 01 c8             	add    %rcx,%rax
  10e20e:	8b 48 10             	mov    0x10(%rax),%ecx
  10e211:	83 c1 ff             	add    $0xffffffff,%ecx
  10e214:	89 48 10             	mov    %ecx,0x10(%rax)
  10e217:	8b 7d f4             	mov    -0xc(%rbp),%edi
  10e21a:	48 8b 75 d8          	mov    -0x28(%rbp),%rsi
  10e21e:	e8 bd 83 ff ff       	call   1065e0 <_ZN4acos9scheduler14enqueue_threadEjPNS0_6ThreadE>
  10e223:	e9 56 ff ff ff       	jmp    10e17e <_ZN4acos3smp12LoadBalancer7balanceEv+0xbe>
  10e228:	e9 00 00 00 00       	jmp    10e22d <_ZN4acos3smp12LoadBalancer7balanceEv+0x16d>
  10e22d:	8b 45 e8             	mov    -0x18(%rbp),%eax
  10e230:	83 c0 01             	add    $0x1,%eax
  10e233:	89 45 e8             	mov    %eax,-0x18(%rbp)
  10e236:	e9 0c ff ff ff       	jmp    10e147 <_ZN4acos3smp12LoadBalancer7balanceEv+0x87>
  10e23b:	48 83 c4 40          	add    $0x40,%rsp
  10e23f:	5d                   	pop    %rbp
  10e240:	c3                   	ret
  10e241:	66 66 66 66 66 66 2e 	data16 data16 data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
  10e248:	0f 1f 84 00 00 00 00
  10e24f:	00

000000000010e250 <_ZN4acos3smp12LoadBalancer20get_least_loaded_cpuEv>:
  10e250:	55                   	push   %rbp
  10e251:	48 89 e5             	mov    %rsp,%rbp
  10e254:	48 83 ec 20          	sub    $0x20,%rsp
  10e258:	e8 63 10 00 00       	call   10f2c0 <_ZN4acos3smp3Cpu5countEv>
  10e25d:	89 45 fc             	mov    %eax,-0x4(%rbp)
  10e260:	c7 45 f8 ff ff ff ff 	movl   $0xffffffff,-0x8(%rbp)
  10e267:	c7 45 f4 00 00 00 00 	movl   $0x0,-0xc(%rbp)
  10e26e:	c7 45 f0 00 00 00 00 	movl   $0x0,-0x10(%rbp)
  10e275:	8b 45 f0             	mov    -0x10(%rbp),%eax
  10e278:	3b 45 fc             	cmp    -0x4(%rbp),%eax
  10e27b:	0f 83 40 00 00 00    	jae    10e2c1 <_ZN4acos3smp12LoadBalancer20get_least_loaded_cpuEv+0x71>
  10e281:	e8 ba 82 ff ff       	call   106540 <_ZN4acos9scheduler14get_run_queuesEv>
  10e286:	8b 4d f0             	mov    -0x10(%rbp),%ecx
  10e289:	48 6b c9 18          	imul   $0x18,%rcx,%rcx
  10e28d:	48 01 c8             	add    %rcx,%rax
  10e290:	8b 40 10             	mov    0x10(%rax),%eax
  10e293:	89 45 ec             	mov    %eax,-0x14(%rbp)
  10e296:	8b 45 ec             	mov    -0x14(%rbp),%eax
  10e299:	3b 45 f8             	cmp    -0x8(%rbp),%eax
  10e29c:	0f 83 0c 00 00 00    	jae    10e2ae <_ZN4acos3smp12LoadBalancer20get_least_loaded_cpuEv+0x5e>
  10e2a2:	8b 45 ec             	mov    -0x14(%rbp),%eax
  10e2a5:	89 45 f8             	mov    %eax,-0x8(%rbp)
  10e2a8:	8b 45 f0             	mov    -0x10(%rbp),%eax
  10e2ab:	89 45 f4             	mov    %eax,-0xc(%rbp)
  10e2ae:	e9 00 00 00 00       	jmp    10e2b3 <_ZN4acos3smp12LoadBalancer20get_least_loaded_cpuEv+0x63>
  10e2b3:	8b 45 f0             	mov    -0x10(%rbp),%eax
  10e2b6:	83 c0 01             	add    $0x1,%eax
  10e2b9:	89 45 f0             	mov    %eax,-0x10(%rbp)
  10e2bc:	e9 b4 ff ff ff       	jmp    10e275 <_ZN4acos3smp12LoadBalancer20get_least_loaded_cpuEv+0x25>
  10e2c1:	8b 45 f4             	mov    -0xc(%rbp),%eax
  10e2c4:	48 83 c4 20          	add    $0x20,%rsp
  10e2c8:	5d                   	pop    %rbp
  10e2c9:	c3                   	ret
  10e2ca:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

000000000010e2d0 <_ZN4acos4arch6x86_644MADT5parseEPv>:
  10e2d0:	55                   	push   %rbp
  10e2d1:	48 89 e5             	mov    %rsp,%rbp
  10e2d4:	48 83 ec 30          	sub    $0x30,%rsp
  10e2d8:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  10e2dc:	48 83 7d f0 00       	cmpq   $0x0,-0x10(%rbp)
  10e2e1:	0f 85 09 00 00 00    	jne    10e2f0 <_ZN4acos4arch6x86_644MADT5parseEPv+0x20>
  10e2e7:	c6 45 ff 00          	movb   $0x0,-0x1(%rbp)
  10e2eb:	e9 ca 00 00 00       	jmp    10e3ba <_ZN4acos4arch6x86_644MADT5parseEPv+0xea>
  10e2f0:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10e2f4:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
  10e2f8:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  10e2fc:	48 83 c0 2c          	add    $0x2c,%rax
  10e300:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  10e304:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10e308:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  10e30c:	8b 49 04             	mov    0x4(%rcx),%ecx
  10e30f:	48 01 c8             	add    %rcx,%rax
  10e312:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
  10e316:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  10e31a:	48 3b 45 d8          	cmp    -0x28(%rbp),%rax
  10e31e:	0f 83 92 00 00 00    	jae    10e3b6 <_ZN4acos4arch6x86_644MADT5parseEPv+0xe6>
  10e324:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  10e328:	8a 00                	mov    (%rax),%al
  10e32a:	88 45 d7             	mov    %al,-0x29(%rbp)
  10e32d:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  10e331:	8a 40 01             	mov    0x1(%rax),%al
  10e334:	88 45 d6             	mov    %al,-0x2a(%rbp)
  10e337:	0f b6 45 d7          	movzbl -0x29(%rbp),%eax
  10e33b:	83 f8 00             	cmp    $0x0,%eax
  10e33e:	0f 85 5b 00 00 00    	jne    10e39f <_ZN4acos4arch6x86_644MADT5parseEPv+0xcf>
  10e344:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  10e348:	8a 40 03             	mov    0x3(%rax),%al
  10e34b:	88 45 d5             	mov    %al,-0x2b(%rbp)
  10e34e:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  10e352:	8b 40 04             	mov    0x4(%rax),%eax
  10e355:	89 45 d0             	mov    %eax,-0x30(%rbp)
  10e358:	8b 45 d0             	mov    -0x30(%rbp),%eax
  10e35b:	83 e0 01             	and    $0x1,%eax
  10e35e:	83 f8 00             	cmp    $0x0,%eax
  10e361:	0f 84 33 00 00 00    	je     10e39a <_ZN4acos4arch6x86_644MADT5parseEPv+0xca>
  10e367:	83 3c 25 10 f3 16 00 	cmpl   $0x40,0x16f310
  10e36e:	40
  10e36f:	0f 83 20 00 00 00    	jae    10e395 <_ZN4acos4arch6x86_644MADT5parseEPv+0xc5>
  10e375:	0f b6 4d d5          	movzbl -0x2b(%rbp),%ecx
  10e379:	8b 04 25 10 f3 16 00 	mov    0x16f310,%eax
  10e380:	89 c2                	mov    %eax,%edx
  10e382:	83 c2 01             	add    $0x1,%edx
  10e385:	89 14 25 10 f3 16 00 	mov    %edx,0x16f310
  10e38c:	89 c0                	mov    %eax,%eax
  10e38e:	89 0c 85 10 f2 16 00 	mov    %ecx,0x16f210(,%rax,4)
  10e395:	e9 00 00 00 00       	jmp    10e39a <_ZN4acos4arch6x86_644MADT5parseEPv+0xca>
  10e39a:	e9 00 00 00 00       	jmp    10e39f <_ZN4acos4arch6x86_644MADT5parseEPv+0xcf>
  10e39f:	0f b6 4d d6          	movzbl -0x2a(%rbp),%ecx
  10e3a3:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  10e3a7:	48 63 c9             	movslq %ecx,%rcx
  10e3aa:	48 01 c8             	add    %rcx,%rax
  10e3ad:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  10e3b1:	e9 60 ff ff ff       	jmp    10e316 <_ZN4acos4arch6x86_644MADT5parseEPv+0x46>
  10e3b6:	c6 45 ff 01          	movb   $0x1,-0x1(%rbp)
  10e3ba:	8a 45 ff             	mov    -0x1(%rbp),%al
  10e3bd:	24 01                	and    $0x1,%al
  10e3bf:	0f b6 c0             	movzbl %al,%eax
  10e3c2:	48 83 c4 30          	add    $0x30,%rsp
  10e3c6:	5d                   	pop    %rbp
  10e3c7:	c3                   	ret
  10e3c8:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  10e3cf:	00

000000000010e3d0 <_ZN4acos4arch6x86_649LocalApic5writeEjj>:
  10e3d0:	55                   	push   %rbp
  10e3d1:	48 89 e5             	mov    %rsp,%rbp
  10e3d4:	50                   	push   %rax
  10e3d5:	89 7d fc             	mov    %edi,-0x4(%rbp)
  10e3d8:	89 75 f8             	mov    %esi,-0x8(%rbp)
  10e3db:	8b 4d f8             	mov    -0x8(%rbp),%ecx
  10e3de:	48 8b 04 25 18 45 15 	mov    0x154518,%rax
  10e3e5:	00
  10e3e6:	8b 55 fc             	mov    -0x4(%rbp),%edx
  10e3e9:	48 01 d0             	add    %rdx,%rax
  10e3ec:	89 08                	mov    %ecx,(%rax)
  10e3ee:	48 83 c4 08          	add    $0x8,%rsp
  10e3f2:	5d                   	pop    %rbp
  10e3f3:	c3                   	ret
  10e3f4:	66 66 66 2e 0f 1f 84 	data16 data16 cs nopw 0x0(%rax,%rax,1)
  10e3fb:	00 00 00 00 00

000000000010e400 <_ZN4acos4arch6x86_649LocalApic4readEj>:
  10e400:	55                   	push   %rbp
  10e401:	48 89 e5             	mov    %rsp,%rbp
  10e404:	48 83 ec 04          	sub    $0x4,%rsp
  10e408:	89 7d fc             	mov    %edi,-0x4(%rbp)
  10e40b:	48 8b 04 25 18 45 15 	mov    0x154518,%rax
  10e412:	00
  10e413:	8b 4d fc             	mov    -0x4(%rbp),%ecx
  10e416:	48 01 c8             	add    %rcx,%rax
  10e419:	8b 00                	mov    (%rax),%eax
  10e41b:	48 83 c4 04          	add    $0x4,%rsp
  10e41f:	5d                   	pop    %rbp
  10e420:	c3                   	ret
  10e421:	66 66 66 66 66 66 2e 	data16 data16 data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
  10e428:	0f 1f 84 00 00 00 00
  10e42f:	00

000000000010e430 <_ZN4acos4arch6x86_649LocalApic4initEv>:
  10e430:	55                   	push   %rbp
  10e431:	48 89 e5             	mov    %rsp,%rbp
  10e434:	bf f0 00 00 00       	mov    $0xf0,%edi
  10e439:	e8 c2 ff ff ff       	call   10e400 <_ZN4acos4arch6x86_649LocalApic4readEj>
  10e43e:	89 c6                	mov    %eax,%esi
  10e440:	81 ce ff 01 00 00    	or     $0x1ff,%esi
  10e446:	bf f0 00 00 00       	mov    $0xf0,%edi
  10e44b:	e8 80 ff ff ff       	call   10e3d0 <_ZN4acos4arch6x86_649LocalApic5writeEjj>
  10e450:	5d                   	pop    %rbp
  10e451:	c3                   	ret
  10e452:	66 66 66 66 66 2e 0f 	data16 data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
  10e459:	1f 84 00 00 00 00 00

000000000010e460 <_ZN4acos4arch6x86_649LocalApic6get_idEv>:
  10e460:	55                   	push   %rbp
  10e461:	48 89 e5             	mov    %rsp,%rbp
  10e464:	bf 20 00 00 00       	mov    $0x20,%edi
  10e469:	e8 92 ff ff ff       	call   10e400 <_ZN4acos4arch6x86_649LocalApic4readEj>
  10e46e:	c1 e8 18             	shr    $0x18,%eax
  10e471:	5d                   	pop    %rbp
  10e472:	c3                   	ret
  10e473:	66 66 66 66 2e 0f 1f 	data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
  10e47a:	84 00 00 00 00 00

000000000010e480 <_ZN4acos4arch6x86_649LocalApic3eoiEv>:
  10e480:	55                   	push   %rbp
  10e481:	48 89 e5             	mov    %rsp,%rbp
  10e484:	bf b0 00 00 00       	mov    $0xb0,%edi
  10e489:	31 f6                	xor    %esi,%esi
  10e48b:	e8 40 ff ff ff       	call   10e3d0 <_ZN4acos4arch6x86_649LocalApic5writeEjj>
  10e490:	5d                   	pop    %rbp
  10e491:	c3                   	ret
  10e492:	66 66 66 66 66 2e 0f 	data16 data16 data16 data16 cs nopw 0x0(%rax,%rax,1)
  10e499:	1f 84 00 00 00 00 00

000000000010e4a0 <_ZN4acos4arch6x86_649LocalApic8send_ipiEjh>:
  10e4a0:	55                   	push   %rbp
  10e4a1:	48 89 e5             	mov    %rsp,%rbp
  10e4a4:	48 83 ec 10          	sub    $0x10,%rsp
  10e4a8:	40 88 f0             	mov    %sil,%al
  10e4ab:	89 7d fc             	mov    %edi,-0x4(%rbp)
  10e4ae:	88 45 fb             	mov    %al,-0x5(%rbp)
  10e4b1:	8b 75 fc             	mov    -0x4(%rbp),%esi
  10e4b4:	c1 e6 18             	shl    $0x18,%esi
  10e4b7:	bf 10 03 00 00       	mov    $0x310,%edi
  10e4bc:	e8 0f ff ff ff       	call   10e3d0 <_ZN4acos4arch6x86_649LocalApic5writeEjj>
  10e4c1:	0f b6 75 fb          	movzbl -0x5(%rbp),%esi
  10e4c5:	83 ce 00             	or     $0x0,%esi
  10e4c8:	bf 00 03 00 00       	mov    $0x300,%edi
  10e4cd:	e8 fe fe ff ff       	call   10e3d0 <_ZN4acos4arch6x86_649LocalApic5writeEjj>
  10e4d2:	48 83 c4 10          	add    $0x10,%rsp
  10e4d6:	5d                   	pop    %rbp
  10e4d7:	c3                   	ret
  10e4d8:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
  10e4df:	00

000000000010e4e0 <_ZN4acos4arch6x86_646IoApic5writeEjj>:
  10e4e0:	55                   	push   %rbp
  10e4e1:	48 89 e5             	mov    %rsp,%rbp
  10e4e4:	50                   	push   %rax
  10e4e5:	89 7d fc             	mov    %edi,-0x4(%rbp)
  10e4e8:	89 75 f8             	mov    %esi,-0x8(%rbp)
  10e4eb:	8b 4d fc             	mov    -0x4(%rbp),%ecx
  10e4ee:	48 8b 04 25 20 45 15 	mov    0x154520,%rax
  10e4f5:	00
  10e4f6:	89 08                	mov    %ecx,(%rax)
  10e4f8:	8b 4d f8             	mov    -0x8(%rbp),%ecx
  10e4fb:	48 8b 04 25 20 45 15 	mov    0x154520,%rax
  10e502:	00
  10e503:	89 48 10             	mov    %ecx,0x10(%rax)
  10e506:	48 83 c4 08          	add    $0x8,%rsp
  10e50a:	5d                   	pop    %rbp
  10e50b:	c3                   	ret
  10e50c:	0f 1f 40 00          	nopl   0x0(%rax)

000000000010e510 <_ZN4acos4arch6x86_646IoApic4readEj>:
  10e510:	55                   	push   %rbp
  10e511:	48 89 e5             	mov    %rsp,%rbp
  10e514:	48 83 ec 04          	sub    $0x4,%rsp
  10e518:	89 7d fc             	mov    %edi,-0x4(%rbp)
  10e51b:	8b 4d fc             	mov    -0x4(%rbp),%ecx
  10e51e:	48 8b 04 25 20 45 15 	mov    0x154520,%rax
  10e525:	00
  10e526:	89 08                	mov    %ecx,(%rax)
  10e528:	48 8b 04 25 20 45 15 	mov    0x154520,%rax
  10e52f:	00
  10e530:	8b 40 10             	mov    0x10(%rax),%eax
  10e533:	48 83 c4 04          	add    $0x4,%rsp
  10e537:	5d                   	pop    %rbp
  10e538:	c3                   	ret
  10e539:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

000000000010e540 <_ZN4acos4arch6x86_646IoApic4initEm>:
  10e540:	55                   	push   %rbp
  10e541:	48 89 e5             	mov    %rsp,%rbp
  10e544:	50                   	push   %rax
  10e545:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10e549:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10e54d:	48 89 04 25 20 45 15 	mov    %rax,0x154520
  10e554:	00
  10e555:	48 83 c4 08          	add    $0x8,%rsp
  10e559:	5d                   	pop    %rbp
  10e55a:	c3                   	ret
  10e55b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

000000000010e560 <_ZN4acos4arch6x86_646IoApic7set_irqEhhj>:
  10e560:	55                   	push   %rbp
  10e561:	48 89 e5             	mov    %rsp,%rbp
  10e564:	48 83 ec 10          	sub    $0x10,%rsp
  10e568:	40 88 f0             	mov    %sil,%al
  10e56b:	40 88 f9             	mov    %dil,%cl
  10e56e:	88 4d ff             	mov    %cl,-0x1(%rbp)
  10e571:	88 45 fe             	mov    %al,-0x2(%rbp)
  10e574:	89 55 f8             	mov    %edx,-0x8(%rbp)
  10e577:	0f b6 45 fe          	movzbl -0x2(%rbp),%eax
  10e57b:	25 ff 00 00 00       	and    $0xff,%eax
  10e580:	89 45 f4             	mov    %eax,-0xc(%rbp)
  10e583:	8b 45 f8             	mov    -0x8(%rbp),%eax
  10e586:	c1 e0 18             	shl    $0x18,%eax
  10e589:	89 45 f0             	mov    %eax,-0x10(%rbp)
  10e58c:	0f b6 7d ff          	movzbl -0x1(%rbp),%edi
  10e590:	d1 e7                	shl    $1,%edi
  10e592:	83 c7 10             	add    $0x10,%edi
  10e595:	8b 75 f4             	mov    -0xc(%rbp),%esi
  10e598:	e8 43 ff ff ff       	call   10e4e0 <_ZN4acos4arch6x86_646IoApic5writeEjj>
  10e59d:	0f b6 7d ff          	movzbl -0x1(%rbp),%edi
  10e5a1:	d1 e7                	shl    $1,%edi
  10e5a3:	83 c7 11             	add    $0x11,%edi
  10e5a6:	8b 75 f0             	mov    -0x10(%rbp),%esi
  10e5a9:	e8 32 ff ff ff       	call   10e4e0 <_ZN4acos4arch6x86_646IoApic5writeEjj>
  10e5ae:	48 83 c4 10          	add    $0x10,%rsp
  10e5b2:	5d                   	pop    %rbp
  10e5b3:	c3                   	ret

000000000010e5b4 <context_switch>:
  10e5b4:	55                   	push   %rbp
  10e5b5:	53                   	push   %rbx
  10e5b6:	41 54                	push   %r12
  10e5b8:	41 55                	push   %r13
  10e5ba:	41 56                	push   %r14
  10e5bc:	41 57                	push   %r15
  10e5be:	48 89 27             	mov    %rsp,(%rdi)
  10e5c1:	48 89 f4             	mov    %rsi,%rsp
  10e5c4:	41 5f                	pop    %r15
  10e5c6:	41 5e                	pop    %r14
  10e5c8:	41 5d                	pop    %r13
  10e5ca:	41 5c                	pop    %r12
  10e5cc:	5b                   	pop    %rbx
  10e5cd:	5d                   	pop    %rbp
  10e5ce:	c3                   	ret

000000000010e5cf <enter_user_mode>:
  10e5cf:	48 89 f4             	mov    %rsi,%rsp
  10e5d2:	6a 23                	push   $0x23
  10e5d4:	56                   	push   %rsi
  10e5d5:	9c                   	pushf
  10e5d6:	58                   	pop    %rax
  10e5d7:	48 0d 00 02 00 00    	or     $0x200,%rax
  10e5dd:	50                   	push   %rax
  10e5de:	6a 1b                	push   $0x1b
  10e5e0:	57                   	push   %rdi
  10e5e1:	48 31 c0             	xor    %rax,%rax
  10e5e4:	48 31 db             	xor    %rbx,%rbx
  10e5e7:	48 31 c9             	xor    %rcx,%rcx
  10e5ea:	48 31 d2             	xor    %rdx,%rdx
  10e5ed:	48 31 f6             	xor    %rsi,%rsi
  10e5f0:	48 31 ff             	xor    %rdi,%rdi
  10e5f3:	48 31 ed             	xor    %rbp,%rbp
  10e5f6:	4d 31 c0             	xor    %r8,%r8
  10e5f9:	4d 31 c9             	xor    %r9,%r9
  10e5fc:	4d 31 d2             	xor    %r10,%r10
  10e5ff:	4d 31 db             	xor    %r11,%r11
  10e602:	4d 31 e4             	xor    %r12,%r12
  10e605:	4d 31 ed             	xor    %r13,%r13
  10e608:	4d 31 f6             	xor    %r14,%r14
  10e60b:	4d 31 ff             	xor    %r15,%r15
  10e60e:	48 cf                	iretq

000000000010e610 <syscall_entry>:
  10e610:	0f 01 f8             	swapgs
  10e613:	65 48 89 24 25 00 00 	mov    %rsp,%gs:0x0
  10e61a:	00 00
  10e61c:	65 48 8b 24 25 08 00 	mov    %gs:0x8,%rsp
  10e623:	00 00
  10e625:	51                   	push   %rcx
  10e626:	41 53                	push   %r11
  10e628:	4c 89 d1             	mov    %r10,%rcx
  10e62b:	e8 c0 5a ff ff       	call   1040f0 <syscall_dispatch>
  10e630:	41 5b                	pop    %r11
  10e632:	59                   	pop    %rcx
  10e633:	65 48 8b 24 25 00 00 	mov    %gs:0x0,%rsp
  10e63a:	00 00
  10e63c:	0f 01 f8             	swapgs
  10e63f:	48 0f 07             	sysretq
  10e642:	66 90                	xchg   %ax,%ax

000000000010e644 <_start>:
  10e644:	fa                   	cli
  10e645:	48 c7 c4 20 33 17 00 	mov    $0x173320,%rsp
  10e64c:	e8 af b5 ff ff       	call   109c00 <kernelMain>

000000000010e651 <_halt>:
  10e651:	f4                   	hlt
  10e652:	eb fd                	jmp    10e651 <_halt>

Disassembly of section .text._ZN4acos7storage11BlockDeviceC2Ev:

000000000010e660 <_ZN4acos7storage11BlockDeviceC2Ev>:
  10e660:	55                   	push   %rbp
  10e661:	48 89 e5             	mov    %rsp,%rbp
  10e664:	50                   	push   %rax
  10e665:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10e669:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10e66d:	48 b9 68 f8 10 00 00 	movabs $0x10f868,%rcx
  10e674:	00 00 00
  10e677:	48 83 c1 10          	add    $0x10,%rcx
  10e67b:	48 89 08             	mov    %rcx,(%rax)
  10e67e:	48 83 c4 08          	add    $0x8,%rsp
  10e682:	5d                   	pop    %rbp
  10e683:	c3                   	ret

Disassembly of section .text._ZN4acos7storage8AHCIPortD2Ev:

000000000010e690 <_ZN4acos7storage8AHCIPortD2Ev>:
  10e690:	55                   	push   %rbp
  10e691:	48 89 e5             	mov    %rsp,%rbp
  10e694:	48 83 ec 10          	sub    $0x10,%rsp
  10e698:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10e69c:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  10e6a0:	e8 7b 00 00 00       	call   10e720 <_ZN4acos7storage11BlockDeviceD2Ev>
  10e6a5:	48 83 c4 10          	add    $0x10,%rsp
  10e6a9:	5d                   	pop    %rbp
  10e6aa:	c3                   	ret

Disassembly of section .text._ZN4acos7storage8AHCIPortD0Ev:

000000000010e6b0 <_ZN4acos7storage8AHCIPortD0Ev>:
  10e6b0:	55                   	push   %rbp
  10e6b1:	48 89 e5             	mov    %rsp,%rbp
  10e6b4:	48 83 ec 10          	sub    $0x10,%rsp
  10e6b8:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10e6bc:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  10e6c0:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  10e6c4:	e8 c7 ff ff ff       	call   10e690 <_ZN4acos7storage8AHCIPortD2Ev>
  10e6c9:	48 8b 7d f0          	mov    -0x10(%rbp),%rdi
  10e6cd:	e8 5e 1d ff ff       	call   100430 <_ZdlPv>
  10e6d2:	48 83 c4 10          	add    $0x10,%rsp
  10e6d6:	5d                   	pop    %rbp
  10e6d7:	c3                   	ret

Disassembly of section .text._ZNK4acos7storage8AHCIPort10block_sizeEv:

000000000010e6e0 <_ZNK4acos7storage8AHCIPort10block_sizeEv>:
  10e6e0:	55                   	push   %rbp
  10e6e1:	48 89 e5             	mov    %rsp,%rbp
  10e6e4:	50                   	push   %rax
  10e6e5:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10e6e9:	b8 00 02 00 00       	mov    $0x200,%eax
  10e6ee:	48 83 c4 08          	add    $0x8,%rsp
  10e6f2:	5d                   	pop    %rbp
  10e6f3:	c3                   	ret

Disassembly of section .text._ZNK4acos7storage8AHCIPort8capacityEv:

000000000010e700 <_ZNK4acos7storage8AHCIPort8capacityEv>:
  10e700:	55                   	push   %rbp
  10e701:	48 89 e5             	mov    %rsp,%rbp
  10e704:	50                   	push   %rax
  10e705:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10e709:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10e70d:	48 8b 40 18          	mov    0x18(%rax),%rax
  10e711:	48 83 c4 08          	add    $0x8,%rsp
  10e715:	5d                   	pop    %rbp
  10e716:	c3                   	ret

Disassembly of section .text._ZN4acos7storage11BlockDeviceD2Ev:

000000000010e720 <_ZN4acos7storage11BlockDeviceD2Ev>:
  10e720:	55                   	push   %rbp
  10e721:	48 89 e5             	mov    %rsp,%rbp
  10e724:	50                   	push   %rax
  10e725:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10e729:	48 83 c4 08          	add    $0x8,%rsp
  10e72d:	5d                   	pop    %rbp
  10e72e:	c3                   	ret

Disassembly of section .text._ZN4acos7storage11BlockDeviceD0Ev:

000000000010e730 <_ZN4acos7storage11BlockDeviceD0Ev>:
  10e730:	55                   	push   %rbp
  10e731:	48 89 e5             	mov    %rsp,%rbp
  10e734:	50                   	push   %rax
  10e735:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10e739:	0f 0b                	ud2

Disassembly of section .text._ZN4acos7storage9PartitionD2Ev:

000000000010e740 <_ZN4acos7storage9PartitionD2Ev>:
  10e740:	55                   	push   %rbp
  10e741:	48 89 e5             	mov    %rsp,%rbp
  10e744:	48 83 ec 10          	sub    $0x10,%rsp
  10e748:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10e74c:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  10e750:	e8 cb ff ff ff       	call   10e720 <_ZN4acos7storage11BlockDeviceD2Ev>
  10e755:	48 83 c4 10          	add    $0x10,%rsp
  10e759:	5d                   	pop    %rbp
  10e75a:	c3                   	ret

Disassembly of section .text._ZN4acos7storage9PartitionD0Ev:

000000000010e760 <_ZN4acos7storage9PartitionD0Ev>:
  10e760:	55                   	push   %rbp
  10e761:	48 89 e5             	mov    %rsp,%rbp
  10e764:	48 83 ec 10          	sub    $0x10,%rsp
  10e768:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10e76c:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  10e770:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  10e774:	e8 c7 ff ff ff       	call   10e740 <_ZN4acos7storage9PartitionD2Ev>
  10e779:	48 8b 7d f0          	mov    -0x10(%rbp),%rdi
  10e77d:	e8 ae 1c ff ff       	call   100430 <_ZdlPv>
  10e782:	48 83 c4 10          	add    $0x10,%rsp
  10e786:	5d                   	pop    %rbp
  10e787:	c3                   	ret

Disassembly of section .text._ZNK4acos7storage9Partition10block_sizeEv:

000000000010e790 <_ZNK4acos7storage9Partition10block_sizeEv>:
  10e790:	55                   	push   %rbp
  10e791:	48 89 e5             	mov    %rsp,%rbp
  10e794:	48 83 ec 10          	sub    $0x10,%rsp
  10e798:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10e79c:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10e7a0:	48 8b 78 08          	mov    0x8(%rax),%rdi
  10e7a4:	48 8b 07             	mov    (%rdi),%rax
  10e7a7:	ff 50 28             	call   *0x28(%rax)
  10e7aa:	48 83 c4 10          	add    $0x10,%rsp
  10e7ae:	5d                   	pop    %rbp
  10e7af:	c3                   	ret

Disassembly of section .text._ZNK4acos7storage9Partition8capacityEv:

000000000010e7b0 <_ZNK4acos7storage9Partition8capacityEv>:
  10e7b0:	55                   	push   %rbp
  10e7b1:	48 89 e5             	mov    %rsp,%rbp
  10e7b4:	48 83 ec 10          	sub    $0x10,%rsp
  10e7b8:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10e7bc:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  10e7c0:	48 8b 47 18          	mov    0x18(%rdi),%rax
  10e7c4:	48 89 45 f0          	mov    %rax,-0x10(%rbp)
  10e7c8:	48 8b 07             	mov    (%rdi),%rax
  10e7cb:	ff 50 28             	call   *0x28(%rax)
  10e7ce:	48 89 c1             	mov    %rax,%rcx
  10e7d1:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10e7d5:	48 0f af c1          	imul   %rcx,%rax
  10e7d9:	48 83 c4 10          	add    $0x10,%rsp
  10e7dd:	5d                   	pop    %rbp
  10e7de:	c3                   	ret

Disassembly of section .text._ZN4acos3vfs10FileSystemC2Ev:

000000000010e7e0 <_ZN4acos3vfs10FileSystemC2Ev>:
  10e7e0:	55                   	push   %rbp
  10e7e1:	48 89 e5             	mov    %rsp,%rbp
  10e7e4:	50                   	push   %rax
  10e7e5:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10e7e9:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10e7ed:	48 b9 40 fb 10 00 00 	movabs $0x10fb40,%rcx
  10e7f4:	00 00 00
  10e7f7:	48 83 c1 10          	add    $0x10,%rcx
  10e7fb:	48 89 08             	mov    %rcx,(%rax)
  10e7fe:	48 83 c4 08          	add    $0x8,%rsp
  10e802:	5d                   	pop    %rbp
  10e803:	c3                   	ret

Disassembly of section .text._ZN4acos7storage15FAT32FileSystemC2Ev:

000000000010e810 <_ZN4acos7storage15FAT32FileSystemC2Ev>:
  10e810:	55                   	push   %rbp
  10e811:	48 89 e5             	mov    %rsp,%rbp
  10e814:	48 83 ec 10          	sub    $0x10,%rsp
  10e818:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10e81c:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  10e820:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  10e824:	e8 b7 ff ff ff       	call   10e7e0 <_ZN4acos3vfs10FileSystemC2Ev>
  10e829:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10e82d:	48 b9 60 f3 10 00 00 	movabs $0x10f360,%rcx
  10e834:	00 00 00
  10e837:	48 83 c1 10          	add    $0x10,%rcx
  10e83b:	48 89 08             	mov    %rcx,(%rax)
  10e83e:	48 c7 40 08 00 00 00 	movq   $0x0,0x8(%rax)
  10e845:	00
  10e846:	48 83 c4 10          	add    $0x10,%rsp
  10e84a:	5d                   	pop    %rbp
  10e84b:	c3                   	ret

Disassembly of section .text._ZN4acos7storage15FAT32FileSystemaSEOS1_:

000000000010e850 <_ZN4acos7storage15FAT32FileSystemaSEOS1_>:
  10e850:	55                   	push   %rbp
  10e851:	48 89 e5             	mov    %rsp,%rbp
  10e854:	48 83 ec 20          	sub    $0x20,%rsp
  10e858:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10e85c:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  10e860:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  10e864:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
  10e868:	48 8b 75 f0          	mov    -0x10(%rbp),%rsi
  10e86c:	e8 4f 01 00 00       	call   10e9c0 <_ZN4acos3vfs10FileSystemaSERKS1_>
  10e871:	48 8b 7d e8          	mov    -0x18(%rbp),%rdi
  10e875:	48 83 c7 08          	add    $0x8,%rdi
  10e879:	48 8b 75 f0          	mov    -0x10(%rbp),%rsi
  10e87d:	48 83 c6 08          	add    $0x8,%rsi
  10e881:	ba 24 00 00 00       	mov    $0x24,%edx
  10e886:	e8 75 17 ff ff       	call   100000 <memcpy>
  10e88b:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  10e88f:	48 83 c4 20          	add    $0x20,%rsp
  10e893:	5d                   	pop    %rbp
  10e894:	c3                   	ret

Disassembly of section .text._ZN4acos7storage15FAT32FileSystemD2Ev:

000000000010e8a0 <_ZN4acos7storage15FAT32FileSystemD2Ev>:
  10e8a0:	55                   	push   %rbp
  10e8a1:	48 89 e5             	mov    %rsp,%rbp
  10e8a4:	48 83 ec 10          	sub    $0x10,%rsp
  10e8a8:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10e8ac:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  10e8b0:	e8 bb 00 00 00       	call   10e970 <_ZN4acos3vfs10FileSystemD2Ev>
  10e8b5:	48 83 c4 10          	add    $0x10,%rsp
  10e8b9:	5d                   	pop    %rbp
  10e8ba:	c3                   	ret

Disassembly of section .text._ZN4acos7storage15FAT32FileSystemD0Ev:

000000000010e8c0 <_ZN4acos7storage15FAT32FileSystemD0Ev>:
  10e8c0:	55                   	push   %rbp
  10e8c1:	48 89 e5             	mov    %rsp,%rbp
  10e8c4:	48 83 ec 10          	sub    $0x10,%rsp
  10e8c8:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10e8cc:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  10e8d0:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  10e8d4:	e8 c7 ff ff ff       	call   10e8a0 <_ZN4acos7storage15FAT32FileSystemD2Ev>
  10e8d9:	48 8b 7d f0          	mov    -0x10(%rbp),%rdi
  10e8dd:	e8 4e 1b ff ff       	call   100430 <_ZdlPv>
  10e8e2:	48 83 c4 10          	add    $0x10,%rsp
  10e8e6:	5d                   	pop    %rbp
  10e8e7:	c3                   	ret

Disassembly of section .text._ZN4acos3vfs4NodeC2Ev:

000000000010e8f0 <_ZN4acos3vfs4NodeC2Ev>:
  10e8f0:	55                   	push   %rbp
  10e8f1:	48 89 e5             	mov    %rsp,%rbp
  10e8f4:	50                   	push   %rax
  10e8f5:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10e8f9:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10e8fd:	48 b9 f8 fa 10 00 00 	movabs $0x10faf8,%rcx
  10e904:	00 00 00
  10e907:	48 83 c1 10          	add    $0x10,%rcx
  10e90b:	48 89 08             	mov    %rcx,(%rax)
  10e90e:	48 83 c4 08          	add    $0x8,%rsp
  10e912:	5d                   	pop    %rbp
  10e913:	c3                   	ret

Disassembly of section .text._ZN4acos3vfs4NodeD2Ev:

000000000010e920 <_ZN4acos3vfs4NodeD2Ev>:
  10e920:	55                   	push   %rbp
  10e921:	48 89 e5             	mov    %rsp,%rbp
  10e924:	50                   	push   %rax
  10e925:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10e929:	48 83 c4 08          	add    $0x8,%rsp
  10e92d:	5d                   	pop    %rbp
  10e92e:	c3                   	ret

Disassembly of section .text._ZN4acos3vfs4NodeD0Ev:

000000000010e930 <_ZN4acos3vfs4NodeD0Ev>:
  10e930:	55                   	push   %rbp
  10e931:	48 89 e5             	mov    %rsp,%rbp
  10e934:	50                   	push   %rax
  10e935:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10e939:	0f 0b                	ud2

Disassembly of section .text._ZN4acos3vfs4Node8read_dirEmPNS0_14DirectoryEntryEm:

000000000010e940 <_ZN4acos3vfs4Node8read_dirEmPNS0_14DirectoryEntryEm>:
  10e940:	55                   	push   %rbp
  10e941:	48 89 e5             	mov    %rsp,%rbp
  10e944:	48 83 ec 20          	sub    $0x20,%rsp
  10e948:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10e94c:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  10e950:	48 89 55 e8          	mov    %rdx,-0x18(%rbp)
  10e954:	48 89 4d e0          	mov    %rcx,-0x20(%rbp)
  10e958:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  10e95d:	48 83 c4 20          	add    $0x20,%rsp
  10e961:	5d                   	pop    %rbp
  10e962:	c3                   	ret

Disassembly of section .text._ZN4acos3vfs10FileSystemD2Ev:

000000000010e970 <_ZN4acos3vfs10FileSystemD2Ev>:
  10e970:	55                   	push   %rbp
  10e971:	48 89 e5             	mov    %rsp,%rbp
  10e974:	50                   	push   %rax
  10e975:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10e979:	48 83 c4 08          	add    $0x8,%rsp
  10e97d:	5d                   	pop    %rbp
  10e97e:	c3                   	ret

Disassembly of section .text._ZN4acos3vfs10FileSystemD0Ev:

000000000010e980 <_ZN4acos3vfs10FileSystemD0Ev>:
  10e980:	55                   	push   %rbp
  10e981:	48 89 e5             	mov    %rsp,%rbp
  10e984:	50                   	push   %rax
  10e985:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10e989:	0f 0b                	ud2

Disassembly of section .text._ZN4acos3vfs10FileSystem5probeEPvPKc:

000000000010e990 <_ZN4acos3vfs10FileSystem5probeEPvPKc>:
  10e990:	55                   	push   %rbp
  10e991:	48 89 e5             	mov    %rsp,%rbp
  10e994:	48 83 ec 18          	sub    $0x18,%rsp
  10e998:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10e99c:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  10e9a0:	48 89 55 e8          	mov    %rdx,-0x18(%rbp)
  10e9a4:	31 c0                	xor    %eax,%eax
  10e9a6:	24 01                	and    $0x1,%al
  10e9a8:	0f b6 c0             	movzbl %al,%eax
  10e9ab:	48 83 c4 18          	add    $0x18,%rsp
  10e9af:	5d                   	pop    %rbp
  10e9b0:	c3                   	ret

Disassembly of section .text._ZN4acos3vfs10FileSystemaSERKS1_:

000000000010e9c0 <_ZN4acos3vfs10FileSystemaSERKS1_>:
  10e9c0:	55                   	push   %rbp
  10e9c1:	48 89 e5             	mov    %rsp,%rbp
  10e9c4:	48 83 ec 10          	sub    $0x10,%rsp
  10e9c8:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10e9cc:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  10e9d0:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10e9d4:	48 83 c4 10          	add    $0x10,%rsp
  10e9d8:	5d                   	pop    %rbp
  10e9d9:	c3                   	ret

Disassembly of section .text._ZN4acos7storage7RamDiskD2Ev:

000000000010e9e0 <_ZN4acos7storage7RamDiskD2Ev>:
  10e9e0:	55                   	push   %rbp
  10e9e1:	48 89 e5             	mov    %rsp,%rbp
  10e9e4:	48 83 ec 10          	sub    $0x10,%rsp
  10e9e8:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10e9ec:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  10e9f0:	e8 2b fd ff ff       	call   10e720 <_ZN4acos7storage11BlockDeviceD2Ev>
  10e9f5:	48 83 c4 10          	add    $0x10,%rsp
  10e9f9:	5d                   	pop    %rbp
  10e9fa:	c3                   	ret

Disassembly of section .text._ZN4acos7storage7RamDiskD0Ev:

000000000010ea00 <_ZN4acos7storage7RamDiskD0Ev>:
  10ea00:	55                   	push   %rbp
  10ea01:	48 89 e5             	mov    %rsp,%rbp
  10ea04:	48 83 ec 10          	sub    $0x10,%rsp
  10ea08:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10ea0c:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  10ea10:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  10ea14:	e8 c7 ff ff ff       	call   10e9e0 <_ZN4acos7storage7RamDiskD2Ev>
  10ea19:	48 8b 7d f0          	mov    -0x10(%rbp),%rdi
  10ea1d:	e8 0e 1a ff ff       	call   100430 <_ZdlPv>
  10ea22:	48 83 c4 10          	add    $0x10,%rsp
  10ea26:	5d                   	pop    %rbp
  10ea27:	c3                   	ret

Disassembly of section .text._ZNK4acos7storage7RamDisk10block_sizeEv:

000000000010ea30 <_ZNK4acos7storage7RamDisk10block_sizeEv>:
  10ea30:	55                   	push   %rbp
  10ea31:	48 89 e5             	mov    %rsp,%rbp
  10ea34:	50                   	push   %rax
  10ea35:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10ea39:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10ea3d:	48 8b 40 18          	mov    0x18(%rax),%rax
  10ea41:	48 83 c4 08          	add    $0x8,%rsp
  10ea45:	5d                   	pop    %rbp
  10ea46:	c3                   	ret

Disassembly of section .text._ZNK4acos7storage7RamDisk8capacityEv:

000000000010ea50 <_ZNK4acos7storage7RamDisk8capacityEv>:
  10ea50:	55                   	push   %rbp
  10ea51:	48 89 e5             	mov    %rsp,%rbp
  10ea54:	50                   	push   %rax
  10ea55:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10ea59:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10ea5d:	48 8b 40 10          	mov    0x10(%rax),%rax
  10ea61:	48 83 c4 08          	add    $0x8,%rsp
  10ea65:	5d                   	pop    %rbp
  10ea66:	c3                   	ret

Disassembly of section .text._ZNK4acos6memory12AddressSpace9pml4_physEv:

000000000010ea70 <_ZNK4acos6memory12AddressSpace9pml4_physEv>:
  10ea70:	55                   	push   %rbp
  10ea71:	48 89 e5             	mov    %rsp,%rbp
  10ea74:	50                   	push   %rax
  10ea75:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10ea79:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10ea7d:	48 8b 00             	mov    (%rax),%rax
  10ea80:	48 83 c4 08          	add    $0x8,%rsp
  10ea84:	5d                   	pop    %rbp
  10ea85:	c3                   	ret

Disassembly of section .text._ZN4acos3hal10ScopedLockC2ERNS0_8SpinLockE:

000000000010ea90 <_ZN4acos3hal10ScopedLockC2ERNS0_8SpinLockE>:
  10ea90:	55                   	push   %rbp
  10ea91:	48 89 e5             	mov    %rsp,%rbp
  10ea94:	48 83 ec 10          	sub    $0x10,%rsp
  10ea98:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10ea9c:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  10eaa0:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10eaa4:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
  10eaa8:	48 89 08             	mov    %rcx,(%rax)
  10eaab:	48 8b 38             	mov    (%rax),%rdi
  10eaae:	e8 2d 00 00 00       	call   10eae0 <_ZN4acos3hal8SpinLock4lockEv>
  10eab3:	48 83 c4 10          	add    $0x10,%rsp
  10eab7:	5d                   	pop    %rbp
  10eab8:	c3                   	ret

Disassembly of section .text._ZN4acos3hal10ScopedLockD2Ev:

000000000010eac0 <_ZN4acos3hal10ScopedLockD2Ev>:
  10eac0:	55                   	push   %rbp
  10eac1:	48 89 e5             	mov    %rsp,%rbp
  10eac4:	48 83 ec 10          	sub    $0x10,%rsp
  10eac8:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10eacc:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10ead0:	48 8b 38             	mov    (%rax),%rdi
  10ead3:	e8 48 00 00 00       	call   10eb20 <_ZN4acos3hal8SpinLock6unlockEv>
  10ead8:	48 83 c4 10          	add    $0x10,%rsp
  10eadc:	5d                   	pop    %rbp
  10eadd:	c3                   	ret

Disassembly of section .text._ZN4acos3hal8SpinLock4lockEv:

000000000010eae0 <_ZN4acos3hal8SpinLock4lockEv>:
  10eae0:	55                   	push   %rbp
  10eae1:	48 89 e5             	mov    %rsp,%rbp
  10eae4:	48 83 ec 10          	sub    $0x10,%rsp
  10eae8:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10eaec:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10eaf0:	48 89 45 f0          	mov    %rax,-0x10(%rbp)
  10eaf4:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
  10eaf8:	b0 01                	mov    $0x1,%al
  10eafa:	86 01                	xchg   %al,(%rcx)
  10eafc:	3c 00                	cmp    $0x0,%al
  10eafe:	0f 84 07 00 00 00    	je     10eb0b <_ZN4acos3hal8SpinLock4lockEv+0x2b>
  10eb04:	f3 90                	pause
  10eb06:	e9 e9 ff ff ff       	jmp    10eaf4 <_ZN4acos3hal8SpinLock4lockEv+0x14>
  10eb0b:	48 83 c4 10          	add    $0x10,%rsp
  10eb0f:	5d                   	pop    %rbp
  10eb10:	c3                   	ret

Disassembly of section .text._ZN4acos3hal8SpinLock6unlockEv:

000000000010eb20 <_ZN4acos3hal8SpinLock6unlockEv>:
  10eb20:	55                   	push   %rbp
  10eb21:	48 89 e5             	mov    %rsp,%rbp
  10eb24:	50                   	push   %rax
  10eb25:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10eb29:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10eb2d:	c6 00 00             	movb   $0x0,(%rax)
  10eb30:	48 83 c4 08          	add    $0x8,%rsp
  10eb34:	5d                   	pop    %rbp
  10eb35:	c3                   	ret

Disassembly of section .text._ZNK4acos8graphics11Framebuffer4sizeEv:

000000000010eb40 <_ZNK4acos8graphics11Framebuffer4sizeEv>:
  10eb40:	55                   	push   %rbp
  10eb41:	48 89 e5             	mov    %rsp,%rbp
  10eb44:	50                   	push   %rax
  10eb45:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10eb49:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10eb4d:	48 8b 40 08          	mov    0x8(%rax),%rax
  10eb51:	48 83 c4 08          	add    $0x8,%rsp
  10eb55:	5d                   	pop    %rbp
  10eb56:	c3                   	ret

Disassembly of section .text._ZNK4acos8graphics11Framebuffer5widthEv:

000000000010eb60 <_ZNK4acos8graphics11Framebuffer5widthEv>:
  10eb60:	55                   	push   %rbp
  10eb61:	48 89 e5             	mov    %rsp,%rbp
  10eb64:	50                   	push   %rax
  10eb65:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10eb69:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10eb6d:	8b 40 10             	mov    0x10(%rax),%eax
  10eb70:	48 83 c4 08          	add    $0x8,%rsp
  10eb74:	5d                   	pop    %rbp
  10eb75:	c3                   	ret

Disassembly of section .text._ZNK4acos8graphics11Framebuffer6heightEv:

000000000010eb80 <_ZNK4acos8graphics11Framebuffer6heightEv>:
  10eb80:	55                   	push   %rbp
  10eb81:	48 89 e5             	mov    %rsp,%rbp
  10eb84:	50                   	push   %rax
  10eb85:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10eb89:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10eb8d:	8b 40 14             	mov    0x14(%rax),%eax
  10eb90:	48 83 c4 08          	add    $0x8,%rsp
  10eb94:	5d                   	pop    %rbp
  10eb95:	c3                   	ret

Disassembly of section .text._ZNK4acos8graphics11Framebuffer5pitchEv:

000000000010eba0 <_ZNK4acos8graphics11Framebuffer5pitchEv>:
  10eba0:	55                   	push   %rbp
  10eba1:	48 89 e5             	mov    %rsp,%rbp
  10eba4:	50                   	push   %rax
  10eba5:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10eba9:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10ebad:	8b 40 18             	mov    0x18(%rax),%eax
  10ebb0:	48 83 c4 08          	add    $0x8,%rsp
  10ebb4:	5d                   	pop    %rbp
  10ebb5:	c3                   	ret

Disassembly of section .text._ZNK4acos8graphics11Framebuffer4baseEv:

000000000010ebc0 <_ZNK4acos8graphics11Framebuffer4baseEv>:
  10ebc0:	55                   	push   %rbp
  10ebc1:	48 89 e5             	mov    %rsp,%rbp
  10ebc4:	50                   	push   %rax
  10ebc5:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10ebc9:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10ebcd:	48 8b 00             	mov    (%rax),%rax
  10ebd0:	48 83 c4 08          	add    $0x8,%rsp
  10ebd4:	5d                   	pop    %rbp
  10ebd5:	c3                   	ret

Disassembly of section .text._ZN4acos3smp3Cpu2idEv:

000000000010ebe0 <_ZN4acos3smp3Cpu2idEv>:
  10ebe0:	55                   	push   %rbp
  10ebe1:	48 89 e5             	mov    %rsp,%rbp
  10ebe4:	e8 b7 f3 ff ff       	call   10dfa0 <_ZN4acos3smp3Cpu7currentEv>
  10ebe9:	8b 40 2c             	mov    0x2c(%rax),%eax
  10ebec:	5d                   	pop    %rbp
  10ebed:	c3                   	ret

Disassembly of section .text._ZN4acos3hal8SpinLockC2Ev:

000000000010ebf0 <_ZN4acos3hal8SpinLockC2Ev>:
  10ebf0:	55                   	push   %rbp
  10ebf1:	48 89 e5             	mov    %rsp,%rbp
  10ebf4:	50                   	push   %rax
  10ebf5:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10ebf9:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10ebfd:	c6 00 00             	movb   $0x0,(%rax)
  10ec00:	48 83 c4 08          	add    $0x8,%rsp
  10ec04:	5d                   	pop    %rbp
  10ec05:	c3                   	ret

Disassembly of section .text._ZN4acos3vfs11ConsoleNodeD2Ev:

000000000010ec10 <_ZN4acos3vfs11ConsoleNodeD2Ev>:
  10ec10:	55                   	push   %rbp
  10ec11:	48 89 e5             	mov    %rsp,%rbp
  10ec14:	48 83 ec 10          	sub    $0x10,%rsp
  10ec18:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10ec1c:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  10ec20:	e8 fb fc ff ff       	call   10e920 <_ZN4acos3vfs4NodeD2Ev>
  10ec25:	48 83 c4 10          	add    $0x10,%rsp
  10ec29:	5d                   	pop    %rbp
  10ec2a:	c3                   	ret

Disassembly of section .text._ZN4acos3vfs11ConsoleNodeD0Ev:

000000000010ec30 <_ZN4acos3vfs11ConsoleNodeD0Ev>:
  10ec30:	55                   	push   %rbp
  10ec31:	48 89 e5             	mov    %rsp,%rbp
  10ec34:	48 83 ec 10          	sub    $0x10,%rsp
  10ec38:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10ec3c:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  10ec40:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  10ec44:	e8 c7 ff ff ff       	call   10ec10 <_ZN4acos3vfs11ConsoleNodeD2Ev>
  10ec49:	48 8b 7d f0          	mov    -0x10(%rbp),%rdi
  10ec4d:	e8 de 17 ff ff       	call   100430 <_ZdlPv>
  10ec52:	48 83 c4 10          	add    $0x10,%rsp
  10ec56:	5d                   	pop    %rbp
  10ec57:	c3                   	ret

Disassembly of section .text._ZNK4acos3vfs11ConsoleNode4sizeEv:

000000000010ec60 <_ZNK4acos3vfs11ConsoleNode4sizeEv>:
  10ec60:	55                   	push   %rbp
  10ec61:	48 89 e5             	mov    %rsp,%rbp
  10ec64:	50                   	push   %rax
  10ec65:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10ec69:	31 c0                	xor    %eax,%eax
  10ec6b:	48 83 c4 08          	add    $0x8,%rsp
  10ec6f:	5d                   	pop    %rbp
  10ec70:	c3                   	ret

Disassembly of section .text._ZNK4acos3vfs11ConsoleNode4typeEv:

000000000010ec80 <_ZNK4acos3vfs11ConsoleNode4typeEv>:
  10ec80:	55                   	push   %rbp
  10ec81:	48 89 e5             	mov    %rsp,%rbp
  10ec84:	50                   	push   %rax
  10ec85:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10ec89:	b8 03 00 00 00       	mov    $0x3,%eax
  10ec8e:	48 83 c4 08          	add    $0x8,%rsp
  10ec92:	5d                   	pop    %rbp
  10ec93:	c3                   	ret

Disassembly of section .text._ZNK4acos7storage14AHCIController10port_countEv:

000000000010eca0 <_ZNK4acos7storage14AHCIController10port_countEv>:
  10eca0:	55                   	push   %rbp
  10eca1:	48 89 e5             	mov    %rsp,%rbp
  10eca4:	50                   	push   %rax
  10eca5:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10eca9:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10ecad:	8b 80 08 01 00 00    	mov    0x108(%rax),%eax
  10ecb3:	48 83 c4 08          	add    $0x8,%rsp
  10ecb7:	5d                   	pop    %rbp
  10ecb8:	c3                   	ret

Disassembly of section .text._ZNK4acos7storage14AHCIController8get_portEj:

000000000010ecc0 <_ZNK4acos7storage14AHCIController8get_portEj>:
  10ecc0:	55                   	push   %rbp
  10ecc1:	48 89 e5             	mov    %rsp,%rbp
  10ecc4:	48 83 ec 20          	sub    $0x20,%rsp
  10ecc8:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10eccc:	89 75 f4             	mov    %esi,-0xc(%rbp)
  10eccf:	48 8b 4d f8          	mov    -0x8(%rbp),%rcx
  10ecd3:	48 89 4d e8          	mov    %rcx,-0x18(%rbp)
  10ecd7:	8b 45 f4             	mov    -0xc(%rbp),%eax
  10ecda:	3b 81 08 01 00 00    	cmp    0x108(%rcx),%eax
  10ece0:	0f 83 15 00 00 00    	jae    10ecfb <_ZNK4acos7storage14AHCIController8get_portEj+0x3b>
  10ece6:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  10ecea:	8b 4d f4             	mov    -0xc(%rbp),%ecx
  10eced:	48 8b 44 c8 08       	mov    0x8(%rax,%rcx,8),%rax
  10ecf2:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  10ecf6:	e9 0b 00 00 00       	jmp    10ed06 <_ZNK4acos7storage14AHCIController8get_portEj+0x46>
  10ecfb:	31 c0                	xor    %eax,%eax
  10ecfd:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  10ed01:	e9 00 00 00 00       	jmp    10ed06 <_ZNK4acos7storage14AHCIController8get_portEj+0x46>
  10ed06:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  10ed0a:	48 83 c4 20          	add    $0x20,%rsp
  10ed0e:	5d                   	pop    %rbp
  10ed0f:	c3                   	ret

Disassembly of section .text._ZN4acos3vfs13DevFileSystemD2Ev:

000000000010ed10 <_ZN4acos3vfs13DevFileSystemD2Ev>:
  10ed10:	55                   	push   %rbp
  10ed11:	48 89 e5             	mov    %rsp,%rbp
  10ed14:	48 83 ec 10          	sub    $0x10,%rsp
  10ed18:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10ed1c:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  10ed20:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  10ed24:	48 83 c7 08          	add    $0x8,%rdi
  10ed28:	e8 e3 fe ff ff       	call   10ec10 <_ZN4acos3vfs11ConsoleNodeD2Ev>
  10ed2d:	48 8b 7d f0          	mov    -0x10(%rbp),%rdi
  10ed31:	e8 3a fc ff ff       	call   10e970 <_ZN4acos3vfs10FileSystemD2Ev>
  10ed36:	48 83 c4 10          	add    $0x10,%rsp
  10ed3a:	5d                   	pop    %rbp
  10ed3b:	c3                   	ret

Disassembly of section .text._ZN4acos3vfs13DevFileSystemD0Ev:

000000000010ed40 <_ZN4acos3vfs13DevFileSystemD0Ev>:
  10ed40:	55                   	push   %rbp
  10ed41:	48 89 e5             	mov    %rsp,%rbp
  10ed44:	48 83 ec 10          	sub    $0x10,%rsp
  10ed48:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10ed4c:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  10ed50:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  10ed54:	e8 b7 ff ff ff       	call   10ed10 <_ZN4acos3vfs13DevFileSystemD2Ev>
  10ed59:	48 8b 7d f0          	mov    -0x10(%rbp),%rdi
  10ed5d:	e8 ce 16 ff ff       	call   100430 <_ZdlPv>
  10ed62:	48 83 c4 10          	add    $0x10,%rsp
  10ed66:	5d                   	pop    %rbp
  10ed67:	c3                   	ret

Disassembly of section .text._ZN4acos3vfs13DevFileSystem4openEPKc:

000000000010ed70 <_ZN4acos3vfs13DevFileSystem4openEPKc>:
  10ed70:	55                   	push   %rbp
  10ed71:	48 89 e5             	mov    %rsp,%rbp
  10ed74:	48 83 ec 38          	sub    $0x38,%rsp
  10ed78:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  10ed7c:	48 89 75 e8          	mov    %rsi,-0x18(%rbp)
  10ed80:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10ed84:	48 89 45 d0          	mov    %rax,-0x30(%rbp)
  10ed88:	48 b8 e6 fa 10 00 00 	movabs $0x10fae6,%rax
  10ed8f:	00 00 00
  10ed92:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  10ed96:	c6 45 df 01          	movb   $0x1,-0x21(%rbp)
  10ed9a:	c7 45 d8 00 00 00 00 	movl   $0x0,-0x28(%rbp)
  10eda1:	48 8b 4d e0          	mov    -0x20(%rbp),%rcx
  10eda5:	48 63 55 d8          	movslq -0x28(%rbp),%rdx
  10eda9:	b0 01                	mov    $0x1,%al
  10edab:	80 3c 11 00          	cmpb   $0x0,(%rcx,%rdx,1)
  10edaf:	88 45 cf             	mov    %al,-0x31(%rbp)
  10edb2:	0f 85 12 00 00 00    	jne    10edca <_ZN4acos3vfs13DevFileSystem4openEPKc+0x5a>
  10edb8:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  10edbc:	48 63 4d d8          	movslq -0x28(%rbp),%rcx
  10edc0:	80 3c 08 00          	cmpb   $0x0,(%rax,%rcx,1)
  10edc4:	0f 95 c0             	setne  %al
  10edc7:	88 45 cf             	mov    %al,-0x31(%rbp)
  10edca:	8a 45 cf             	mov    -0x31(%rbp),%al
  10edcd:	a8 01                	test   $0x1,%al
  10edcf:	0f 85 05 00 00 00    	jne    10edda <_ZN4acos3vfs13DevFileSystem4openEPKc+0x6a>
  10edd5:	e9 3c 00 00 00       	jmp    10ee16 <_ZN4acos3vfs13DevFileSystem4openEPKc+0xa6>
  10edda:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  10edde:	48 63 4d d8          	movslq -0x28(%rbp),%rcx
  10ede2:	0f be 04 08          	movsbl (%rax,%rcx,1),%eax
  10ede6:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  10edea:	48 63 55 d8          	movslq -0x28(%rbp),%rdx
  10edee:	0f be 0c 11          	movsbl (%rcx,%rdx,1),%ecx
  10edf2:	39 c8                	cmp    %ecx,%eax
  10edf4:	0f 84 09 00 00 00    	je     10ee03 <_ZN4acos3vfs13DevFileSystem4openEPKc+0x93>
  10edfa:	c6 45 df 00          	movb   $0x0,-0x21(%rbp)
  10edfe:	e9 13 00 00 00       	jmp    10ee16 <_ZN4acos3vfs13DevFileSystem4openEPKc+0xa6>
  10ee03:	e9 00 00 00 00       	jmp    10ee08 <_ZN4acos3vfs13DevFileSystem4openEPKc+0x98>
  10ee08:	8b 45 d8             	mov    -0x28(%rbp),%eax
  10ee0b:	83 c0 01             	add    $0x1,%eax
  10ee0e:	89 45 d8             	mov    %eax,-0x28(%rbp)
  10ee11:	e9 8b ff ff ff       	jmp    10eda1 <_ZN4acos3vfs13DevFileSystem4openEPKc+0x31>
  10ee16:	f6 45 df 01          	testb  $0x1,-0x21(%rbp)
  10ee1a:	0f 84 11 00 00 00    	je     10ee31 <_ZN4acos3vfs13DevFileSystem4openEPKc+0xc1>
  10ee20:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
  10ee24:	48 83 c0 08          	add    $0x8,%rax
  10ee28:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  10ee2c:	e9 08 00 00 00       	jmp    10ee39 <_ZN4acos3vfs13DevFileSystem4openEPKc+0xc9>
  10ee31:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  10ee38:	00
  10ee39:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10ee3d:	48 83 c4 38          	add    $0x38,%rsp
  10ee41:	5d                   	pop    %rbp
  10ee42:	c3                   	ret

Disassembly of section .text._ZN4acos3vfs13DevFileSystem5mountEPKc:

000000000010ee50 <_ZN4acos3vfs13DevFileSystem5mountEPKc>:
  10ee50:	55                   	push   %rbp
  10ee51:	48 89 e5             	mov    %rsp,%rbp
  10ee54:	48 83 ec 10          	sub    $0x10,%rsp
  10ee58:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10ee5c:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  10ee60:	b0 01                	mov    $0x1,%al
  10ee62:	24 01                	and    $0x1,%al
  10ee64:	0f b6 c0             	movzbl %al,%eax
  10ee67:	48 83 c4 10          	add    $0x10,%rsp
  10ee6b:	5d                   	pop    %rbp
  10ee6c:	c3                   	ret

Disassembly of section .text._ZN4acos8graphics13DisplayDeviceC2Ev:

000000000010ee70 <_ZN4acos8graphics13DisplayDeviceC2Ev>:
  10ee70:	55                   	push   %rbp
  10ee71:	48 89 e5             	mov    %rsp,%rbp
  10ee74:	50                   	push   %rax
  10ee75:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10ee79:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10ee7d:	48 b9 b0 fb 10 00 00 	movabs $0x10fbb0,%rcx
  10ee84:	00 00 00
  10ee87:	48 83 c1 10          	add    $0x10,%rcx
  10ee8b:	48 89 08             	mov    %rcx,(%rax)
  10ee8e:	48 83 c4 08          	add    $0x8,%rsp
  10ee92:	5d                   	pop    %rbp
  10ee93:	c3                   	ret

Disassembly of section .text._ZN4acos8graphics13DisplayDeviceD2Ev:

000000000010eea0 <_ZN4acos8graphics13DisplayDeviceD2Ev>:
  10eea0:	55                   	push   %rbp
  10eea1:	48 89 e5             	mov    %rsp,%rbp
  10eea4:	50                   	push   %rax
  10eea5:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10eea9:	48 83 c4 08          	add    $0x8,%rsp
  10eead:	5d                   	pop    %rbp
  10eeae:	c3                   	ret

Disassembly of section .text._ZN4acos8graphics13DisplayDeviceD0Ev:

000000000010eeb0 <_ZN4acos8graphics13DisplayDeviceD0Ev>:
  10eeb0:	55                   	push   %rbp
  10eeb1:	48 89 e5             	mov    %rsp,%rbp
  10eeb4:	50                   	push   %rax
  10eeb5:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10eeb9:	0f 0b                	ud2

Disassembly of section .text._ZNK4acos8graphics8Renderer10is_clippedEjj:

000000000010eec0 <_ZNK4acos8graphics8Renderer10is_clippedEjj>:
  10eec0:	55                   	push   %rbp
  10eec1:	48 89 e5             	mov    %rsp,%rbp
  10eec4:	48 83 ec 28          	sub    $0x28,%rsp
  10eec8:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  10eecc:	89 75 ec             	mov    %esi,-0x14(%rbp)
  10eecf:	89 55 e8             	mov    %edx,-0x18(%rbp)
  10eed2:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  10eed6:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  10eeda:	f6 40 18 01          	testb  $0x1,0x18(%rax)
  10eede:	0f 85 09 00 00 00    	jne    10eeed <_ZNK4acos8graphics8Renderer10is_clippedEjj+0x2d>
  10eee4:	c6 45 ff 00          	movb   $0x0,-0x1(%rbp)
  10eee8:	e9 61 00 00 00       	jmp    10ef4e <_ZNK4acos8graphics8Renderer10is_clippedEjj+0x8e>
  10eeed:	48 8b 55 e0          	mov    -0x20(%rbp),%rdx
  10eef1:	8b 4d ec             	mov    -0x14(%rbp),%ecx
  10eef4:	b0 01                	mov    $0x1,%al
  10eef6:	3b 4a 08             	cmp    0x8(%rdx),%ecx
  10eef9:	88 45 df             	mov    %al,-0x21(%rbp)
  10eefc:	0f 82 44 00 00 00    	jb     10ef46 <_ZNK4acos8graphics8Renderer10is_clippedEjj+0x86>
  10ef02:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  10ef06:	8b 4d ec             	mov    -0x14(%rbp),%ecx
  10ef09:	8b 50 08             	mov    0x8(%rax),%edx
  10ef0c:	03 50 10             	add    0x10(%rax),%edx
  10ef0f:	b0 01                	mov    $0x1,%al
  10ef11:	39 d1                	cmp    %edx,%ecx
  10ef13:	88 45 df             	mov    %al,-0x21(%rbp)
  10ef16:	0f 83 2a 00 00 00    	jae    10ef46 <_ZNK4acos8graphics8Renderer10is_clippedEjj+0x86>
  10ef1c:	48 8b 55 e0          	mov    -0x20(%rbp),%rdx
  10ef20:	8b 4d e8             	mov    -0x18(%rbp),%ecx
  10ef23:	b0 01                	mov    $0x1,%al
  10ef25:	3b 4a 0c             	cmp    0xc(%rdx),%ecx
  10ef28:	88 45 df             	mov    %al,-0x21(%rbp)
  10ef2b:	0f 82 15 00 00 00    	jb     10ef46 <_ZNK4acos8graphics8Renderer10is_clippedEjj+0x86>
  10ef31:	48 8b 55 e0          	mov    -0x20(%rbp),%rdx
  10ef35:	8b 45 e8             	mov    -0x18(%rbp),%eax
  10ef38:	8b 4a 0c             	mov    0xc(%rdx),%ecx
  10ef3b:	03 4a 14             	add    0x14(%rdx),%ecx
  10ef3e:	39 c8                	cmp    %ecx,%eax
  10ef40:	0f 93 c0             	setae  %al
  10ef43:	88 45 df             	mov    %al,-0x21(%rbp)
  10ef46:	8a 45 df             	mov    -0x21(%rbp),%al
  10ef49:	24 01                	and    $0x1,%al
  10ef4b:	88 45 ff             	mov    %al,-0x1(%rbp)
  10ef4e:	8a 45 ff             	mov    -0x1(%rbp),%al
  10ef51:	24 01                	and    $0x1,%al
  10ef53:	0f b6 c0             	movzbl %al,%eax
  10ef56:	48 83 c4 28          	add    $0x28,%rsp
  10ef5a:	5d                   	pop    %rbp
  10ef5b:	c3                   	ret

Disassembly of section .text._ZNK4acos8graphics4Font8is_validEv:

000000000010ef60 <_ZNK4acos8graphics4Font8is_validEv>:
  10ef60:	55                   	push   %rbp
  10ef61:	48 89 e5             	mov    %rsp,%rbp
  10ef64:	50                   	push   %rax
  10ef65:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10ef69:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10ef6d:	8a 00                	mov    (%rax),%al
  10ef6f:	24 01                	and    $0x1,%al
  10ef71:	0f b6 c0             	movzbl %al,%eax
  10ef74:	48 83 c4 08          	add    $0x8,%rsp
  10ef78:	5d                   	pop    %rbp
  10ef79:	c3                   	ret

Disassembly of section .text._ZNK4acos8graphics4Font5widthEv:

000000000010ef80 <_ZNK4acos8graphics4Font5widthEv>:
  10ef80:	55                   	push   %rbp
  10ef81:	48 89 e5             	mov    %rsp,%rbp
  10ef84:	50                   	push   %rax
  10ef85:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10ef89:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10ef8d:	8b 40 04             	mov    0x4(%rax),%eax
  10ef90:	48 83 c4 08          	add    $0x8,%rsp
  10ef94:	5d                   	pop    %rbp
  10ef95:	c3                   	ret

Disassembly of section .text._ZNK4acos8graphics4Font6heightEv:

000000000010efa0 <_ZNK4acos8graphics4Font6heightEv>:
  10efa0:	55                   	push   %rbp
  10efa1:	48 89 e5             	mov    %rsp,%rbp
  10efa4:	50                   	push   %rax
  10efa5:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10efa9:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10efad:	8b 40 08             	mov    0x8(%rax),%eax
  10efb0:	48 83 c4 08          	add    $0x8,%rsp
  10efb4:	5d                   	pop    %rbp
  10efb5:	c3                   	ret

Disassembly of section .text._ZN4acos3abi5ColorC2Ehhhh:

000000000010efc0 <_ZN4acos3abi5ColorC2Ehhhh>:
  10efc0:	55                   	push   %rbp
  10efc1:	48 89 e5             	mov    %rsp,%rbp
  10efc4:	48 83 ec 10          	sub    $0x10,%rsp
  10efc8:	44 88 c0             	mov    %r8b,%al
  10efcb:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10efcf:	40 88 75 f7          	mov    %sil,-0x9(%rbp)
  10efd3:	88 55 f6             	mov    %dl,-0xa(%rbp)
  10efd6:	88 4d f5             	mov    %cl,-0xb(%rbp)
  10efd9:	88 45 f4             	mov    %al,-0xc(%rbp)
  10efdc:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10efe0:	8a 4d f7             	mov    -0x9(%rbp),%cl
  10efe3:	88 08                	mov    %cl,(%rax)
  10efe5:	8a 4d f6             	mov    -0xa(%rbp),%cl
  10efe8:	88 48 01             	mov    %cl,0x1(%rax)
  10efeb:	8a 4d f5             	mov    -0xb(%rbp),%cl
  10efee:	88 48 02             	mov    %cl,0x2(%rax)
  10eff1:	8a 4d f4             	mov    -0xc(%rbp),%cl
  10eff4:	88 48 03             	mov    %cl,0x3(%rax)
  10eff7:	48 83 c4 10          	add    $0x10,%rsp
  10effb:	5d                   	pop    %rbp
  10effc:	c3                   	ret

Disassembly of section .text._ZNK4acos3abi5Color7to_argbEv:

000000000010f000 <_ZNK4acos3abi5Color7to_argbEv>:
  10f000:	55                   	push   %rbp
  10f001:	48 89 e5             	mov    %rsp,%rbp
  10f004:	50                   	push   %rax
  10f005:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10f009:	48 8b 4d f8          	mov    -0x8(%rbp),%rcx
  10f00d:	0f b6 41 03          	movzbl 0x3(%rcx),%eax
  10f011:	c1 e0 18             	shl    $0x18,%eax
  10f014:	0f b6 11             	movzbl (%rcx),%edx
  10f017:	c1 e2 10             	shl    $0x10,%edx
  10f01a:	09 d0                	or     %edx,%eax
  10f01c:	0f b6 51 01          	movzbl 0x1(%rcx),%edx
  10f020:	c1 e2 08             	shl    $0x8,%edx
  10f023:	09 d0                	or     %edx,%eax
  10f025:	0f b6 49 02          	movzbl 0x2(%rcx),%ecx
  10f029:	09 c8                	or     %ecx,%eax
  10f02b:	48 83 c4 08          	add    $0x8,%rsp
  10f02f:	5d                   	pop    %rbp
  10f030:	c3                   	ret

Disassembly of section .text._ZN4acos8graphics4FontC2Ev:

000000000010f040 <_ZN4acos8graphics4FontC2Ev>:
  10f040:	55                   	push   %rbp
  10f041:	48 89 e5             	mov    %rsp,%rbp
  10f044:	50                   	push   %rax
  10f045:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10f049:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10f04d:	c6 00 00             	movb   $0x0,(%rax)
  10f050:	c7 40 04 00 00 00 00 	movl   $0x0,0x4(%rax)
  10f057:	c7 40 08 00 00 00 00 	movl   $0x0,0x8(%rax)
  10f05e:	c7 40 0c 00 00 00 00 	movl   $0x0,0xc(%rax)
  10f065:	c7 40 10 00 00 00 00 	movl   $0x0,0x10(%rax)
  10f06c:	48 c7 40 18 00 00 00 	movq   $0x0,0x18(%rax)
  10f073:	00
  10f074:	48 c7 40 20 00 00 00 	movq   $0x0,0x20(%rax)
  10f07b:	00
  10f07c:	c6 40 28 00          	movb   $0x0,0x28(%rax)
  10f080:	48 83 c4 08          	add    $0x8,%rsp
  10f084:	5d                   	pop    %rbp
  10f085:	c3                   	ret

Disassembly of section .text._ZN4acos8graphics16get_builtin_fontEv:

000000000010f090 <_ZN4acos8graphics16get_builtin_fontEv>:
  10f090:	55                   	push   %rbp
  10f091:	48 89 e5             	mov    %rsp,%rbp
  10f094:	48 83 ec 20          	sub    $0x20,%rsp
  10f098:	48 89 7d e0          	mov    %rdi,-0x20(%rbp)
  10f09c:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
  10f0a0:	8b 04 25 74 25 11 00 	mov    0x112574,%eax
  10f0a7:	89 c2                	mov    %eax,%edx
  10f0a9:	48 8d 7d f0          	lea    -0x10(%rbp),%rdi
  10f0ad:	48 be b0 fc 10 00 00 	movabs $0x10fcb0,%rsi
  10f0b4:	00 00 00
  10f0b7:	e8 24 00 00 00       	call   10f0e0 <_ZN4acos4SpanIKhEC2EPS1_m>
  10f0bc:	48 8b 7d e0          	mov    -0x20(%rbp),%rdi
  10f0c0:	48 8b 75 f0          	mov    -0x10(%rbp),%rsi
  10f0c4:	48 8b 55 f8          	mov    -0x8(%rbp),%rdx
  10f0c8:	e8 43 00 00 00       	call   10f110 <_ZN4acos8graphics4FontC2ENS_4SpanIKhEE>
  10f0cd:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  10f0d1:	48 83 c4 20          	add    $0x20,%rsp
  10f0d5:	5d                   	pop    %rbp
  10f0d6:	c3                   	ret

Disassembly of section .text._ZN4acos4SpanIKhEC2EPS1_m:

000000000010f0e0 <_ZN4acos4SpanIKhEC2EPS1_m>:
  10f0e0:	55                   	push   %rbp
  10f0e1:	48 89 e5             	mov    %rsp,%rbp
  10f0e4:	48 83 ec 18          	sub    $0x18,%rsp
  10f0e8:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10f0ec:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  10f0f0:	48 89 55 e8          	mov    %rdx,-0x18(%rbp)
  10f0f4:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10f0f8:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
  10f0fc:	48 89 08             	mov    %rcx,(%rax)
  10f0ff:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
  10f103:	48 89 48 08          	mov    %rcx,0x8(%rax)
  10f107:	48 83 c4 18          	add    $0x18,%rsp
  10f10b:	5d                   	pop    %rbp
  10f10c:	c3                   	ret

Disassembly of section .text._ZN4acos8graphics4FontC2ENS_4SpanIKhEE:

000000000010f110 <_ZN4acos8graphics4FontC2ENS_4SpanIKhEE>:
  10f110:	55                   	push   %rbp
  10f111:	48 89 e5             	mov    %rsp,%rbp
  10f114:	48 83 ec 30          	sub    $0x30,%rsp
  10f118:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  10f11c:	48 89 55 f8          	mov    %rdx,-0x8(%rbp)
  10f120:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
  10f124:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  10f128:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
  10f12c:	48 8d 7d f0          	lea    -0x10(%rbp),%rdi
  10f130:	e8 5b 00 00 00       	call   10f190 <_ZNK4acos4SpanIKhE4dataEv>
  10f135:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
  10f139:	48 8d 7d f0          	lea    -0x10(%rbp),%rdi
  10f13d:	e8 6e 00 00 00       	call   10f1b0 <_ZNK4acos4SpanIKhE4sizeEv>
  10f142:	48 8b 7d d8          	mov    -0x28(%rbp),%rdi
  10f146:	48 8b 75 e0          	mov    -0x20(%rbp),%rsi
  10f14a:	48 89 c2             	mov    %rax,%rdx
  10f14d:	e8 de df ff ff       	call   10d130 <_ZN4acos8graphics4FontC1EPKhm>
  10f152:	48 83 c4 30          	add    $0x30,%rsp
  10f156:	5d                   	pop    %rbp
  10f157:	c3                   	ret

Disassembly of section .text._ZN4acos4SpanIKhEC2Ev:

000000000010f160 <_ZN4acos4SpanIKhEC2Ev>:
  10f160:	55                   	push   %rbp
  10f161:	48 89 e5             	mov    %rsp,%rbp
  10f164:	50                   	push   %rax
  10f165:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10f169:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10f16d:	48 c7 00 00 00 00 00 	movq   $0x0,(%rax)
  10f174:	48 c7 40 08 00 00 00 	movq   $0x0,0x8(%rax)
  10f17b:	00
  10f17c:	48 83 c4 08          	add    $0x8,%rsp
  10f180:	5d                   	pop    %rbp
  10f181:	c3                   	ret

Disassembly of section .text._ZNK4acos4SpanIKhE4dataEv:

000000000010f190 <_ZNK4acos4SpanIKhE4dataEv>:
  10f190:	55                   	push   %rbp
  10f191:	48 89 e5             	mov    %rsp,%rbp
  10f194:	50                   	push   %rax
  10f195:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10f199:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10f19d:	48 8b 00             	mov    (%rax),%rax
  10f1a0:	48 83 c4 08          	add    $0x8,%rsp
  10f1a4:	5d                   	pop    %rbp
  10f1a5:	c3                   	ret

Disassembly of section .text._ZNK4acos4SpanIKhE4sizeEv:

000000000010f1b0 <_ZNK4acos4SpanIKhE4sizeEv>:
  10f1b0:	55                   	push   %rbp
  10f1b1:	48 89 e5             	mov    %rsp,%rbp
  10f1b4:	50                   	push   %rax
  10f1b5:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10f1b9:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10f1bd:	48 8b 40 08          	mov    0x8(%rax),%rax
  10f1c1:	48 83 c4 08          	add    $0x8,%rsp
  10f1c5:	5d                   	pop    %rbp
  10f1c6:	c3                   	ret

Disassembly of section .text._ZNK4acos5audio11AudioDevice2idEv:

000000000010f1d0 <_ZNK4acos5audio11AudioDevice2idEv>:
  10f1d0:	55                   	push   %rbp
  10f1d1:	48 89 e5             	mov    %rsp,%rbp
  10f1d4:	50                   	push   %rax
  10f1d5:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10f1d9:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10f1dd:	8b 00                	mov    (%rax),%eax
  10f1df:	48 83 c4 08          	add    $0x8,%rsp
  10f1e3:	5d                   	pop    %rbp
  10f1e4:	c3                   	ret

Disassembly of section .text._ZN4acos5audio11AudioDriverC2Ev:

000000000010f1f0 <_ZN4acos5audio11AudioDriverC2Ev>:
  10f1f0:	55                   	push   %rbp
  10f1f1:	48 89 e5             	mov    %rsp,%rbp
  10f1f4:	50                   	push   %rax
  10f1f5:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10f1f9:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  10f1fd:	48 b9 08 fc 10 00 00 	movabs $0x10fc08,%rcx
  10f204:	00 00 00
  10f207:	48 83 c1 10          	add    $0x10,%rcx
  10f20b:	48 89 08             	mov    %rcx,(%rax)
  10f20e:	48 83 c4 08          	add    $0x8,%rsp
  10f212:	5d                   	pop    %rbp
  10f213:	c3                   	ret

Disassembly of section .text._ZN4acos7drivers5audio11VirtIOSoundD2Ev:

000000000010f220 <_ZN4acos7drivers5audio11VirtIOSoundD2Ev>:
  10f220:	55                   	push   %rbp
  10f221:	48 89 e5             	mov    %rsp,%rbp
  10f224:	48 83 ec 10          	sub    $0x10,%rsp
  10f228:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10f22c:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  10f230:	e8 3b 00 00 00       	call   10f270 <_ZN4acos5audio11AudioDriverD2Ev>
  10f235:	48 83 c4 10          	add    $0x10,%rsp
  10f239:	5d                   	pop    %rbp
  10f23a:	c3                   	ret

Disassembly of section .text._ZN4acos7drivers5audio11VirtIOSoundD0Ev:

000000000010f240 <_ZN4acos7drivers5audio11VirtIOSoundD0Ev>:
  10f240:	55                   	push   %rbp
  10f241:	48 89 e5             	mov    %rsp,%rbp
  10f244:	48 83 ec 10          	sub    $0x10,%rsp
  10f248:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10f24c:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
  10f250:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
  10f254:	e8 c7 ff ff ff       	call   10f220 <_ZN4acos7drivers5audio11VirtIOSoundD2Ev>
  10f259:	48 8b 7d f0          	mov    -0x10(%rbp),%rdi
  10f25d:	e8 ce 11 ff ff       	call   100430 <_ZdlPv>
  10f262:	48 83 c4 10          	add    $0x10,%rsp
  10f266:	5d                   	pop    %rbp
  10f267:	c3                   	ret

Disassembly of section .text._ZN4acos5audio11AudioDriverD2Ev:

000000000010f270 <_ZN4acos5audio11AudioDriverD2Ev>:
  10f270:	55                   	push   %rbp
  10f271:	48 89 e5             	mov    %rsp,%rbp
  10f274:	50                   	push   %rax
  10f275:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10f279:	48 83 c4 08          	add    $0x8,%rsp
  10f27d:	5d                   	pop    %rbp
  10f27e:	c3                   	ret

Disassembly of section .text._ZN4acos5audio11AudioDriverD0Ev:

000000000010f280 <_ZN4acos5audio11AudioDriverD0Ev>:
  10f280:	55                   	push   %rbp
  10f281:	48 89 e5             	mov    %rsp,%rbp
  10f284:	50                   	push   %rax
  10f285:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10f289:	0f 0b                	ud2

Disassembly of section .text._ZN4acos4arch6x86_644MADT9cpu_countEv:

000000000010f290 <_ZN4acos4arch6x86_644MADT9cpu_countEv>:
  10f290:	55                   	push   %rbp
  10f291:	48 89 e5             	mov    %rsp,%rbp
  10f294:	8b 04 25 10 f3 16 00 	mov    0x16f310,%eax
  10f29b:	5d                   	pop    %rbp
  10f29c:	c3                   	ret

Disassembly of section .text._ZN4acos4arch6x86_644MADT11get_apic_idEj:

000000000010f2a0 <_ZN4acos4arch6x86_644MADT11get_apic_idEj>:
  10f2a0:	55                   	push   %rbp
  10f2a1:	48 89 e5             	mov    %rsp,%rbp
  10f2a4:	48 83 ec 04          	sub    $0x4,%rsp
  10f2a8:	89 7d fc             	mov    %edi,-0x4(%rbp)
  10f2ab:	8b 45 fc             	mov    -0x4(%rbp),%eax
  10f2ae:	8b 04 85 10 f2 16 00 	mov    0x16f210(,%rax,4),%eax
  10f2b5:	48 83 c4 04          	add    $0x4,%rsp
  10f2b9:	5d                   	pop    %rbp
  10f2ba:	c3                   	ret

Disassembly of section .text._ZN4acos3smp3Cpu5countEv:

000000000010f2c0 <_ZN4acos3smp3Cpu5countEv>:
  10f2c0:	55                   	push   %rbp
  10f2c1:	48 89 e5             	mov    %rsp,%rbp
  10f2c4:	8b 04 25 00 f2 16 00 	mov    0x16f200,%eax
  10f2cb:	5d                   	pop    %rbp
  10f2cc:	c3                   	ret
