package cat.server;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Collection;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;


import cat.function.CatBean;
import cat.function.ClientBean;


import java.awt.BorderLayout;
import java.awt.EventQueue;
import java.awt.Graphics;
import java.awt.Image;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.JTable;
import javax.swing.JLabel;
import javax.imageio.ImageIO;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JMenuBar;
import javax.swing.JOptionPane;
import javax.swing.JMenu;
import java.awt.List;
import java.awt.MenuItem;
import java.awt.PopupMenu;
import java.awt.TextArea;
import javax.swing.JTextField;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.io.File;
import java.io.IOException;
import java.awt.event.ActionEvent;
import javax.swing.table.DefaultTableModel;
import javax.swing.JList;
import javax.swing.JScrollBar;
import java.awt.Scrollbar;
import java.awt.Color;
public class CatServer {
	 
	 static JTextField textField;
	 static JTextField textField_1;
	 static JTable table;
	 static JTextField textField_2;
	 static JTextField textField_3;
	 static JTextField textField_4;
	 static JTextField textField_5;
	 static ServerSocket ss;
	 static JButton btnNewButton_1;
	 static JButton btnNewButton_2;
	 static boolean isStop=false;
	 static int stopIndex=0;
	 static String []w1=new String[100];
	static int r1=0;
	static String name_stop = null;
	int w2;
	int v;
	public static HashMap<String, ClientBean> onlines;
	static {
		try {
			ss = new ServerSocket(9000);
			onlines = new HashMap<String, ClientBean>();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}

	class CatClientThread extends Thread {
		private Socket client;
		private CatBean bean;
		private ObjectInputStream ois;
		private ObjectOutputStream oos;

		public CatClientThread(Socket client) {
			this.client = client;
		}

		@Override
		public void run() {
			//isStop=false;
			
			try {
				// ��ͣ�Ĵӿͻ��˽�����Ϣ
				while (true) {
					// ��ȡ�ӿͻ��˽��յ���catbean��Ϣ
					ois = new ObjectInputStream(client.getInputStream());
					bean = (CatBean)ois.readObject();
					
					// ����catbean�У�type������һ������
					if(isStop==true) {
						 name_stop=w1[r1-stopIndex-1];
					}
					switch (bean.getType()) {
					// �����߸���
					case 0: { // ����
						// ��¼���߿ͻ����û����Ͷ˿���clientbean��
						ClientBean cbean = new ClientBean();
						cbean.setName(bean.getName());
						cbean.setSocket(client);
						// ��������û�
						onlines.put(bean.getName(), cbean);
						// ������������catbean�������͸��ͻ���
						CatBean serverBean = new CatBean();
						serverBean.setType(0);
						serverBean.setInfo(bean.getTimer() + "  "
								+ bean.getName() + "������");
						w1[r1]=bean.getName();
						r1++;
						 ((DefaultTableModel) table.getModel()).insertRow(0, new String[] { bean.getName(),bean.getIp(),"8250",bean.getTimer(),"����" });
						// ֪ͨ���пͻ���������
						HashSet<String> set = new HashSet<String>();
						// �ͻ��ǳ�
						set.addAll(onlines.keySet());
						serverBean.setClients(set);
						sendAll(serverBean);
						break;
					}
					case -1: { // ����
						// ������������catbean�������͸��ͻ���
						CatBean serverBean = new CatBean();
						serverBean.setType(-1);

						try {
							oos = new ObjectOutputStream(
									client.getOutputStream());
							oos.writeObject(serverBean);
							oos.flush();
						} catch (IOException e) {
							// TODO Auto-generated catch block
							e.printStackTrace();
						}

						onlines.remove(bean.getName());

						// ��ʣ�µ������û����������뿪��֪ͨ
						CatBean serverBean2 = new CatBean();
						serverBean2.setInfo(bean.getTimer() + "  "
								+ bean.getName() + " " + " ������");
						for( v=0;v<r1;v++) {
							if(w1[v].equals(bean.getName())) {
								w2=r1-v-1;
							}
						}
						System.out.println("w2======"+w2);
						v=r1-w2-1;
						System.out.println("v======"+v);
						for(int j=v;j<=r1-2;j++) {
							System.out.println("........."+w1[v]);
							w1[v]=w1[v+1];
							System.out.println("........."+w1[v]);
						}
						System.out.println("r1======"+r1);
						r1--;
						for(int i=0;i<r1;i++) {
							System.out.println(w1[i]);
						}
						((DefaultTableModel) table.getModel()).removeRow(w2);
						serverBean2.setType(0);
						HashSet<String> set = new HashSet<String>();
						set.addAll(onlines.keySet());
						serverBean2.setClients(set);

						sendAll(serverBean2);
						return;
					}
					case 1: { // ����
						
						
//						 ������������catbean�������͸��ͻ���
						CatBean serverBean = new CatBean();

						serverBean.setType(1);
						serverBean.setClients(bean.getClients());
						serverBean.setInfo(bean.getInfo());
						serverBean.setName(bean.getName());
						serverBean.setTimer(bean.getTimer());
						// ��ѡ�еĿͻ���������
						if((!serverBean.getName().equals(name_stop))||isStop==false)sendMessage(serverBean);
						break;
					}
					case 5: { // ����
						
//						 ������������catbean�������͸��ͻ���
						CatBean serverBean = new CatBean();

						serverBean.setType(5);
						serverBean.setClients(bean.getClients());
						serverBean.setInfo(bean.getInfo());
						serverBean.setName(bean.getName());
						serverBean.setTimer(bean.getTimer());
						// ��ѡ�еĿͻ���������
						if(!serverBean.getName().equals(name_stop))sendAll(serverBean);
						//sendMessage(serverBean);
						break;
					}
					case 2: { // ��������ļ�
						// ������������catbean�������͸��ͻ���
						CatBean serverBean = new CatBean();
						String info = bean.getTimer() + "  " + bean.getName()
								+ "���㴫���ļ�,�Ƿ���Ҫ����";

						serverBean.setType(2);
						serverBean.setClients(bean.getClients()); // ���Ƿ��͵�Ŀ�ĵ�
						serverBean.setFileName(bean.getFileName()); // �ļ�����
						serverBean.setSize(bean.getSize()); // �ļ���С
						serverBean.setInfo(info);
						serverBean.setName(bean.getName()); // ��Դ
						serverBean.setTimer(bean.getTimer());
						// ��ѡ�еĿͻ���������
						sendMessage(serverBean);

						break;
					}
					case 3: { // ȷ�������ļ�
						CatBean serverBean = new CatBean();

						serverBean.setType(3);
						serverBean.setClients(bean.getClients()); // �ļ���Դ
						serverBean.setTo(bean.getTo()); // �ļ�Ŀ�ĵ�
						serverBean.setFileName(bean.getFileName()); // �ļ�����
						serverBean.setIp(bean.getIp());
						serverBean.setPort(bean.getPort());
						serverBean.setName(bean.getName()); // ���յĿͻ�����
						serverBean.setTimer(bean.getTimer());
						// ֪ͨ�ļ���Դ�Ŀͻ����Է�ȷ�������ļ�
						sendMessage(serverBean);
						break;
					}
					case 4: {
						CatBean serverBean = new CatBean();

						serverBean.setType(4);
						serverBean.setClients(bean.getClients()); // �ļ���Դ
						serverBean.setTo(bean.getTo()); // �ļ�Ŀ�ĵ�
						serverBean.setFileName(bean.getFileName());
						serverBean.setInfo(bean.getInfo());
						serverBean.setName(bean.getName());// ���յĿͻ�����
						serverBean.setTimer(bean.getTimer());
						sendMessage(serverBean);

						break;
					}
					default: {
						break;
					}
					}
				}
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (ClassNotFoundException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} finally {
				close();
			}
		}

		// ��ѡ�е��û���������
		private void sendMessage(CatBean serverBean) {
			// ����ȡ�����е�values
			Set<String> cbs = onlines.keySet();
			Iterator<String> it = cbs.iterator();
			// ѡ�пͻ�
			HashSet<String> clients = serverBean.getClients();
			while (it.hasNext()) {
				// ���߿ͻ�
				String client = it.next();
				// ѡ�еĿͻ����������ߵģ��ͷ���serverbean
				if (clients.contains(client)) {
					Socket c = onlines.get(client).getSocket();
					ObjectOutputStream oos;
					try {
						oos = new ObjectOutputStream(c.getOutputStream());
						oos.writeObject(serverBean);
						oos.flush();
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}

				}
			}
		}

		// �����е��û���������
		public void sendAll(CatBean serverBean) {
			Collection<ClientBean> clients = onlines.values();
			Iterator<ClientBean> it = clients.iterator();
			ObjectOutputStream oos;
			while (it.hasNext()) {
				Socket c = it.next().getSocket();
				try {
					oos = new ObjectOutputStream(c.getOutputStream());
					oos.writeObject(serverBean);
					oos.flush();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		}

		private void close() {
			if (oos != null) {
				try {
					oos.close();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
			if (ois != null) {
				try {
					ois.close();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
			if (client != null) {
				try {
					client.close();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		}
	}

	public void start() {
		try {
			while (true) {
				Socket client = ss.accept();
				new CatClientThread(client).start();
			}
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					ll frame = new ll();
					
					
					
					 btnNewButton_2 = new JButton("�߳�");
					btnNewButton_2.addActionListener(new ActionListener() {
						public void actionPerformed(ActionEvent e) {
						}
					});
					btnNewButton_2.setBounds(456, 223, 93, 23);
					frame.getContentPane().add(btnNewButton_2);
					
					
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
		new CatServer().start();
	}
}
class ll extends JFrame{
	/*private JTextField textField;
	private JTextField textField_1;
	private static JTable table;
	private JTextField textField_2;
	private JTextField textField_3;
	private JTextField textField_4;
	private JTextField textField_5;*/
	 private Image image;
	@SuppressWarnings("unchecked")
	 
	public ll() {
		 
        //getContentPane().add(new ImagePane());
		
       
         
       /* JPanel contentPane=new JPanel(){
            @Override
            public void paint(Graphics g) {
                ImageIcon icon=new ImageIcon("images\\77.jpg");
         image=icon.getImage();
         g.drawImage(image, 0,0,null);
                // TODO Auto-generated method stub
                 
            }
        };   
       this.add(contentPane,-1);*/
       
        this.setVisible(true);
        setSize(800, 800);
        setVisible(true);
	
	//getContentPane().setBackground(new Color(0, 102, 204));
	//setBackground(new Color(0, 102, 204));
//	setTitle("\u7BA1\u7406\u5458");
	setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	setBounds(100, 100, 660, 397);
	getContentPane().setLayout(null);
	
	JButton button = new JButton("\u66F4\u65B0");
	button.setBounds(58, 293, 81, 23);
	getContentPane().add(button);
	
	JScrollPane scrollPane = new JScrollPane();
	scrollPane.setBounds(42, 155, 121, 117);
	getContentPane().add(scrollPane);
	
	JTextArea textArea = new JTextArea();
	textArea.setText("\u516C\u544A\uFF1A                                                                                                                           ");
	textArea.setToolTipText("");
	textArea.setLineWrap(true);
	scrollPane.setViewportView(textArea);
	
	JScrollPane scrollPane_1 = new JScrollPane();
	scrollPane_1.setBounds(227, 154, 216, 118);
	getContentPane().add(scrollPane_1);
	
	final JTextArea textArea_1 = new JTextArea();
	textArea_1.setLineWrap(true);
	scrollPane_1.setViewportView(textArea_1);
	
	CatServer.textField = new JTextField();
	CatServer.textField.setText("\u7BA1\u7406\u5458");
	CatServer.textField.setBounds(226, 271, 66, 21);
	getContentPane().add(CatServer.textField);
	CatServer.textField.setColumns(10);
	
	CatServer.textField_1 = new JTextField();
	CatServer.textField_1.setBounds(227, 294, 216, 21);
	getContentPane().add(CatServer.textField_1);
	CatServer.textField_1.setColumns(10);
	
	JButton btnNewButton = new JButton("����");
	btnNewButton.addActionListener(new ActionListener() {
		public void actionPerformed(ActionEvent e) {
			String a;
			a=CatServer.textField_1.getText();
			CatServer.textField_1.setText("");
			textArea_1.append(a+"\n");
			
		}
	});
	btnNewButton.setBounds(455, 293, 66, 23);
	getContentPane().add(btnNewButton);
	
	JScrollPane scrollPane_2 = new JScrollPane();
	scrollPane_2.setBounds(42, 10, 401, 139);
	getContentPane().add(scrollPane_2);
	
	CatServer.table = new JTable();
	
	CatServer.table.setModel(new DefaultTableModel(
		new Object[][] {
			{null, null, null, null, null},
			{null, null, null, null, null},
			{null, null, null, null, null},
			{null, null, null, null, null},
			{null, null, null, null, null},
			{null, null, null, null, null},
			{null, null, null, null, null},
			{null, null, null, null, null},
			{null, null, null, null, null},
			{null, null, null, null, null},
			{null, null, null, null, null},
			{null, null, null, null, null},
			{null, null, null, null, null},
			{null, null, null, null, null},
			{null, null, null, null, null},
			{null, null, null, null, null},
		},
		new String[] {
			"\u7528\u6237\u540D", "ip\u5730\u5740", "\u7AEF\u53E3", "\u767B\u5165\u65F6\u95F4", "\u72B6\u6001"
		}
	));
	 CatServer.table.addMouseListener(new MouseAdapter() {
         @Override
         public void mouseClicked(MouseEvent e) {
             int sr;
             if ((sr = CatServer.table.getSelectedRow()) == -1) {
                 return;
             }
             if (e.getButton() == MouseEvent.BUTTON3) {
            	
             }
             if ( e.getClickCount() == 2) {
            	 CatServer.table.getSelectedRow();
             }
             if (e.getButton() == MouseEvent.BUTTON2) {
            	 
             }
         }
     });

	scrollPane_2.setViewportView(CatServer.table);
	
	
	 CatServer.table.addMouseListener(new MouseListener() {
		 public void mouseClicked(MouseEvent e) {
			 if(e.getClickCount()==2) {
				 System.out.println("a");
			 }
		 }

		@Override
		public void mousePressed(MouseEvent e) {
			// TODO Auto-generated method stub
			
		}

		@Override
		public void mouseReleased(MouseEvent e) {
			// TODO Auto-generated method stub
			
		}

		@Override
		public void mouseEntered(MouseEvent e) {
			// TODO Auto-generated method stub
			
		}

		@Override
		public void mouseExited(MouseEvent e) {
			// TODO Auto-generated method stub
			
		}
	 });
	 CatServer.btnNewButton_1 = new JButton("����");
	 CatServer.btnNewButton_1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				 CatServer.isStop=true;
            	 CatServer.stopIndex=CatServer.table.getSelectedRow();
			}
		});
	 CatServer.btnNewButton_1.setBounds(456, 22, 93, 23);
	 getContentPane().add(CatServer.btnNewButton_1);
	 JButton btnNewButton_3 = new JButton("���");
	 
		btnNewButton_3.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				CatServer.isStop=false;
			}
		});
		btnNewButton_3.setBounds(551, 22, 83, 23);
		getContentPane().add(btnNewButton_3);
	
	 CatServer.textField_2 = new JTextField();
	 CatServer.textField_2.setText("\u804A");
	 CatServer.textField_2.setBounds(489, 65, 19, 23);
	getContentPane().add(CatServer.textField_2);
	CatServer.textField_2.setColumns(10);
	
	CatServer.textField_3 = new JTextField();
	CatServer.textField_3.setText("\u5929");
	CatServer.textField_3.setColumns(10);
	CatServer.textField_3.setBounds(489, 106, 19, 23);
	getContentPane().add(CatServer.textField_3);
	
	CatServer.textField_4 = new JTextField();
	CatServer.textField_4.setText("\u8BB0");
	CatServer.textField_4.setColumns(10);
	CatServer.textField_4.setBounds(489, 145, 19, 23);
	getContentPane().add(CatServer.textField_4);
	
	CatServer.textField_5 = new JTextField();
	CatServer.textField_5.setText("\u5F55");
	CatServer.textField_5.setColumns(10);
	CatServer.textField_5.setBounds(489, 189, 19, 23);
	getContentPane().add(CatServer.textField_5);
	
}
}